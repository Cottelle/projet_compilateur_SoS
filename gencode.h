#ifndef GENCODE
#define GENCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct quadrup
{
    char *instruction;
    int cible;
    char free;
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

void gencode(char *code, int allowed);


#endif