
// Prólogo

%%

...

%token ... IF THEN ELSE ...

...

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

...


%% 

...

comando_sem_rotulo : atrib_ou_cp
                   | rep_while
                   | cond_if
                   | comando_goto
                   | comando_composto
;

...

cond_if     : if_then cond_else 
            { 
              em_if_finaliza (); 
            }
;

if_then     : IF expressao 
            {
              em_if_apos_expr ();
            }
             THEN comando_sem_rotulo
            {
              em_if_apos_then ();
            }
;

cond_else   : ELSE comando_sem_rotulo
            | %prec LOWER_THAN_ELSE
;

...
