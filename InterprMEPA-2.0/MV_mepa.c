

/* -------------------------------------------------------------------
 *            Arquivo: MV_mepa.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 09/2020
 *      Atualizado em: [27/09/2020, 17h:49m]
 *
 * -------------------------------------------------------------------
 * Implementacoes dos procedimentos
 * para acesso as cinco estruturas da maquina virtual.
 * ------------------------------------------------------------------- */
#include "MV_mepa.h"
#include "interface_usuario.h"

MV_mepa mv_mepa;

void inicia_MV_mepa () {
  mv_mepa_tam_i = 0;
  mv_mepa_i = 0;
  iniciaInterfaceUsuario();
} 
 

/* -------------------------------------------------------------------
 *
 * ------------------------------------------------------------------- */

void insereInstr_MV_mepa (char* rotulo, instrucao_mepa instr,
                          int op1, int op2, int op3, int op4,
                          char* rotDdesvio) {
  instStruct* VI=&mv_mepa_I[mv_mepa_tam_i];

  strcpy(VI->rotulo,rotulo);
  strcpy(VI->rotDdesvio,rotDdesvio);
  VI->endDesvio = -1;
  
  VI->instr = instr;
  VI->op1 = op1;
  VI->op2 = op2;
  VI->op3 = op3;
  mv_mepa_tam_i = mv_mepa_tam_i+1;
}




/* -------------------------------------------------------------------
 *    relocacao dos enderecos de desvio
 * ------------------------------------------------------------------- */

typedef struct reloc{
  char* rotulo;
  int indice;
} reloc;

reloc tabReloc[1024];

void  relocaDesvios_MV_mepa(){
  int i, k, j, max_tab_reloc;

  // ------------------------------------------------------------------------------
  // obtem os enderecos dos rotulos  (nao testa duplicados)
  j=0;
  for (i=0; i<mv_mepa_tam_i; i++) {
    if (strlen(mv_mepa_I[i].rotulo) != 0) {
      tabReloc[j].rotulo=mv_mepa_I[i].rotulo;
      tabReloc[j].indice=i;
      j++;
    }
  }
  max_tab_reloc=j;
  // ------------------------------------------------------------------------------
  // coloca os enderecos-alvo dos desvios em endDesvio
  for (i=0; i<mv_mepa_tam_i; i++) {  // para cada instrução do Vetor de Instrucoes,
    if (strlen(mv_mepa_I[i].rotDdesvio) != 0) { // esta instr tem rotulo de desvio?
      for (j=0; j<max_tab_reloc; j++) { // procura pelo rotulo na tabela de desvios 
        if (strcmp (mv_mepa_I[i].rotDdesvio, tabReloc[j].rotulo)==0) {
          mv_mepa_I[i].endDesvio = tabReloc[j].indice; // achou: coloca end.
        }
      }
    }
  }
}








/* -------------------------------------------------------------------
 *    Executa uma instrucao
 * ------------------------------------------------------------------- */


