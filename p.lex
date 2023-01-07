%option nounput
%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "p.tab.h"


    unsigned int nligne;

    extern void cpy_without_quote(char *,char *);
%}


NUMBER [1-9][0-9]*|0
LETTRE [a-zA-Z]


ID {LETTRE}({NUMBER}|{LETTRE}|_)*

QUOTE (\"|\')
ALLE [^\"\'" "";""=""\n""\t""\]""\)""\[""\(""$""{""}" "\|"]       
%%

"\n" nligne++;
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


"#".*"\n" nligne++;


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
"return" {return return_;}
"exit" {return exit_;}
"test" {return test;}
"expr" {return expr;}
"local" {return local;}; 

{NUMBER} { yylval = (YYSTYPE)atoi(yytext) ;return entier;}
{ID} {printf("id %s\n",yytext);char *value; value =malloc(strlen(yytext)+1);strcpy(value,yytext);yylval =(YYSTYPE)value;return id;}

{QUOTE}.*{QUOTE} {char *value; value =malloc(strlen(yytext)-1);cpy_without_quote(value,yytext);yylval =(YYSTYPE)value;return chaine;}

{ALLE}+     { printf("mot %s\n",yytext);char *value; value =malloc(strlen(yytext)+1);strcpy(value,yytext);yylval =(YYSTYPE)value;return mot;}



. {printf("Unknow symbol %c\n",*yytext);}



%%

void cpy_without_quote(char *dst, char *src)//copy without quote
{
    int i=1;
    while(src[i]!='\"' && src[i]!='\'' )
    {
        dst[i-1] =src[i];
        i++;
    }
}