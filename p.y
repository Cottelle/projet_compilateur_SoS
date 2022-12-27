%{
#include<stdio.h>

#include "tabsymbole.h"
#include "gencode.h"
#include "usefull.h"


extern int yylex(void);
extern struct quad quad;
extern unsigned int nbarg;
void yyerror(const char *msg);

unsigned int nbfor;



    %}

%union{
    int entier;
    int addr;
    int quad;
    char *name;
    struct {
        struct lpos *true;
        struct lpos *false;
    } cond;

    struct lpos *next;

    struct {
        struct lpos *next;
        struct lpos *follow;
    } nexfoll;

    struct {
        struct lpos *entrer;
        char *last;
    } filtre;

    struct {
        struct lpos *start;
        struct lpos *value;
    } list_ope;


}


%token <entier> entier
%token <name> id mot chaine
%token declare if_ then elif else_ fi for_ do_ done in while_ until case_ esac echo read_ return_ exit_  test expr local to ta teq tne tgt tge tlt tle magic
%type <name> ID  
%type <addr> OPERANDE
%type <list_ope> LISTE_OPERANDES
%type <filtre> FILTRE
%type <cond> TEST_EXPR TEST_EXPR2 TEST_EXPR3 TEST_INSTRUCTION TEST_BLOC
%type <next> INSTRUCTION LISTE_INTRSUCTIONS ELSE_PART 
%type <nexfoll> LISTE_CAS
%type <quad> M
%start PROGRAMME

%%

PROGRAMME : LISTE_INTRSUCTIONS      
            ;

LISTE_INTRSUCTIONS: LISTE_INTRSUCTIONS ';'INSTRUCTION   {
                                                            $$ = $1;
                                                            complete($3,addvalcreate(NULL,quad.next));
                                                        } 
                | INSTRUCTION                           {
                                                            $$ = $1;                    //le remplace si il en est capable
                                                            complete($1,addvalcreate(NULL,quad.next));
                                                        }       
                ;


