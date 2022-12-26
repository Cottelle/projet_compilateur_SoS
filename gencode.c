#include "gencode.h"

struct quad quad;

struct casestack *casestack;

unsigned int nbarg;

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

void gencode(enum instruction instruction, int z, int o, int t, int th)
{
    if (quad.size <= quad.next)
    {
        if (quad.size == 0)
            quad.size++;
        quad.size *= 2;
        quad.quadrup = realloc(quad.quadrup, quad.size * sizeof(quadrup));
        if (!quad.quadrup)
        {
            fprintf(stderr, "[gSoSSoS]Erreur genecode: realloc");
            exit(1);
        }
    }

    quad.quadrup[quad.next].instruction = instruction;
    quad.quadrup[quad.next].zero = z;
    quad.quadrup[quad.next].one = o;
    quad.quadrup[quad.next].two = t;
    quad.quadrup[quad.next].three = th;

    quad.next++;
}

void printquad()
{
    for (int i = 0; i < quad.next; i++)
    {
        printf("%i ", i);
        switch (quad.quadrup[i].instruction)
        {
        case GOTO:
            if (quad.quadrup[i].one == 0)
                printf("goto [%i]\n", quad.quadrup[i].zero);
            else
                printf("goto %i\n", quad.quadrup[i].zero);
            break;

        case AFF:
            if (quad.quadrup[i].two >= 0)
                printf("[%i]:=%i %s %i\n", quad.quadrup[i].zero, quad.quadrup[i].one, (quad.quadrup[i].two == 1) ? "+" : "??", quad.quadrup[i].three);
            else
                printf("[%i]:=%i \n", quad.quadrup[i].zero, quad.quadrup[i].one);

            break;

        case IF:
            printf("if %i (%i) %i goto %i\n", quad.quadrup[i].one, quad.quadrup[i].two, quad.quadrup[i].three, quad.quadrup[i].zero);
            break;

        case CALL:
            printf("call %i\n", quad.quadrup[i].zero);
            break;

        case SYS:
            printf("sys %i\n", quad.quadrup[i].zero);

        default:
            printf("?(%i)\n", quad.quadrup[i].instruction);
            break;
        }
    }
}

void casepush(int value)
{
    struct casestack *head = malloc(sizeof(struct casestack));
    if (!head)
    {
        fprintf(stderr, "Error malloc (casepush)\n");
        exit(1);
    }
    head->head = value;
    head->tail = casestack;
    casestack = head;
}

int casepop(void)
{
    if (!casestack)
    {
        fprintf(stderr, "Error casestack is empty\n");
        exit(2);
    }
    int ret = casestack->head;
    struct casestack *temp = casestack->tail;
    free(casestack);
    casestack = temp;

    return ret;
}

int casetop(void)
{
    if (casestack)
        return casestack->head;
    fprintf(stderr, "Error casestack is empty\n");
    exit(2);
}

lpos *arggencode(lpos **start)
{
    struct lpos *value=NULL;
    nbarg =3;               //pour tester
    

    for (int i = 0; i < nbarg; i++)
    {
        value = concat(value, crelist(quad.next));
        gencode(AFF,-1,'s'+'p'-i,-1,-1);            //les argument sont quelque part je sais pas où 's' 'p' à la place
        *start = concat(*start,crelist(quad.next)); 
        gencode(GOTO,-1,-1,-1,-1);
    }

    return value;
}
