%{
#include<stdio.h>

#include "tabsymbole.h"
#include "gencode.h"


extern int yylex(void);
extern struct quad quad;
void yyerror(const char *msg);



    %}

%union{
    int entier;
    int quad;
    char *name;
    struct {
        struct lpos* true;
        struct lpos* false;
    } cond;

    struct lpos* next;


}


%token <entier> entier
%token <name> id mot
%token declare if_ then elif else_ fi for_ do_ done in while_ until case_ esac echo read_ return_ exit_ chaine test expr local to ta teq tne tgt tge tlt tle magic
%type <name> ID
%type <cond> TEST_EXPR TEST_EXPR2 TEST_EXPR3 TEST_INSTRUCTION TEST_BLOC
%type <next> INSTRUCTION LISTE_INTRSUCTIONS ELSE_PART 
%type <quad> M
%start PROGRAMME

%%

PROGRAMME : LISTE_INTRSUCTIONS      
            ;

LISTE_INTRSUCTIONS: LISTE_INTRSUCTIONS ';' {complete($1,quad.next);} INSTRUCTION 
                | INSTRUCTION {$$= $1;}       
                ;

INSTRUCTION : ID '=' CONCATENATION  { gencode(1,"%s(%i)",$1,findtable($1,1)); } 
            |ID'['OPERANDE_ENTIER']' '=' CONCATENATION {printf(">ID[]= %s(%i)\n",$1,findtable($1,1));} 
            |declare ID'['entier']' {printf(">declare %s[%i]\n",$2,$4);}
            |if_ TEST_BLOC then {complete($2.true, quad.next);} LISTE_INTRSUCTIONS M {gencode(0,"goto"); complete($2.false, quad.next);}  ELSE_PART fi {printf(">if \n"); $$ = concat($5, crelist($6) ); }
            |for_ ID do_ LISTE_INTRSUCTIONS done {printf(">for (%i)\n",findtable($2,1));}   //peut ecraser les ancien même id
            |for_ ID in LISTE_OPERANDES do_ LISTE_INTRSUCTIONS done {printf(">for in (%i)\n",findtable($2,1));} //idem
            |while_ M TEST_BLOC do_ {complete($3.true,quad.next);} LISTE_INTRSUCTIONS done {printf(">while \n"); $$ = $3.false; complete($6, $2), gencode(1,"goto %i",$2);  }
            |until TEST_BLOC do_ LISTE_INTRSUCTIONS done {printf(">until \n");}
            |case_ OPERANDE in LISTE_CAS esac {printf(">case \n");}
            |echo LISTE_OPERANDES {printf(">echo \n");}
            |read_ ID   {printf(">Read %s(%i)\n",$2,findtable($2,1));}
            |read_ ID'['OPERANDE_ENTIER']' {printf(">Read %s[ent](%i)\n",$2,findtable($2,1));}
            |DECLARATION_FONTION {printf(">declaration fonction \n");}
            |return_ {printf(">return \n");}
            |return_ OPERANDE_ENTIER {printf(">return entier \n");}
            |APPEL_FONCTION {printf(">appel fonction \n");}
            |exit_ {printf(">exit \n");}
            |exit_ OPERANDE_ENTIER {printf(">exit entier \n");}
            ;

ELSE_PART: elif TEST_BLOC {complete($2.true, quad.next);} then LISTE_INTRSUCTIONS M {gencode(0,"goto");complete($2.false, quad.next); } ELSE_PART { $$ = concat(crelist($6),$5); $$ = concat($$,crelist(quad.next)); gencode(0,"goto");}
            |else_ LISTE_INTRSUCTIONS {$$ = $2; $$ = concat($$,crelist(quad.next)); gencode(0,"goto");}
            |%empty 
            ;

LISTE_CAS: LISTE_CAS FILTRE ')' LISTE_INTRSUCTIONS ';'';' 
            |FILTRE ')'LISTE_INTRSUCTIONS ';'';' 
            ; 

FILTRE: mot
           |'\''chaine'\'' 
           |'"'chaine'"' 
           |FILTRE '|' mot 
           |FILTRE '|' '"'chaine'"' 
           | '*' 
           ;

