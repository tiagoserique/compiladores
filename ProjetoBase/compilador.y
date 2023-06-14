
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

TabelaSimbolos *ts, *pilhaAtribuicao;
tipoConteudo conteudo;
Simbolo s;
PilhaInt pilhaRotulos, pilhaAmem, pilhaProcs;

int num_vars;
int num_params;
int nivel_lexico;
int rotulo_atual;
int quantidade_tipo_atual;
int elem_a_esq;

char mepa_comand[128];

int str2type(const char *str){
   if (!strcmp(str, "integer")) return INTEGER;
   if (!strcmp(str, "boolean")) return BOOLEAN;
   return UNDEFINED_TYPE;
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
      }

   //   parte_declara_subrotinas
   //   {
   //   }

      comando_composto

      {
         sprintf(mepa_comand, "DMEM %d", topoPilhaInt(&pilhaAmem));
         removeN(&ts, topoPilhaInt(&pilhaAmem));
         geraCodigo(NULL, mepa_comand);
         popPilhaInt(&pilhaAmem);
      }
;

// regra 08 ====================================================================
parte_declara_vars:
                  { num_vars = 0; } 
                  
                  VAR declara_vars
                  
                  {
                     sprintf(mepa_comand, "AMEM %d", num_vars); 
                     geraCodigo(NULL, mepa_comand);

                     pushPilhaInt(&pilhaAmem, num_vars);
                  }

                  |  { pushPilhaInt(&pilhaAmem, 0); }
;

// regra 09 ====================================================================
declara_vars: declara_vars declara_var
            | declara_var
;

declara_var:
            { quantidade_tipo_atual = 0; }
            
            lista_id_var DOIS_PONTOS tipo
            
            { atribuiTipo(&ts, VARIAVEL, $4, quantidade_tipo_atual); }

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
               s = criaSimbolo(token, VARIAVEL, nivel_lexico, conteudo);
               push(&ts, s);
               num_vars++; quantidade_tipo_atual++;
            }
            
            | IDENT 
            {
               conteudo.var.deslocamento = num_vars;
               s = criaSimbolo(token, VARIAVEL, nivel_lexico, conteudo);
               push(&ts, s);
               num_vars++; quantidade_tipo_atual++;      
            }
;

lista_idents: lista_idents VIRGULA IDENT
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
;

comandos: comandos PONTO_E_VIRGULA comando
         | comando
;

// regra 17 ====================================================================
comando: comando_sem_rotulo
;

// regra 18 ====================================================================
comando_sem_rotulo: 
   atribuicao
   | comando_composto
   // | escrita
   // | leitura
   // | chamada_de_procedimento
   // | comando_condicional
   // | comando_repetitivo
   |
;

// regra 19 ====================================================================
atribuicao: variavel ATRIBUICAO expressao
;

// // TODO: fazer
// chamada_de_procedimento: IDENT lista_expressoes
// ;

// // TODO: fazer
// comando_composto: 
// ;

// // TODO: fazer
// comando_condicional: IF expressao THEN comando_sem_rotulo 
//    ELSE comando_sem_rotulo
// ;

// // TODO: fazer
// comando_repetitivo: WHILE expressao DO comando_sem_rotulo
// ;

// // TODO: fazer
// lista_expressoes: expressao VIRGULA expressao
// ;

// regra 25 ====================================================================
expressao: expressao_simples relacao_e_expressao_ou_nada
;

relacao_e_expressao_ou_nada: relacao expressao_simples
                              |
;

// regra 26 ====================================================================
relacao: IGUAL       { geraCodigo(NULL, "CMIG"); }
      | DIFERENTE    { geraCodigo(NULL, "CMDG"); }
      | MENOR        { geraCodigo(NULL, "CMME"); }
      | MENOR_IGUAL  { geraCodigo(NULL, "CMEG"); }
      | MAIOR        { geraCodigo(NULL, "CMMA"); }
      | MAIOR_IGUAL  { geraCodigo(NULL, "CMAG"); }
;

// regra 27 ====================================================================
expressao_simples: expressao_simples mais_menos_or termo
                  | mais_ou_menos_ou_nada termo 
;

mais_ou_menos_ou_nada: MAIS 
                     | MENOS
                     |
;

mais_menos_or: MAIS { geraCodigo(NULL, "SOMA"); }
            | MENOS { geraCodigo(NULL, "SUBT"); }
            | OR    { geraCodigo(NULL, "DISJ"); }
;

// regra 28 ====================================================================
termo: termo vezes_div_and fator
     | fator
;

vezes_div_and: VEZES { geraCodigo(NULL, "MULT"); } 
               | DIV { geraCodigo(NULL, "DIVI"); } 
               | AND { geraCodigo(NULL, "CONJ"); }
;

// regra 29 ====================================================================
fator: variavel
      | NUMERO 
         { 
            sprintf(mepa_comand, "CRCT %d", atoi(token)); 
            geraCodigo(NULL, mepa_comand);
         }
      | VALOR_BOOL
      | ABRE_PARENTESES expressao FECHA_PARENTESES
      | NOT fator
;

// // TODO: fazer
variavel: IDENT
//    | IDENT lista_expressoes
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

   inicializa(&ts);
   inicializa(&pilhaAtribuicao);
   inicializaPilhaInt(&pilhaRotulos);
   inicializaPilhaInt(&pilhaAmem);
   inicializaPilhaInt(&pilhaProcs);

   yyin=fp;
   yyparse();

   destroiPilhaInt(&pilhaRotulos);
   destroiPilhaInt(&pilhaAmem);
   destroiPilhaInt(&pilhaProcs);

   return 0;
}
