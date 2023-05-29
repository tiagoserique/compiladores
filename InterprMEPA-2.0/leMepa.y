/* -------------------------------------------------------------------
 *            Arquivo: leMepa.y
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 11/2015
 *      Atualizado em: [20/09/2020, 08h:10m]
 *
 * -------------------------------------------------------------------
 *   Analisador sintático do arquivo indicado
 *   A regra básica é: 
 *   [RXX[:]] XXXX [P1 [P2 [P3]]] 
 * ------------------------------------------------------------------- */

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "executaMepa.h"

#include "leMepa.h"


char rotInstr[TAM_TOKEN];
char rotulo[TAM_TOKEN];
int  p1_int;
int  p2_int;
int  p3_int;
char p1_rot[TAM_TOKEN];
int  inteiro;
instrucao_mepa instr;

  int yylex();
  void yyerror(char *s);
%}

// símbolos 
%token DOIS_PONTOS ROTULO INTEIRO VIRGULA
// instruções com nenhum parâmetro
%token INPP PARA SOMA SUBT MULT DIVI INVR CONJ DISJ NEGA 
%token CMME CMMA CMIG CMDG CMEG CMAG NADA LEIT IMPR 
// instruções com um parâmetro
%token CRCT AMEM DMEM ENPR ENRT DSVS DSVF 
// instruções com dois parâmetros
%token CRVL ARMZ CRVI ARMI CREN CHPR RTPR DSVR

%%
 // REGRAS --------------------------------

linhas: linhas linha
      | linha
;

linha: rot comando 
;

// A regra abaixo coloca na variável global "rotInstr" o string
// correspondente ao rótulo-alvo (o que fica à esquerda do comando)
rot : ROTULO { strcpy(rotInstr,rotulo); } DOIS_PONTOS 
    | %empty { strcpy(rotInstr,""); }
;

// Para não exigir a presença da vírgula
virgula : VIRGULA 
        | %empty
;

comando :
// Comandos sem parametros
  cmd_sem_param
               {insereInstr_MV_mepa(rotInstr,instr, 0,0,0,0,"");}; 
// Comandos com um parametro inteiro 
| cmd_um_param_int param1_int
               {insereInstr_MV_mepa(rotInstr,instr,p1_int,0,0,0,"");};
// Comandos com um parametro que é um rotulo 
| cmd_um_param_rot param1_rot
               {insereInstr_MV_mepa(rotInstr,instr,0,0,0,0,p1_rot);};
// Comandos com dois parametros inteiros 
| cmd_dois_param_int param1_int virgula param2_int
               {insereInstr_MV_mepa(rotInstr,instr,p1_int,p2_int,0,0,"");}
// Comandos com parametros fora dos padroes acima
| CHPR param1_rot virgula param2_int
               {insereInstr_MV_mepa(rotInstr,instr,0,p2_int,0,0,p1_rot);}
| DSVR param1_rot virgula param2_int virgula param3_int
               {insereInstr_MV_mepa(rotInstr,instr,0,p2_int,p3_int,0,p1_rot);}

cmd_sem_param: 
  INPP | PARA | SOMA | SUBT | MULT | DIVI | INVR | CONJ | DISJ |
  NEGA | CMME | CMMA | CMIG | CMDG | CMEG | CMAG | NADA | LEIT |
  IMPR
;

cmd_um_param_int:
  CRCT | AMEM | DMEM | ENPR 
; 

cmd_um_param_rot:
  DSVS | DSVF
;

cmd_dois_param_int:
   CRVL | ARMZ | CRVI | ARMI | CREN | ENRT | RTPR
;


// Parametros
param1_int: INTEIRO { p1_int = inteiro;};
param2_int: INTEIRO { p2_int = inteiro;};
param3_int: INTEIRO { p3_int = inteiro;};
param1_rot: ROTULO {strncpy(p1_rot, rotulo, TAM_TOKEN);};

%%

/* -------------------------------------------------------------------
 *  le programa indicado em plc->fp o coloca no vetor de instruções da
 *  máquina virtual mepa (variável global "mv_mepa_I" *
 * ------------------------------------------------------------------- */
void leComandosMepa(params_linha_comando *plc) {
  extern FILE* yyin;
  
  yyin = plc->fp_in;
  yyparse();
}

/* -------------------------------------------------------------------
 *  Programa Principal
 * ------------------------------------------------------------------- */
int main (int argc, char** argv) {
  int i;
  params_linha_comando *plc;

  // ----------------
  plc = le_params_linha_comando(argc, argv);
  imprime_params_linha_comando (plc);
  
  // ----------------
  inicia_MV_mepa ();


  // le programa indicado e o coloca na mv_mepa
  leComandosMepa(plc);
  relocaDesvios_MV_mepa();
  
  executaMepa(plc);
 }
