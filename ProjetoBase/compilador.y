
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tabelaSimbolos/tabelaSimbolos.h"
#include "tabelaSimbolos/simbolo.h"
#include "pilha/pilhaInt.h"
#include "pilha/pilhaSimbolos.h"


TabelaSimbolos *ts, *pilhaAtribuicao;
tipoConteudo conteudo;
Simbolo *s_ptr, *s_var_ou_proc, proc_atual, *s_atribuicao;
PilhaInt pilhaRotulos, pilhaAmem, pilhaProcs;
PilhaSimbolos pilhaVarAEsquerda;

int num_vars;
int num_params;
int num_params_section;
int num_procedimentos_proc_atual;
int num_param_chamada_atual;
int nivel_lexico;
int rotulo_atual;
int quantidade_tipo_atual;
int dentro_chamada_procedimento; // conta chamadas encadeadas de procedimentos

int flag_referencia; // pra passagem por referencia ou nao
int flag_atribui;

char mepa_comand[128];
char proc_nome[128];

parametro lista_parametros[128];
Simbolo lista_simbolos[128];
char idents[128][128];

int str2type(const char *str){
   if (!strcmp(str, "integer")) return TIPO_INTEGER;
   if (!strcmp(str, "boolean")) return TIPO_BOOLEAN;
   return TIPO_UNDEFINED_TYPE;
}

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token TIPO
%token PROCEDURE FUNCTION
%token IGUAL MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL DIFERENTE
%token AND OR NOT DIV VEZES MENOS MAIS
%token IF THEN ELSE
%token WHILE DO
%token READ WRITE
%token NUMERO VALOR_BOOL
%token LABEL
%token TYPE
%token ARRAY
%token OF GOTO
%token ABRE_COLCHETES FECHA_COLCHETES 
%token ABRE_CHAVES FECHA_CHAVES

%union {
   char *str;
   int int_val;
}

%type <str> relacao
%type <str> mais_menos_or
%type <str> mais_menos_ou_nada
%type <str> vezes_div_and
%type <int_val> expressao
%type <int_val> expressao_simples
%type <int_val> fator
%type <int_val> tipo 
%type <int_val> termo

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

// regra 01 ====================================================================
programa:
   {
      geraCodigo (NULL, "INPP");
      nivel_lexico = 0;
      rotulo_atual = 0;
      dentro_chamada_procedimento = 0;
   }
   
   PROGRAM IDENT
   ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
   bloco PONTO 

   {
      geraCodigo (NULL, "PARA");
   }
;

// regra 02 ====================================================================
bloco:
   parte_declara_vars
      {
         pushPilhaInt(&pilhaRotulos, rotulo_atual);

         sprintf(mepa_comand, "DSVS R%02d", rotulo_atual);
         geraCodigo(NULL, mepa_comand);
         rotulo_atual++;

         nivel_lexico++;
         num_procedimentos_proc_atual = 0;
      }

   parte_declara_subrotinas
      {
         pushPilhaInt(&pilhaProcs, num_procedimentos_proc_atual);

         nivel_lexico--;

         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(mepa_comand, "NADA");

         popPilhaInt(&pilhaRotulos);
      }

   comando_composto
      {
         sprintf(mepa_comand, "DMEM %d", topoPilhaInt(&pilhaAmem));
         removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaAmem));
         geraCodigo(NULL, mepa_comand);
         popPilhaInt(&pilhaAmem);
      }
;

// regra 08 ====================================================================
parte_declara_vars:
   { 
      num_vars = 0; 
   } 
   
   VAR declara_vars
   
   {
      pushPilhaInt(&pilhaAmem, num_vars);
   }

   |  { pushPilhaInt(&pilhaAmem, 0); }
;

// regra 09 ====================================================================
declara_vars: 
   declara_vars declara_var
   | declara_var
;

