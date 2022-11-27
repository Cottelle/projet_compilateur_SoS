/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "p.y"

#include<stdio.h>
extern int yylex(void);
void yyerror(const char *msg);
    

#line 78 "p.tab.c"

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

#include "p.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_entier = 3,                     /* entier  */
  YYSYMBOL_id = 4,                         /* id  */
  YYSYMBOL_mot = 5,                        /* mot  */
  YYSYMBOL_declare = 6,                    /* declare  */
  YYSYMBOL_if_ = 7,                        /* if_  */
  YYSYMBOL_then = 8,                       /* then  */
  YYSYMBOL_elif = 9,                       /* elif  */
  YYSYMBOL_else_ = 10,                     /* else_  */
  YYSYMBOL_fi = 11,                        /* fi  */
  YYSYMBOL_for_ = 12,                      /* for_  */
  YYSYMBOL_do_ = 13,                       /* do_  */
  YYSYMBOL_done = 14,                      /* done  */
  YYSYMBOL_in = 15,                        /* in  */
  YYSYMBOL_while_ = 16,                    /* while_  */
  YYSYMBOL_until = 17,                     /* until  */
  YYSYMBOL_case_ = 18,                     /* case_  */
  YYSYMBOL_esac = 19,                      /* esac  */
  YYSYMBOL_echo = 20,                      /* echo  */
  YYSYMBOL_read_ = 21,                     /* read_  */
  YYSYMBOL_return_ = 22,                   /* return_  */
  YYSYMBOL_exit_ = 23,                     /* exit_  */
  YYSYMBOL_chaine = 24,                    /* chaine  */
  YYSYMBOL_test = 25,                      /* test  */
  YYSYMBOL_expr = 26,                      /* expr  */
  YYSYMBOL_local = 27,                     /* local  */
  YYSYMBOL_to = 28,                        /* to  */
  YYSYMBOL_ta = 29,                        /* ta  */
  YYSYMBOL_teq = 30,                       /* teq  */
  YYSYMBOL_tne = 31,                       /* tne  */
  YYSYMBOL_tgt = 32,                       /* tgt  */
  YYSYMBOL_tge = 33,                       /* tge  */
  YYSYMBOL_tlt = 34,                       /* tlt  */
  YYSYMBOL_tle = 35,                       /* tle  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* '='  */
  YYSYMBOL_38_ = 38,                       /* '['  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_41_ = 41,                       /* '\''  */
  YYSYMBOL_42_ = 42,                       /* '"'  */
  YYSYMBOL_43_ = 43,                       /* '|'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '$'  */
  YYSYMBOL_46_ = 46,                       /* '{'  */
  YYSYMBOL_47_ = 47,                       /* '}'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* '!'  */
  YYSYMBOL_50_ = 50,                       /* '?'  */
  YYSYMBOL_51_ = 51,                       /* '-'  */
  YYSYMBOL_52_n_ = 52,                     /* 'n'  */
  YYSYMBOL_53_z_ = 53,                     /* 'z'  */
  YYSYMBOL_54_ = 54,                       /* '+'  */
  YYSYMBOL_55_ = 55,                       /* '/'  */
  YYSYMBOL_56_ = 56,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_PROGRAMME = 58,                 /* PROGRAMME  */
  YYSYMBOL_LISTE_INTRSUCTIONS = 59,        /* LISTE_INTRSUCTIONS  */
  YYSYMBOL_INSTRUCTION = 60,               /* INSTRUCTION  */
  YYSYMBOL_ELSE_PART = 61,                 /* ELSE_PART  */
  YYSYMBOL_LISTE_CAS = 62,                 /* LISTE_CAS  */
  YYSYMBOL_FILTRE = 63,                    /* FILTRE  */
  YYSYMBOL_LISTE_OPERANDES = 64,           /* LISTE_OPERANDES  */
  YYSYMBOL_CONCATENATION = 65,             /* CONCATENATION  */
  YYSYMBOL_TEST_BLOC = 66,                 /* TEST_BLOC  */
  YYSYMBOL_TEST_EXPR = 67,                 /* TEST_EXPR  */
  YYSYMBOL_TEST_EXPR2 = 68,                /* TEST_EXPR2  */
  YYSYMBOL_TEST_EXPR3 = 69,                /* TEST_EXPR3  */
  YYSYMBOL_TEST_INSTRUCTION = 70,          /* TEST_INSTRUCTION  */
  YYSYMBOL_OPERANDE = 71,                  /* OPERANDE  */
  YYSYMBOL_OPERATEUR1 = 72,                /* OPERATEUR1  */
  YYSYMBOL_OPERATEUR2 = 73,                /* OPERATEUR2  */
  YYSYMBOL_SOMME_ENTIER = 74,              /* SOMME_ENTIER  */
  YYSYMBOL_PRODUIT_ENTIER = 75,            /* PRODUIT_ENTIER  */
  YYSYMBOL_OPERANDE_ENTIER = 76,           /* OPERANDE_ENTIER  */
  YYSYMBOL_PLUS_MOINS = 77,                /* PLUS_MOINS  */
  YYSYMBOL_FOIS_DIV_MOD = 78,              /* FOIS_DIV_MOD  */
  YYSYMBOL_DECLARATION_FONTION = 79,       /* DECLARATION_FONTION  */
  YYSYMBOL_DECL_LOC = 80,                  /* DECL_LOC  */
  YYSYMBOL_APPEL_FONCTION = 81,            /* APPEL_FONCTION  */
  YYSYMBOL_ID = 82                         /* ID  */
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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   316

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  213

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
       2,     2,     2,    49,    42,     2,    45,    56,     2,    41,
      48,    40,    44,    54,     2,    51,     2,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
       2,    37,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    53,    46,    43,    47,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    21,    21,    24,    25,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    48,    49,    50,    53,    54,    57,    58,
      59,    60,    61,    62,    65,    66,    67,    70,    71,    74,
      77,    78,    81,    82,    85,    86,    87,    88,    91,    92,
      93,    94,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   110,   111,   115,   116,   117,   118,   119,
     120,   123,   124,   127,   128,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   142,   143,   146,   147,   148,   151,
     155,   156,   159,   160,   162,   163
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
  "\"end of file\"", "error", "\"invalid token\"", "entier", "id", "mot",
  "declare", "if_", "then", "elif", "else_", "fi", "for_", "do_", "done",
  "in", "while_", "until", "case_", "esac", "echo", "read_", "return_",
  "exit_", "chaine", "test", "expr", "local", "to", "ta", "teq", "tne",
  "tgt", "tge", "tlt", "tle", "';'", "'='", "'['", "']'", "')'", "'\\''",
  "'\"'", "'|'", "'*'", "'$'", "'{'", "'}'", "'('", "'!'", "'?'", "'-'",
  "'n'", "'z'", "'+'", "'/'", "'%'", "$accept", "PROGRAMME",
  "LISTE_INTRSUCTIONS", "INSTRUCTION", "ELSE_PART", "LISTE_CAS", "FILTRE",
  "LISTE_OPERANDES", "CONCATENATION", "TEST_BLOC", "TEST_EXPR",
  "TEST_EXPR2", "TEST_EXPR3", "TEST_INSTRUCTION", "OPERANDE", "OPERATEUR1",
  "OPERATEUR2", "SOMME_ENTIER", "PRODUIT_ENTIER", "OPERANDE_ENTIER",
  "PLUS_MOINS", "FOIS_DIV_MOD", "DECLARATION_FONTION", "DECL_LOC",
  "APPEL_FONCTION", "ID", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     287,   -74,   -74,    26,    13,    26,    13,    13,    29,   116,
      26,    38,    38,    45,    46,   -74,   -74,   -74,   172,    55,
      22,   108,    49,   105,   122,   -74,   -74,   -74,   -74,    62,
     136,   123,    29,   -74,    99,   -74,     4,    38,   -74,   -74,
     -74,    33,   -74,   -74,   287,    29,    38,   118,    29,   167,
      22,    93,   160,   129,   166,   159,   -74,   -74,   281,    29,
     287,   287,   116,   287,   287,   -74,   -74,    26,    98,   -74,
     149,    26,   -74,    38,   -74,    26,    60,   142,   -74,   -74,
       6,   -74,    29,   -74,   175,   161,   177,     7,    22,   -74,
     -74,   -74,    29,   169,   -74,    22,    22,   -74,   -74,   -74,
     -74,   -74,   -74,    29,    29,    19,    25,   176,    71,    77,
     121,    38,   178,   116,   -74,   195,   198,   -74,   104,   162,
     125,   184,   154,   -74,    38,   -74,   -74,   -74,    38,   -74,
      26,   192,   -74,   -74,   -74,   115,    29,    29,   159,   -74,
     -74,    13,   287,   219,   -74,   287,   -74,   -74,    38,   -74,
      88,   -74,   190,   193,   -74,   168,   287,    39,    12,   -74,
      38,   -74,   142,   -74,   157,    29,   263,   -74,    29,   224,
      46,   -74,   113,   197,   -74,   -74,   -74,   287,   204,   -74,
     210,   206,   211,    38,   -74,    29,    26,    43,   287,   -74,
     205,   215,   221,   213,   209,   214,   227,   216,   -74,    19,
     -74,   242,   -74,   -74,   -74,   -74,   225,    29,   -74,   -74,
     -74,   179,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    21,     0,     2,     4,    17,    20,    93,     0,
       0,     0,     0,     0,     0,    55,    56,    54,    60,     0,
       0,     0,    14,    35,    15,    81,     0,     0,    85,    84,
      19,     0,    22,     1,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,    39,    41,    43,    46,    38,     0,
       0,     0,     0,     0,     0,    57,    58,     0,     0,    59,
       0,     0,    34,     0,    77,     0,     0,    72,    74,    82,
       0,     3,     5,    38,     0,     0,     0,     0,     0,    47,
      63,    64,     0,     0,    37,     0,     0,    65,    66,    67,
      68,    69,    70,     0,    50,    25,     0,     0,     0,     0,
       0,     0,     0,    93,    28,     0,     0,    33,     0,     0,
       0,     0,     0,    83,     0,    86,    87,    88,     0,    80,
       0,     0,    91,     7,    44,     0,    48,     0,    40,    42,
      51,     0,     0,     0,     9,     0,    11,    12,     0,    52,
       0,    62,     0,     0,    13,     0,     0,     0,     0,    16,
       0,    75,    71,    73,     0,     0,     0,    45,    49,     0,
      24,     8,     0,     0,    61,    29,    30,     0,     0,    31,
       0,     0,     0,     0,    78,     6,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    25,
      53,     0,    27,    32,    36,    76,     0,     0,    23,    26,
      79,     0,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -41,   -36,    72,   -74,   155,    -4,   -43,    11,
     -29,   181,   186,   223,    -8,   -74,   -74,   185,   153,     2,
     -73,   -74,   -74,   -74,   220,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    13,    14,    15,   143,   118,   119,    48,    53,    21,
      54,    55,    56,    57,    94,    59,   103,    76,    77,    78,
      41,   128,    16,   166,    17,    18
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    33,    82,   124,    19,    32,    22,    74,    81,   129,
      33,    34,    58,    40,    42,    35,   104,    23,    24,   105,
     106,    87,   108,   109,    72,    25,    26,    27,   141,   142,
       1,     2,    25,    26,    27,    95,    79,    83,    20,   144,
      72,    35,    58,    58,   179,    43,    28,   134,    84,   136,
      75,    83,   130,    28,    33,    44,   181,    36,   107,   135,
      37,    44,    61,    38,    62,    65,    39,    29,   110,   113,
      50,    51,   120,    52,    29,   121,   122,   124,    80,    44,
      58,   180,    44,    36,    83,   146,    37,    58,    58,    38,
     198,   147,    39,    49,   168,   140,    25,    26,    27,    72,
     123,   170,     1,     2,   172,    33,    66,    44,    67,   114,
      68,    38,    69,    44,    39,   178,    60,    28,    63,    25,
      26,    27,   185,   154,   111,   187,    65,   189,   174,    83,
     163,   164,    25,    26,    27,    64,   191,    73,    29,    38,
      28,    88,    39,    95,    52,   115,   116,   199,   117,    44,
     173,    70,   169,    28,   114,   167,    81,    83,    85,   148,
     173,    31,   182,   158,   211,    81,    92,    66,   149,    71,
      86,    68,   149,    69,    29,    25,    26,    27,    93,    25,
      26,    27,    25,    26,    27,   196,   125,   197,    96,   145,
     115,   116,   160,   117,    95,   183,    28,   126,   127,    83,
      28,   161,   156,    28,   184,   157,   137,   132,   177,    45,
      46,   157,    90,    91,   131,   212,   133,    31,   151,   152,
      47,    29,   153,   159,    29,     1,     2,     3,     4,   165,
     171,   175,   188,     5,   193,   176,   190,     6,     7,     8,
     192,     9,    10,    11,    12,   194,     1,     2,     3,     4,
     195,   201,   200,   207,     5,   203,   204,   202,     6,     7,
       8,   205,     9,    10,    11,    12,   206,     1,     2,     3,
       4,   208,   210,   155,    89,     5,   138,   162,   209,     6,
       7,     8,   139,     9,    10,    11,    12,     0,   112,     0,
     186,     1,     2,     3,     4,     0,   150,     0,     0,     5,
       0,     0,     0,     6,     7,     8,     0,     9,    10,    11,
      12,    97,    98,    99,   100,   101,   102
};

