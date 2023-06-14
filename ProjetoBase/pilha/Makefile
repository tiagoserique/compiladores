
all: pilhaInt.o
	gcc main.c pilhaInt.o -o teste_pilha

pilhaInt.o : pilhaInt.h pilhaInt.c
	gcc -c pilhaInt.c -o pilhaInt.o

clean:
	rm -f *.o teste_pilha