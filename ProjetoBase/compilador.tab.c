/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tabelaSimbolos/tabelaSimbolos.h"
#include "tabelaSimbolos/simbolo.h"
#include "pilha/pilhaInt.h"
#include "pilha/pilhaSimbolos.h"


TabelaSimbolos *ts, *pilhaAtribuicao;
tipoConteudo conteudo;
Simbolo *s_ptr, *s_var_ou_proc, proc_atual, *s_atribuicao;
PilhaInt pilhaRotulos, pilhaAmem, pilhaProcs;
PilhaSimbolos pilhaVarAEsquerda;

int num_vars;
int num_params;
int num_params_section;
int num_procedimentos_proc_atual;
int num_param_chamada_atual;
int nivel_lexico;
int rotulo_atual;
int quantidade_tipo_atual;
int dentro_chamada_procedimento; // conta chamadas encadeadas de procedimentos

int flag_referencia; // pra passagem por referencia ou nao
int flag_atribui;

char mepa_comand[128];
char proc_nome[128];

parametro lista_parametros[128];
Simbolo lista_simbolos[128];
char idents[128][128];

int str2type(const char *str){
   if (!strcmp(str, "integer")) return TIPO_INTEGER;
   if (!strcmp(str, "boolean")) return TIPO_BOOLEAN;
   return TIPO_UNDEFINED_TYPE;
}


