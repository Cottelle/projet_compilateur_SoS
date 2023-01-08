#ifndef GENCODE
#define GENCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "tabsymbole.h"

#define SIZECODE 32
#define SIZEPRINT 32      //evite les malloc dans printquad

struct stack
{
    unsigned int value;
    struct stack *next;
};



enum instruction
{
    GOTO,
    AFF,
    IF,
    SYS,
    CALL,
};

struct addval{
    struct symbole *s;      //if NULL it is immediate: is the value
    int value;
};


typedef struct quadrup
{
    struct addval zero;
    struct addval one;
    struct addval two;
    enum instruction instruction;
    int type;

} quadrup;

struct quad
{
    quadrup *quadrup;
    unsigned int size;
    unsigned int next;
};

typedef struct lpos
{
    int position;
    struct lpos *suivant;
} lpos;

struct casestack
{
    struct symbole *s;
    int addr;
    struct casestack *tail;
};


/**
 * init lpos with position value 
 */
lpos *crelist(int position);

/**
 * Concate two lpos
*/
lpos *concat(lpos *l1, lpos *l2);

/**
 * complete the zero addr of the quad in the position contain in liste
 */
void complete(lpos *liste, struct addval value);

/**
 * create a newquad (inc quad.next) with the instruction (GOTO AFF IF CALL ) with 3 addresse (or val) and with type (type 1 in AFF is an adition)
 */
void gencode(enum instruction, struct addval z, struct addval o, struct addval t, int type);

/**
 * create a addval struct with the arg 
 */
struct addval avc(struct symbole *s,int value);


/**
 * print the quad for debug
 * 
 */
void printquad(void);

/**
 * free the memory of quad
*/
void freequad(void);

/**
 * for case instruction push on a casestack the addval (s,addr)
*/
void casepush( struct symbole *s,int addr );

/**
 * pop the casestack and return it
*/
struct addval casepop(void);

/**
 * return the top of casestack
 */
struct addval casetop(void);


#endif