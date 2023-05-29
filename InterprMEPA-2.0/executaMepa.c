/* -------------------------------------------------------------------
 *            Arquivo: executaMepa.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 09/2020
 *      Atualizado em: [20/09/2020, 08h:05m]
 *
 * -------------------------------------------------------------------
 * Talvez o melhor lugar de moradia deste procedimento seja no modulo
 * de interface com o usuario. Achei que ficava melhor em um arquivo
 * separado , e por isso ficou aqui.
 * ------------------------------------------------------------------- */

#include<stdio.h>
#include "executaMepa.h"

/* -------------------------------------------------------------------
 * Laço de execucaoo de comandos MEPA. Ja entra executando o primeiro 
 * comando do arquivo, normalmente INPP.
 * ------------------------------------------------------------------- */
void executaMepa(params_linha_comando* plc) {
  cmd_usr cmd;
  instrucao_mepa instr_exec;
  
  do {
    instr_exec = executa_instr_MV_mepa();
    if (plc->interativo)
      imprime_estado_MV_mepa_interativo();
    else
      imprime_estado_MV_mepa_batch();

    if (instr_exec == para) {
      printf("execução finalizada\n");
      break;
    }

    if (plc->interativo) {
      cmd = le_comando();
      if (cmd == resume)
        plc->interativo = 0;
    }
  }  while (cmd != sair);
}
