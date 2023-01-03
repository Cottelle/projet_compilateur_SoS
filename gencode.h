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

lpos *crelist(int position);

lpos *concat(lpos *l1, lpos *l2);

void complete(lpos *liste, struct addval value);

void gencode(enum instruction, struct addval z, struct addval o, struct addval t, int type);

struct addval avc(struct symbole *s,int value);

void printquad(void);

void casepush( struct symbole *s,int addr );

struct addval casepop(void);

struct addval casetop(void);

lpos *arggencode(lpos **);

struct symbole *stackpush(char *name,int value);



#endif