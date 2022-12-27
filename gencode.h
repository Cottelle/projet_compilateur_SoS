#ifndef GENCODE
#define GENCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "tabsymbole.h"

#define SIZECODE 32
#define SIZEPRINT 10      //evite les malloc dans printquad

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
    CALL,
    SYS
};

struct addval{
    struct symbole *s;      //if NULL it is immediate: is the value
    int value;
};


typedef struct quadrup
{
    enum instruction instruction;
    struct addval zero;
    struct addval one;
    struct addval two;
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
    int head;
    struct casestack *tail;
};

lpos *crelist(int position);

lpos *concat(lpos *l1, lpos *l2);

void complete(lpos *liste, struct addval value);

void gencode(enum instruction, struct addval z, struct addval o, struct addval t, int type);

struct addval addvalcreate(struct symbole *s,int value);

void printquad(void);

void casepush(int);

int casepop(void);

int casetop(void);

lpos *arggencode(lpos **);


#endif