#line 117 "compilador.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_ABRE_PARENTESES = 4,            /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 5,           /* FECHA_PARENTESES  */
  YYSYMBOL_VIRGULA = 6,                    /* VIRGULA  */
  YYSYMBOL_PONTO_E_VIRGULA = 7,            /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 8,                /* DOIS_PONTOS  */
  YYSYMBOL_PONTO = 9,                      /* PONTO  */
  YYSYMBOL_T_BEGIN = 10,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 11,                     /* T_END  */
  YYSYMBOL_VAR = 12,                       /* VAR  */
  YYSYMBOL_IDENT = 13,                     /* IDENT  */
  YYSYMBOL_ATRIBUICAO = 14,                /* ATRIBUICAO  */
  YYSYMBOL_TIPO = 15,                      /* TIPO  */
  YYSYMBOL_PROCEDURE = 16,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 17,                  /* FUNCTION  */
  YYSYMBOL_IGUAL = 18,                     /* IGUAL  */
  YYSYMBOL_MENOR = 19,                     /* MENOR  */
  YYSYMBOL_MENOR_IGUAL = 20,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR = 21,                     /* MAIOR  */
  YYSYMBOL_MAIOR_IGUAL = 22,               /* MAIOR_IGUAL  */
  YYSYMBOL_DIFERENTE = 23,                 /* DIFERENTE  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_VEZES = 28,                     /* VEZES  */
  YYSYMBOL_MENOS = 29,                     /* MENOS  */
  YYSYMBOL_MAIS = 30,                      /* MAIS  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_THEN = 32,                      /* THEN  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_DO = 35,                        /* DO  */
  YYSYMBOL_READ = 36,                      /* READ  */
  YYSYMBOL_WRITE = 37,                     /* WRITE  */
  YYSYMBOL_NUMERO = 38,                    /* NUMERO  */
  YYSYMBOL_VALOR_BOOL = 39,                /* VALOR_BOOL  */
  YYSYMBOL_LABEL = 40,                     /* LABEL  */
  YYSYMBOL_TYPE = 41,                      /* TYPE  */
  YYSYMBOL_ARRAY = 42,                     /* ARRAY  */
  YYSYMBOL_OF = 43,                        /* OF  */
  YYSYMBOL_GOTO = 44,                      /* GOTO  */
  YYSYMBOL_ABRE_COLCHETES = 45,            /* ABRE_COLCHETES  */
  YYSYMBOL_FECHA_COLCHETES = 46,           /* FECHA_COLCHETES  */
  YYSYMBOL_ABRE_CHAVES = 47,               /* ABRE_CHAVES  */
  YYSYMBOL_FECHA_CHAVES = 48,              /* FECHA_CHAVES  */
  YYSYMBOL_LOWER_THAN_ELSE = 49,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_programa = 51,                  /* programa  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_bloco = 53,                     /* bloco  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_55_3 = 55,                      /* $@3  */
  YYSYMBOL_parte_declara_vars = 56,        /* parte_declara_vars  */
  YYSYMBOL_57_4 = 57,                      /* $@4  */
  YYSYMBOL_declara_vars = 58,              /* declara_vars  */
  YYSYMBOL_declara_var = 59,               /* declara_var  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_tipo = 62,                      /* tipo  */
  YYSYMBOL_lista_id_var = 63,              /* lista_id_var  */
  YYSYMBOL_lista_idents = 64,              /* lista_idents  */
  YYSYMBOL_ident_params = 65,              /* ident_params  */
  YYSYMBOL_parte_declara_subrotinas = 66,  /* parte_declara_subrotinas  */
  YYSYMBOL_declara_procedimento = 67,      /* declara_procedimento  */
  YYSYMBOL_68_7 = 68,                      /* $@7  */
  YYSYMBOL_69_8 = 69,                      /* $@8  */
  YYSYMBOL_70_9 = 70,                      /* $@9  */
  YYSYMBOL_param_formais_ou_nada = 71,     /* param_formais_ou_nada  */
  YYSYMBOL_parte_param_formais = 72,       /* parte_param_formais  */
  YYSYMBOL_parametros = 73,                /* parametros  */
  YYSYMBOL_var_ou_nada = 74,               /* var_ou_nada  */
  YYSYMBOL_secao_param_formais = 75,       /* secao_param_formais  */
  YYSYMBOL_76_10 = 76,                     /* $@10  */
  YYSYMBOL_comando_composto = 77,          /* comando_composto  */
  YYSYMBOL_comandos = 78,                  /* comandos  */
  YYSYMBOL_79_11 = 79,                     /* $@11  */
  YYSYMBOL_comando = 80,                   /* comando  */
  YYSYMBOL_comando_sem_rotulo = 81,        /* comando_sem_rotulo  */
  YYSYMBOL_leitura = 82,                   /* leitura  */
  YYSYMBOL_leitura_itens = 83,             /* leitura_itens  */
  YYSYMBOL_item_leitura = 84,              /* item_leitura  */
  YYSYMBOL_escrita = 85,                   /* escrita  */
  YYSYMBOL_escrita_itens = 86,             /* escrita_itens  */
  YYSYMBOL_item_escrita = 87,              /* item_escrita  */
  YYSYMBOL_atribuicao_ou_procedimento = 88, /* atribuicao_ou_procedimento  */
  YYSYMBOL_89_12 = 89,                     /* $@12  */
  YYSYMBOL_atribuicao_continua = 90,       /* atribuicao_continua  */
  YYSYMBOL_91_13 = 91,                     /* $@13  */
  YYSYMBOL_chamada_de_procedimento = 92,   /* chamada_de_procedimento  */
  YYSYMBOL_93_14 = 93,                     /* $@14  */
  YYSYMBOL_94_15 = 94,                     /* $@15  */
  YYSYMBOL_procedimento_sem_parametros = 95, /* procedimento_sem_parametros  */
  YYSYMBOL_comando_condicional = 96,       /* comando_condicional  */
  YYSYMBOL_if_then = 97,                   /* if_then  */
  YYSYMBOL_98_16 = 98,                     /* $@16  */
  YYSYMBOL_cond_else = 99,                 /* cond_else  */
  YYSYMBOL_100_17 = 100,                   /* $@17  */
  YYSYMBOL_comando_repetitivo = 101,       /* comando_repetitivo  */
  YYSYMBOL_102_18 = 102,                   /* $@18  */
  YYSYMBOL_103_19 = 103,                   /* $@19  */
  YYSYMBOL_lista_expressoes = 104,         /* lista_expressoes  */
  YYSYMBOL_105_20 = 105,                   /* $@20  */
  YYSYMBOL_expressao = 106,                /* expressao  */
  YYSYMBOL_relacao = 107,                  /* relacao  */
  YYSYMBOL_expressao_simples = 108,        /* expressao_simples  */
  YYSYMBOL_mais_menos_ou_nada = 109,       /* mais_menos_ou_nada  */
  YYSYMBOL_mais_menos_or = 110,            /* mais_menos_or  */
  YYSYMBOL_termo = 111,                    /* termo  */
  YYSYMBOL_vezes_div_and = 112,            /* vezes_div_and  */
  YYSYMBOL_procedimento_ou_nada = 113,     /* procedimento_ou_nada  */
  YYSYMBOL_fator = 114,                    /* fator  */
  YYSYMBOL_115_21 = 115                    /* $@21  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,    93,   112,   124,   111,   146,   146,   156,
     161,   162,   166,   170,   166,   186,   191,   199,   209,   210,
     214,   225,   228,   234,   241,   273,   233,   297,   298,   302,
     306,   307,   312,   317,   324,   323,   341,   346,   345,   353,
     357,   366,   367,   368,   369,   370,   371,   372,   375,   378,
     379,   382,   396,   400,   401,   405,   414,   413,   432,   431,
     470,   471,   476,   495,   476,   514,   546,   555,   554,   572,
     571,   583,   589,   598,   588,   620,   619,   625,   633,   634,
     648,   649,   650,   651,   652,   653,   658,   674,   695,   696,
     697,   701,   702,   703,   708,   735,   739,   740,   741,   747,
     760,   768,   767,   861,   867,   873,   874
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM",
  "ABRE_PARENTESES", "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA",
  "DOIS_PONTOS", "PONTO", "T_BEGIN", "T_END", "VAR", "IDENT", "ATRIBUICAO",
  "TIPO", "PROCEDURE", "FUNCTION", "IGUAL", "MENOR", "MENOR_IGUAL",
  "MAIOR", "MAIOR_IGUAL", "DIFERENTE", "AND", "OR", "NOT", "DIV", "VEZES",
  "MENOS", "MAIS", "IF", "THEN", "ELSE", "WHILE", "DO", "READ", "WRITE",
  "NUMERO", "VALOR_BOOL", "LABEL", "TYPE", "ARRAY", "OF", "GOTO",
  "ABRE_COLCHETES", "FECHA_COLCHETES", "ABRE_CHAVES", "FECHA_CHAVES",
  "LOWER_THAN_ELSE", "$accept", "programa", "$@1", "bloco", "$@2", "$@3",
  "parte_declara_vars", "$@4", "declara_vars", "declara_var", "$@5", "$@6",
  "tipo", "lista_id_var", "lista_idents", "ident_params",
  "parte_declara_subrotinas", "declara_procedimento", "$@7", "$@8", "$@9",
  "param_formais_ou_nada", "parte_param_formais", "parametros",
  "var_ou_nada", "secao_param_formais", "$@10", "comando_composto",
  "comandos", "$@11", "comando", "comando_sem_rotulo", "leitura",
  "leitura_itens", "item_leitura", "escrita", "escrita_itens",
  "item_escrita", "atribuicao_ou_procedimento", "$@12",
  "atribuicao_continua", "$@13", "chamada_de_procedimento", "$@14", "$@15",
  "procedimento_sem_parametros", "comando_condicional", "if_then", "$@16",
  "cond_else", "$@17", "comando_repetitivo", "$@18", "$@19",
  "lista_expressoes", "$@20", "expressao", "relacao", "expressao_simples",
  "mais_menos_ou_nada", "mais_menos_or", "termo", "vezes_div_and",
  "procedimento_ou_nada", "fator", "$@21", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -106,     6,    24,  -106,    -4,    12,    11,  -106,    28,  -106,
      22,    11,    25,  -106,    36,  -106,    37,  -106,  -106,  -106,
      41,    45,  -106,    46,    48,    50,  -106,  -106,  -106,    13,
    -106,    -6,  -106,    51,    52,    58,  -106,    18,  -106,    59,
      61,  -106,    55,  -106,  -106,  -106,  -106,  -106,  -106,    35,
    -106,  -106,  -106,  -106,    57,  -106,  -106,     1,  -106,  -106,
    -106,    21,    -3,    18,    60,    18,  -106,    63,  -106,  -106,
      64,  -106,    67,  -106,    68,    69,  -106,  -106,  -106,    70,
    -106,    53,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,    18,    -3,    18,  -106,    -3,  -106,  -106,   -10,  -106,
    -106,  -106,    47,  -106,    49,  -106,  -106,    -6,    -6,  -106,
    -106,    11,    57,    25,    18,  -106,    -6,   -17,   -10,    73,
      75,  -106,  -106,  -106,  -106,    -3,    54,  -106,    60,  -106,
      18,  -106,  -106,    14,  -106,  -106,  -106,    18,  -106,  -106,
    -106,  -106,  -106,    -6,  -106,  -106,    52,    74,    77,    78,
    -106,  -106,  -106,  -106,    80,    18,  -106
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    20,     0,    19,
       0,     0,     9,    18,     0,     4,     0,     3,    22,    12,
       5,     8,    11,     0,     0,     0,    21,    10,    17,     0,
      23,    47,     6,     0,     0,    28,    56,    90,    72,     0,
       0,    42,    37,    39,    40,    43,    44,    41,    45,    71,
      46,    16,    15,    13,    33,    24,    27,    65,    89,    88,
      67,    78,     0,    90,     0,    90,    36,     0,    69,    66,
       0,    32,     0,    34,    31,     0,    58,    57,    60,     0,
      61,     0,    80,    82,    83,    84,    85,    81,    93,    92,
      91,    90,     0,    90,   101,     0,   103,   104,    87,    95,
      73,    51,     0,    50,     0,    54,    55,    47,    47,    14,
      29,     0,    33,     9,    90,    63,    47,    79,    86,     0,
     100,   106,    98,    97,    96,     0,     0,    48,     0,    52,
      90,    38,    70,     0,    30,    25,    59,    90,    68,   105,
      99,   102,    94,    47,    49,    53,     0,     0,     0,    75,
      74,    35,    26,    64,     0,    90,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,   -33,  -106,  -106,  -106,  -106,  -106,    66,
    -106,  -106,   -62,  -106,   -23,    79,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,   -21,  -106,    71,  -106,  -106,
     -15,  -105,  -106,  -106,   -35,  -106,  -106,   -36,  -106,  -106,
    -106,  -106,   -25,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,   -58,  -106,   -37,  -106,     7,  -106,
    -106,     9,  -106,  -106,   -93,  -106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    18,    25,    15,    16,    21,    22,
      23,    70,    53,    29,     8,     9,    20,    26,    35,    75,
     147,    55,    56,    72,    73,    74,   111,    41,    42,    67,
      43,    44,    45,   102,   103,    46,   104,   105,    47,    57,
      77,   114,    78,    79,   137,    80,    48,    49,    81,    69,
     108,    50,    63,   126,   148,   154,   106,    91,    61,    62,
      92,    98,   125,   141,    99,   120
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,    93,   121,   132,    31,   -62,     3,    36,    88,     5,
      94,   138,    89,    90,   122,    76,     6,   123,   124,    33,
      11,    34,   146,    95,     7,    37,   100,     4,    38,    12,
      39,    40,   142,    10,    11,    96,    97,    -7,   150,    82,
      83,    84,    85,    86,    87,    17,    88,    58,    59,    19,
      89,    90,   127,   128,   129,   130,   119,    24,   -12,    28,
      31,    30,    54,    64,    51,    65,    66,    52,    68,    71,
     107,   109,   110,   101,   115,   112,   113,   136,   139,   -62,
     135,   152,   153,   -77,   151,   116,   155,    27,   133,   143,
      13,   134,   131,   144,   145,   140,    32,   156,   117,     0,
     149,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149
};

static const yytype_int16 yycheck[] =
{
      37,     4,    95,   108,    10,     4,     0,    13,    25,    13,
      13,   116,    29,    30,    24,    14,     4,    27,    28,     6,
       6,     8,     8,    26,    13,    31,    63,     3,    34,     7,
      36,    37,   125,     5,     6,    38,    39,    12,   143,    18,
      19,    20,    21,    22,    23,     9,    25,    29,    30,    12,
      29,    30,     5,     6,     5,     6,    93,    16,    13,    13,
      10,    13,     4,     4,    13,     4,    11,    15,    33,    12,
       7,     7,     5,    13,     4,     7,     7,   114,     5,     4,
     113,     7,     5,     5,   146,    32,     6,    21,   111,    35,
      11,   112,   107,   128,   130,   120,    25,   155,    91,    -1,
     137,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,     3,    13,     4,    13,    64,    65,
       5,     6,     7,    65,    53,    56,    57,     9,    54,    12,
      66,    58,    59,    60,    16,    55,    67,    59,    13,    63,
      13,    10,    77,     6,     8,    68,    13,    31,    34,    36,
      37,    77,    78,    80,    81,    82,    85,    88,    96,    97,
     101,    13,    15,    62,     4,    71,    72,    89,    29,    30,
     106,   108,   109,   102,     4,     4,    11,    79,    33,    99,
      61,    12,    73,    74,    75,    69,    14,    90,    92,    93,
      95,    98,    18,    19,    20,    21,    22,    23,    25,    29,
      30,   107,   110,     4,    13,    26,    38,    39,   111,   114,
     106,    13,    83,    84,    86,    87,   106,     7,   100,     7,
       5,    76,     7,     7,    91,     4,    32,   108,   111,   106,
     115,   114,    24,    27,    28,   112,   103,     5,     6,     5,
       6,    80,    81,    64,    75,    53,   106,    94,    81,     5,
      92,   113,   114,    35,    84,    87,     8,    70,   104,   106,
      81,    62,     7,     5,   105,     6,   104
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    54,    55,    53,    57,    56,    56,
      58,    58,    60,    61,    59,    62,    63,    63,    64,    64,
      65,    66,    66,    68,    69,    70,    67,    71,    71,    72,
      73,    73,    74,    74,    76,    75,    77,    79,    78,    78,
      80,    81,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    84,    85,    86,    86,    87,    89,    88,    91,    90,
      90,    90,    93,    94,    92,    95,    96,    98,    97,   100,
      99,    99,   102,   103,   101,   105,   104,   104,   106,   106,
     107,   107,   107,   107,   107,   107,   108,   108,   109,   109,
     109,   110,   110,   110,   111,   111,   112,   112,   112,   113,
     113,   115,   114,   114,   114,   114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     1,     0,     0,     6,     1,     3,     1,     3,     1,
       1,     2,     0,     0,     0,     0,     9,     1,     0,     3,
       3,     1,     1,     0,     0,     5,     3,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       1,     1,     4,     3,     1,     1,     0,     3,     0,     3,
       1,     1,     0,     0,     5,     0,     2,     0,     5,     0,
       3,     0,     0,     0,     6,     0,     4,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     1,
       0,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       0,     0,     3,     1,     1,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 93 "compilador.y"
   {
      geraCodigo (NULL, "INPP");
      nivel_lexico = 0;
      rotulo_atual = 0;
      dentro_chamada_procedimento = 0;
   }
#line 1356 "compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 104 "compilador.y"
   {
      geraCodigo (NULL, "PARA");
   }
#line 1364 "compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 112 "compilador.y"
      {
         pushPilhaInt(&pilhaRotulos, rotulo_atual);

         sprintf(mepa_comand, "DSVS R%02d", rotulo_atual);
         geraCodigo(NULL, mepa_comand);
         rotulo_atual++;

         nivel_lexico++;
         num_procedimentos_proc_atual = 0;
      }
#line 1379 "compilador.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 124 "compilador.y"
      {
         pushPilhaInt(&pilhaProcs, num_procedimentos_proc_atual);

         nivel_lexico--;

         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(mepa_comand, "NADA");

         popPilhaInt(&pilhaRotulos);
      }
#line 1394 "compilador.tab.c"
    break;

  case 6: /* bloco: parte_declara_vars $@2 parte_declara_subrotinas $@3 comando_composto  */
