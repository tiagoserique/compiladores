#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilhaInt.h"

int main(){

    PilhaInt pilha;

    inicializaPilhaInt(&pilha);

    pushPilhaInt(&pilha, 1);

    pushPilhaInt(&pilha, 2);

    printf("A string: %02d\n", topoPilhaInt(&pilha));

    popPilhaInt(&pilha);
    printf("A string: %02d\n", topoPilhaInt(&pilha));

    popPilhaInt(&pilha);
    if (vaziaPilhaInt(&pilha))
        printf("Pilha vazia\n");
    else 
        printf("A string: %2d\n", topoPilhaInt(&pilha));

    destroiPilhaInt(&pilha);

    return 0;
}