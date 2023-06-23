#ifndef PILHA_SIMBOLOS_H
#define PILHA_SIMBOLOS_H

#include "../tabelaSimbolos/simbolo.h"

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32


typedef struct PilhaSimbolos {
    Simbolo **simbolos;
    int topo;
    int tamanho;
} PilhaSimbolos;

void inicializaPilhaSimbolos(PilhaSimbolos *p);

void pushPilhaSimbolos(PilhaSimbolos *p, Simbolo *elemento);

void popPilhaSimbolos(PilhaSimbolos *p);

Simbolo *topoPilhaSimbolos(PilhaSimbolos *p);

int vaziaPilhaSimbolos(PilhaSimbolos *p);

void destroiPilhaSimbolos(PilhaSimbolos *p);

void imprimePilhaSimbolos(PilhaSimbolos *p);

#endif
