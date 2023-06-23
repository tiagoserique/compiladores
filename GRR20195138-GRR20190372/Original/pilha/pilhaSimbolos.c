#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaSimbolos.h"

// Função que inicializa a pilha
void inicializaPilhaSimbolos(PilhaSimbolos *p){
    p->simbolos = NULL;
    p->tamanho = 0;
    p->topo = 0;
}

void pushPilhaSimbolos(PilhaSimbolos *p, Simbolo *elemento){
    if ( p->topo == p->tamanho ){
        p->tamanho += PILHA_TAM_INCREMENTO;
        p->simbolos = realloc(p->simbolos, p->tamanho * sizeof(Simbolo));
 
        if ( p->simbolos == NULL ){
            fprintf(stderr, "Erro ao alocar memória!\n");
            exit(0);
        }
    }

    p->simbolos[p->topo++] = elemento;
}

void popPilhaSimbolos(PilhaSimbolos *p){
    if ( p->topo > 0) 
        p->topo--;
}

Simbolo *topoPilhaSimbolos(PilhaSimbolos *p){

    if ( p->tamanho > 0 ){
        return p->simbolos[p->topo-1];
    }
    else {
        fprintf(stderr, "Pilha de símbolos vazia!\n");
        exit(1);
    }

    return NULL;
}

int vaziaPilhaSimbolos(PilhaSimbolos *p){
    return p->topo == 0;
}

void destroiPilhaSimbolos(PilhaSimbolos *p){
    p->topo = 0;
    p->tamanho = 0;
    free(p->simbolos);

    return;
}

void imprimePilhaSimbolos(PilhaSimbolos *p){
    int i;

    printf("Pilha de símbolos:\n");
    for (i = 0; i < p->topo; i++){
        printf("%s\n", p->simbolos[i]->identificador);
    }

    return;
}

