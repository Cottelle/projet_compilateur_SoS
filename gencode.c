#include "gencode.h"


struct quad quad;

lpos *crelist(int position)
{
    lpos *new = malloc(sizeof(lpos));
    new->position = position;
    new->suivant = NULL;
    return new;
}

lpos *concat(lpos *l1, lpos *l2)
{
    lpos *res;
    if (l1 != NULL)
        res = l1;
    else if (l2 != NULL)
        res = l2;
    else
        res = NULL;
    if (l1 != NULL)
    {
        while (l1->suivant != NULL)
        {
            l1 = l1->suivant;
        }
        l1->suivant = l2;
    }
    return res;
}

void complete(lpos *liste, int cible)
{
    lpos *last = liste;
    if (liste)
    {
        quad.quadrup[liste->position].cible = cible;
        while (liste->suivant != NULL)
        {
            liste = liste->suivant;
            quad.quadrup[liste->position].cible = cible;
            free(last);
            last = liste;
        }
    }
}

void gencode(char *code, int allowed)
{
    if (quad.size <= quad.next)
    {
        if (quad.size ==0)
            quad.size++;
        quad.size=2* quad.size;
        quad.quadrup = realloc(quad.quadrup, quad.size);
        if (!quad.quadrup)
            {
                fprintf(stderr,"[gSoSSoS]Erreur genecode: realloc");
                exit(1);
            }
    }
    quad.quadrup[quad.next].instruction = code;
    quad.quadrup[quad.next].cible = -1;
    if (allowed)
        quad.quadrup[quad.next].free = 1;
    quad.next++;
}