declara_var:
   { quantidade_tipo_atual = 0; }
   
   lista_id_var DOIS_PONTOS tipo
   
   { 
      if ( $4 == TIPO_UNDEFINED_TYPE ){
         fprintf(stderr, "COMPILATION ERROR!!! Tipo indefinido\n");
         exit(1);
      }

      sprintf(mepa_comand, "AMEM %d", quantidade_tipo_atual); 
      geraCodigo(NULL, mepa_comand);

      atribuiTipoTabelaSimbolos(&ts, CAT_VARIAVEL, $4, quantidade_tipo_atual); 
   }

   PONTO_E_VIRGULA
;

tipo: 
   TIPO { $$ = str2type(token); }
;

// regra 10 ====================================================================
lista_id_var:
   lista_id_var VIRGULA IDENT
   { 
      conteudo.var.deslocamento = num_vars;
      Simbolo s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      num_vars++; quantidade_tipo_atual++;
   }
   
   | IDENT 
   {
      conteudo.var.deslocamento = num_vars;
      Simbolo s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      num_vars++; quantidade_tipo_atual++;      
   }
;

lista_idents: 
   lista_idents VIRGULA ident_params
   | ident_params
;

ident_params: 
   IDENT
   {
      strcpy(idents[num_params], token);
      lista_parametros[num_params].passagem = flag_referencia? PAS_REFERENCIA : PAS_COPIA;
      num_params++;
      num_params_section++;
   }
;

// regra 11 ====================================================================
parte_declara_subrotinas: 
   parte_declara_subrotinas 
   declara_procedimento { num_procedimentos_proc_atual++; }
   // | declara_funcao
   |
;

// regra 12 ====================================================================
declara_procedimento: 
   PROCEDURE IDENT 
   {
      strcpy(proc_nome, token);

      num_params = 0;
   }

   param_formais_ou_nada
   {
      tipoConteudo conteudo;

      conteudo.proc.rotulo = rotulo_atual;

      char rotulo[128];

      sprintf(rotulo, "R%02d", rotulo_atual);
      sprintf(mepa_comand, "ENPR %d", nivel_lexico);
      geraCodigo(rotulo, mepa_comand);

      conteudo.proc.tipoRetorno = TIPO_UNDEFINED_TYPE;
      conteudo.proc.qtdParametros = num_params;

      // copia lista de paramtros para a tabela de simbolos 
      memcpy(conteudo.proc.lista, lista_parametros, sizeof(parametro) * num_params);

      Simbolo s = criaSimbolo(proc_nome, CAT_PROCEDIMENTO, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      
      // coloca params com deslocamento correto na tabela de simbolos
      for (int i = num_params-1; i >= 0; --i){
         lista_simbolos[i].conteudo.param.deslocamento = -4 + (i - (num_params - 1));
         pushTabelaSimbolos(&ts, lista_simbolos[i]);
      }

      rotulo_atual++;
      
      pushPilhaInt(&pilhaAmem, num_params);
   }

   PONTO_E_VIRGULA bloco
   {
      removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaAmem));
      sprintf(mepa_comand, "RTPR %d, %d", nivel_lexico, topoPilhaInt(&pilhaAmem));
      geraCodigo(NULL, mepa_comand);

      popPilhaInt(&pilhaAmem);
      removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaProcs));
      popPilhaInt(&pilhaProcs);
   }

   PONTO_E_VIRGULA
;


// regra 13 ====================================================================
// // TODO: fazer
// declara_funcao: FUNCTION IDENT 
//    ABRE_PARENTESES parte_param_formais FECHA_PARENTESES DOIS_PONTOS IDENT
//    PONTO_E_VIRGULA
//    bloco
// ;

// regra 14 ====================================================================
param_formais_ou_nada: 
   parte_param_formais 
   |
;

parte_param_formais: 
   ABRE_PARENTESES parametros FECHA_PARENTESES
;

parametros: 
   secao_param_formais PONTO_E_VIRGULA secao_param_formais
   | secao_param_formais
;

// regra 15 ====================================================================
var_ou_nada: 
   VAR 
      {
         flag_referencia = 1;
      }
   |  
      { 
         flag_referencia = 0;
      }
;

