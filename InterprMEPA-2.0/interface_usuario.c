/* -------------------------------------------------------------------
 *            Arquivo: interface_usuario.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 09/2020
 *      Atualizado em: [20/09/2020, 07h:54m]
 *
 * -------------------------------------------------------------------
 * Implementação de todos os procedimentos de leitura ou de impressão 
 * na tela.
 * ------------------------------------------------------------------- */

#include "interface_usuario.h"
#include "MV_mepa.h"

#define CLEAR_SCREEN "\e[1;1H\e[2J"

char* _01_resumo_param_linha_comando =
    "-----------------------------------------\n"
    " Arquivo de entrada: %s                  \n"
    " Modo Interativo:    %s                  \n"
    " Iniciando Execução                      \n"
    "-----------------------------------------\n";

char* _02_ajuda_linha_comando = 
  "uso: compilaMepa [-r -h -iArqIn]                   \n"
  "Onde:                                              \n"
  "    -r => desativa modo interativo (default=ativo) \n"
  "    -h => help                                     \n"
  "    -iARQ => arquivo de entrada (default=MEPA)     \n";

char* _03_ajuda_modo_interativo =
  "Modo interativo:                   \n"
  "       q => sai                    \n"
  "       r => resume execucao        \n"
  "       ? => imprime esta mensagem  \n"
  "  outros => proximo comando        \n";

/* -------------------------------------------------------------------
 *   Trata linha de comando
 * ------------------------------------------------------------------- */
void imprime_params_linha_comando (params_linha_comando* plc) {

  printf (_01_resumo_param_linha_comando,
          plc->arq_in,
          (plc->interativo==1) ? "sim" : "nao"); 

  if (plc->interativo) {
    printf("%s", _03_ajuda_modo_interativo);
  }
}



/* -------------------------------------------------------------------
 *  carrega  params_linha_comando
 * ------------------------------------------------------------------- */


params_linha_comando* le_params_linha_comando (int argc, char** argv) {
  int c;
  params_linha_comando *plc;

  plc = (params_linha_comando*) malloc (sizeof(params_linha_comando));
  plc->interativo = 1;
  strcpy(plc->arq_in, "");

  while ((c = getopt (argc, argv, "rphi:")) != -1) {
    switch (c)
      {
      case 'r': 
        plc->interativo = 0;
        break;
      case 'i':
        strcpy(plc->arq_in, optarg);
      break;
      default:
        printf("%s", _02_ajuda_linha_comando);
        exit(0);
        break;
      }
  }

  // Se não disse o nome do arquivo de entrada, 
  // então a entrada é o arquivo "MEPA"
  if (strlen(plc->arq_in)==0)
    strcpy (plc->arq_in, "MEPA");

  plc->fp_in=fopen (plc->arq_in, "r");
  if (plc->fp_in == NULL) {
    printf("Arquivo %s não encontrado\n", plc->arq_in);
    exit(-1);
  }
  return plc;
}



/* -------------------------------------------------------------------
 *  Trata modo interativo: le comando do usuário
 * ------------------------------------------------------------------- */
cmd_usr le_comando(){
  char linha[20];
  char cmd;
  int i=0;

  while (1) {
    printf("=> "); // prompt
    scanf("%c", &cmd);
    if (cmd == '\n')
      cmd = 's';
    else
      getchar(); // consome o '\n'
    
    switch (cmd) {
    case '?':
      printf("%s", _03_ajuda_modo_interativo);
      break;
    case 'q': return sair;
    case 'r': return resume;
    default : return proximo;
    }
  
  }
}

// *********************************************************************
// *********************************************************************
// Operacoes sobre o vetor_impr (armazena results do IMPR
// *********************************************************************

#define TAM_VET_IMPR 100
int _vetor_impr[TAM_VET_IMPR];
int _inicio_vetor_impr =0;
int _fim_vetor_impr =-1;
void insere_fim_vetor_impr(int elem){
  _fim_vetor_impr++;
  if (_fim_vetor_impr >= TAM_VET_IMPR) {
    printf ("Overflow do buffer de impressao\n");
    exit (-1);
  }
  _vetor_impr[_fim_vetor_impr] = elem;
}

void imprime_vetor_impr(char *s){
  s[0]='\0';
  for (int i=_inicio_vetor_impr; i<=_fim_vetor_impr; i++)
    sprintf(s+strlen(s), "%d ", _vetor_impr[i]);
}

int alguem_no_vetor_impr() {
  return(_inicio_vetor_impr == _fim_vetor_impr);
}

void anda_inicio_vetor_impr() {
  _inicio_vetor_impr++;
  return;
}


// *********************************************************************
// *********************************************************************
// Impressao da maquina virtual em execucao
// 1: Vetor de instrucoes
// *********************************************************************


 

