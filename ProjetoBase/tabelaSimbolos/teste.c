#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.h"
#include "simbolo.h"

int main(){
    // Simbolo var;
    // Simbolo param;
    Simbolo proc;
    tipoConteudo conteudo;

    // conteudo.var.tipo = 0;
    // conteudo.var.deslocamento = 99;
    // var = cria_simbolo("teste", 123, 532, variavel, conteudo);
    // printf("%d\n", var.tipo.var.deslocamento);

    // conteudo.param.deslocamento = 98;
    // conteudo.param.passagem = 1;
    // conteudo.param.tipo = 3;
    // param = cria_simbolo("cont", 123, 532, variavel, conteudo);
    // printf("%s\n", param.identificador);

    conteudo.proc.rotulo = malloc(strlen("soma"));
    strcpy(conteudo.proc.rotulo, "soma");
    conteudo.proc.qtdParametros = 13;
    // conteudo.proc.lista = NULL;
    proc = criaSimbolo("soma", 56, 65, conteudo);


    TabelaSimbolos *ts;
    inicializa(&ts);
    printf("Procurando por '%s' antes de inserir\n", proc.identificador);
    if(busca(&ts, proc.identificador)) printf("Achou simbolo\n");
    else printf("Simbolo nao achado");

    push(&ts, proc);
    push(&ts, proc);
    push(&ts, proc);
    push(&ts, proc);

    printf("Procurando por '%s' depois de inserir\n", proc.identificador);
    if(busca(&ts, proc.identificador)) printf("Achou simbolo\n");
    else printf("Simbolo nao achado");
    printf("A tabela tem %d simbolos\n", ts->quantidade);

    printf("Removendo 2 entradas\n");
    removeN(&ts, 2);
    printf("A tabela agora tem %d simbolos\n", ts->quantidade);


    // struct simbolo s = pop(&ts);
    // printf("%s\n", s.identificador);
    // printf("%d\n", ts->qtd);



    return 0;
}