#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simbolo.h"

Simbolo criaSimbolo(char *id, int cat, int nivel, int tipo, tipoConteudo conteudo){
    Simbolo s;
    
    s.identificador = malloc(strlen(id)+1);
    strcpy(s.identificador, id);

    s.categoria = cat;
    s.nivel = nivel;
    s.conteudo = conteudo;

    return s;
}