%{
#include<stdio.h>

#include "tabsymbole.h"
#include "gencode.h"
#include "usefull.h"

#define SIZEREAD 32
#define CELLSIZE 4

extern int yylex(void);
extern struct quad quad;
extern unsigned int nbarg;
extern unsigned int nligne;
unsigned int infun;



extern unsigned int cur_sp, cur_memory;             //cur_sp utilisé dans appel fonction
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

    struct{
        struct symbole *s;
        unsigned int addr;
    } operande;


}

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%token <entier> entier
%token <name> id mot chaine
%token declare if_ then elif else_ fi for_ do_ done in while_ until case_ esac echo read_ return_ exit_  test expr local to ta teq tne tgt tge tlt tle magic
%type <name> ID  
%type <operande> OPERANDE CONCATENATION OPERANDE_ENTIER OPERATEUR_ENTIER
%type <list_ope> LISTE_OPERANDES
%type <filtre> FILTRE
%type <cond> TEST_EXPR TEST_EXPR2 TEST_EXPR3 TEST_INSTRUCTION TEST_BLOC
%type <next> INSTRUCTION LISTE_INTRSUCTIONS ELSE_PART 
%type <nexfoll> LISTE_CAS
%type <quad> M
%start PROGRAMME

%%

                                                                                                                                                
PROGRAMME : {clabel("Bidon: C'est pour read");} LISTE_INTRSUCTIONS      {gencode(SYS,avc(NULL,10),avc(NULL,-1),avc(NULL,-1),0); }     //On ecrit l'endroit de la mémoire ici pour pouvoir dans le code generer acceder a cette memoire ( par ex dans read)
            ;

LISTE_INTRSUCTIONS: LISTE_INTRSUCTIONS ';'INSTRUCTION   {
                                                            $$ = $1;
                                                            complete($3,avc(NULL,quad.next));
                                                        } 
                | INSTRUCTION                           {
                                                            $$ = $1;                    //le remplace si il en est capable
                                                            complete($1,avc(NULL,quad.next));
                                                        }       
                ;


