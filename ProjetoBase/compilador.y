
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
Simbolo s;
PilhaInt pilhaRotulos, pilhaAmem, pilhaProcs;
PilhaSimbolos pilhaVarAEsquerda;

int num_vars;
int num_params;
int nivel_lexico;
int rotulo_atual = 0;
int quantidade_tipo_atual;

char mepa_comand[128];

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
%type <int_val> atribuicao
%type <int_val> termo
// %type <int_xval> declara_var

%%

// regra 01 ====================================================================
programa:
         {
            geraCodigo (NULL, "INPP");
            nivel_lexico = 0;
            rotulo_atual = 0;
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
         }

      // parte_declara_subrotinas
         {
            sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos));
            geraCodigo(mepa_comand, "NADA");

            popPilhaInt(&pilhaRotulos);
         }

      comando_composto
         {
            imprimeTabelaSimbolos(&ts);
            sprintf(mepa_comand, "DMEM %d", topoPilhaInt(&pilhaAmem));
            removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaAmem));
            geraCodigo(NULL, mepa_comand);
            popPilhaInt(&pilhaAmem);
         }
;

// regra 08 ====================================================================
parte_declara_vars:
                  { num_vars = 0; } 
                  
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

// tipo: IDENT 
tipo: TIPO { $$ = str2type(token); }
;

// regra 10 ====================================================================
lista_id_var:
            lista_id_var VIRGULA IDENT
            { 
               conteudo.var.deslocamento = num_vars;
               s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
               pushTabelaSimbolos(&ts, s);
               num_vars++; quantidade_tipo_atual++;
            }
            
            | IDENT 
            {
               conteudo.var.deslocamento = num_vars;
               s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
               pushTabelaSimbolos(&ts, s);
               num_vars++; quantidade_tipo_atual++;      
            }
;

lista_idents: 
            lista_idents VIRGULA IDENT
            | IDENT
;

// // TODO: fazer
// parte_declara_subrotinas: declara_procedimento PONTO_E_VIRGULA
//             | declara_funcao PONTO_E_VIRGULA
// ;

// // TODO: fazer
// declara_procedimento: PROCEDURE IDENT 
//    ABRE_PARENTESES parte_param_formais FECHA_PARENTESES 
//    PONTO_E_VIRGULA
//    bloco
// ;

// // TODO: fazer
// declara_funcao: FUNCTION IDENT 
//    ABRE_PARENTESES parte_param_formais FECHA_PARENTESES DOIS_PONTOS IDENT
//    PONTO_E_VIRGULA
//    bloco
// ;

// // TODO: fazer
// parte_param_formais: secao_param_formais PONTO_E_VIRGULA secao_param_formais
// ;

// // TODO: fazer
// secao_param_formais: var lista_id_var DOIS_PONTOS IDENT
//    | FUNCTION lista_id_var DOIS_PONTOS IDENT
//    | PROCEDURE lista_id_var
// ;

// regra 16 ====================================================================
comando_composto: T_BEGIN comandos T_END
// comando_composto: T_BEGIN comandos { imprime(&ts); } T_END
// comando_composto: T_BEGIN comandos { imprimePilhaInt(&pilhaAmem); } T_END
;

comandos: 
         comandos PONTO_E_VIRGULA comando
         | comando
;

// regra 17 ====================================================================
comando: comando_sem_rotulo
;

// regra 18 ====================================================================
comando_sem_rotulo: 
                  atribuicao
                  | comando_composto
                  | leitura
                  | escrita
                  // | chamada_de_procedimento
                  // | comando_condicional
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
atribuicao: 
         variavel ATRIBUICAO expressao
         {

            Simbolo *s = topoPilhaSimbolos(&pilhaVarAEsquerda);

            if ( s->categoria == CAT_VARIAVEL 
               && s->conteudo.var.tipo != $3 ){
               fprintf(stderr, "COMPILATION ERROR!!! Atribuicao de tipos divergentes\n");
               // fprintf(stderr, "Ident: %s\n", s->identificador);
               // fprintf(stderr, "Tipo da variavel: %d\n", s->conteudo.var.tipo);
               // fprintf(stderr, "Tipo da expressao: %d\n", $3);
               // imprimeTabelaSimbolos(&ts);
               exit(1);
            }
   
            sprintf(mepa_comand, "ARMZ %d, %d", s->nivel, s->conteudo.var.deslocamento);
            geraCodigo(NULL, mepa_comand);

            popPilhaSimbolos(&pilhaVarAEsquerda);
         }
;

// regra 20 ====================================================================
// // TODO: fazer
// chamada_de_procedimento: IDENT lista_expressoes
// ;

// regra 21 ====================================================================
// // TODO: fazer
// comando_composto: 
// ;

// regra 22 ====================================================================
// // TODO: fazer
// comando_condicional: IF expressao THEN comando_sem_rotulo 
//    ELSE comando_sem_rotulo
// ;

// regra 23 ====================================================================
// TODO: fazer
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
// // TODO: fazer
// lista_expressoes: expressao VIRGULA expressao
// ;

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
                  MAIS  { $$ = "MAIS"; }
                  | MENOS { $$ = "MENOS"; }
                  |       { $$ = "NADA"; }
;

mais_menos_or: 
            MAIS { $$ = "MAIS";  } 
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
fator: 
      variavel
         {
            Simbolo *s = topoPilhaSimbolos(&pilhaVarAEsquerda);

            sprintf(mepa_comand, "CRVL %d, %d", s->nivel, s->conteudo.var.deslocamento);
            geraCodigo(NULL, mepa_comand);

            popPilhaSimbolos(&pilhaVarAEsquerda);
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
variavel: 
         IDENT
         {
            Simbolo *s = buscaTabelaSimbolos(&ts, token);

            if ( s == NULL ){
               fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
               exit(1);
            }

            pushPilhaSimbolos(&pilhaVarAEsquerda, s);
         }
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




