#ifndef TABSYMBOL
#define TABSYMBOL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITSIZETAB 0;


struct tabsymbole{
    int size;
    struct symbole{
        char *name;
        char IsInt;
        char used; 
    } *tab;
};


/**
 * *  return the index in the tabsymbole -1 if issn't present and create = 0, else create (Isint id create =2)  
 */
unsigned int findtable(char *id,int create);



/**
 * Print the tabsymbol
 */
void printtabsymbole(void);



#endif

