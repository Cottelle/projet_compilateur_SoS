#include <stdio.h>
#include "gencode.h"

extern int yyparse(void);
extern struct quad quad;

int main(void)
{
    quad.quadrup = NULL; // Sinon pb de realloc
    if (yyparse() != 0)
        ;
    printf("<%i>\n", quad.next);
    for (int i = 0; i < quad.next; i++)
    {
        printf("[%i]%s ", i, quad.quadrup[i].instruction);
        if (quad.quadrup[i].cible!=-1)
            printf("%i\n",quad.quadrup[i].cible);
        else
            printf("\n");
    }
    return 0;
}