#line 136 "compilador.y"
      {
         sprintf(mepa_comand, "DMEM %d", topoPilhaInt(&pilhaAmem));
         removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaAmem));
         geraCodigo(NULL, mepa_comand);
         popPilhaInt(&pilhaAmem);
      }
#line 1405 "compilador.tab.c"
    break;

  case 7: /* $@4: %empty  */
#line 146 "compilador.y"
   { 
      num_vars = 0; 
   }
#line 1413 "compilador.tab.c"
    break;

  case 8: /* parte_declara_vars: $@4 VAR declara_vars  */
#line 152 "compilador.y"
   {
      pushPilhaInt(&pilhaAmem, num_vars);
   }
#line 1421 "compilador.tab.c"
    break;

  case 9: /* parte_declara_vars: %empty  */
#line 156 "compilador.y"
      { pushPilhaInt(&pilhaAmem, 0); }
#line 1427 "compilador.tab.c"
    break;

  case 12: /* $@5: %empty  */
#line 166 "compilador.y"
   { quantidade_tipo_atual = 0; }
#line 1433 "compilador.tab.c"
    break;

  case 13: /* $@6: %empty  */
#line 170 "compilador.y"
   { 
      if ( (yyvsp[0].int_val) == TIPO_UNDEFINED_TYPE ){
         fprintf(stderr, "COMPILATION ERROR!!! Tipo indefinido\n");
         exit(1);
      }

      sprintf(mepa_comand, "AMEM %d", quantidade_tipo_atual); 
      geraCodigo(NULL, mepa_comand);

      atribuiTipoTabelaSimbolos(&ts, CAT_VARIAVEL, (yyvsp[0].int_val), quantidade_tipo_atual); 
   }