secao_param_formais: 
   var_ou_nada 
      { 
         num_params_section = 0; 
      } 
   lista_idents DOIS_PONTOS tipo
      {
         for (int i = num_params - num_params_section; i < num_params; ++i){
            tipoConteudo conteudo;
            conteudo.param = lista_parametros[i];
            conteudo.param.tipo = $5;
            lista_simbolos[i] = criaSimbolo(idents[i], CAT_PARAMETRO, nivel_lexico, conteudo);
         }

         // atribuiTipoTabelaSimbolos(&ts, CAT_PARAMETRO, $4, num_params_section);
      }
;

// regra 16 ====================================================================
comando_composto: T_BEGIN comandos T_END
;

comandos: 
   comandos 
      { 
         if ( strcmp(token,";") ){ 
            fprintf(stderr, "COMPILATION ERROR!!! Falta de ; apos comando\n");
            exit(1);
         }
      } 
   PONTO_E_VIRGULA comando 
   | comando 
;

// regra 17 ====================================================================
comando: comando_sem_rotulo
   // {
   //    sprintf(mepa_comand, "ENRT %d, %d", nivel_lexico, num_param_chamada_atual);
   //    geraCodigo(NULL, mepa_comand);
   // }
;

// regra 18 ====================================================================
comando_sem_rotulo: 
   atribuicao_ou_procedimento
   | comando_composto
   | leitura
   | escrita
   | comando_condicional
   | comando_repetitivo
   |
;

leitura: READ ABRE_PARENTESES leitura_itens FECHA_PARENTESES

leitura_itens: 
   leitura_itens VIRGULA item_leitura
   | item_leitura

item_leitura: 
   IDENT 
   {
      geraCodigo(NULL, "LEIT");
      Simbolo *s = buscaTabelaSimbolos(&ts, token);
      if ( s == NULL || s->categoria == CAT_PROCEDIMENTO ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
         exit(1);
      }

      sprintf(mepa_comand, "ARMZ %d, %d", s->nivel, s->conteudo.var.deslocamento);
      geraCodigo(NULL, mepa_comand);
   }
;

escrita: WRITE ABRE_PARENTESES escrita_itens FECHA_PARENTESES
;

escrita_itens: 
   escrita_itens VIRGULA item_escrita
   | item_escrita
;

item_escrita:  
   expressao
   {
      geraCodigo(NULL, "IMPR");
   }
;

// regra 19 ====================================================================
atribuicao_ou_procedimento: 
   IDENT
   {
      s_var_ou_proc = buscaTabelaSimbolos(&ts, token);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada %s\n", token);
         exit(1);
      }

      pushPilhaSimbolos(&pilhaVarAEsquerda, s_var_ou_proc);
   } 
   atribuicao_continua 
   {
      popPilhaSimbolos(&pilhaVarAEsquerda);
   }
;

