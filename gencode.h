#ifndef GENCODE
#define GENCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SIZECODE 32

enum instruction
{
    GOTO,
    AFF,
    IF,
    CALL,
    SYS
};

typedef struct quadrup
{
    enum instruction instruction;
    int zero;
    int one;
    int two;
    int three;

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

void complete(lpos *liste, int cible);

void gencode(enum instruction, int z, int o, int t, int th);

void printquad(void);

void casepush(int);

int casepop(void);

#endif