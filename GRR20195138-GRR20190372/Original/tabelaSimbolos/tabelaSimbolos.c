#include <stdlib.h>
#include <stdio.h>
#include "tabelaSimbolos.h"
#include <string.h> 

void inicializaTabelaSimbolos(TabelaSimbolos **ts){
    *ts = (TabelaSimbolos *) malloc(sizeof(TabelaSimbolos));
    (*ts)->simbolos = malloc(sizeof(Simbolo));
    (*ts)->quantidade = 0;
    (*ts)->tamanho = 1;

    return;
}

void pushTabelaSimbolos(TabelaSimbolos **ts, Simbolo s){
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

Simbolo popTabelaSimbolos(TabelaSimbolos **ts){
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

void removeNTabelaSimbolos(TabelaSimbolos **ts, int n){
    if ( (*ts)->quantidade == 0 ){
        printf("Tabela de símbolos vazia!\n");
        exit(1);
    }

    (*ts)->quantidade -= n;

    return;
}

void atribuiTipoTabelaSimbolos(TabelaSimbolos **ts, int categoria, int tipo, int qtd){
    int i, total;

    if ( (*ts)->quantidade == 0 ){
        printf("Tabela de símbolos vazia!\n");
        exit(1);
    }

    total = (*ts)->quantidade;

    for (i = 1; i <= qtd; i++){
        (*ts)->simbolos[total - i].conteudo.var.tipo = tipo;
    }

    return;
}

Simbolo *buscaTabelaSimbolos(TabelaSimbolos **ts, const char *nome){
    int i = (*ts)->quantidade - 1;

    while ( i >= 0 ){
        Simbolo *atual = &( (*ts)->simbolos[i--] );
        if ( !strcmp(atual->identificador, nome) ) return atual;
    }

    return NULL;
}

void imprimeTabelaSimbolos(TabelaSimbolos **ts){
    int i;
    printf("\nTabela de símbolos:\n");

    for (i = (*ts)->quantidade - 1; i >= 0 ; i--){
        Simbolo *atual = &( (*ts)->simbolos[i] );

        if ( atual->categoria == CAT_PROCEDIMENTO || atual->categoria == CAT_FUNCAO ){
            fprintf(stderr, "Ident: %s \t|| Cat: %s \t|| Nível: %d \t|| Tipo R: %s \t|| Deslocamento: %d \t|| Rotulo: R%02d \t\t|| QtdParam: %d\n", 
                atual->identificador, 
                imprimeCategoria(atual->categoria), 
                atual->nivel,
                imprimeTipo(atual->conteudo.proc.tipoRetorno),
                atual->conteudo.proc.deslocamento,
                atual->conteudo.proc.rotulo,
                atual->conteudo.proc.qtdParametros);
            continue;
        }

        if ( atual->categoria == CAT_PARAMETRO ){
            fprintf(stderr, "Ident: %s \t|| Cat: %s \t|| Nível: %d \t|| Tipo: %s \t|| Deslocamento: %d \t|| Passagem: %s\n", 
                atual->identificador, 
                imprimeCategoria(atual->categoria), 
                atual->nivel,
                imprimeTipo(atual->conteudo.param.tipo),
                atual->conteudo.param.deslocamento,
                atual->conteudo.param.passagem == PAS_COPIA ? "copia" : "referencia");
            continue;
        }

        if ( atual->categoria == CAT_VARIAVEL ){
            fprintf(stderr, "Ident: %s \t|| Cat: %s \t|| Nível: %d \t|| Tipo: %s \t|| Deslocamento: %d\n", 
                atual->identificador, 
                imprimeCategoria(atual->categoria), 
                atual->nivel,
                imprimeTipo(atual->conteudo.var.tipo),
                atual->conteudo.var.deslocamento);
            continue;
        }

         if ( atual->categoria == CAT_LABEL ){
            fprintf(stderr, "Ident: %s \t|| Cat: %s \t|| Nível: %d \t|| Tipo R: %s \t|| Deslocamento: %d \t|| Rotulo: R%02d \t\t|| QtdParam: %d\n", 
                atual->identificador, 
                imprimeCategoria(atual->categoria), 
                atual->nivel,
                imprimeTipo(atual->conteudo.proc.tipoRetorno),
                atual->conteudo.proc.deslocamento,
                atual->conteudo.proc.rotulo,
                atual->conteudo.proc.qtdParametros);
            continue;
        }

    }
    printf("\n");


    return;
}