atribuicao_continua: 
   ATRIBUICAO 
      { 
         flag_atribui = 1; 
      } 
   expressao 
      {
         flag_atribui = 0;

         s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

        switch (s_var_ou_proc->categoria){
            case CAT_VARIAVEL:
                sprintf(mepa_comand, "ARMZ %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
            break;
            
            case CAT_PARAMETRO:
                if (s_var_ou_proc->conteudo.param.passagem == PAS_COPIA){
                    sprintf(mepa_comand, "ARMZ %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
                }
                else if (s_var_ou_proc->conteudo.param.passagem == PAS_REFERENCIA){
                    sprintf(mepa_comand, "ARMI %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
                }
                else {
                    fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametror nao especificada\n");
                    exit(1);
                }
            break;

            // case CAT_FUNCAO:
            // break;

            default:
                fprintf(stderr, "COMPILATION ERROR!!! procedimento tratado como variavel\n");
                exit(1);
            break;
        }

         geraCodigo(NULL, mepa_comand);
      }
   | chamada_de_procedimento
   | procedimento_sem_parametros
;

// regra 20 ====================================================================
chamada_de_procedimento:  
   {
      Simbolo *s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
         exit(1);
      }

      s_atribuicao = s_var_ou_proc;
      memcpy(&proc_atual, s_var_ou_proc, sizeof(Simbolo));

      if (proc_atual.categoria == CAT_FUNCAO){
         geraCodigo(NULL, "AMEM 1");
      }

      sprintf(proc_nome, "CHPR R%02d", s_var_ou_proc->conteudo.proc.rotulo);
   }

   ABRE_PARENTESES 
   {
      num_param_chamada_atual = 0;
      dentro_chamada_procedimento++;
   }

   lista_expressoes FECHA_PARENTESES
   {
      dentro_chamada_procedimento--;

      if (num_param_chamada_atual != proc_atual.conteudo.proc.qtdParametros){
         fprintf(stderr, "COMPILATION ERROR!!! numero de parametros divergentes\n");
         exit(1);
      }

      geraCodigo(NULL, proc_nome);
   }
;

procedimento_sem_parametros: 
   {
      Simbolo *s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
         exit(1);
      }

      if ( s_var_ou_proc->categoria != CAT_PROCEDIMENTO ){
         fprintf(stderr, "COMPILATION ERROR!!! %s nao eh um procedimento\n", token);
         exit(1);
      }

      sprintf(mepa_comand, "CHPR R%02d", s_var_ou_proc->conteudo.proc.rotulo);
      geraCodigo(NULL, mepa_comand);
   }
;

                         

// regra 21 ====================================================================
// // TODO: fazer
// comando_goto:
//    {

//       sprintf(mepa_comand, "DSVS R%02d", conteudo.proc.rotulo,  nivel_lexico_proc??? , nivel_lexico);
//       geraCodigo(NULL, ,mepa_comand);
//    }
   
// ;

// regra 22 ====================================================================
comando_condicional: if_then cond_else 
   {
      popPilhaInt(&pilhaRotulos);
      rotulo_atual -= 2;
   }
;

if_then: 
   IF expressao 
      {
         sprintf(mepa_comand, "DSVF R%02d", rotulo_atual);
         geraCodigo(NULL, mepa_comand);

         pushPilhaInt(&pilhaRotulos, rotulo_atual);
         rotulo_atual += 2;
      }

   THEN comando_sem_rotulo
      {
         sprintf(mepa_comand, "DSVS R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(NULL, mepa_comand);
      }
;

cond_else: 
   ELSE 
      {
         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(mepa_comand, "NADA");
      } 
   
   comando_sem_rotulo
      {
      sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos) + 1);
      geraCodigo(mepa_comand, "NADA");
   }

   | %prec LOWER_THAN_ELSE
;

