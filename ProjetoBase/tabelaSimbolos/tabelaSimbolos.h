#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include "simbolo.h"

typedef struct TabelaSimbolos {
    Simbolo *simbolos;
    unsigned int tamanho;
    unsigned int quantidade;
} TabelaSimbolos;


void inicializaTabelaSimbolos(TabelaSimbolos **ts);

void pushTabelaSimbolos(TabelaSimbolos **ts, Simbolo s);

Simbolo popTabelaSimbolos(TabelaSimbolos **ts);

void removeNTabelaSimbolos(TabelaSimbolos **ts, int n);

void atribuiTipoTabelaSimbolos(TabelaSimbolos **ts, int categoria, int tipo, int qtd);

Simbolo *buscaTabelaSimbolos(TabelaSimbolos **ts, const char *nome);

void imprimeTabelaSimbolos(TabelaSimbolos **ts);

#endif