#line 1449 "compilador.tab.c"
    break;

  case 15: /* tipo: TIPO  */
#line 186 "compilador.y"
        { (yyval.int_val) = str2type(token); }
#line 1455 "compilador.tab.c"
    break;

  case 16: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 192 "compilador.y"
   { 
      conteudo.var.deslocamento = num_vars;
      Simbolo s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      num_vars++; quantidade_tipo_atual++;
   }
#line 1466 "compilador.tab.c"
    break;

  case 17: /* lista_id_var: IDENT  */
#line 200 "compilador.y"
   {
      conteudo.var.deslocamento = num_vars;
      Simbolo s = criaSimbolo(token, CAT_VARIAVEL, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      num_vars++; quantidade_tipo_atual++;      
   }
#line 1477 "compilador.tab.c"
    break;

  case 20: /* ident_params: IDENT  */
#line 215 "compilador.y"
   {
      strcpy(idents[num_params], token);
      lista_parametros[num_params].passagem = flag_referencia? PAS_REFERENCIA : PAS_COPIA;
      num_params++;
      num_params_section++;
   }
#line 1488 "compilador.tab.c"
    break;

  case 21: /* parte_declara_subrotinas: parte_declara_subrotinas declara_procedimento  */
#line 226 "compilador.y"
                        { num_procedimentos_proc_atual++; }
#line 1494 "compilador.tab.c"
    break;

  case 23: /* $@7: %empty  */
#line 234 "compilador.y"
   {
      strcpy(proc_nome, token);

      num_params = 0;
   }
#line 1504 "compilador.tab.c"
    break;

  case 24: /* $@8: %empty  */
#line 241 "compilador.y"
   {
      tipoConteudo conteudo;

      conteudo.proc.rotulo = rotulo_atual;

      char rotulo[128];

      sprintf(rotulo, "R%02d", rotulo_atual);
      sprintf(mepa_comand, "ENPR %d", nivel_lexico);
      geraCodigo(rotulo, mepa_comand);

      conteudo.proc.tipoRetorno = TIPO_UNDEFINED_TYPE;
      conteudo.proc.qtdParametros = num_params;

      // copia lista de paramtros para a tabela de simbolos 
      memcpy(conteudo.proc.lista, lista_parametros, sizeof(parametro) * num_params);

      Simbolo s = criaSimbolo(proc_nome, CAT_PROCEDIMENTO, nivel_lexico, conteudo);
      pushTabelaSimbolos(&ts, s);
      
      // coloca params com deslocamento correto na tabela de simbolos
      for (int i = num_params-1; i >= 0; --i){
         lista_simbolos[i].conteudo.param.deslocamento = -4 + (i - (num_params - 1));
         pushTabelaSimbolos(&ts, lista_simbolos[i]);
      }

      rotulo_atual++;
      
      pushPilhaInt(&pilhaAmem, num_params);
   }
#line 1539 "compilador.tab.c"
    break;

  case 25: /* $@9: %empty  */
#line 273 "compilador.y"
   {
      removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaAmem));
      sprintf(mepa_comand, "RTPR %d, %d", nivel_lexico, topoPilhaInt(&pilhaAmem));
      geraCodigo(NULL, mepa_comand);

      popPilhaInt(&pilhaAmem);
      removeNTabelaSimbolos(&ts, topoPilhaInt(&pilhaProcs));
      popPilhaInt(&pilhaProcs);
   }
