#ifndef PILHA_INT_H
#define PILHA_INT_H

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32

typedef struct PilhaInt {
    int *dados;
    int topo;
    int tamanho;
} PilhaInt;

void inicializaPilhaInt(PilhaInt *p);

void pushPilhaInt(PilhaInt *p, int dado);

int popPilhaInt(PilhaInt *p);

int topoPilhaInt(PilhaInt *p);

int vaziaPilhaInt(PilhaInt *p);

void destroiPilhaInt(PilhaInt *p);

void imprimePilhaInt(PilhaInt *p);

#endif