instrucao_mepa _executa_instr_MV_mepa( int* i, int* s,
                              instStruct *I, int *D, int *M) {
  instrucao_mepa instr_exec = I[*i].instr;

  int k = mv_instr_op1;
  int m = mv_instr_op1;
  int n = mv_instr_op2;
  int j = mv_instr_op2;
  int p = mv_instr_opR;

  
  switch (instr_exec) {

//----------------* AMEM k
  case amem:
    *s = *s + k;
    *i = *i + 1;
    break;
    
//---------------- ARMI m,n
  case armi:
    M[M[D[m]+n]] = M[*s];
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* ARMZ m,n
  case armz:
    M[D[m]+n] = M[*s];
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CHPR p,n
  case chpr:
    M[*s+1] = *i+1;  
    M[*s+2] = n;  
    *s = *s + 2;
    *i = p;
    break;
//---------------- CMAG
  case cmag:
    M[*s-1] = (M[*s-1] >= M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CMDG
  case cmdg:
    M[*s-1] = (M[*s-1] != M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CMEG
  case cmeg:
    M[*s-1] = (M[*s-1] <= M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CMIG
  case cmig:
    M[*s-1] = (M[*s-1] == M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CMMA
  case cmma:
    M[*s-1] = (M[*s-1] > M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------- CMME
  case cmme:
    M[*s-1] = (M[*s-1] < M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* CONJ
  case conj:
    M[*s-1] = (M[*s-1] & M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* CRCT k
  case crct:
    *s = *s + 1;
    M[*s] = k;     
    *i = *i + 1;
    break;
//---------------- CREN m,n
  case cren:
    *s = *s + 1;
    M[*s] = D[m]+n;   
    *i = *i + 1;
    break;
//---------------- CRVI m,n
  case crvi:
    *s = *s + 1;
    M[*s] = M[M[D[m]+n]];
    *i = *i + 1;
    break;
//----------------* CRVL m,n
  case crvl:
    *s = *s + 1;
    M[*s] = M[D[m]+n];
    *i = *i + 1;
    break;
//----------------* DISJ
  case disj:
    M[*s-1] = (M[*s-1] | M[*s]) ? 1 : 0;  
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* DIVI
  case divi:
    M[*s-1] = (M[*s-1] / M[*s]);  
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* DMEM k
  case dmem:
    *s = *s - k;
    *i = *i + 1;
    break;
//---------------- DSVF p
  case dsvf:
    *i = (M[*s] == 0) ? p : *i+1;  
    *s = *s - 1;
    break;
//---------------- DSVR p,n,j
  case dsvr:
    {
      int atual = n;
      int dest = j;
      int temp;
      while (atual != dest) {
        temp = M[D[atual]-2];
        D[atual]=M[D[atual]-1];
        atual = temp;
      }
      *i = p;
      break;
    }
//---------------- DSVS p
  case dsvs:
    *i = p;
    break;
//---------------- ENPR m
  case enpr:
    *s = *s + 1;
    M[*s] = D[m];
    D[m] = *s+1;
    *i = *i + 1;
    break;
//---------------- ENRT m,n
  case enrt:
    *s = D[m] + n - 1;
    *i = *i + 1;
    break;
//---------------- IMPR
  case impr:
    insere_fim_vetor_impr(M[*s]);
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* INPP
  case inpp:
    *s = -1;
    D[0] = 0;
    *i = *i + 1;
    break;
//----------------* INVR
  case invr:
    M[*s] = (-1) * M[*s];  
    *i = *i + 1;
    break;
//---------------- LEIT
  case leit:
    *s = *s + 1;
    printf("(entrada):");
    scanf("%d", &M[*s]);
    getchar(); // consome o \n
    *i = *i + 1;
    break;
//----------------* MULT
  case mult:
    M[*s-1] = (M[*s-1] * M[*s]);  
    *s = *s - 1;
    *i = *i + 1;
    break;
//---------------*- NADA
  case nada:
    *i = *i + 1;
    break;
//----------------* NEGA
  case nega:
    M[*s] = 1 - M[*s];  
    *i = *i + 1;
    break;
//----------------* PARA
  case para:
  // como nao muda *i, fica preso aqui.
  break;
//---------------- RTPR m,n
  case rtpr:
    D[k]=M[*s];
    *i = M[*s-2];
    *s = *s-(n+3);
    break;
//----------------* SOMA
  case soma:
    M[*s-1] = (M[*s-1] + M[*s]);
    *s = *s - 1;
    *i = *i + 1;
    break;
//----------------* SUBT
  case subt:
    M[*s-1] = (M[*s-1] - M[*s]);  
    *s = *s - 1;
    *i = *i + 1;
    break;
  }

  //  imprimePilha(5, D, M, *s);
  
  return instr_exec;
}


instrucao_mepa executa_instr_MV_mepa() {

  return _executa_instr_MV_mepa(&mv_mepa_i,
                                &mv_mepa_s,
                                mv_mepa_I,
                                mv_mepa_D,
                                mv_mepa_M
                                );
  
}
