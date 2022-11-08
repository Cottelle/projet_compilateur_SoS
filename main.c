#include <stdio.h>

extern int yyparse(void);

int main(void)
{
    while (yyparse() != 0)
        ;
    return 0;
}