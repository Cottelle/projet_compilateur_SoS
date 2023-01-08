#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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

    if (options.input)
    {
        int fd = open(options.input,O_RDONLY);
        if (fd==-1)
        {
            fprintf(stderr,"Error can't open %s\n",options.input);
            exit(2);
        }
        if(dup2(fd,0)==-1)
        {
            fprintf(stderr,"Error dup2 failed\n");
            exit(2);
        }

    }

    if (yyparse() != 0)
        return 0;

    if (options.debug)
        printquad();
    if (options.debug || options.tos)
        printtabsymbole(options.debug);
    il2MIPS(quad, tabsymbole, labels, options.output);
    return 0;
}