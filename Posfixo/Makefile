posfixo: posfixo.tab.c lex.yy.c posfixo.o 
	gcc lex.yy.c posfixo.tab.c -o posfixo -ll -ly -lc

posfixo.tab.c: posfixo.y 
	bison posfixo.y -d -v

lex.yy.c: posfixo.l 
	flex posfixo.l


clean : 
	rm -f posfixo.tab.* lex.yy.c 