INSTRUCTION : ID '=' CONCATENATION                                                                                                          { 
                                                                                                                                                $$= NULL;
                                                                                                                                                struct symbole *s =findtable($1,1);
                                                                                                                                                s->nb= 1;                   //idem tableau 
                                                                                                                                                //s->isint ???
                                                                                                                                                gencode(AFF, avc(s,-1),avc($3.s,$3.addr),avc(NULL,-1),0);
                                                                                                                                            } 
            |ID'['OPERANDE_ENTIER']' '=' CONCATENATION                                                                                      {
                                                                                                                                                $$= NULL;
                                                                                                                                                printf(">ID[]= %s(%i)\n",$1,findtable($1,1)->memory_place);
                                                                                                                                            } 
            |declare ID'['entier']'                                                                                                                     {
                                                                                                                                                $$= NULL;
                                                                                                                                                struct symbole s = simples();
                                                                                                                                                s.nb = $4; //test si $4>0?
                                                                                                                                                s.name = $2;
                                                                                                                                                s.onstack_reg_label =0;
                                                                                                                                                int a = createsymbole(&s)->memory_place;
                                                                                                                                                printf(">declare %s[%i] : %i\n",$2,$4,a);
                                                                                                                                                 
                                                                                                                                            }
            |if_ TEST_BLOC then {complete($2.true, avc(NULL,quad.next));} LISTE_INTRSUCTIONS M {
                                                                                        gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0); 
                                                                                        complete($2.false, avc(NULL,quad.next));
                                                                                    }  
                ELSE_PART fi                                                                                                                {
                                                                                                                                                printf(">if \n"); 
                                                                                                                                                $$ = concat($5, crelist($6) ); 
                                                                                                                                            }
            |for_ ID                                                                                                                        {
                                                                                                                                                gencode(AFF,avc(findtable(createbuf("_for%i",++nbfor),1),-1),avc(NULL,quad.next+1),avc(NULL,-1),0);
                                                                                                                                            }  
                do_ M                                                                                                                        <next>{
                                                                                                                                                    lpos *start;
                                                                                                                                                    lpos *value =arggencode(&start);
                                                                                                                                                    char *buf = createbuf("_for%i",nbfor);
                                                                                                                                                    $$ = crelist(quad.next);
                                                                                                                                                    gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                                    complete(value, avc(findtable($2,1),-1));
                                                                                                                                                    complete(start,avc(NULL,quad.next));
                                                                                                                                                    gencode(AFF,avc(findtable(buf,0),-1),avc(findtable(buf,0),-1),avc(NULL,2),1);
                                                                                                                                                 } 
                LISTE_INTRSUCTIONS done                                                                                                         {
                                                                                                                                                        printf(">for in (%i)\n",findtable($2,1)->memory_place); 
                                                                                                                                                        $$ =$6; 
                                                                                                                                                        gencode(GOTO,avc(findtable(createbuf("_for%i",nbfor--),0),-1),avc(NULL,-1),avc(NULL,-1),0); 
                                                                                                                                                }
            |for_ ID in                                                                                                                         {
                                                                                                                                                    gencode(AFF,avc(findtable(createbuf("_for%i",++nbfor),1),-1),avc(NULL,quad.next+1),avc(NULL,-1),0);
                                                                                                                                                }
                 M LISTE_OPERANDES do_ M                                                                                                            {
                                                                                                                                                        char *buf = createbuf("_for%i",nbfor);
                                                                                                                                                        gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                                        complete($6.value, avc(findtable($2,1),-1));

                                                                                                                                                        complete($6.start,avc(NULL,quad.next));
                                                                                                                                                        gencode(AFF,avc(findtable(buf,0),-1),avc(findtable(buf,0),-1),avc(NULL,2),1);
                                                                                                                                                      free(buf);

                                                                                                                                                     } 
                LISTE_INTRSUCTIONS done                                                                                                         {
                                                                                                                                                    printf(">for in \n");
                                                                                                                                                    $$ =crelist($8);
                                                                                                                                                    gencode(GOTO,avc(findtable(createbuf("_for%i",nbfor--),0),-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                                } 
            |while_ M TEST_BLOC do_ {complete($3.true,avc(NULL,quad.next));} LISTE_INTRSUCTIONS done                                  {
                                                                                                                                                printf(">while \n");
                                                                                                                                                $$ = $3.false;
                                                                                                                                                complete($6, avc(NULL,$2)), gencode(GOTO,avc(NULL,$2),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            |until M TEST_BLOC do_ {complete($3.false, avc(NULL,quad.next));} LISTE_INTRSUCTIONS done                               {
                                                                                                                                                printf(">until \n");
                                                                                                                                                $$ = $3.true;
                                                                                                                                                complete($6, avc(NULL,$2)), gencode(GOTO,avc(NULL,$2),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            |case_  OPERANDE {casepush($2.s,$2.addr);} in LISTE_CAS esac                                           {
                                                                                                                                                printf(">case \n");
                                                                                                                                                $$ = concat($5.follow,$5.next) ;
                                                                                                                                                casepop();
                                                                                                                                                }
            |echo LISTE_ECHO                                                                                                           {
                                                                                                                                                $$ = NULL;
                                                                                                                                                printf(">echo \n");
                                                                                                                                            }
            |read_ ID                                                                                                                       {           // faudra utiliser le label la-1 de 32
                                                                                                                                                $$ = NULL;
                                                                                                                                                printf(">Read \n");
                                                                                                                                                struct symbole *id = findtable($2,1), *buf_read = malloc(sizeof(struct symbole));
                                                                                                                                                gencode(AFF,avc(reg(4),-1),avc(buf_read,-1),avc(NULL,-1),0); 
                                                                                                                                                gencode(AFF,avc(reg(5),-1),avc(NULL,SIZEREAD),avc(NULL,-1),0); 
                                                                                                                                                gencode(SYS,avc(NULL,4),avc(NULL,-1),avc(NULL,-1),0);

                                                                                                                                                //calcul de la taille 


                                                                                                                                            }
            |read_ ID'['OPERATEUR_ENTIER']'                                                                                                  {
                                                                                                                                                $$ = NULL;
                                                                                                                                                printf(">Read \n");
                                                                                                                                                struct symbole *mem = findtable("-mem",1), *id =findtable($2,0), *stemp =findtable("_read_id_tab",1);
                                                                                                                                                if (!id)
                                                                                                                                                {
                                                                                                                                                    // fprintf(stderr,"Error %s is not declared (declare %s[%i] before) \n",$2,$2,$4);
                                                                                                                                                    exit(2);
                                                                                                                                                }

                                                                                                                                                stemp->isint =1;
                                                                                                                                                stemp->nb =1;
                                                                                                                                                stemp->onstack_reg_label =0;



                                                                                                                                                
                                                                                                                                                gencode(AFF,avc(stemp,-1),avc(NULL,id->memory_place),avc($4.s,$4.addr),0);           //--> pb de double  indirection

                                                                                                                                                gencode(AFF,avc(stemp,-1),avc(mem,-1),avc(NULL,SIZEREAD),1);

                                                                                                                                                gencode(AFF,avc(reg(4),-1),avc(mem,-1),avc(NULL,-1),0);
                                                                                                                                                gencode(AFF,avc(reg(5),-1),avc(NULL,SIZEREAD),avc(NULL,-1),0);
                                                                                                                                                gencode(AFF,avc(NULL,-8),avc(NULL,-1),avc(NULL,-1),0);                                                                                                                                            
                                                                                                                                                gencode(AFF,avc(mem,-1),avc(mem,-1),avc(NULL,SIZEREAD),1);
                                                                                                                                            }
            |DECLARATION_FONTION                                                                                                            {
                                                                                                                                                printf(">declaration fonction \n");
                                                                                                                                                $$ = NULL;
                                                                                                                                            }
            |return_                                                                                                                        {
                                                                                                                                                $$ =NULL;
                                                                                                                                                printf(">return \n");
                                                                                                                                                if(!infun)
                                                                                                                                                {
                                                                                                                                                    fprintf(stderr,"Error you are not in a function you can't return (use exit to exit the programme)\n");
                                                                                                                                                    exit(1);
                                                                                                                                                }

                                                                                                                                                gencode(AFF,avc(findtable("_ret_val",1),-1) ,avc(NULL,0),avc(NULL,-1),0);
                                                                                                                                                gencode(GOTO,avc(reg(31),-1) ,avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            |return_ '(' OPERATEUR_ENTIER ')'                                                                                                        {
                                                                                                                                                $$ =NULL;
                                                                                                                                                printf(">return entier \n");
                                                                                                                                                if(!infun)
                                                                                                                                                {
                                                                                                                                                    fprintf(stderr,"Error you are not in a function you can't return (use exit to exit the programme)\n");
                                                                                                                                                    exit(1);
                                                                                                                                                }

                                                                                                                                                gencode(AFF,avc(findtable("_ret_val",1),-1) ,avc(reg(23),-1),avc(NULL,-1),0);
                                                                                                                                                gencode(GOTO,avc(reg(31),-1) ,avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            |APPEL_FONCTION                                                                                                                 {
                                                                                                                                                printf(">appel fonction \n");
                                                                                                                                                $$=NULL;
                                                                                                                                                
                                                                                                                                            }
            |exit_                                                                                                                          {
                                                                                                                                                $$ =NULL;
                                                                                                                                                printf(">exit \n");
                                                                                                                                                gencode(AFF,avc(reg(31),-1) ,avc(NULL,0),avc(NULL,-1),0);
                                                                                                                                                gencode(SYS,avc(NULL,10) ,avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            |exit_ '(' OPERATEUR_ENTIER ')'                                                                                                          {
                                                                                                                                                $$ =NULL;
                                                                                                                                                printf(">exit entier \n");
                                                                                                                                                gencode(AFF,avc(reg(31),-1) ,avc(reg(23),-1),avc(NULL,-1),0);
                                                                                                                                                gencode(SYS,avc(NULL,10) ,avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                            }
            ;                                       



ELSE_PART: elif TEST_BLOC                                                                                                                   {
                                                                                                                                                complete($2.true, avc(NULL,quad.next));
                                                                                                                                            } 
                then LISTE_INTRSUCTIONS M                                                                                                       {
                                                                                                                                                     gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                                     complete($2.false, avc(NULL,quad.next));
                                                                                                                                                 } 
                    ELSE_PART                                                                                                                         { 
                                                                                                                                                        $$ = concat(crelist($6),$5);
                                                                                                                                                        $$ = concat($$,crelist(quad.next));
                                                                                                                                                        gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                                      }
            |else_ LISTE_INTRSUCTIONS                                                                                                        {
                                                                                                                                                 $$ = $2;
                                                                                                                                                 $$ = concat($$,crelist(quad.next));
                                                                                                                                                 gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                                                                             }
            |%empty                                                                                                                          {
                                                                                                                                                $$= NULL;
                                                                                                                                             }
    

LISTE_CAS: LISTE_CAS M FILTRE ')' M                                                                                                         { 
                                                                                                                                                gencode(IF,avc(NULL,-1),avc(casetop().s,casetop().value),avc(clabel($3.last),-1),1); 
                                                                                                                                                complete($3.entrer,avc(NULL,quad.next));
                                                                                                                                            } 
                 LISTE_INTRSUCTIONS ';'';'                                                                                                                      {
                                                                                                                                                                    $$.next = concat($7,crelist(quad.next)); 
                                                                                                                                                                    gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0); 
                                                                                                                                                                    $$.next = concat($$.next,$1.next); 
                                                                                                                                                                    complete($1.follow,avc(NULL,$2)); 
                                                                                                                                                                    $$.follow = crelist($5) ; 
                                                                                                                                                                } 
            |M FILTRE ')'M                                                                                                                  {
                                                                                                                                                 gencode(IF,avc(NULL,-1),avc(casetop().s,casetop().value),avc(clabel($2.last),-1),1); 
                                                                                                                                                 complete($2.entrer,avc(NULL,quad.next));
                                                                                                                                            } 
                LISTE_INTRSUCTIONS ';'';'                                                                                                                       {
                                                                                                                                                                    $$.next = concat($6,crelist(quad.next));
                                                                                                                                                                    gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
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
                                        gencode(IF,avc(NULL,-1),avc(casetop().s,casetop().value),avc(clabel($1.last),-1),0);
                                    }           
           |FILTRE '|'chaine        {
                                        $$.last=$3;
                                        $$.entrer = concat($1.entrer, crelist(quad.next)) ;
                                        gencode(IF,avc(NULL,-1),avc(casetop().s,casetop().value),avc(clabel($1.last),-1),0) ;
                                    }     
            |FILTRE '|' ID          {
                                        $$.last=$3;
                                        $$.entrer = concat($1.entrer, crelist(quad.next)) ;
                                        gencode(IF,avc(NULL,-1),avc(casetop().s,casetop().value),avc(clabel($1.last),-1),0) ;
                                    }              
           | '*'                    {
                                        $$.entrer = crelist(quad.next) ;
                                        gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                        $$.last = "Bidon"; 
                                    }
           ;


LISTE_OPERANDES:LISTE_OPERANDES OPERANDE {
                                            $$.start = concat($1.start,crelist(quad.next+1)); 
                                            $$.value = concat($1.value, crelist(quad.next));
                                             gencode(AFF,avc(NULL,-1),avc($2.s,$2.addr),avc(NULL,-1),0); 
                                             gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                        } 
            |OPERANDE                   {
                                            $$.start = crelist(quad.next+1) ;
                                            $$.value = crelist(quad.next);
                                            gencode(AFF,avc(NULL,-1),avc($1.s,$1.addr),avc(NULL,-1),0);
                                            gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                        }
            |'$''{'ID'[''*'']''}'        { 
                                            struct symbole *id= findtable($3,0); 
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
                                                gencode(AFF,avc(NULL,-1),avc(NULL,id->memory_place+i*CELLSIZE),avc(NULL,-1),0);      //pb car c'est une addr et pas direct ... a mediter quand les tab seront elusider
                                                gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                                            }
                                        } 
            ;

LISTE_ECHO:LISTE_ECHO OPERANDE {
                                             gencode(AFF,avc(reg(4),-1),avc($2.s,$2.addr),avc(NULL,-1),0); 
                                             gencode(SYS,avc(NULL,4),avc(NULL,-1),avc(NULL,-1),0);
                                        } 
            |OPERANDE                   {
                                            struct symbole *s = malloc(sizeof(struct symbole));
                                            if (!s)
                                            {
                                                fprintf(stderr,"Error malloc\n");
                                                exit(1);
                                            }
                                            s->name = "BIDON";
                                            s->memory_place = 4;
                                            s->onstack_reg_label =2;
                                            s->isint =4;
                                             gencode(AFF,avc(s,-1),avc($1.s,$1.addr),avc(NULL,-1),0);
                                             if ($1.s && $1.s->isint)
                                                 gencode(SYS,avc(NULL,1),avc(NULL,-1),avc(NULL,-1),0);
                                            else
                                             gencode(SYS,avc(NULL,4),avc(NULL,-1),avc(NULL,-1),0);
                                        }
            |'$''{'ID'[''*'']''}'        { 
                                            struct symbole *id= findtable($3,0); 
                                            if(!id) 
                                            {
                                                fprintf(stderr,"Error %s is Unknow \n",$3); 
                                                exit(2); 
                                            } 
                                            struct symbole *s;
                                            for(int i=0 ;i<id->nb ; i++)
                                            {
                                                s = malloc(sizeof(struct symbole));
                                                if (!s)
                                                {
                                                    fprintf(stderr,"Error malloc\n");
                                                    exit(1);
                                                }
                                                s->name = "BIDON";
                                                s->onstack_reg_label =2;
                                                s->memory_place = 4;
                                                s->isint =4;

                                                gencode(AFF,avc(s,-1),avc(NULL,id->memory_place+i*CELLSIZE),avc(NULL,-1),0);      //pb car c'est une addr et pas direct ... a mediter quand les tab seront elusider
                                                 gencode(SYS,avc(NULL,4),avc(NULL,-1),avc(NULL,-1),0);
                                            }
                                        } 
            ;



CONCATENATION: CONCATENATION OPERANDE   {$$.s = NULL ; $$.addr = -1;}
            |OPERANDE           {$$ = $1;}
            ;


TEST_BLOC: test TEST_EXPR   {$$=$2;}
            ;


TEST_EXPR: TEST_EXPR to {complete($1.false, avc(NULL,quad.next)); } TEST_EXPR2    {
                                                                            $$.true = concat($1.true,$4.true);
                                                                            $$.false = $4.false;
                                                                        }
            |TEST_EXPR2                                                 {
                                                                            $$= $1;
                                                                        }
            ;


TEST_EXPR2: TEST_EXPR2 ta {complete($1.true,avc(NULL,quad.next)); } TEST_EXPR3    {
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


TEST_INSTRUCTION :CONCATENATION '=' CONCATENATION       // Si operande entier comparaison impossible -> false 
            |CONCATENATION '!''=' CONCATENATION         //idem 
            |OPERATEUR1 CONCATENATION 
            |OPERANDE OPERATEUR2 OPERANDE 
            |magic {                                                                        //Pour tester
                $$.true = crelist(quad.next);
                gencode(GOTO,avc(NULL,-1),avc(NULL,-1),avc(NULL,-1),0);
                $$.false = NULL;
                    }
            ;


OPERANDE:'$''{'ID'}'                          {
                                                $$.s = findtable($3,0);
                                                }
            |'$''{'ID'['OPERANDE_ENTIER']''}' {
                                                $$.s=NULL;
                                                $$.addr= findtable($3,0)->memory_place;              //pb ici
                                                }
            |mot                              {
                                                $$.s=clabel($1);
                                                $$.addr=-1;
                                                }
            |entier                           {                      //Rajouter a la grammaire 
                                                char *mal = malloc(32);
                                                 if (!mal)
                                                 {
                                                    fprintf(stderr,"Error malloc qs");
                                                    exit(1);
                                                 } 
                                                 snprintf(mal,32,"%i",$1);
                                                $$.s=clabel(mal);
                                                 $$.addr = -1;
                                                }                     
            |id                               {
                                                $$.addr =-1;
                                                $$.s=clabel($1);
                                                }     //Rajouter a la grammaire
            |chaine                           {
                                                $$.addr =-1;
                                                $$.s=clabel($1);
                                                }
            |'$'entier                         { 
                                                if($2>nbarg)
                                                {
                                                    fprintf(stderr,"Error $%i doesn't exit (there is %i arg) \n",$2,nbarg);
                                                    exit(3);
                                                }
                                                char buf[4];
                                                if (snprintf(buf,4,"$%i",$2)<0)
                                                {
                                                    fprintf(stderr,"Error snprintf\n");
                                                    exit(2);
                                                }
                                                $$.s = spfindtable(buf,0);              //Si c'est un int ça ne marche pas ... pb ici
                                                }
            |'$''*'                             {          
                                                    $$.s=NULL;                         //pas connu a la compim
                                                    if(nbarg==0)
                                                        $$.addr=writestringmemory(" ");
                                                    else
                                                    {
                                                        char *buf ="$1";
                                                        $$.addr=spfindtable(buf,0)->memory_place;                //ne marche pas     pb ici
                                                        for(int i=1;i<nbarg;i++)
                                                        {

                                                        }
                                                    }
                                                }
            |'$''?'                             {
                                                    $$.s = reg(31);
                                                    $$.addr = -1; 
                                                    /* struct symbole s =simples();
                                                    s.onstack_reg_label=2;
                                                    s.name="$?";
                                                    s.isint = 15;               //prend la valeur du registre
                                                    struct symbole *sb=createsymbole(&s);      */                 //the symbole $? ????????
                                                }
            |'$''('expr OPERATEUR_ENTIER ')' 
            |'$' '('APPEL_FONCTION ')'          {
                                                    //Il faut store $? puis appeler la fonction voire le nouveau $? puis remettre l'ancient ou pas, je ne sais pas 
                                                }
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

//possible error if weird calcls
OPERATEUR_ENTIER:OPERATEUR_ENTIER '*' OPERANDE_ENTIER   {
                                                            //create buffer to store result
                                                            gencode(AFF, avc(reg(23), -1), avc(reg(23), -1), avc($3.s, $3.addr), 3);
                                                        }
                |OPERATEUR_ENTIER '/' OPERANDE_ENTIER   {

                                                            gencode(AFF, avc(reg(23), -1), avc(reg(23), -1), avc($3.s, $3.addr), 4);
                                                        }
                |OPERATEUR_ENTIER '%' OPERANDE_ENTIER   {

                                                            gencode(AFF, avc(reg(23), -1), avc(reg(23), -1), avc($3.s, $3.addr), 42);
                                                        }
                |OPERATEUR_ENTIER '+' OPERANDE_ENTIER   {

                                                            gencode(AFF, avc(reg(23), -1), avc(reg(23), -1), avc($3.s, $3.addr), 1);
                                                        }
                |OPERATEUR_ENTIER '-' OPERANDE_ENTIER   {

                                                            gencode(AFF, avc(reg(23), -1), avc(reg(23), -1), avc($3.s, $3.addr), 2);
                                                        }
                |'(' OPERATEUR_ENTIER ')'               {

                                                        }
                |OPERANDE_ENTIER                        {
                                                            gencode(AFF, avc(reg(23), -1), avc($1.s, $1.addr), avc(NULL, -1), 0);
                                                        }
                |'+' OPERANDE_ENTIER                    {
                                                            gencode(AFF, avc(reg(23), -1), avc($2.s, $2.addr), avc(NULL, -1), 0);
                                                        }
                |'-' OPERANDE_ENTIER                    {
                                                            gencode(AFF, avc(reg(23), -1), avc($2.s, $2.addr), avc(NULL, -1), 3);
                                                        }




OPERANDE_ENTIER:'$''{'ID'}' {
                                if ( ($$.s=findtable($3, 0)) == NULL ) {
                                    //erreur
                                }
                                $$.s->isint = 1;
                                $$.addr=-1;
                            }
            |'$''{'ID'['OPERANDE_ENTIER']''}'   {
                                                    $$.s=NULL;
                                                    $$.addr=-1;
                                                }
            |'$' entier { 
                            if($2 > nbarg) {
                                //erreur
                            }
                            $$.s=spfindtable(createbuf("$%i", $2), 0);
                            $$.addr=-1;
                        }
            |entier {                      
                        $$.addr = $1;
                        $$.s=NULL;
                    }  
            ;


DECLARATION_FONTION: ID '(' entier ')'                                              <entier>{       //chagement de la grammaire (ajout entier) car sinon valeur inconue à la compilation (nb d'argument) ce qui pose nottament probleme sur for i do ...
                                                                                        infun++;
                                                                                        struct function *f = findfun($1,1);                 //peut ecraser une autre function
                                                                                        f->nbarg = $3;
                                                                                        $$ = nbarg;
                                                                                        nbarg = $3;

                                                                                        nextstackcreate();              //the local variable space is create

                                                                                        char *buf;
                                                                                        
                                                                                        for(int i=0;i<$3;i++)
                                                                                        {
                                                                                            if ((buf=malloc(4))<0)
                                                                                            { 
                                                                                                fprintf(stderr,"Error malloc\n");
                                                                                            exit(1);
                                                                                            }
                                                                                          if (snprintf(buf,4,"$%i",i+1)<0)
                                                                                          {
                                                                                            fprintf(stderr,"Error snprintf\n");
                                                                                            exit(1);
                                                                                          }
                                                                                          struct symbole *s=spfindtable(buf,1);            //create the entry on sp for the arg
                                                                                        }   

                                                                                        f->place = quad.next;

                                                                                    }
                '{'DECL_LOC LISTE_INTRSUCTIONS '}'                                  {
                                                                                        nbarg = $5;                                     // On resature le nb d'arg d'avant
                                                                                        complete($8,avc(reg(31),-1));  // -3 --> valeur de retour de la fonction (:pas encore implementé)
                                                                                        gencode(AFF,avc(findtable("_ret_val",1),-1),avc(NULL,0),avc(NULL,-1),0);
                                                                                        gencode(GOTO,avc(reg(31),-1),avc(NULL,-1),avc(NULL,-1),0);
                                                                                        popstacknext();                  //the local variable space is delete
                                                                                        infun--;
                                                                                    }
            ;



DECL_LOC: DECL_LOC  local ID '=' CONCATENATION ';'                                      {
                                                                                            printf(">Local\n");
                                                                                            struct symbole s;
                                                                                            s.name = $3;
                                                                                            s.isint =0;
                                                                                            struct symbole *id =spcreatesymbole(&s);
                                                                                            gencode(AFF,avc(id,-1),avc($5.s,$5.addr),avc(NULL,-1),0);

                                                                                        }
            |%empty 
            ;


APPEL_FONCTION: ID                                                                      {
                                                                                            
                                                                                        }
                LISTE_ARG                                                                   {
                                                                                                struct function *f;
                                                                                                if (!(f = findfun($1,0)))
                                                                                                {
                                                                                                    fprintf(stderr,"Error %s not declared\n",$1);
                                                                                                    exit(3);
                                                                                                }
                                                                                                gencode(GOTO,avc(NULL,f->place),avc(NULL,-1),avc(NULL,-1),1);
                                                                                            }
            |ID                                                                     {
                                                                                        struct function *f;
                                                                                        if (!(f=findfun($1,0)))
                                                                                        {
                                                                                            fprintf(stderr,"Error %s not declared\n",$1);
                                                                                            exit(3);
                                                                                        }
                                                                                        gencode(GOTO,avc(NULL,f->place),avc(NULL,-1),avc(NULL,-1),0);
                                                                                    }
            ;

LISTE_ARG: OPERANDE LISTE_ARG             {         //arg à l'envers comme le C
                                            struct symbole s =simples();
                                            s.onstack_reg_label =1;
                                            s.name = malloc(5);
                                            if (!s.name ||snprintf(s.name,5,"_%i",cur_sp)<0)
                                            {
                                                fprintf(stderr,"Error malloc or snprintf\n");
                                                exit(2);
                                            }
                                            struct symbole *sb=spcreatesymbole(&s);
                                            gencode(AFF,avc(sb,-1),avc($1.s,$1.addr),avc(NULL,-1),0);     //même pb que pour for ${id[*]}, cela revient a push sur la pile 
                                        } 
            |OPERANDE                   {
                                            struct symbole s =simples();
                                            s.onstack_reg_label =1;
                                            s.name=malloc(5);
                                            if (!s.name ||snprintf(s.name,5,"_%i",cur_sp)<0)
                                            {
                                                fprintf(stderr,"Error malloc or snprintf\n");
                                                exit(2);
                                            }
                                            struct symbole *sb=spcreatesymbole(&s);
                                            gencode(AFF,avc(sb,-1),avc($1.s,$1.addr),avc(NULL,-1),0);

                                            
                                        }
            |'$''{'ID'[''*'']''}'       { 
                                          struct  symbole *id= findtable($3,0); 
                                            if(!id) 
                                            {
                                                fprintf(stderr,"Error %s is Unknow \n",$3); 
                                                exit(2); 
                                            } 
                                            for(int i=0 ;i<id->nb ; i++)
                                            {
                                                gencode(AFF,avc(NULL,-1),avc(NULL,id->memory_place+i*CELLSIZE),avc(NULL,-1),0);      //pb car c'est une addr et pas direct ... a mediter quand les tab seront elusider
                                                cur_sp+=CELLSIZE;
                                            }
                                            
                                        }
                                        
            ;


ID : id //C'est bien un id
    |mot    //C'est prit pour mot mais peut être que c'est un id
    ;


M: %empty { $$ = quad.next;}

%%

void yyerror(const char *msg)
{
    fprintf(stderr,"%s ligne %i\n",msg,nligne);
}