#line 1553 "compilador.tab.c"
    break;

  case 32: /* var_ou_nada: VAR  */
#line 313 "compilador.y"
      {
         flag_referencia = 1;
      }
#line 1561 "compilador.tab.c"
    break;

  case 33: /* var_ou_nada: %empty  */
#line 317 "compilador.y"
      { 
         flag_referencia = 0;
      }
#line 1569 "compilador.tab.c"
    break;

  case 34: /* $@10: %empty  */
#line 324 "compilador.y"
      { 
         num_params_section = 0; 
      }
#line 1577 "compilador.tab.c"
    break;

  case 35: /* secao_param_formais: var_ou_nada $@10 lista_idents DOIS_PONTOS tipo  */
#line 328 "compilador.y"
      {
         for (int i = num_params - num_params_section; i < num_params; ++i){
            tipoConteudo conteudo;
            conteudo.param = lista_parametros[i];
            conteudo.param.tipo = (yyvsp[0].int_val);
            lista_simbolos[i] = criaSimbolo(idents[i], CAT_PARAMETRO, nivel_lexico, conteudo);
         }

         // atribuiTipoTabelaSimbolos(&ts, CAT_PARAMETRO, $4, num_params_section);
      }
#line 1592 "compilador.tab.c"
    break;

  case 37: /* $@11: %empty  */
#line 346 "compilador.y"
      { 
         if ( strcmp(token,";") ){ 
            fprintf(stderr, "COMPILATION ERROR!!! Falta de ; apos comando\n");
            exit(1);
         }
      }
#line 1603 "compilador.tab.c"
    break;

  case 51: /* item_leitura: IDENT  */
#line 383 "compilador.y"
   {
      geraCodigo(NULL, "LEIT");
      Simbolo *s = buscaTabelaSimbolos(&ts, token);
      if ( s == NULL || s->categoria == CAT_PROCEDIMENTO ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
         exit(1);
      }

      sprintf(mepa_comand, "ARMZ %d, %d", s->nivel, s->conteudo.var.deslocamento);
      geraCodigo(NULL, mepa_comand);
   }
#line 1619 "compilador.tab.c"
    break;

  case 55: /* item_escrita: expressao  */
#line 406 "compilador.y"
   {
      geraCodigo(NULL, "IMPR");
   }
#line 1627 "compilador.tab.c"
    break;

  case 56: /* $@12: %empty  */
#line 414 "compilador.y"
   {
      s_var_ou_proc = buscaTabelaSimbolos(&ts, token);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada %s\n", token);
         exit(1);
      }

      pushPilhaSimbolos(&pilhaVarAEsquerda, s_var_ou_proc);
   }
#line 1642 "compilador.tab.c"
    break;

  case 57: /* atribuicao_ou_procedimento: IDENT $@12 atribuicao_continua  */
#line 425 "compilador.y"
   {
      popPilhaSimbolos(&pilhaVarAEsquerda);
   }
#line 1650 "compilador.tab.c"
    break;

  case 58: /* $@13: %empty  */
#line 432 "compilador.y"
      { 
         flag_atribui = 1; 
      }
#line 1658 "compilador.tab.c"
    break;

  case 59: /* atribuicao_continua: ATRIBUICAO $@13 expressao  */
