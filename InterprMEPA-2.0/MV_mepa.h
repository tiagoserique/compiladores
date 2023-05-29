


/* -------------------------------------------------------------------
 *            Arquivo: MV_mepa.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 09/2020
 *      Atualizado em: [20/09/2020, 09h:46m]
 *
 * -------------------------------------------------------------------
 * A MEPA é uma máquina virtual contendo 5 estruturas: M, D, I, i, s.
 * Este arquivo contém as estruturas, variáveis globais e procedimentos
 * para acesso as cinco estruturas da máquina virtual.
 * ------------------------------------------------------------------- */

#ifndef MEPA_H
#define MEPA_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


// ------------------------------------------------------------------------
// Declaração de Constantes
// ------------------------------------------------------------------------

#define TAM_M  4096     // Tamanho do Vetor Pilha da MV_mepa
#define TAM_RB 16       // Tamanho do Vetor Reg. Base da MV_mepa
#define TAM_I  4096     // Tamanho do Vetor Instruções da MV_mepa

typedef enum instrucao_mepa { 
  amem,   armi,   armz,   chpr,   cmag,   cmdg,   cmeg,   cmig,   cmma,
  cmme,   conj,   crct,   cren,   crvi,   crvl,   disj,   divi,   dmem,
  dsvf,   dsvr,   dsvs,   enpr,   enrt,   impr,   inpp,  invr,   leit,
  mult,   nada,   nega,   para,   rtpr,   soma,   subt
} instrucao_mepa;

// ------------------------------------------------------------------------
// Estrutura contida no vetor de instrucoes.
// ------------------------------------------------------------------------
typedef struct instStruct {
  instrucao_mepa instr;   // código de operação
  int op1;          // operando 1 
  int op2;          // operando 2
  int op3;          // operando 3
  int endDesvio;    // indice do desvio no vetor de instrucoes
  // --------- rotulo e rotDdesvio sao copias do arquivo de entrada
  char rotulo[10];  // rotulo associado a esta linha (se não houver, NULL)
  char rotDdesvio[10]; // o rotulo para onde desviar por exemplo dsvs (ou NULL)
} instStruct;


typedef struct MV_mepa {
  int vetorPilha[TAM_M];
  int vetorRegBase[TAM_RB];
  instStruct vetorInstr[TAM_I];
  int tam_i;
  int i;
  int s;
} MV_mepa;

// ------------------------------------------------------------------------
// Declaração de Variáveis Globais
// ------------------------------------------------------------------------
extern MV_mepa mv_mepa;


// ------------------------------------------------------------------------
// Declaração de Sinônimos
// ------------------------------------------------------------------------
#define mv_mepa_M      mv_mepa.vetorPilha
#define mv_mepa_D      mv_mepa.vetorRegBase
#define mv_mepa_I      mv_mepa.vetorInstr
#define mv_mepa_i      mv_mepa.i
#define mv_mepa_s      mv_mepa.s
#define mv_mepa_tam_i  mv_mepa.tam_i
#define mv_instr_atual mv_mepa_I[mv_mepa_i].instr
#define mv_instr_op1   mv_mepa_I[mv_mepa_i].op1
#define mv_instr_op2   mv_mepa_I[mv_mepa_i].op2
#define mv_instr_op3   mv_mepa_I[mv_mepa_i].op3
#define mv_instr_opR   mv_mepa_I[mv_mepa_i].endDesvio


// ------------------------------------------------------------------------
// Procedimentos
// ------------------------------------------------------------------------


void inicia_MV_mepa ();
void insereInstr_MV_mepa (char* rotulo, instrucao_mepa instr,
                          int op1, int op2, int op3, int op4,
                          char* rotDdesvio);

void relocaDesvios_MV_mepa();


// ------------------------------------------------------------------------
// Executa a instrução indicada pelo registrador "i" e retorna  o
// código de instrução executada.
// ------------------------------------------------------------------------

instrucao_mepa executa_instr_MV_mepa();


#endif



