#ifndef SIMBOLO_H
#define SIMBOLO_H


typedef enum enumCategoriaSimbolo {
    CAT_VARIAVEL,
    CAT_PARAMETRO,
    CAT_PROCEDIMENTO,
    CAT_FUNCAO,
    CAT_LABEL
} enumCategoriaSimbolo;

typedef enum tipoVariavel {
    TIPO_INTEGER,
    TIPO_FLOAT,
    TIPO_BOOLEAN,
    TIPO_UNDEFINED_TYPE
} tipoVariavel;

typedef enum tipoPassagem {
    PAS_COPIA,
    PAS_REFERENCIA
} tipoPassagem;


// tipos de simbolos

typedef struct variavel {
    int tipo;
    int deslocamento;
} variavel;

typedef struct parametro {
    int tipo;
    int deslocamento;
    int passagem;
} parametro;

typedef struct procedimento {
    int tipoRetorno;
    int deslocamento;
    int rotulo;
    int qtdParametros;
    parametro lista[128];
} procedimento;


// define simbolo

typedef union tipoConteudo {
    variavel var;
    parametro param;
    procedimento proc;
} tipoConteudo;

typedef struct Simbolo {
    char *identificador;
    int categoria; // variaveis simples, parametros formais simples, procedimentos 
    int nivel;
    tipoConteudo conteudo;
} Simbolo;


char *imprimeTipo(int tipo);

char *imprimeCategoria(int categoria);

Simbolo criaSimbolo(char *id, int cat, int nivel, tipoConteudo Conteudo);

void imprimeSimbolo(Simbolo *s);

#endif