#line 436 "compilador.y"
      {
         flag_atribui = 0;

         s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

        switch (s_var_ou_proc->categoria){
            case CAT_VARIAVEL:
                sprintf(mepa_comand, "ARMZ %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
            break;
            
            case CAT_PARAMETRO:
                if (s_var_ou_proc->conteudo.param.passagem == PAS_COPIA){
                    sprintf(mepa_comand, "ARMZ %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
                }
                else if (s_var_ou_proc->conteudo.param.passagem == PAS_REFERENCIA){
                    sprintf(mepa_comand, "ARMI %d, %d", s_var_ou_proc->nivel, s_var_ou_proc->conteudo.var.deslocamento);
                }
                else {
                    fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametror nao especificada\n");
                    exit(1);
                }
            break;

            // case CAT_FUNCAO:
            // break;

            default:
                fprintf(stderr, "COMPILATION ERROR!!! procedimento tratado como variavel\n");
                exit(1);
            break;
        }

         geraCodigo(NULL, mepa_comand);
      }
#line 1697 "compilador.tab.c"
    break;

  case 62: /* $@14: %empty  */
#line 476 "compilador.y"
   {
      Simbolo *s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
         exit(1);
      }

      s_atribuicao = s_var_ou_proc;
      memcpy(&proc_atual, s_var_ou_proc, sizeof(Simbolo));

      if (proc_atual.categoria == CAT_FUNCAO){
         geraCodigo(NULL, "AMEM 1");
      }

      sprintf(proc_nome, "CHPR R%02d", s_var_ou_proc->conteudo.proc.rotulo);
   }
#line 1719 "compilador.tab.c"
    break;

  case 63: /* $@15: %empty  */
#line 495 "compilador.y"
   {
      num_param_chamada_atual = 0;
      dentro_chamada_procedimento++;
   }
#line 1728 "compilador.tab.c"
    break;

  case 64: /* chamada_de_procedimento: $@14 ABRE_PARENTESES $@15 lista_expressoes FECHA_PARENTESES  */
#line 501 "compilador.y"
   {
      dentro_chamada_procedimento--;

      if (num_param_chamada_atual != proc_atual.conteudo.proc.qtdParametros){
         fprintf(stderr, "COMPILATION ERROR!!! numero de parametros divergentes\n");
         exit(1);
      }

      geraCodigo(NULL, proc_nome);
   }
#line 1743 "compilador.tab.c"
    break;

  case 65: /* procedimento_sem_parametros: %empty  */
#line 514 "compilador.y"
   {
      Simbolo *s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

      if ( s_var_ou_proc == NULL ){
         fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
         exit(1);
      }

      if ( s_var_ou_proc->categoria != CAT_PROCEDIMENTO ){
         fprintf(stderr, "COMPILATION ERROR!!! %s nao eh um procedimento\n", token);
         exit(1);
      }

      sprintf(mepa_comand, "CHPR R%02d", s_var_ou_proc->conteudo.proc.rotulo);
      geraCodigo(NULL, mepa_comand);
   }
#line 1764 "compilador.tab.c"
    break;

  case 66: /* comando_condicional: if_then cond_else  */
#line 547 "compilador.y"
   {
      popPilhaInt(&pilhaRotulos);
      rotulo_atual -= 2;
   }
#line 1773 "compilador.tab.c"
    break;

  case 67: /* $@16: %empty  */
#line 555 "compilador.y"
      {
         sprintf(mepa_comand, "DSVF R%02d", rotulo_atual);
         geraCodigo(NULL, mepa_comand);

         pushPilhaInt(&pilhaRotulos, rotulo_atual);
         rotulo_atual += 2;
      }
#line 1785 "compilador.tab.c"
    break;

  case 68: /* if_then: IF expressao $@16 THEN comando_sem_rotulo  */
#line 564 "compilador.y"
      {
         sprintf(mepa_comand, "DSVS R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(NULL, mepa_comand);
      }
#line 1794 "compilador.tab.c"
    break;

  case 69: /* $@17: %empty  */
#line 572 "compilador.y"
      {
         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(mepa_comand, "NADA");
      }
#line 1803 "compilador.tab.c"
    break;

  case 70: /* cond_else: ELSE $@17 comando_sem_rotulo  */
#line 578 "compilador.y"
      {
      sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos) + 1);
      geraCodigo(mepa_comand, "NADA");
   }
#line 1812 "compilador.tab.c"
    break;

  case 72: /* $@18: %empty  */
#line 589 "compilador.y"
      {
         pushPilhaInt(&pilhaRotulos, rotulo_atual);

         sprintf(mepa_comand, "R%02d", rotulo_atual);
         geraCodigo(mepa_comand, "NADA");

         rotulo_atual += 2;
      }
#line 1825 "compilador.tab.c"
    break;

  case 73: /* $@19: %empty  */
