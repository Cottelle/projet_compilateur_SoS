#include <stdio.h>
#include "gencode.h"

extern int yyparse(void);
extern struct quad quad;

int main(void)
{
    quad.quadrup = NULL;                // Sinon pb de realloc
    if (yyparse() != 0)
        ;
    for (int i=0; i<quad.size;i++)
        printf("%s %i\n",quad.quadrup[i].instruction, quad.quadrup[i].cible );
    return 0;
}