#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"
#include "SoS2MIPS.h"
#include "args-parser.h"

extern int yyparse(void);
extern struct quad quad;
extern struct tabsymbole tabsymbole;
extern struct labels labels;

int main(int argc, char **argv)
{
    quad.quadrup = NULL; // Sinon pb de realloc
    struct options_t options;

    parseArgs(argc, argv, &options); // Parse les arguments
    if (yyparse() != 0)
        return 0;

    if (options.debug)
        printquad();
    if (options.debug || options.tos)
        printtabsymbole(options.debug);
    il2MIPS(quad, tabsymbole, labels,options.output);
    return 0;
}