#line 598 "compilador.y"
      {
         sprintf(mepa_comand, "DSVF R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(NULL, mepa_comand);
      }
#line 1834 "compilador.tab.c"
    break;

  case 74: /* comando_repetitivo: WHILE $@18 expressao $@19 DO comando_sem_rotulo  */
#line 604 "compilador.y"
      {
         sprintf(mepa_comand, "DSVS R%02d", topoPilhaInt(&pilhaRotulos));
         geraCodigo(NULL, mepa_comand);

         sprintf(mepa_comand, "R%02d", topoPilhaInt(&pilhaRotulos) + 1);
         geraCodigo(mepa_comand, "NADA");

         popPilhaInt(&pilhaRotulos);

         rotulo_atual -= 2;
      }
#line 1850 "compilador.tab.c"
    break;

  case 75: /* $@20: %empty  */
#line 620 "compilador.y"
   {
      num_param_chamada_atual++;
   }
#line 1858 "compilador.tab.c"
    break;

  case 77: /* lista_expressoes: expressao  */
#line 626 "compilador.y"
   {
      num_param_chamada_atual++;
   }
#line 1866 "compilador.tab.c"
    break;

  case 78: /* expressao: expressao_simples  */
#line 633 "compilador.y"
                  { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1872 "compilador.tab.c"
    break;

  case 79: /* expressao: expressao_simples relacao expressao_simples  */
#line 635 "compilador.y"
   { 
      if ( (yyvsp[-2].int_val) != (yyvsp[0].int_val) ){
         fprintf(stderr, "COMPILATION ERROR!!! Comparacao de tipos divergentes\n");
         exit(1);
      }

      geraCodigo(NULL, (yyvsp[-1].str));
      (yyval.int_val) = TIPO_BOOLEAN;
   }
#line 1886 "compilador.tab.c"
    break;

  case 80: /* relacao: IGUAL  */
#line 648 "compilador.y"
                  { (yyval.str) = "CMIG"; }
#line 1892 "compilador.tab.c"
    break;

  case 81: /* relacao: DIFERENTE  */
#line 649 "compilador.y"
                  { (yyval.str) = "CMDG"; }
#line 1898 "compilador.tab.c"
    break;

  case 82: /* relacao: MENOR  */
#line 650 "compilador.y"
                  { (yyval.str) = "CMME"; }
#line 1904 "compilador.tab.c"
    break;

  case 83: /* relacao: MENOR_IGUAL  */
#line 651 "compilador.y"
                  { (yyval.str) = "CMEG"; }
#line 1910 "compilador.tab.c"
    break;

  case 84: /* relacao: MAIOR  */
#line 652 "compilador.y"
                  { (yyval.str) = "CMMA"; }
#line 1916 "compilador.tab.c"
    break;

  case 85: /* relacao: MAIOR_IGUAL  */
#line 653 "compilador.y"
                  { (yyval.str) = "CMAG"; }
#line 1922 "compilador.tab.c"
    break;

  case 86: /* expressao_simples: expressao_simples mais_menos_or termo  */
#line 659 "compilador.y"
   {
      if ( !strcmp("MAIS", (yyvsp[-1].str)) && (yyvsp[0].int_val) == TIPO_INTEGER ){
         geraCodigo(NULL, "SOMA");
         (yyval.int_val) = TIPO_INTEGER;
      }
      else if ( !strcmp("MENOS", (yyvsp[-1].str)) && (yyvsp[0].int_val) == TIPO_INTEGER ){
         geraCodigo(NULL, "SUBT");
         (yyval.int_val) = TIPO_INTEGER;
      }
      else if ( !strcmp("OR", (yyvsp[-1].str)) && (yyvsp[0].int_val) == TIPO_BOOLEAN ){
         geraCodigo(NULL, "DISJ");
         (yyval.int_val) = TIPO_BOOLEAN;
      }
   }
#line 1941 "compilador.tab.c"
    break;

  case 87: /* expressao_simples: mais_menos_ou_nada termo  */
#line 675 "compilador.y"
   {
      if ( !strcmp("NADA", (yyvsp[-1].str)) ){ 
         (yyval.int_val) = (yyvsp[0].int_val); 
      }
      else if ( (yyvsp[0].int_val) == TIPO_INTEGER ){
         if ( !strcmp("MENOS", (yyvsp[-1].str)) ){ 
            geraCodigo(NULL, "INVR");
         }

         (yyval.int_val) = TIPO_INTEGER;
      }
      else {
         fprintf(stderr, "COMPILATION ERROR!!!"
            " Operadores aritmeticos aplicados a tipo booleano\n");
         exit(1);
      }
   }
#line 1963 "compilador.tab.c"
    break;

  case 88: /* mais_menos_ou_nada: MAIS  */
#line 695 "compilador.y"
           { (yyval.str) = "MAIS";  }
#line 1969 "compilador.tab.c"
    break;

  case 89: /* mais_menos_ou_nada: MENOS  */
#line 696 "compilador.y"
           { (yyval.str) = "MENOS"; }
#line 1975 "compilador.tab.c"
    break;

  case 90: /* mais_menos_ou_nada: %empty  */
#line 697 "compilador.y"
           { (yyval.str) = "NADA";  }
#line 1981 "compilador.tab.c"
    break;

  case 91: /* mais_menos_or: MAIS  */
#line 701 "compilador.y"
           { (yyval.str) = "MAIS";  }
#line 1987 "compilador.tab.c"
    break;

  case 92: /* mais_menos_or: MENOS  */
#line 702 "compilador.y"
           { (yyval.str) = "MENOS"; }
#line 1993 "compilador.tab.c"
    break;

  case 93: /* mais_menos_or: OR  */
#line 703 "compilador.y"
           { (yyval.str) = "OR";    }
#line 1999 "compilador.tab.c"
    break;

  case 94: /* termo: termo vezes_div_and fator  */
#line 709 "compilador.y"
   {
      if ( TIPO_BOOLEAN == (yyvsp[0].int_val) ){
         if ( !strcmp("CONJ", (yyvsp[-1].str)) ){
            geraCodigo(NULL, "CONJ");
         }
         else {
            fprintf(stderr, "COMPILATION ERROR!!!"
               " Operacao invalida para tipo booleano\n");
         }
      }
      else if ( TIPO_INTEGER == (yyvsp[0].int_val) ){
         if ( !strcmp("MULT", (yyvsp[-1].str)) ){
            geraCodigo(NULL, "MULT");
         }
         else if ( !strcmp("DIVI", (yyvsp[-1].str)) ){
            geraCodigo(NULL, "DIVI");
         }
         else {
            fprintf(stderr, "COMPILATION ERROR!!!"
               " Operacao invalida para tipo integer\n");

         }
      }

      (yyval.int_val) = (yyvsp[0].int_val);
   }
#line 2030 "compilador.tab.c"
    break;

  case 95: /* termo: fator  */
#line 735 "compilador.y"
           { (yyval.int_val) = (yyvsp[0].int_val); }
#line 2036 "compilador.tab.c"
    break;

  case 96: /* vezes_div_and: VEZES  */
#line 739 "compilador.y"
         { (yyval.str) = "MULT"; }
#line 2042 "compilador.tab.c"
    break;

  case 97: /* vezes_div_and: DIV  */
#line 740 "compilador.y"
         { (yyval.str) = "DIVI"; }
#line 2048 "compilador.tab.c"
    break;

  case 98: /* vezes_div_and: AND  */
#line 741 "compilador.y"
         { (yyval.str) = "CONJ"; }
#line 2054 "compilador.tab.c"
    break;

  case 99: /* procedimento_ou_nada: chamada_de_procedimento  */
#line 748 "compilador.y"
      {
                     // run ../arquivos-aula/aula11.pas
         s_var_ou_proc = topoPilhaSimbolos(&pilhaVarAEsquerda);

         if ( s_var_ou_proc == NULL ){
            fprintf(stderr, "COMPILATION ERROR!!! variavel ou procedimento inexistente %s\n", token);
            exit(1);
         }

         popPilhaSimbolos(&pilhaVarAEsquerda);
      }
#line 2070 "compilador.tab.c"
    break;

  case 100: /* procedimento_ou_nada: %empty  */
#line 760 "compilador.y"
      {
         s_ptr = topoPilhaSimbolos(&pilhaVarAEsquerda);
         popPilhaSimbolos(&pilhaVarAEsquerda);
      }
#line 2079 "compilador.tab.c"
    break;

  case 101: /* $@21: %empty  */
#line 768 "compilador.y"
         {
            s_ptr = buscaTabelaSimbolos(&ts, token);

            if ( s_ptr == NULL ){
               fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
               exit(1);
            }

            pushPilhaSimbolos(&pilhaVarAEsquerda, s_ptr);
         }
#line 2094 "compilador.tab.c"
    break;

  case 102: /* fator: IDENT $@21 procedimento_ou_nada  */
#line 779 "compilador.y"
         {
            if ( s_ptr == NULL ){
               fprintf(stderr, "COMPILATION ERROR!!! variavel nao declarada\n");
               exit(1);
            }

            int flag_imprime = 1;

            switch (s_ptr->categoria){
               case CAT_VARIAVEL:
                  (yyval.int_val) = s_ptr->conteudo.var.tipo;

                  if (dentro_chamada_procedimento){

                     int qtdParametros = s_var_ou_proc->conteudo.proc.qtdParametros;

                     if (num_param_chamada_atual > qtdParametros){
                        fprintf(stderr, "COMPILATION ERROR!!! excesso de parametros em funcao\n");
                        exit(1);
                     }

                     if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_REFERENCIA)
                        sprintf(mepa_comand, "CREN %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);

                     else if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_COPIA)
                        sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);

                     else {
                        fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametro nao identificada\n");
                        exit(1);
                     }
                  }
                  else if ( s_var_ou_proc != NULL && s_var_ou_proc->categoria != CAT_FUNCAO)
                     sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);
                 
                  else if (flag_atribui && (s_var_ou_proc != NULL && s_var_ou_proc->categoria == CAT_FUNCAO) && s_atribuicao->categoria != CAT_FUNCAO)
                     sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.var.deslocamento);
                 
                  else {
                     flag_imprime = 0;
                  }

                  break;

               case CAT_PARAMETRO:
                  (yyval.int_val) = s_ptr->conteudo.param.tipo;

                  switch (s_ptr->conteudo.param.passagem){
                     case PAS_COPIA:
                        sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        break;

                     case PAS_REFERENCIA:

                        if (s_var_ou_proc->conteudo.proc.lista[num_param_chamada_atual].passagem == PAS_REFERENCIA){
                           sprintf(mepa_comand, "CRVL %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        }
                        else {
                           sprintf(mepa_comand, "CRVI %d, %d", s_ptr->nivel, s_ptr->conteudo.param.deslocamento);
                        }
                        break;

                     default:
                        fprintf(stderr, "COMPILATION ERROR!!! tipo de passagem de parametro nao identificada\n");
                        exit(1);
                        break;
                  }
                  break;

               case CAT_PROCEDIMENTO:
                  fprintf(stderr, "COMPILATION ERROR!!! procedimento tratado como variavel\n");
                  break;

               default:
                  flag_imprime = 0;
                  break;
            }
            
            if ( flag_imprime ){
               geraCodigo(NULL, mepa_comand);
            }
         }
