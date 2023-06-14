#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaInt.h"

// Função que inicializa a pilha
void inicializaPilhaInt(PilhaInt *p){
    p->dados = NULL;
    p->tamanho = 0;
    p->topo = 0;
}

void pushPilhaInt(PilhaInt *p, int elemento){
    if ( p->topo == p->tamanho ){
        p->tamanho += PILHA_TAM_INCREMENTO;
        p->dados = realloc(p->dados, p->tamanho * sizeof(int));
 
        if ( p->dados == NULL ){
            fprintf(stderr, "Erro ao alocar memória!\n");
            exit(0);
        }
    }

    p->dados[p->topo++] = elemento;
}

int popPilhaInt(PilhaInt *p){
    if ( p->topo > 0) 
        p->topo--;
}

int topoPilhaInt(PilhaInt *p){

    if ( p->topo > 0 ){
        return p->dados[p->topo-1];
    }
    else {
        fprintf(stderr, "Pilha de inteiros vazia!\n");
        exit(1);
    }

    return 0;
}

int vaziaPilhaInt(PilhaInt *p){
    return p->topo == 0;
}

void destroiPilhaInt(PilhaInt *p){
    p->topo = 0;
    p->tamanho = 0;
    free(p->dados);

    return;
}

