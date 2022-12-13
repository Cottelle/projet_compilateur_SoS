#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct quadrup
{
    char *instruction;
    int cible;
    char free;
} quadrup;

typedef struct quad
{
    quadrup *quadrup;
    unsigned int size;
    unsigned int next;
} quad;

typedef struct lpos
{
    int position;
    struct lpos *suivant;
} lpos;

lpos *crelist(int position);

lpos *concat(lpos *l1, lpos *l2);

void complete(lpos *liste, int cible);