#line 2181 "compilador.tab.c"
    break;

  case 103: /* fator: NUMERO  */
#line 862 "compilador.y"
         { 
            (yyval.int_val) = TIPO_INTEGER;
            sprintf(mepa_comand, "CRCT %d", atoi(token)); 
            geraCodigo(NULL, mepa_comand);
         }
#line 2191 "compilador.tab.c"
    break;

  case 104: /* fator: VALOR_BOOL  */
#line 868 "compilador.y"
         { 
            (yyval.int_val) = TIPO_BOOLEAN; 
            sprintf(mepa_comand, "CRCT %d", !strcmp(token, "True") ? 1 : 0);
            geraCodigo(NULL, mepa_comand);
         }
#line 2201 "compilador.tab.c"
    break;

  case 105: /* fator: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 873 "compilador.y"
                                                   { (yyval.int_val) = (yyvsp[-1].int_val); }
#line 2207 "compilador.tab.c"
    break;

  case 106: /* fator: NOT fator  */
#line 875 "compilador.y"
         {
            if ( (yyvsp[0].int_val) != TIPO_BOOLEAN ){
               fprintf(stderr, "COMPILATION ERROR!!!"
                  " Operador NOT aplicado a tipo nao booleano\n");
               exit(1);
            }

            (yyval.int_val) = TIPO_BOOLEAN;
            geraCodigo(NULL, "NEGA");
         }
#line 2222 "compilador.tab.c"
    break;


#line 2226 "compilador.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 908 "compilador.y"


int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   inicializaTabelaSimbolos(&ts);
   inicializaTabelaSimbolos(&pilhaAtribuicao);
   inicializaPilhaInt(&pilhaRotulos);
   inicializaPilhaInt(&pilhaAmem);
   inicializaPilhaInt(&pilhaProcs);
   inicializaPilhaSimbolos(&pilhaVarAEsquerda);

   yyin=fp;
   yyparse();

   destroiPilhaInt(&pilhaRotulos);
   destroiPilhaInt(&pilhaAmem);
   destroiPilhaInt(&pilhaProcs);
   destroiPilhaSimbolos(&pilhaVarAEsquerda);

   return 0;
}


// gere a regra sintatica para o comando de atribuicao




