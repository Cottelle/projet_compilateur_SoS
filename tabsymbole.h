#ifndef TABSYMBOL
#define TABSYMBOL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITSIZETAB 0
#define MEMORYSIZE 1024
#define CELLSIZE 4              //the size of one cell in memory (addr or int) 

typedef struct symbole{
        char *name;
        char isint;             //if the isint the memory_place direct contained the value else contained the addr to the string
        int fun;               // -1 if not function else the number of argument
        char used; 
        unsigned int memory_place;
        unsigned int nb; 
}symbole;

struct tabsymbole{
    int size;
    symbole* tab;
};


/**
 * *  return the index in the tabsymbole -1 if issn't present and create = 0, else create 
 */
struct symbole *findtable(char *id,int create);



/**
 * create an entry in tabsymbole with s atribute (name, nb, isint) following
*/
symbole *createsymbole(symbole *s);

/**
 * return a classique symbole isint =0, fun =-1, name = NULL, nb=1, 
*/
symbole simples(void);


/**
 * write the buf in memory
 */
unsigned int writememory(char *buf, int sizebuf);


/**
 * Write string in memory until '\0' (include) following
 */
unsigned int writestringmemory(char *buf);

/**
 * Write in memory at the place the buf
*/
void inmemory(unsigned int place,char *buf,int sizebuf);




/**
 * Print the tabsymbol
 */
void printtabsymbole(void);



#endif

