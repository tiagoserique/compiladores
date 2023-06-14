#ifndef SIMBOLO_H
#define SIMBOLO_H


typedef enum enumTipoSimbolo {
    VARIAVEL,
    PARAMETRO,
    PROCEDIMENTO,
    FUNCAO
} enumTipoSimbolo;

typedef enum tipoVariavel {
    INTEGER,
    FLOAT,
    BOOLEAN,
    UNDEFINED_TYPE
} tipoVariavel;

typedef enum tipoPassagem {
    COPIA,
    REFERENCIA
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
    char *rotulo;
    int qtdParametros;
    parametro lista[128];
} procedimento;


// define simbolo

typedef struct tipoConteudo {
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

Simbolo criaSimbolo(char *id, int cat, int nivel, tipoConteudo Conteudo);

#endif
