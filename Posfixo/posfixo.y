
%{
#include <stdio.h>
%}

%token IDENT MAIS MENOS OR ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             termo
;

termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             fator
;

fator      : IDENT {printf ("A"); }
;

%%

main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

