 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h simbolo.o tabelaSimbolos.o pilhaInt.o pilhaSimbolos.o
	gcc lex.yy.c compilador.tab.c compilador.o simbolo.o tabelaSimbolos.o pilhaInt.o pilhaSimbolos.o -o compilador -lfl -L /usr/lib/x86_64-linux-gnu -ly -lc -g

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o 

simbolo.o : compilador.h tabelaSimbolos/simbolo.c tabelaSimbolos/simbolo.h
	gcc -c tabelaSimbolos/simbolo.c -o simbolo.o -g

tabelaSimbolos.o : compilador.h tabelaSimbolos/tabelaSimbolos.c tabelaSimbolos/tabelaSimbolos.h
	gcc -c tabelaSimbolos/tabelaSimbolos.c -o tabelaSimbolos.o -g

pilhaInt.o : pilha/pilhaInt.h pilha/pilhaInt.c
	gcc -c pilha/pilhaInt.c -o pilhaInt.o -g

pilhaSimbolos.o : pilha/pilhaSimbolos.h pilha/pilhaSimbolos.c
	gcc -c pilha/pilhaSimbolos.c -o pilhaSimbolos.o -g

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador *.o













