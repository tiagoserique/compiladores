CC = gcc
OBJ = executaMepa.o interface_usuario.o MV_mepa.o

executaMepa: lex.yy.c leMepa.tab.c  $(OBJ)
	gcc lex.yy.c leMepa.tab.c $(OBJ) -o executaMepa -ll -ly -lc

lex.yy.c: leMepa.l leMepa.h leMepa.tab.c
	flex leMepa.l

leMepa.tab.c: leMepa.y leMepa.h
	bison leMepa.y -d -v

$(OBJ) :

clean : 
	rm -f leMepa.tab.? lex.yy.c *.output *.o executaMepa
