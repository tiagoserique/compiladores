
all: pilhaInt.o pilhaSimbolos.o
	gcc main.c pilhaInt.o -o teste_pilha
	gcc main.c pilhaSimbolos.o -o teste_pilhaSimbolos

pilhaInt.o : pilhaInt.h pilhaInt.c
	gcc -c pilhaInt.c -o pilhaInt.o

pilhaSimbolos.o : pilhaSimbolos.h pilhaSimbolos.c
	gcc -c pilhaSimbolos.c -o pilhaSimbolos.o

clean:
	rm -f *.o teste_pilha