static const yytype_int16 yycheck[] =
{
       8,     9,    45,    76,     3,     9,     5,     3,    44,     3,
      18,    10,    20,    11,    12,     3,    59,     6,     7,    60,
      61,    50,    63,    64,    32,     3,     4,     5,     9,    10,
       4,     5,     3,     4,     5,    28,     3,    45,    25,    14,
      48,     3,    50,    51,     5,     0,    24,    40,    46,    92,
      46,    59,    46,    24,    62,    36,    44,    45,    62,    88,
      48,    36,    13,    51,    15,     3,    54,    45,    67,    68,
      48,    49,    71,    51,    45,    73,    75,   150,    45,    36,
      88,    42,    36,    45,    92,    14,    48,    95,    96,    51,
      47,    14,    54,    38,   137,   103,     3,     4,     5,   107,
      40,   142,     4,     5,   145,   113,    44,    36,    46,     5,
      48,    51,    50,    36,    54,   156,     8,    24,    13,     3,
       4,     5,   165,    19,    26,   166,     3,    14,    40,   137,
     128,   130,     3,     4,     5,    13,   177,    38,    45,    51,
      24,    48,    54,    28,    51,    41,    42,   188,    44,    36,
     148,    15,   141,    24,     5,    40,   192,   165,    40,    38,
     158,    45,   160,    38,   207,   201,    37,    44,    47,    46,
       3,    48,    47,    50,    45,     3,     4,     5,    49,     3,
       4,     5,     3,     4,     5,   183,    44,   186,    29,    13,
      41,    42,    38,    44,    28,    38,    24,    55,    56,   207,
      24,    47,    40,    24,    47,    43,    37,    46,    40,    37,
      38,    43,    52,    53,    39,    36,    39,    45,    40,    24,
      48,    45,    24,    39,    45,     4,     5,     6,     7,    37,
      11,    41,     8,    12,    24,    42,    39,    16,    17,    18,
      36,    20,    21,    22,    23,    39,     4,     5,     6,     7,
      39,    36,    47,    37,    12,    42,    47,    36,    16,    17,
      18,    47,    20,    21,    22,    23,    39,     4,     5,     6,
       7,   199,    47,   118,    51,    12,    95,   124,    36,    16,
      17,    18,    96,    20,    21,    22,    23,    -1,    68,    -1,
      27,     4,     5,     6,     7,    -1,   111,    -1,    -1,    12,
      -1,    -1,    -1,    16,    17,    18,    -1,    20,    21,    22,
      23,    30,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,    12,    16,    17,    18,    20,
      21,    22,    23,    58,    59,    60,    79,    81,    82,    82,
      25,    66,    82,    66,    66,     3,     4,     5,    24,    45,
      71,    45,    64,    71,    82,     3,    45,    48,    51,    54,
      76,    77,    76,     0,    36,    37,    38,    48,    64,    38,
      48,    49,    51,    65,    67,    68,    69,    70,    71,    72,
       8,    13,    15,    13,    13,     3,    44,    46,    48,    50,
      15,    46,    71,    38,     3,    46,    74,    75,    76,     3,
      45,    60,    65,    71,    76,    40,     3,    67,    48,    70,
      52,    53,    37,    49,    71,    28,    29,    30,    31,    32,
      33,    34,    35,    73,    65,    59,    59,    64,    59,    59,
      82,    26,    81,    82,     5,    41,    42,    44,    62,    63,
      82,    76,    82,    40,    77,    44,    55,    56,    78,     3,
      46,    39,    46,    39,    40,    67,    65,    37,    68,    69,
      71,     9,    10,    61,    14,    13,    14,    14,    38,    47,
      74,    40,    24,    24,    19,    63,    40,    43,    38,    39,
      38,    47,    75,    76,    82,    37,    80,    40,    65,    66,
      59,    11,    59,    76,    40,    41,    42,    40,    59,     5,
      42,    44,    76,    38,    47,    65,    27,    59,     8,    14,
      39,    59,    36,    24,    39,    39,    76,    82,    47,    59,
      47,    36,    36,    42,    47,    47,    39,    37,    61,    36,
      47,    65,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    63,    64,    64,    64,    65,    65,    66,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    74,    74,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    77,    77,    78,    78,    78,    79,
      80,    80,    81,    81,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     3,     6,     5,     6,     5,
       7,     5,     5,     5,     2,     2,     5,     1,     1,     2,
       1,     1,     2,     5,     2,     0,     6,     5,     1,     3,
       3,     3,     5,     1,     2,     1,     7,     2,     1,     2,
       3,     1,     3,     1,     3,     4,     1,     2,     3,     4,
       2,     3,     4,     7,     1,     1,     1,     2,     2,     2,
       1,     5,     4,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     4,     7,     2,     5,     8,
       3,     1,     2,     3,     1,     1,     1,     1,     1,     7,
       6,     0,     2,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 5: /* INSTRUCTION: ID '=' CONCATENATION  */
#line 28 "p.y"
                                    {printf(">ID= %s\n",(yyvsp[-2].name));}
#line 1304 "p.tab.c"
    break;

  case 6: /* INSTRUCTION: ID '[' OPERANDE_ENTIER ']' '=' CONCATENATION  */
#line 29 "p.y"
                                                       {printf(">ID[]= %s\n",(yyvsp[-5].name));}
#line 1310 "p.tab.c"
    break;

  case 7: /* INSTRUCTION: declare ID '[' entier ']'  */
#line 30 "p.y"
                                    {printf(">declare %s[%i]\n",(yyvsp[-3].name),(yyvsp[-1].entier));}
#line 1316 "p.tab.c"
    break;

  case 8: /* INSTRUCTION: if_ TEST_BLOC then LISTE_INTRSUCTIONS ELSE_PART fi  */
#line 31 "p.y"
                                                                {printf(">if \n");}
#line 1322 "p.tab.c"
    break;

  case 9: /* INSTRUCTION: for_ ID do_ LISTE_INTRSUCTIONS done  */
#line 32 "p.y"
                                                 {printf(">for \n");}
#line 1328 "p.tab.c"
    break;

  case 10: /* INSTRUCTION: for_ ID in LISTE_OPERANDES do_ LISTE_INTRSUCTIONS done  */
#line 33 "p.y"
                                                                    {printf(">for do \n");}
#line 1334 "p.tab.c"
    break;

  case 11: /* INSTRUCTION: while_ TEST_BLOC do_ LISTE_INTRSUCTIONS done  */
#line 34 "p.y"
                                                          {printf(">while \n");}
#line 1340 "p.tab.c"
    break;

  case 12: /* INSTRUCTION: until TEST_BLOC do_ LISTE_INTRSUCTIONS done  */
#line 35 "p.y"
                                                         {printf(">until \n");}
#line 1346 "p.tab.c"
    break;

  case 13: /* INSTRUCTION: case_ OPERANDE in LISTE_CAS esac  */
#line 36 "p.y"
                                              {printf(">case \n");}
#line 1352 "p.tab.c"
    break;

  case 14: /* INSTRUCTION: echo LISTE_OPERANDES  */
#line 37 "p.y"
                                  {printf(">echo \n");}
#line 1358 "p.tab.c"
    break;

  case 15: /* INSTRUCTION: read_ ID  */
#line 38 "p.y"
                        {printf(">Read %s\n",(yyvsp[0].name));}
#line 1364 "p.tab.c"
    break;

  case 16: /* INSTRUCTION: read_ ID '[' OPERANDE_ENTIER ']'  */
#line 39 "p.y"
                                           {printf(">Read %s[ent]\n",(yyvsp[-3].name));}
#line 1370 "p.tab.c"
    break;

  case 17: /* INSTRUCTION: DECLARATION_FONTION  */
#line 40 "p.y"
                                 {printf(">declaration fonction \n");}
#line 1376 "p.tab.c"
    break;

  case 18: /* INSTRUCTION: return_  */
#line 41 "p.y"
                     {printf(">return \n");}
#line 1382 "p.tab.c"
    break;

  case 19: /* INSTRUCTION: return_ OPERANDE_ENTIER  */
#line 42 "p.y"
                                     {printf(">return entier \n");}
#line 1388 "p.tab.c"
    break;

  case 20: /* INSTRUCTION: APPEL_FONCTION  */
#line 43 "p.y"
                            {printf(">appel fonction \n");}
#line 1394 "p.tab.c"
    break;

  case 21: /* INSTRUCTION: exit_  */
#line 44 "p.y"
                   {printf(">exit \n");}
#line 1400 "p.tab.c"
    break;

  case 22: /* INSTRUCTION: exit_ OPERANDE_ENTIER  */
#line 45 "p.y"
                                   {printf(">exit entier \n");}
#line 1406 "p.tab.c"
    break;

  case 39: /* TEST_BLOC: test TEST_EXPR  */
#line 74 "p.y"
                            {printf("Test Bloc\n");}
#line 1412 "p.tab.c"
    break;

  case 56: /* OPERANDE: id  */
#line 101 "p.y"
                {printf("id mais mot enfait %s\n",(yyvsp[0].name));}
#line 1418 "p.tab.c"
    break;

  case 90: /* DECL_LOC: DECL_LOC local ID '=' CONCATENATION ';'  */
#line 155 "p.y"
                                                   {printf(">Local\n");}
#line 1424 "p.tab.c"
    break;

  case 94: /* ID: id  */
#line 162 "p.y"
        {printf("C'est bien un id %s\n",(yyvsp[0].name));(yyval.name)=(yyvsp[0].name);}
#line 1430 "p.tab.c"
    break;

  case 95: /* ID: mot  */
#line 163 "p.y"
            {printf("C'est prit pour mot mais peut être que c'est un id?? %s\n",(yyvsp[0].name));(yyval.name)=(yyvsp[0].name);}
#line 1436 "p.tab.c"
    break;


#line 1440 "p.tab.c"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 169 "p.y"


void yyerror(const char *msg)
{
    fprintf(stderr,"%s\n",msg);
}
