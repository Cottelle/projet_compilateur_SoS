#ifndef TABSYMBOL
#define TABSYMBOL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITSIZETAB 0
#define MEMORYSIZE 1024

struct symbole{
        char *name;
        char IsInt;             //if the IsInt the memory_place direct contained the value else contained the addr to the string
        char used; 
        unsigned int memory_place;
        unsigned int size; 
};

struct tabsymbole{
    int size;
    struct symbole* tab;
};


/**
 * *  return the index in the tabsymbole -1 if issn't present and create = 0, else create 
 */
struct symbole *findtable(char *id,int create);


/**
 * write the buf in memory
 */
unsigned int writememory(char *buf, int sizebuf);


/**
 * Write string in memory until '\0' (include)
 */
unsigned int writestringmemory(char *buf);




/**
 * Print the tabsymbol
 */
void printtabsymbole(void);



#endif

