#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"
#include "SoSMIPS.h"

extern int yyparse(void);
extern struct quad quad;

int main(void)
{
    quad.quadrup = NULL; // Sinon pb de realloc
    if (yyparse() != 0)
        ;
    printquad();
    printtabsymbole();
    iltoMIPS(quad);
    return 0;
}