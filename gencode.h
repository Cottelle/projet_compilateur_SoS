#ifndef GENCODE
#define GENCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define SIZECODE 32

typedef struct quadrup
{
    char *instruction;
    int cible;
    char free;
    /* 
    char instruction
    char z;                 On pert l'ecriture des id par exemple (juste indice dans tabsymbole) 
    char u;
    char d;
    char t;
     */
} quadrup;

struct quad
{
    quadrup *quadrup;
    unsigned int size;
    unsigned int next;
};

typedef struct lpos
{
    int position;
    struct lpos *suivant;
} lpos;




lpos *crelist(int position);

lpos *concat(lpos *l1, lpos *l2);

void complete(lpos *liste, int cible);

void gencode(int alowed,char *code,...);


#endif