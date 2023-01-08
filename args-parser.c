
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

#include "args-parser.h"

void printhelp(void)
{

    printf("Usage : CcS [OPTION]");
    printf("\n\n  -i <file>          File is the input of the compiler");
    printf("\n  -o <file>            The mips genereted code is in file");
    printf("\n  -version             Print the version and the members");
    printf("\n  -tos                 Print the table of symbole");
    printf("\n  -d                   Print debug (table symbole, some memory state,intermediate code) ");
    printf("\n  -h                   print help\n\n");
    return;
}

void cleanOptions(struct options_t *options)
{
    options = options;
    return;
}

void initOptions(struct options_t *options)
{
    options->output = 0;
    options->input = 0;
    options->tos = 0;
    options->debug = 0;
}

void parseArgs(int argc, char **argv, struct options_t *options)
{

    initOptions(options);

    int c;
    while ((c = getopt(argc, argv, "i:o:d:t:vh")) != -1)
    {
        switch (c)
        {
        case 'h':
            printhelp();
            exit(7);
        case 'v':
            printf("Version 1.01\n-Sylvain Balakrishnan\n-Jules Brandsaedt\n-Nicolas Cipolla\n-Maxime Collette\n");
            exit(7);

        case 'i':
            options->input = optarg;
            break;
        case 'o':
            options->output = optarg;
            break;
        case 't':
            options->tos = 1;
            break;
        case 'd':
            options->debug = 1;
            break;

        case '?':
            fprintf(stderr, "Unknown option, try again\n");
            if (optopt == 'i' || optopt == 'o' || optopt == 'f' || optopt == 'v' || optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            abort();
        default:
            abort();
        }
    }

}