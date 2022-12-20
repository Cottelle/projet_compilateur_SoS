#include "gencode.h"

struct quad quad;

struct casestack *casestack;

lpos *crelist(int position)
{
    lpos *new = malloc(sizeof(lpos));
    if (!new)
    {
        fprintf(stderr, "Error malloc\n");
        exit(1);
    }
    new->position = position;
    new->suivant = NULL;
    return new;
}

lpos *concat(lpos *l1, lpos *l2)
{
    lpos *res;
    if (l1 != NULL)
        res = l1;
    else if (l2 != NULL)
        res = l2;
    else
        res = NULL;
    if (l1 != NULL)
    {
        while (l1->suivant != NULL)
        {
            l1 = l1->suivant;
        }
        l1->suivant = l2;
    }
    return res;
}

void complete(lpos *liste, int cible)
{
    lpos *last = liste;
    if (liste)
    {
        quad.quadrup[liste->position].zero = cible;
        while (liste->suivant != NULL)
        {
            liste = liste->suivant;
            quad.quadrup[liste->position].zero = cible;
            free(last);
            last = liste;
        }
    }
}

void gencode(enum instruction instruction, int z, int o, int t, int th )
{
    if (quad.size <= quad.next)
    {
        if (quad.size == 0)
            quad.size++;
        quad.size = 100;
        quad.quadrup = realloc(quad.quadrup, 100);
        if (!quad.quadrup)
        {
            fprintf(stderr, "[gSoSSoS]Erreur genecode: realloc");
            exit(1);
        }
    }

    quad.quadrup[quad.next].instruction= instruction;
    quad.quadrup[quad.next].zero = z;
    quad.quadrup[quad.next].one = o;
    quad.quadrup[quad.next].two = t;
    quad.quadrup[quad.next].three = th;

    quad.next++;
}


void printquad()
{
    for(int i=0; i<quad.next;i++)
    {
        printf("%i ",i);
        switch (quad.quadrup[i].instruction)
        {
        case GOTO:
            printf("goto %i\n",quad.quadrup[i].zero);
            break;

        case AFF:
            printf("[%i]:=\n",quad.quadrup[i].zero);
            break;
        
        case IF:
            printf("if %i = %i goto %i",quad.quadrup[i].zero,quad.quadrup[i].one,quad.quadrup[i].two);
            break;
        
        case CALL:
            printf("call %i\n",quad.quadrup[i].zero);
            break;

        case SYS:
            printf("sys %i\n",quad.quadrup[i].zero);

        default:
            printf("??\n");
            break;
        }
    }
}



void casepush(int value)
{
    struct casestack *head = malloc(sizeof(struct casestack));
    if (!head)
    {
        fprintf(stderr,"Error malloc (casepush)\n");
        exit(1);
    }
    head->head= value;
    head->tail= casestack;
    casestack = head;
}

int casepop(void)
{
    if(!casestack)
    {
        fprintf(stderr,"Error casestack is empty\n");
        exit(2);
    }
    int ret = casestack->head;
    struct casestack *temp = casestack->tail;
    free(casestack);
    casestack = temp;

    return ret;

}
