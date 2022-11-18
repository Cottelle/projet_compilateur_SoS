#include <stdio.h>

extern int yyparse(void);

int main(void)
{
    if (yyparse() != 0)
        ;
    return 0;
}