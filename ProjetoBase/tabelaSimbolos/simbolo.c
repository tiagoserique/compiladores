#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simbolo.h"


char *imprimeTipo(int tipo){
    switch (tipo){
        case TIPO_INTEGER:
            return "integer";
        case TIPO_FLOAT:
            return "float";
        case TIPO_BOOLEAN:
            return "boolean";
        case TIPO_UNDEFINED_TYPE:
            return "undefined";
        default:
            return "undefined";
    }
}

char *imprimeCategoria(int categoria){
    switch (categoria){
        case CAT_VARIAVEL:
            return "variavel";
        case CAT_PARAMETRO:
            return "parametro";
        case CAT_PROCEDIMENTO:
            return "procedure";
        case CAT_FUNCAO:
            return "function";
        default:
            return "undefined";
    }
}

Simbolo criaSimbolo(char *id, int cat, int nivel, tipoConteudo conteudo){
    Simbolo s;
    
    s.identificador = malloc(strlen(id)+1);
    strcpy(s.identificador, id);

    s.categoria = cat;
    s.nivel = nivel;
    s.conteudo = conteudo;

    return s;
}

void imprimeSimbolo(Simbolo *s){

    printf("\n\n IMPRIMIINDO Simbolo: %s\n\n", s->identificador);

    printf("Simbolo: %s\n", s->identificador);
    printf("Categoria: %s\n", imprimeCategoria(s->categoria));
    printf("Nivel: %d\n", s->nivel);

    switch (s->categoria){
        case CAT_VARIAVEL:
            printf("Tipo: %s\n", imprimeTipo(s->conteudo.var.tipo));
            printf("Deslocamento: %d\n", s->conteudo.var.deslocamento);
            break;
        case CAT_PARAMETRO:
            printf("Tipo: %s\n", imprimeTipo(s->conteudo.param.tipo));
            printf("Deslocamento: %d\n", s->conteudo.param.deslocamento);
            printf("Passagem: %s\n", s->conteudo.param.passagem == PAS_COPIA ? "copia" : "referencia");
            break;
        case CAT_PROCEDIMENTO:
            printf("Tipo de retorno: %s\n", imprimeTipo(s->conteudo.proc.tipoRetorno));
            printf("Deslocamento: %d\n", s->conteudo.proc.deslocamento);
            printf("Rotulo: R%02d\n", s->conteudo.proc.rotulo);
            printf("Quantidade de parametros: %d\n", s->conteudo.proc.qtdParametros);
            break;
        case CAT_FUNCAO:
            printf("Tipo de retorno: %s\n", imprimeTipo(s->conteudo.proc.tipoRetorno));
            printf("Deslocamento: %d\n", s->conteudo.proc.deslocamento);
            printf("Rotulo: R%02d\n", s->conteudo.proc.rotulo);
            printf("Quantidade de parametros: %d\n", s->conteudo.proc.qtdParametros);
            break;
        default:
            printf("Tipo: %s\n", imprimeTipo(s->conteudo.var.tipo));
            printf("Deslocamento: %d\n", s->conteudo.var.deslocamento);
            break;
    }

    printf("FIIIIIIIIIIIIIIIIIIIIIiiiiM\n\n");

    return;
}