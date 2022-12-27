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

void complete(lpos *liste, struct addval value)
{
    lpos *last = liste;
    if (liste)
    {
        quad.quadrup[liste->position].zero = value;
        while (liste->suivant != NULL)
        {
            liste = liste->suivant;
            quad.quadrup[liste->position].zero = value;
            free(last);
            last = liste;
        }
    }
}

void gencode(enum instruction instruction, struct addval z, struct addval o, struct addval t, int type)
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
    quad.quadrup[quad.next].type = type;

    quad.next++;
}

struct addval addvalcreate(struct symbole *s,int value)
{
    struct addval a;
    a.s=s;
    a.value=value;
    return a;
}

void printquad()
{
    for (int i = 0; i < quad.next; i++)
    {
        printf("%i ", i);

        char zero[SIZEPRINT],one[SIZEPRINT],two[SIZEPRINT];
        snprintf(zero,SIZEPRINT,"%s%i%s",(quad.quadrup[i].zero.s ==NULL)? "":"[", (quad.quadrup[i].zero.s ==NULL)? quad.quadrup[i].zero.value : quad.quadrup[i].zero.s->memory_place, (quad.quadrup[i].zero.s ==NULL)? "":"]" );
        snprintf(one,SIZEPRINT,"%s%i%s",(quad.quadrup[i].one.s ==NULL)? "":"[", (quad.quadrup[i].one.s ==NULL)? quad.quadrup[i].one.value : quad.quadrup[i].one.s->memory_place, (quad.quadrup[i].one.s ==NULL)? "":"]" );
        snprintf(two,SIZEPRINT,"%s%i%s",(quad.quadrup[i].two.s ==NULL)? "":"[", (quad.quadrup[i].two.s ==NULL)? quad.quadrup[i].two.value : quad.quadrup[i].two.s->memory_place, (quad.quadrup[i].two.s ==NULL)? "":"]" );

        switch (quad.quadrup[i].instruction)
        {
        case GOTO:
            printf("goto %s\n",zero);
            break;

        case AFF:
            printf(" %s:= %s",zero,one);
            switch (quad.quadrup[i].type)
            {
            case 0:
                break;
            case 1:
                printf(" +%s",two);
                break;
            case 2:
                printf(" -%s",two);
                break;
            case 3:
                printf(" *%s",two);
            case 4:
                printf(" /%s",two);
                break;
            default:
                printf(" ??%i",quad.quadrup[i].type);
                break;
            }
            printf("\n");
            break;

        case IF:
            printf("%s",one);
            switch (quad.quadrup[i].type)
            {
            case 0:
                printf("=");
                break;
            case 1:
                printf("!=");
                break;
            case 2:
                printf("<");
                break;
            case 3:
                printf(">");
                break;
            case 4:
                printf("<=");
                break;
            case 5:
                printf(">=");
                break;
            default:
                printf(" ??%i",quad.quadrup[i].type);
                break;
            }
            printf("%s goto %s\n",two,zero);
            break;

        case CALL:
            printf("call %i\n", quad.quadrup[i].zero.value);
            break;

        case SYS:
            printf("sys %i\n", quad.quadrup[i].zero.value);

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
    struct lpos *value = NULL;
    *start = NULL;

    for (int i = 0; i < nbarg; i++)
    {
        value = concat(value, crelist(quad.next));
        gencode(AFF, addvalcreate(NULL,-1), addvalcreate(NULL,'s' + 'p' - i*4), addvalcreate(NULL,-1), 0); // les argument sont quelque part je sais pas où 's' 'p' à la place
        *start = concat(*start, crelist(quad.next));
        gencode(GOTO, addvalcreate(NULL,-1), addvalcreate(NULL,-1), addvalcreate(NULL,-1), 0);
    }

    return value;
}
