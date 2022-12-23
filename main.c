#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"

extern int yyparse(void);
extern struct quad quad;

int main(void)
{
    quad.quadrup = NULL; // Sinon pb de realloc
    if (yyparse() != 0)
        ;
    printquad();
    printtabsymbole();
    return 0;
}