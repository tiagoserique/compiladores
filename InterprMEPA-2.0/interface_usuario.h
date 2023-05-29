/* -------------------------------------------------------------------
 *            Arquivo: acao_usuario.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 09/2020
 *      Atualizado em: [20/09/2020, 07h:56m]
 *
 * -------------------------------------------------------------------
 *
 * ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct params_linha_comando {
  FILE* fp_in;        // arquivo entrada
  char arq_in[100];   // nome arquivo entrada
  int interativo;     // executa passo a passo ou de uma vez
} params_linha_comando;

typedef enum cmd_usr {
  sair, imprime, resume, proximo
} cmd_usr;


void iniciaInterfaceUsuario();

/* -------------------------------------------------------------------
 * Os valores gerados por IMPR são armazenados no vetor abaixo e
 * são impressos logo antes da linha de interação com o usuário.  
 * ------------------------------------------------------------------- */
void insere_fim_vetor_impr(int elem);

/* -------------------------------------------------------------------
 * Os parâmetros incluídos na linha de invocação do programa são 
 * extraídos pelo procedimento abaixo.
 * ------------------------------------------------------------------- */
params_linha_comando* le_params_linha_comando (int argc, char** argv);
void imprime_params_linha_comando (params_linha_comando* olc);// util para depurar

/* -------------------------------------------------------------------
 * Leitura dá opção de interação do usuário solicitada após a impressão 
 * do estado da máquina virtual
 * ------------------------------------------------------------------- */
cmd_usr le_comando();

/* -------------------------------------------------------------------
 * TODO: Quando o programa MEPA é muito grande, ele não cabe na tela. 
 * Quero adaptar o procedimento abaixo para imprimir o vetor de instruções 
 * centralizado na instrução atual.
 * ------------------------------------------------------------------- */
void printf_interv_instr_MV_mepa (int delta, int atual);

/* -------------------------------------------------------------------
 * O termo "estado" significa os valores atuais de cada uma das 
 * estruturas da máquina virtual.
 * ------------------------------------------------------------------- */
void imprime_estado_MV_mepa_interativo();
void imprime_estado_MV_mepa_batch(); // só imprime o result de IMPR
