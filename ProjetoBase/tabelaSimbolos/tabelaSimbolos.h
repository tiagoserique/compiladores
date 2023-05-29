#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include "simbolo.h"

typedef struct TabelaSimbolos {
    Simbolo *simbolos;
    unsigned int tamanho;
    unsigned int quantidade;
} TabelaSimbolos;


void inicializa(TabelaSimbolos *ts);

void push(TabelaSimbolos *ts, Simbolo s);

Simbolo pop(TabelaSimbolos *ts);

void removeN(TabelaSimbolos *ts, int n);

void atribuiTipo(TabelaSimbolos *ts, int categoria, int tipo, int qtd);


#endif
