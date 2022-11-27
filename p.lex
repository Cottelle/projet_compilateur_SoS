%option nounput
%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "p.tab.h"
%}


NUMBER [1-9][0-9]*|0
LETTRE [a-zA-Z]


ID {LETTRE}({NUMBER}|{LETTRE}|_)*

QUOTE (\"|\')
ALLE [^\"\'" "";""=""\n""\t""\]""\)""\[""\(""$""{""}"]       
%%


";" return yytext[0];
"[" return yytext[0];
"]" return yytext[0];
"(" return yytext[0];
")" return yytext[0];
"=" return yytext[0];
"!" return yytext[0];
"|" return yytext[0];
"$" return yytext[0];
"*" return yytext[0];
"{" return yytext[0];
"}" return yytext[0];
"+" return yytext[0];
"-" return yytext[0];
"/" return yytext[0];
"%" return yytext[0];
"?" return yytext[0];

"-o" return to;
"-a" return ta;
"-eq" return teq;
"-ne" return tne;
"-gt" return tgt;
"-ge" return tge;
"-lt" return tlt;
"-le" return tle;

"#".*"\n" {printf("Commentaire %s\n",yytext);}


[[:space:]] ;



"declare" {return declare; }  
"if" {return if_;}
"then" {return then;}
"elif" {return elif;}
"else" {return else_;}
"fi" {return fi;}
"for" {return for_;}
"do" {return do_;}
"done" {return done;}
"in" {return in;}
"while" {return while_;}
"until" {return until;}
"case" {return case_;}
"esac" {return esac;}
"echo" {return echo;}
"read" {return read_;}
"return" {printf("lex return\n"); return return_;}
"exit" {return exit_;}
"test" {return test;}
"expr" {return expr;}
"local" {printf("lexlocal\n");return local;}; 

{NUMBER} { yylval = (YYSTYPE)atoi(yytext) ;return entier;}
{ID} {char *value; value =malloc(strlen(yytext));strcpy(value,yytext);yylval =(YYSTYPE)value;return id;}

{QUOTE}.*{QUOTE} {char *value; value =malloc(strlen(yytext));strcpy(value,yytext);yylval =(YYSTYPE)value;return chaine;}

{ALLE}+     {printf("mot:%s\n",yytext); char *value; value =malloc(strlen(yytext));strcpy(value,yytext);yylval =(YYSTYPE)value;return mot;}



. {printf("Unknow symbol %c\n",*yytext);}

%%