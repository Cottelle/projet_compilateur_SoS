/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_P_TAB_H_INCLUDED
# define YY_YY_P_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    entier = 258,                  /* entier  */
    id = 259,                      /* id  */
    mot = 260,                     /* mot  */
    declare = 261,                 /* declare  */
    if_ = 262,                     /* if_  */
    then = 263,                    /* then  */
    elif = 264,                    /* elif  */
    else_ = 265,                   /* else_  */
    fi = 266,                      /* fi  */
    for_ = 267,                    /* for_  */
    do_ = 268,                     /* do_  */
    done = 269,                    /* done  */
    in = 270,                      /* in  */
    while_ = 271,                  /* while_  */
    until = 272,                   /* until  */
    case_ = 273,                   /* case_  */
    esac = 274,                    /* esac  */
    echo = 275,                    /* echo  */
    read_ = 276,                   /* read_  */
    return_ = 277,                 /* return_  */
    exit_ = 278,                   /* exit_  */
    chaine = 279,                  /* chaine  */
    test = 280,                    /* test  */
    expr = 281,                    /* expr  */
    local = 282,                   /* local  */
    to = 283,                      /* to  */
    ta = 284,                      /* ta  */
    teq = 285,                     /* teq  */
    tne = 286,                     /* tne  */
    tgt = 287,                     /* tgt  */
    tge = 288,                     /* tge  */
    tlt = 289,                     /* tlt  */
    tle = 290                      /* tle  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 7 "p.y"

    int entier;
    char *name;

#line 104 "p.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_P_TAB_H_INCLUDED  */
