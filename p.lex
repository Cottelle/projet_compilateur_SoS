%option nounput
%option noyywrap

%{
    #include <stdio.h>
    #include "p.tab.h"
%}


NUMBER [1-9][0-9]*|0
LETTRE [a-zA-Z]


ID {LETTRE}({NUMBER}|{LETTRE}|_)*

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





"declare "  {return declare;}
"if " {return if_;}
"then " {return then;}
"elif " {return elif;}
"else " {return else_;}
"fi " {return fi;}
"for " {return for_;}
"do " {return do_;}
"done " {return done;}
"in " {return in;}
"while " {return while_;}
"until " {return until;}
"case " {return case_;}
"esac " {return esac;}
"echo " {return echo;}
"read " {return read_;}
"return " {return return_;}
"exit " {return exit_;}
"test " {return test;}
"expr " {return expr;}
"local " {return local;}

{NUMBER} { yylval = (YYSTYPE)atoi(yytext) ;return entier;}
{ID}    {yylval = (YYSTYPE)yytext; return id;}

\".*\" {printf("MOTCHAINE");yylval = (YYSTYPE)yytext;return chaine;}
\'.*\' {printf("MOTCHAINE");yylval = (YYSTYPE)yytext;return chaine;}
%{//.*" "     {printf("MOTCHAINE");yylval = (YYSTYPE)yytext; return mot;} %}

"\n" ;
"\t" ;
" "  ;

%%