#include <stdlib.h>
#include <stdio.h>
#include "tabelaSimbolos.h"
#include <string.h> 

// Função que inicializa a tabela de símbolos
void inicializa(TabelaSimbolos **ts){
    *ts = (TabelaSimbolos *) malloc(sizeof(TabelaSimbolos));
    (*ts)->simbolos = malloc(sizeof(Simbolo));
    (*ts)->quantidade = 0;
    (*ts)->tamanho = 1;

    return;
}

void push(TabelaSimbolos **ts, Simbolo s){
    int i;
    (*ts)->quantidade++;
    
    
    if ((*ts)->quantidade > (*ts)->tamanho){
        (*ts)->tamanho *= 2;
        (*ts)->simbolos = realloc((*ts)->simbolos, (*ts)->tamanho * sizeof(Simbolo));
    }

    i = (*ts)->quantidade - 1;
    (*ts)->simbolos[i] = s;

    return;
}

Simbolo pop(TabelaSimbolos **ts){
    int i;
    Simbolo s;

    if ( (*ts)->quantidade == 0 ){
        printf("Tabela de símbolos vazia!\n");
        exit(1);
    }

    i = (*ts)->quantidade - 1;
    s = (*ts)->simbolos[i];
    (*ts)->quantidade--;

    return s;
}

void removeN(TabelaSimbolos **ts, int n){
    if ( (*ts)->quantidade == 0 ){
        printf("Tabela de símbolos vazia!\n");
        exit(1);
    }

    (*ts)->quantidade -= n;

    return;
}

void atribuiTipo(TabelaSimbolos **ts, int categoria, int tipo, int qtd){
    int i;

    if ( (*ts)->quantidade == 0 ){
        printf("Tabela de símbolos vazia!\n");
        exit(1);
    }

    i = (*ts)->quantidade - 1;

    for (; i < qtd; i++){
        (*ts)->simbolos[i - 1].conteudo.var.tipo = tipo;
    }

    return;
}

Simbolo *busca(TabelaSimbolos **ts, const char *nome){
    int i = (*ts)->quantidade - 1;

    while ( i >= 0 ){
        Simbolo *atual = &( (*ts)->simbolos[i--] );
        if ( !strcmp( atual->identificador, nome) ) return atual;
    }

    return NULL;
}