LISTE_OPERANDES:LISTE_OPERANDES OPERANDE 
            |OPERANDE 
            |'$''{'ID'[''*'']''}' 
            ;

CONCATENATION: CONCATENATION OPERANDE
            |OPERANDE 
            ;

TEST_BLOC: test TEST_EXPR   {$$=$2;}
            ;
        
TEST_EXPR: TEST_EXPR to {complete($1.false, quad.next); } TEST_EXPR2  
{
    $$.true = concat($1.true,$4.true);
    $$.false = $4.false;
}
            |TEST_EXPR2 {$$= $1;}
            ;

TEST_EXPR2: TEST_EXPR2 ta {complete($1.true,quad.next); } TEST_EXPR3 
{
    $$.false = concat($1.false, $4.false);
    $$.true  = $4.true;
}
            |TEST_EXPR3 {$$= $1;}
            ;
    
TEST_EXPR3: '(' TEST_EXPR ')' {$$=$2;} 
            |'!''(' TEST_EXPR ')' { $$.true = $3.false; $$.false = $3.true;}
            |TEST_INSTRUCTION {$$=$1;}
            |'!' TEST_INSTRUCTION { $$.true = $2.false; $$.false = $2.true;}
            ;

TEST_INSTRUCTION :CONCATENATION '=' CONCATENATION 
            |CONCATENATION '!''=' CONCATENATION 
            |OPERATEUR1 CONCATENATION 
            |OPERANDE OPERATEUR2 OPERANDE 
            |magic {
                $$.true = crelist(quad.next);
                gencode(0,"goto");
                $$.false = NULL;}
            ;



OPERANDE:'$''{'ID'}' {int a; if ((a=findtable($3,0))<0) { printf("Erreur %s n'existe pas\n ",$3); exit(2);}}
            |'$''{'ID'['OPERANDE_ENTIER']''}' 
            |mot   
            |entier                 //Rajouter a la grammaire        
            |id {printf("id mais mot enfait %s\n",$1);}     //Rajouter a la grammaire
            |'$'entier      
            |'$''*' 
            |'$''?' 
            |chaine
            |'$''('expr SOMME_ENTIER ')' 
            |'$' '('APPEL_FONCTION ')' 
            ;

OPERATEUR1: '-''n' 
            |'-''z' 
            ;


OPERATEUR2: teq 
            |tne 
            | tgt
            |tge 
            | tlt
            |tle
            ;

SOMME_ENTIER:SOMME_ENTIER PLUS_MOINS PRODUIT_ENTIER 
            |PRODUIT_ENTIER 
            ;

PRODUIT_ENTIER:PRODUIT_ENTIER FOIS_DIV_MOD OPERANDE_ENTIER 
            |OPERANDE_ENTIER 
            ;

OPERANDE_ENTIER:'$''{'ID'}' 
            |'$''{'ID'['OPERANDE_ENTIER']''}' 
            |'$' entier 
            |PLUS_MOINS '$''{'ID'}' 
            |PLUS_MOINS '$''{'ID'['OPERANDE_ENTIER']''}' 
            |PLUS_MOINS '$'entier 
            |entier 
            |PLUS_MOINS entier 
            |'('SOMME_ENTIER ')' 
            ;

PLUS_MOINS : '+' 
            |'-' 
            ;

FOIS_DIV_MOD: '*' 
            |'/' 
            |'%' 
            ;

DECLARATION_FONTION: ID '('')''{'DECL_LOC LISTE_INTRSUCTIONS '}' 
            ;


DECL_LOC: DECL_LOC  local ID '=' CONCATENATION ';' {printf(">Local\n");}
            |%empty 
            ;

APPEL_FONCTION: ID LISTE_OPERANDES 
            |ID 
            ;
ID : id {printf("C'est bien un id %s\n",$1);$$=$1;}
    |mot    {printf("C'est prit pour mot mais peut être que c'est un id?? %s\n",$1);$$=$1;}
    ;

M: %empty { $$ = quad.next;}

%%

void yyerror(const char *msg)
{
    fprintf(stderr,"%s\n",msg);
}