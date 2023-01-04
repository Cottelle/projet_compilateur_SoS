#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"
#include "SoS2MIPS.h"

extern int yyparse(void);
extern struct quad quad;

int main(void)
{
    quad.quadrup = NULL; // Sinon pb de realloc
    if (yyparse() != 0)
        ;
    printquad();
    printtabsymbole();
    il2MIPS(quad);
    return 0;
}