#ifndef TABSYMBOL
#define TABSYMBOL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "usefull.h"

#define INITSIZETAB 0
#define MEMORYSIZE 1024
#define CELLSIZE 4              //the size of one cell in memory (addr or int) 




struct symbole{
        char *name;
        unsigned int nb; 
        unsigned int memory_place;
        int fun;               // -1 if not function else the number of argument
        char isint;             //if the isint the memory_place direct contained the value else contained the addr to the string. Also if the onstack_reg=2 contain the number of register
        char onstack_reg;           //1 is int the stack 2 if is register (can't be on the stack and a register)
};

struct tabsymbole{
    int size;
    struct symbole** tab;
};


struct tabsymbolesp{
    struct tabsymbolesp *next;                 //The next local variable tab                     
    int size;
    struct symbole **tab;                              //The currents locals variables   
};

/**
 * *  return the index in the tabsymbole -1 if issn't present and create = 0, else create 
 */
struct symbole *findtable(char *id,int create);



/**
 * create an entry in tabsymbole with s atribute (name, nb, isint) following
*/
struct symbole *createsymbole(struct symbole *s);

/**
 * return a classique symbole isint =0, fun =-1, name = NULL, nb=1, 
*/
struct symbole simples(void);


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
 * Create (alloc) the next int tabsymbolesp
*/
struct tabsymbolesp *nextstackcreate(void);

/**
 * pop the last next of tabsymbolesp 
*/
void popstacknext(void);

/**
 * *  return the index in the tabsymbole -1 if issn't present and create = 0, else create. For local variable (on the stack)
 */
struct symbole *spfindtable(char *id,int create);



/**
 * create an entry in tabsymbole with s atribute (name, nb, isint) following. For local variable (on the stack.
*/
struct symbole *spcreatesymbole(struct symbole *s);

/**
 * return a classique symbole isint =0, fun =-1, name = NULL, nb=1. For local variable (on the stack)
*/
struct symbole spsimples(void);


/**
 * write the buf in the stack
 */
unsigned int writesp(char *buf, int sizebuf);


/**
 * Write string in the stack until '\0' (include) following
 */
unsigned int writestringsp(char *buf);

/**
 * Write in the stack at the place the buf 
*/
void insp(unsigned int place,char *buf,int sizebuf);



/**
 * return an allocated symbole of registre $value
*/
struct symbole *reg(int value);


/**
 * Print the tabsymbol
 */
void printtabsymbole(void);



#endif