INSTRUCTION : ID '=' CONCATENATION                                                                                                          { 
                                                                                                                                                $$= NULL;
                                                                                                                                                gencode(AFF, addvalcreate(findtable($1,1),-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                            } 
            |ID'['OPERANDE_ENTIER']' '=' CONCATENATION                                                                                      {
                                                                                                                                                $$= NULL;
                                                                                                                                                printf(">ID[]= %s(%i)\n",$1,findtable($1,1)->memory_place);
                                                                                                                                            } 
            |declare ID'['entier']'                                                                                                                     {
                                                                                                                                                $$= NULL;
                                                                                                                                                symbole s = simples();
                                                                                                                                                s.nb = $4; //test si $4>0?
                                                                                                                                                s.name = $2;
                                                                                                                                                int a = createsymbole(&s)->memory_place;
                                                                                                                                                printf(">declare %s[%i] : %i\n",$2,$4,a);
                                                                                                                                                 
                                                                                                                                            }
            |if_ TEST_BLOC then {complete($2.true, addvalcreate(NULL,quad.next));} LISTE_INTRSUCTIONS M {
                                                                                        gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0); 
                                                                                        complete($2.false, addvalcreate(NULL,quad.next));
                                                                                    }  
                ELSE_PART fi                                                                                                                {
                                                                                                                                                printf(">if \n"); 
                                                                                                                                                $$ = concat($5, crelist($6) ); 
                                                                                                                                            }
            |for_ ID                                                                                                                        {
                                                                                                                                                gencode(AFF,addvalcreate(findtable(createbuf("_for%i",++nbfor),1),1),addvalcreate(NULL,quad.next+1),addvalcreate(NULL,-1),0);
                                                                                                                                            }  
                do_ M                                                                                                                        <next>{
                                                                                                                                                    lpos *start;
                                                                                                                                                    lpos *value =arggencode(&start);
                                                                                                                                                    char *buf = createbuf("_for%i",nbfor);
                                                                                                                                                    $$ = crelist(quad.next);
                                                                                                                                                    gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                    complete(value, addvalcreate(findtable($2,1),-1));
                                                                                                                                                    complete(start,addvalcreate(NULL,quad.next));
                                                                                                                                                    gencode(AFF,addvalcreate(findtable(buf,0),-1),addvalcreate(findtable(buf,0),-1),addvalcreate(NULL,2),1);
                                                                                                                                                 } 
                LISTE_INTRSUCTIONS done                                                                                                         {
                                                                                                                                                        printf(">for in (%i)\n",findtable($2,1)->memory_place); 
                                                                                                                                                        $$ =$6; 
                                                                                                                                                        gencode(GOTO,addvalcreate(findtable(createbuf("_for%i",nbfor--),0),-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0); 
                                                                                                                                                }
            |for_ ID in                                                                                                                         {
                                                                                                                                                    gencode(AFF,addvalcreate(findtable(createbuf("_for%i",++nbfor),1),-1),addvalcreate(NULL,quad.next+1),addvalcreate(NULL,-1),0);
                                                                                                                                                }
                 M LISTE_OPERANDES do_ M                                                                                                            {
                                                                                                                                                        char *buf = createbuf("_for%i",nbfor);
                                                                                                                                                        gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                        complete($6.value, addvalcreate(findtable($2,1),-1));
                                                                                                                                                        complete($6.start,addvalcreate(NULL,quad.next));
                                                                                                                                                        gencode(AFF,addvalcreate(findtable(buf,0),-1),addvalcreate(findtable(buf,0),-1),addvalcreate(NULL,2),1);
                                                                                                                                                     } 
                LISTE_INTRSUCTIONS done                                                                                                         {
                                                                                                                                                    printf(">for in (%i)\n",findtable($2,1)->memory_place);
                                                                                                                                                    $$ =crelist($8);
                                                                                                                                                    gencode(GOTO,addvalcreate(findtable(createbuf("_for%i",nbfor--),0),-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                } 
            |while_ M TEST_BLOC do_ {complete($3.true,addvalcreate(NULL,quad.next));} LISTE_INTRSUCTIONS done                                  {
                                                                                                                                                printf(">while \n");
                                                                                                                                                $$ = $3.false;
                                                                                                                                                complete($6, addvalcreate(NULL,$2)), gencode(GOTO,addvalcreate(NULL,$2),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                            }
            |until M TEST_BLOC do_ {complete($3.false, addvalcreate(NULL,quad.next));} LISTE_INTRSUCTIONS done                               {
                                                                                                                                                printf(">until \n");
                                                                                                                                                $$ = $3.true;
                                                                                                                                                complete($6, addvalcreate(NULL,$2)), gencode(GOTO,addvalcreate(NULL,$2),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                            }
            |case_  OPERANDE {casepush($2);} in LISTE_CAS esac                                                                              {
                                                                                                                                                printf(">case \n");
                                                                                                                                                $$ = concat($5.follow,$5.next) ;
                                                                                                                                                casepop();
                                                                                                                                                }
            |echo LISTE_OPERANDES                                                                                                           {
                                                                                                                                                printf(">echo \n");
                                                                                                                                            }
            |read_ ID                                                                                                                       {
                                                                                                                                                printf(">Read %s(%i)\n",$2,findtable($2,1)->memory_place);
                                                                                                                                            }
            |read_ ID'['OPERANDE_ENTIER']'                                                                                                  {
                                                                                                                                                printf(">Read %s[ent](%i)\n",$2,findtable($2,1)->memory_place);
                                                                                                                                            }
            |DECLARATION_FONTION                                                                                                            {
                                                                                                                                                printf(">declaration fonction \n");
                                                                                                                                                $$ = NULL;
                                                                                                                                            }
            |return_                                                                                                                        {
                                                                                                                                                printf(">return \n");
                                                                                                                                            }
            |return_ OPERANDE_ENTIER                                                                                                        {
                                                                                                                                                printf(">return entier \n");
                                                                                                                                            }
            |APPEL_FONCTION                                                                                                                 {
                                                                                                                                                printf(">appel fonction \n");
                                                                                                                                                $$=NULL;
                                                                                                                                            }
            |exit_                                                                                                                          {
                                                                                                                                                printf(">exit \n");
                                                                                                                                            }
            |exit_ OPERANDE_ENTIER                                                                                                          {
                                                                                                                                                printf(">exit entier \n");
                                                                                                                                            }
            ;                                       



ELSE_PART: elif TEST_BLOC                                                                                                                   {
                                                                                                                                                complete($2.true, addvalcreate(NULL,quad.next));
                                                                                                                                            } 
                then LISTE_INTRSUCTIONS M                                                                                                       {
                                                                                                                                                     gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                     complete($2.false, addvalcreate(NULL,quad.next));
                                                                                                                                                 } 
                    ELSE_PART                                                                                                                         { 
                                                                                                                                                        $$ = concat(crelist($6),$5);
                                                                                                                                                        $$ = concat($$,crelist(quad.next));
                                                                                                                                                        gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                      }
            |else_ LISTE_INTRSUCTIONS                                                                                                        {
                                                                                                                                                 $$ = $2;
                                                                                                                                                 $$ = concat($$,crelist(quad.next));
                                                                                                                                                 gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                             }
            |%empty                                                                                                                          {
                                                                                                                                                $$= NULL;
                                                                                                                                             }
    

LISTE_CAS: LISTE_CAS M FILTRE ')' M                                                                                                         { 
                                                                                                                                                gencode(IF,addvalcreate(NULL,-1),addvalcreate(NULL,casetop()),addvalcreate(findtable($3.last,1),-1),2); 
                                                                                                                                                complete($3.entrer,addvalcreate(NULL,quad.next));
                                                                                                                                            } 
                 LISTE_INTRSUCTIONS ';'';'                                                                                                                      {
                                                                                                                                                                    $$.next = concat($7,crelist(quad.next)); 
                                                                                                                                                                    gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0); 
                                                                                                                                                                    $$.next = concat($$.next,$1.next); 
                                                                                                                                                                    complete($1.follow,addvalcreate(NULL,$2)); 
                                                                                                                                                                    $$.follow = crelist($5) ; 
                                                                                                                                                                } 
            |M FILTRE ')'M                                                                                                                  {
                                                                                                                                                 gencode(IF,addvalcreate(NULL,-1),addvalcreate(NULL,casetop()),addvalcreate(findtable($2.last,1),-1),2); 
                                                                                                                                                 complete($2.entrer,addvalcreate(NULL,quad.next));
                                                                                                                                            } 
                LISTE_INTRSUCTIONS ';'';'                                                                                                                       {
                                                                                                                                                                    $$.next = concat($6,crelist(quad.next));
                                                                                                                                                                    gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                                                                                                    $$.follow = crelist($4) ;
                                                                                                                                                                }
            ; 


FILTRE: ID                          {
                                     $$.last=$1;
                                     $$.entrer = NULL;
                                    }                      
           |chaine                  {
                                        $$.last=$1;
                                        $$.entrer = NULL;
                                    }           
           |FILTRE '|' mot          
                                    {
                                        $$.last=$3;
                                        $$.entrer = concat($1.entrer, crelist(quad.next)) ;
                                        gencode(IF,addvalcreate(NULL,-1),addvalcreate(NULL,casetop()),addvalcreate(findtable($1.last,1),-1),1) ;
                                    }           
           |FILTRE '|'chaine        {
                                        $$.last=$3;
                                        $$.entrer = concat($1.entrer, crelist(quad.next)) ;
                                        gencode(IF,addvalcreate(NULL,-1),addvalcreate(NULL,casetop()),addvalcreate(findtable($1.last,1),-1),1) ;
                                    }              
           | '*'                    {
                                        $$.entrer = crelist(quad.next) ;
                                        gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                        $$.last = "Bidon"; 
                                    }
           ;


LISTE_OPERANDES:LISTE_OPERANDES OPERANDE {
                                            $$.start = concat($1.start,crelist(quad.next+1)); 
                                            $$.value = concat($1.value, crelist(quad.next));
                                             gencode(AFF,addvalcreate(NULL,-1),addvalcreate(NULL,$2),addvalcreate(NULL,-1),0); 
                                             gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                        } 
            |OPERANDE                   {
                                            $$.start = crelist(quad.next+1) ;
                                            $$.value = crelist(quad.next);
                                            gencode(AFF,addvalcreate(NULL,-1),addvalcreate(NULL,$1),addvalcreate(NULL,-1),0);
                                            gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                        }
            |'$''{'ID'[''*'']''}'        { 
                                            symbole *id= findtable($3,0); 
                                            if(!id) 
                                            {
                                                fprintf(stderr,"Error %s is Unknow \n",$3); 
                                                exit(2); 
                                            } 
                                            $$.start=NULL;
                                            $$.value= NULL;
                                            for(int i=0 ;i<id->nb ; i++)
                                            {
                                                $$.start = concat($$.start,crelist(quad.next+1));
                                                $$.value = concat($$.value, crelist(quad.next));
                                                gencode(AFF,addvalcreate(NULL,-1),addvalcreate(NULL,id->memory_place+i*CELLSIZE),addvalcreate(NULL,-1),0);      //pb car c'est une addr et pas direct ... a mediter quand les tab seront elusider
                                                gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                            }
                                        } 
            ;


CONCATENATION: CONCATENATION OPERANDE
            |OPERANDE 
            ;


TEST_BLOC: test TEST_EXPR   {$$=$2;}
            ;


TEST_EXPR: TEST_EXPR to {complete($1.false, addvalcreate(NULL,quad.next)); } TEST_EXPR2    {
                                                                            $$.true = concat($1.true,$4.true);
                                                                            $$.false = $4.false;
                                                                        }
            |TEST_EXPR2                                                 {
                                                                            $$= $1;
                                                                        }
            ;


TEST_EXPR2: TEST_EXPR2 ta {complete($1.true,addvalcreate(NULL,quad.next)); } TEST_EXPR3    {
                                                                            $$.false = concat($1.false, $4.false);
                                                                            $$.true  = $4.true;
                                                                        }
            |TEST_EXPR3                                                 {
                                                                            $$= $1;
                                                                        }
            ;
    

TEST_EXPR3: '(' TEST_EXPR ')'                                           {
                                                                            $$=$2;
                                                                        } 
            |'!''(' TEST_EXPR ')'                                       {
                                                                            $$.true = $3.false;
                                                                            $$.false = $3.true;
                                                                        }
            |TEST_INSTRUCTION                                           {
                                                                            $$=$1;
                                                                        }
            |'!' TEST_INSTRUCTION                                       {
                                                                            $$.true = $2.false;
                                                                            $$.false = $2.true;
                                                                        }
            ;


TEST_INSTRUCTION :CONCATENATION '=' CONCATENATION 
            |CONCATENATION '!''=' CONCATENATION 
            |OPERATEUR1 CONCATENATION 
            |OPERANDE OPERATEUR2 OPERANDE 
            |magic {
                $$.true = crelist(quad.next);
                gencode(GOTO,addvalcreate(NULL,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                $$.false = NULL;
                    }
            ;


OPERANDE:'$''{'ID'}'                          {
                                                $$ = findtable($3,0)->memory_place;
                                                }
            |'$''{'ID'['OPERANDE_ENTIER']''}' {
                                                $$= findtable($3,0)->memory_place;
                                                }
            |mot                              {
                                                $$=writestringmemory($1);
                                                }
            |entier                           {                      //Rajouter a la grammaire 
                                                char *mal = malloc(32);
                                                 if (!mal)
                                                 {
                                                    fprintf(stderr,"Error malloc qs");
                                                    exit(1);
                                                 } 
                                                 snprintf(mal,32,"%i",$1);
                                                 $$ = writestringmemory(mal);
                                                }                     
            |id                               {
                                                printf("id mais mot enfait %s\n",$1);
                                                $$ =writestringmemory($1);
                                                }     //Rajouter a la grammaire
            |chaine                           {
                                                $$ =writestringmemory($1);
                                                }
            |'$'entier      
            |'$''*' 
            |'$''?' 
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


DECLARATION_FONTION: ID '(' entier ')'                                              <entier>{       //chagement de la grammaire (ajout entier) car sinon valeur inconue à la compilation (nb d'argument) ce qui pose nottament probleme sur for i do ...
                                                                                        symbole s = simples();
                                                                                        s.fun = $3; 
                                                                                        s.name = $1;
                                                                                        inmemory(createsymbole(&s)->memory_place,(char *)&quad.next,CELLSIZE);
                                                                                        $$ = nbarg;
                                                                                        nbarg = $3;
                                                                                    }
                '{'DECL_LOC LISTE_INTRSUCTIONS '}'                                  {
                                                                                        nbarg = $5;
                                                                                        complete($8,addvalcreate(NULL,-3));  // -3 --> valeur de retour de la fonction (:pas encore implementé)
                                                                                    }
            ;



DECL_LOC: DECL_LOC  local ID '=' CONCATENATION ';' {printf(">Local\n");}
            |%empty 
            ;


APPEL_FONCTION: ID LISTE_ARG                                                       {
                                                                                        symbole *s;
                                                                                        if (!(s=findtable($1,0)))
                                                                                        {
                                                                                            fprintf(stderr,"Error %s not declared\n",$1);
                                                                                            exit(3);
                                                                                        }
                                                                                        gencode(GOTO,addvalcreate(s,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                    }
            |ID                                                                     {
                                                                                        symbole *s;
                                                                                        if (!(s=findtable($1,0)))
                                                                                        {
                                                                                            fprintf(stderr,"Error %s not declared\n",$1);
                                                                                            exit(3);
                                                                                        }
                                                                                        gencode(GOTO,addvalcreate(s,-1),addvalcreate(NULL,-1),addvalcreate(NULL,-1),0);
                                                                                    }
            ;

LISTE_ARG:LISTE_ARG OPERANDE            {
                                          
                                        } 
            |OPERANDE                   {
                                            
                                        }
            |'$''{'ID'[''*'']''}'       { 
                                            
                                        }
                                        
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