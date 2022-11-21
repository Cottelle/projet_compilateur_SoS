%{
#include<stdio.h>
extern int yylex(void);
void yyerror(const char *msg);
    %}

%union{
    int entier;
    char *name;
}


%token <entier> entier
%token <name> id
%token declare if_ then elif else_ fi for_ do_ done in while_ until case_ esac echo read_ return_ exit_ mot chaine test expr local
%start PROGRAMME

%%

PROGRAMME : LISTE_INTRSUCTIONS      
            ;

LISTE_INTRSUCTIONS: LISTE_INTRSUCTIONS ';' INSTRUCTION {printf("Instriction\n");}
                | INSTRUCTION  {printf("Instrictionqsd\n");}     
                ;

INSTRUCTION : id '=' CONCATENATION  {printf("Id= %s\n",$1);} 
            |id'['OPERANDE_ENTIER']' '=' CONCATENATION {printf("Id[]= %s\n",$1);} 
            |declare id'['entier']' {printf("declare %s[%i]\n",$2,$4);}
            |if_ TEST_BLOC then LISTE_INTRSUCTIONS ELSE_PART fi 
            |for_ id do_ LISTE_INTRSUCTIONS done 
            |for_ id in LISTE_OPERANDES do_ LISTE_INTRSUCTIONS done 
            |while_ TEST_BLOC do_ LISTE_INTRSUCTIONS done 
            |until TEST_BLOC do_ LISTE_INTRSUCTIONS done 
            |case_ OPERANDE in LISTE_CAS esac 
            |echo LISTE_OPERANDES 
            |read_ id 
            |read_ id'['OPERANDE_ENTIER']' 
            |DECLARATION_FONTION 
            |APPEL_FONCTION 
            |return_ 
            |return_ OPERANDE_ENTIER 
            |exit_ 
            |exit_ OPERANDE_ENTIER 
            ;

ELSE_PART: elif TEST_BLOC then LISTE_INTRSUCTIONS ELSE_PART 
            |else_ LISTE_INTRSUCTIONS 
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
            |'$''{'id'[''*'']''}' 
            ;

CONCATENATION: CONCATENATION OPERANDE 
            |OPERANDE 
            ;

TEST_BLOC: test TEST_EXPR 
            ;
        
TEST_EXPR: TEST_EXPR '-''o' TEST_EXPR2 
            |TEST_EXPR2 
            ;

TEST_EXPR2: TEST_EXPR2 '-''a' TEST_EXPR3 
            |TEST_EXPR3 
            ;
    
TEST_EXPR3: '(' TEST_EXPR ')' 
            |'!''(' TEST_EXPR ')' 
            |TEST_INSTRUCTION 
            |'!' TEST_INSTRUCTION 
            ;

TEST_INSTRUCTION :CONCATENATION '=' CONCATENATION 
            |CONCATENATION '!''=' CONCATENATION 
            |OPERATEUR1 CONCATENATION 
            |OPERANDE OPERATEUR2 OPERANDE 
            ;

OPERANDE:'$''{'id'}' 
            |'$''{'id'['OPERANDE_ENTIER']''}' 
            |mot {printf("mot\n");}
            |id {printf("id mais mot enfait");}     //Rajouter a la grammaire
            |'$'entier      
            |'$''*' 
            |'$''?' 
            |chaine  {printf("chaine\n");}
            |'$''('expr SOMME_ENTIER ')' 
            |'$' '('APPEL_FONCTION ')' 
            ;

OPERATEUR1: '-''n' 
            |'-''z' 
            ;


OPERATEUR2: '-''e''q' 
            |'-''n''e' 
            |'-''g''t' 
            |'-''g''e' 
            |'-''l''t' 
            |'-''l''e' 
            ;

SOMME_ENTIER:SOMME_ENTIER PLUS_MOINS PRODUIT_ENTIER 
            |PRODUIT_ENTIER 
            ;

PRODUIT_ENTIER:PRODUIT_ENTIER FOIS_DIV_MOD OPERANDE_ENTIER 
            |OPERANDE_ENTIER 
            ;

OPERANDE_ENTIER:'$''{'id'}' 
            |'$''{'id'['OPERANDE_ENTIER']''}' 
            |'$' entier 
            |PLUS_MOINS '$''{'id'}' 
            |PLUS_MOINS '$''{'id'['OPERANDE_ENTIER']''}' 
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

DECLARATION_FONTION: id '('')''{'DECL_LOC LISTE_INTRSUCTIONS '}' 
            ;


DECL_LOC: DECL_LOC local id '=' CONCATENATION 
            |%empty 
            ;


APPEL_FONCTION: id LISTE_OPERANDES 
            |id 
            ;

    



%%

void yyerror(const char *msg)
{
    fprintf(stderr,"%s\n",msg);
}