/* -------------------------------------------------------------------
 *  Mapa entre códigos de operação e o string a ser impresso.
 * ------------------------------------------------------------------- */
char _tabInstr[100][100];
void iniciaTabInstr ()
{
  strcpy(_tabInstr[inpp], "INPP"); 
  strcpy(_tabInstr[para], "PARA"); 
  strcpy(_tabInstr[nada], "NADA"); 
  strcpy(_tabInstr[soma], "SOMA"); 
  strcpy(_tabInstr[subt], "SUBT"); 
  strcpy(_tabInstr[mult], "MULT"); 
  strcpy(_tabInstr[divi], "DIVI");
  strcpy(_tabInstr[invr], "INVR");
  strcpy(_tabInstr[conj], "CONJ");
  strcpy(_tabInstr[disj], "DISJ");
  strcpy(_tabInstr[nega], "NEGA"); 
  strcpy(_tabInstr[cmme], "CMME"); 
  strcpy(_tabInstr[cmma], "CMMA"); 
  strcpy(_tabInstr[cmig], "CMIG"); 
  strcpy(_tabInstr[cmdg], "CMDG"); 
  strcpy(_tabInstr[cmeg], "CMEG"); 
  strcpy(_tabInstr[cmag], "CMAG"); 
  strcpy(_tabInstr[leit], "LEIT"); 
  strcpy(_tabInstr[impr], "IMPR"); 
  strcpy(_tabInstr[crct], "CRCT"); 
  strcpy(_tabInstr[amem], "AMEM"); 
  strcpy(_tabInstr[dmem], "DMEM"); 
  strcpy(_tabInstr[enpr], "ENPR"); 
  strcpy(_tabInstr[dsvs], "DSVS"); 
  strcpy(_tabInstr[dsvf], "DSVF"); 
  strcpy(_tabInstr[crvl], "CRVL"); 
  strcpy(_tabInstr[armz], "ARMZ"); 
  strcpy(_tabInstr[crvi], "CRVI");
  strcpy(_tabInstr[crvi], "CRVI"); 
  strcpy(_tabInstr[armi], "ARMI"); 
  strcpy(_tabInstr[cren], "CREN"); 
  strcpy(_tabInstr[enrt], "ENRT"); 
  strcpy(_tabInstr[chpr], "CHPR"); 
  strcpy(_tabInstr[rtpr], "RTPR"); 
  strcpy(_tabInstr[dsvr], "DSVR"); 
}

/* -------------------------------------------------------------------
 * Coloca em "sout" a impressão da instrução contida em mv_mepa_I[i].
 * O parâmetro "primeiro" é incluído no primeiro caractere de "sout".
 * ------------------------------------------------------------------- */

void gera_linha_impr_Instr_MV_mepa (char* sout, int i, char *primeiro) {

  sprintf(sout, "%s", "");

  // Se estiver fora do intervalo de instrucoes, retorna linha vazia
  if (i<0 || i>mv_mepa_tam_i-1)
    return;

  // concatena primeiro
  sprintf(sout+strlen(sout), "%s", primeiro);
  
  // concatena endereco da instrucao
  sprintf (sout+strlen(sout),"I[%04d] ", i);
    
  // concatena nome do rotulo (se houver)
  if (strlen(mv_mepa_I[i].rotulo) == 0) 
    sprintf (sout+strlen(sout),"     ");
  else
    sprintf (sout+strlen(sout),"%s: ", mv_mepa_I[i].rotulo);

  // concatena nome da instrucao
  sprintf (sout+strlen(sout),"%s ", _tabInstr[mv_mepa_I[i].instr]);

  // concatena parametros de acordo com a instrucao
  switch (mv_mepa_I[i].instr) {
    // caso 1: instrucao com zero parametros
  case inpp: case para: case soma: case subt: case mult: case divi:
  case invr: case conj: case disj: case nega: case cmme: case cmma:
  case cmig: case cmdg: case cmeg: case cmag: case nada: case leit:
  case impr:
    break;
    // ------------------------------------------------------------
    // caso 2: instrucao com um parametro: inteiro
  case crct: case amem: case dmem: case enpr: 
    sprintf (sout+strlen(sout),"%d", mv_mepa_I[i].op1);
    break;
    // ------------------------------------------------------------
    // caso 3: instrucao com um parametro: rotulo
  case dsvs: case dsvf:
    sprintf (sout+strlen(sout),"%s", mv_mepa_I[i].rotDdesvio);
    break;
    // ------------------------------------------------------------
    // caso 4: instrucao com dois parametros: dois inteiros
  case crvl: case armz: case crvi: case armi: case cren: case enrt:
    sprintf (sout+strlen(sout),"%d, %d", mv_mepa_I[i].op1,
             mv_mepa_I[i].op2);
    break;
    // ------------------------------------------------------------
    // caso 5: instrucao com dois parametros: um rotulo, um inteiro
  case chpr: 
    sprintf (sout+strlen(sout),"%s, %d", mv_mepa_I[i].rotDdesvio,
             mv_mepa_I[i].op2);
    break;
    // ------------------------------------------------------------
    // caso 6: instrucao com tres parametros: tres inteiros
  case dsvr: 
    sprintf (sout+strlen(sout),"%s, %d, %d", mv_mepa_I[i].rotDdesvio,
             mv_mepa_I[i].op2, mv_mepa_I[i].op3);
    break;
  }
}