// regra 23 ====================================================================
comando_repetitivo: 
   WHILE 
      {
         pushPilhaInt(&pilhaRotulos, rotulo_atual);

         sprintf(mepa_comand, "R%02d", rotulo_atual);
         geraCodigo(mepa_comand, "NADA");

         rotulo_atual += 2;
      }
   expressao 
      {
         sprintf(mepa_comand, "DSVF R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(NULL, mepa_comand);
      }                  
   
   DO comando_sem_rotulo
      {
         sprintf(mepa_comand, "DSVS R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(NULL, mepa_comand);

         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(mepa_comand, "NADA");

         popPilhaInt(&pilhaRotulos);

         rotulo_atual -= 2;
      }
;

// regra 24 ====================================================================
lista_expressoes: 
   expressao 
   {
      num_param_chamada_atual++;
   }

   VIRGULA lista_expressoes 
   | expressao
   {
      num_param_chamada_atual++;
   }
;

// regra 25 ====================================================================
expressao: 
expressao_simples { $$ = $1; }
| expressao_simples relacao expressao_simples 
   { 
      if ( $1 != $3 ){
         fprintf(stderr, "COMPILATION ERROR!!! Comparacao de tipos divergentes\n");
         exit(1);
      }

      geraCodigo(NULL, $2);
      $$ = TIPO_BOOLEAN;
   }
;

// regra 26 ====================================================================
relacao: 
   IGUAL          { $$ = "CMIG"; }
   | DIFERENTE    { $$ = "CMDG"; }
   | MENOR        { $$ = "CMME"; }
   | MENOR_IGUAL  { $$ = "CMEG"; }
   | MAIOR        { $$ = "CMMA"; }
   | MAIOR_IGUAL  { $$ = "CMAG"; }
;

// regra 27 ====================================================================
expressao_simples: 
   expressao_simples mais_menos_or termo
   {
      if ( !strcmp("MAIS", $2) && $3 == TIPO_INTEGER ){
         geraCodigo(NULL, "SOMA");
         $$ = TIPO_INTEGER;
      }
      else if ( !strcmp("MENOS", $2) && $3 == TIPO_INTEGER ){
         geraCodigo(NULL, "SUBT");
         $$ = TIPO_INTEGER;
      }
      else if ( !strcmp("OR", $2) && $3 == TIPO_BOOLEAN ){
         geraCodigo(NULL, "DISJ");
         $$ = TIPO_BOOLEAN;
      }
   }
   
   | mais_menos_ou_nada termo 
   {
      if ( !strcmp("NADA", $1) ){ 
         $$ = $2; 
      }
      else if ( $2 == TIPO_INTEGER ){
         if ( !strcmp("MENOS", $1) ){ 
            geraCodigo(NULL, "INVR");
         }

         $$ = TIPO_INTEGER;
      }
      else {
         fprintf(stderr, "COMPILATION ERROR!!!"
            " Operadores aritmeticos aplicados a tipo booleano\n");
         exit(1);
      }
   }
;

mais_menos_ou_nada: 
   MAIS    { $$ = "MAIS";  }
   | MENOS { $$ = "MENOS"; }
   |       { $$ = "NADA";  }
;

mais_menos_or: 
   MAIS    { $$ = "MAIS";  } 
   | MENOS { $$ = "MENOS"; } 
   | OR    { $$ = "OR";    } 
;

// regra 28 ====================================================================
termo: 
   termo vezes_div_and fator 
   {
      if ( TIPO_BOOLEAN == $3 ){
         if ( !strcmp("CONJ", $2) ){
            geraCodigo(NULL, "CONJ");
         }
         else {
            fprintf(stderr, "COMPILATION ERROR!!!"
               " Operacao invalida para tipo booleano\n");
         }
      }
      else if ( TIPO_INTEGER == $3 ){
         if ( !strcmp("MULT", $2) ){
            geraCodigo(NULL, "MULT");
         }
         else if ( !strcmp("DIVI", $2) ){
            geraCodigo(NULL, "DIVI");
         }
         else {
            fprintf(stderr, "COMPILATION ERROR!!!"
               " Operacao invalida para tipo integer\n");

         }
      }

      $$ = $3;
   }
   | fator { $$ = $1; }
;

vezes_div_and: 
   VEZES { $$ = "MULT"; } 
   | DIV { $$ = "DIVI"; } 
   | AND { $$ = "CONJ"; }
;

// regra 29 ====================================================================

procedimento_ou_nada :
   chamada_de_procedimento
      {
                     // run ../arquivos-aula/aula11.pas
         s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

         if ( s_var_ou_proc == NULL ){
            fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
            exit(1);
         }

         popPilhaSimbolos(&pilhaVarAEsquerda);
      }
   | 
      {
         s_ptr = topoPilhaSimbolos(&pilhaVarAEsquerda);
         popPilhaSimbolos(&pilhaVarAEsquerda);
      }
;

fator: 
      IDENT
         {
            s_ptr = buscaTabelaSimbolos(&ts, token);

            if ( s_ptr == NULL ){
               fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
               exit(1);
            }

            pushPilhaSimbolos(&pilhaVarAEsquerda, s_ptr);
         }
      procedimento_ou_nada
         {
            if ( s_ptr == NULL ){
               fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
               exit(1);
            }

            int flag_imprime = 1;

            switch (s_ptr->categoria){
               case CAT_VARIAVEL:
                  $$ = s_ptr->conteudo.var.tipo;

                  if (dentro_chamada_procedimento){

                     int qtdParametros = s_var_ou_proc->conteudo.proc.qtdParametros;

                     if (num_param_chamada_atual > qtdParametros){
                        fprintf(stderr, "COMPILATION ERROR!!! excesso de parametros em funcao\n");
                        exit(1);
                     }

                     if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_REFERENCIA)
                        sprintf(mepa_comand, "CREN %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);

                     else if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_COPIA)
                        sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);

                     else {
                        fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametro nao identificada\n");
                        exit(1);
                     }
                  }
                  else if ( s_var_ou_proc != NULL && s_var_ou_proc->categoria != CAT_FUNCAO)
                     sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);
                 
                  else if (flag_atribui && (s_var_ou_proc != NULL && s_var_ou_proc->categoria == CAT_FUNCAO) && s_atribuicao->categoria != CAT_FUNCAO)
                     sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);
                 
                  else {
                     flag_imprime = 0;
                  }

                  break;

               case CAT_PARAMETRO:
                  $$ = s_ptr->conteudo.param.tipo;

                  switch (s_ptr->conteudo.param.passagem){
                     case PAS_COPIA:
                        sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        break;

                     case PAS_REFERENCIA:

                        if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_REFERENCIA){
                           sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        }
                        else {
                           sprintf(mepa_comand, "CRVI %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        }
                        break;

                     default:
                        fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametro nao identificada\n");
                        exit(1);
                        break;
                  }
                  break;

               case CAT_PROCEDIMENTO:
                  fprintf(stderr, "COMPILATION ERROR!!! procedimento tratado como variavel\n");
                  break;

               default:
                  flag_imprime = 0;
                  break;
            }
            
            if ( flag_imprime ){
               geraCodigo(NULL, mepa_comand);
            }
         }
      | NUMERO 
         { 
            $$ = TIPO_INTEGER;
            sprintf(mepa_comand, "CRCT %d", atoi(token)); 
            geraCodigo(NULL, mepa_comand);
         }
      | VALOR_BOOL 
         { 
            $$ = TIPO_BOOLEAN; 
            sprintf(mepa_comand, "CRCT %d", !strcmp(token, "True") ? 1 : 0);
            geraCodigo(NULL, mepa_comand);
         }
      | ABRE_PARENTESES expressao FECHA_PARENTESES { $$ = $2; }
      | NOT fator
         {
            if ( $2 != TIPO_BOOLEAN ){
               fprintf(stderr, "COMPILATION ERROR!!!"
                  " Operador NOT aplicado a tipo nao booleano\n");
               exit(1);
            }

            $$ = TIPO_BOOLEAN;
            geraCodigo(NULL, "NEGA");
         }
      // | chamada_de_funcao
;

// regra 30 ====================================================================
// variavel: 
//          IDENT
//          {
//             Simbolo *s = buscaTabelaSimbolos(&ts, token);

//             if ( s == NULL ){
//                fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada %s\n", token);
//                exit(1);
//             }

//             pushPilhaSimbolos(&pilhaVarAEsquerda, s);
//          }
;


// chamada_de_funcao: IDENT ABRE_PARENTESES lista_expressoes FECHA_PARENTESES
// ;


%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   inicializaTabelaSimbolos(&ts);
   inicializaTabelaSimbolos(&pilhaAtribuicao);
   inicializaPilhaInt(&pilhaRotulos);
   inicializaPilhaInt(&pilhaAmem);
   inicializaPilhaInt(&pilhaProcs);
   inicializaPilhaSimbolos(&pilhaVarAEsquerda);

   yyin=fp;
   yyparse();

   destroiPilhaInt(&pilhaRotulos);
   destroiPilhaInt(&pilhaAmem);
   destroiPilhaInt(&pilhaProcs);
   destroiPilhaSimbolos(&pilhaVarAEsquerda);

   return 0;
}


// gere a regra sintatica para o comando de atribuicao