/* -------------------------------------------------------------------
 * Imprime todo o vetor de instruções sem fazer nenhum refinamento. 
 * Foi muito utilizada na fase de desenvolvimento e testes, mas talvez 
 * nao tenha mais nenhuma utilidade.
 * ------------------------------------------------------------------- */

void dump_todas_instr_MV_mepa () {
  char sout[100];
  for (int i=0; i<mv_mepa_tam_i-1; i++) {
    gera_linha_impr_Instr_MV_mepa(sout, i," ");
    printf("%s\n", sout);
  }
}

// *********************************************************************
// *********************************************************************
// Impressao da maquina virtual em execucao
// 2: Vetor de regs de base
// *********************************************************************



void gera_linha_impr_base_MV_mepa (char* sout, int* D, int l){
  sprintf(sout, "%s", "");

  if (l<0 || l>4)
    return;

  sprintf (sout+strlen(sout),"D[%04d] %04d", l, D[l]);

}

// *********************************************************************
// *********************************************************************
// Impressao da maquina virtual em execucao
// 3: Vetor da pilha
// *********************************************************************

void gera_linha_impr_pilha_MV_mepa (char* sout, int* M, int l){
  sprintf(sout, "%s", "");

  if (l<0 || l>mv_mepa_s)
    return;

  sprintf (sout+strlen(sout),"M[%04d] %04d", l, M[l]);

  if (l == mv_mepa_s)
    sprintf (sout+strlen(sout), "<");
  else
    sprintf (sout+strlen(sout), " ");
}



/* -------------------------------------------------------------------
 * O procedimento abaixo anexa espaços em branco até o índice indicado 
 * (pos). O vetor brancos só foi criado para agilizar o processo.
 * ------------------------------------------------------------------- */

char *_brancos="                                        ";
void  preenche_ate_posicao(char *s, int pos) {
  int tam = strlen(s);
  strncpy(&s[tam], _brancos, pos-tam);
  s[pos]='\0';
}  

/* -------------------------------------------------------------------
 * Apresenta "graficamente" a situacao atual (estado) da máquina 
 * virtual mepa.
 * ------------------------------------------------------------------- */

void imprime_estado_MV_mepa_interativo() {
  char linha_I[100];
  char linha_M[100];
  char linha_D[100];
  char linha_out[100];
  char linha_impr[TAM_VET_IMPR];

  // Imprime todas as instruções na primeira coluna e, baseado na
  // altura, colunas com o vetor de registradores de base e a pilha.
  // Observe que os índices dos vetores de instrução são crescentes
  // (do começo do vetor, índice zero até o fim do vetor,
  // mv_mepa_tam_i) enquanto que os vetores de registrador de base e
  // da pilha são decrescentes. Para ajustá-los a a base da figura, é
  // utilizada a fórmula (mv_mepa_tam_i-j-1);

  printf(CLEAR_SCREEN);
  for(int j=0; j<mv_mepa_tam_i; j++) {
    if (j==mv_mepa_i)
      gera_linha_impr_Instr_MV_mepa(linha_I, j, ">");//indica instr a ser exec
    else
      gera_linha_impr_Instr_MV_mepa(linha_I, j, " ");
    preenche_ate_posicao(linha_I, 40);

    gera_linha_impr_pilha_MV_mepa(linha_M, mv_mepa_M, mv_mepa_tam_i-j-1);
    preenche_ate_posicao(linha_M, 20); 

    gera_linha_impr_base_MV_mepa (linha_D, mv_mepa_D, mv_mepa_tam_i-j-1);
    preenche_ate_posicao(linha_D,20);
    
    printf ("%s %s %s \n", linha_I, linha_D, linha_M);
  }
  imprime_vetor_impr(linha_impr);
  printf ("saida: %s \n", linha_impr);
}


/* -------------------------------------------------------------------
 * em modo de execução batch (!interativo), só imprime o resultado de IMPR
 * ------------------------------------------------------------------- */

void imprime_estado_MV_mepa_batch() {
  char linha_impr[TAM_VET_IMPR];

  if (alguem_no_vetor_impr()) {
      imprime_vetor_impr(linha_impr);
      printf ("saida: %s \n", linha_impr);
      anda_inicio_vetor_impr();
  }
}



void iniciaInterfaceUsuario() {
  iniciaTabInstr ();
}
