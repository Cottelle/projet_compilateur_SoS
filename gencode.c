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
        exit(2);
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
        quadrup *temp = (quadrup *)realloc(quad.quadrup, quad.size * sizeof(*(quad.quadrup)));
        if (!temp)
        {
            fprintf(stderr, "Erreur genecode: realloc");
            exit(2);
        }
        quad.quadrup = temp;
    }

    quad.quadrup[quad.next].instruction = instruction;
    quad.quadrup[quad.next].zero = z;
    quad.quadrup[quad.next].one = o;
    quad.quadrup[quad.next].two = t;
    quad.quadrup[quad.next].type = type;

    quad.next++;
}

struct addval avc(struct symbole *s, int value)
{
    struct addval a;
    a.s = s;
    a.value = value;
    return a;
}

void printquad()
{
    printf("\n\n");
    for (unsigned int i = 0; i < quad.next; i++)
    {
        printf("%i ", i);

        char zero[SIZEPRINT], one[SIZEPRINT], two[SIZEPRINT];
        snprintf(zero, SIZEPRINT, "%s%s%i%s", (quad.quadrup[i].zero.s == NULL) ? "" : "[", (quad.quadrup[i].zero.s != NULL && quad.quadrup[i].zero.s->onstack_reg_label == 1) ? "<sp>" : (quad.quadrup[i].zero.s != NULL && quad.quadrup[i].zero.s->onstack_reg_label == 2) ? "R"
                                                                                                                                                                                     : (quad.quadrup[i].zero.s != NULL && quad.quadrup[i].zero.s->onstack_reg_label == 3)   ? "la"
                                                                                                                                                                                                                                                                            : "",
                 (quad.quadrup[i].zero.s == NULL) ? quad.quadrup[i].zero.value : (int)quad.quadrup[i].zero.s->memory_place, (quad.quadrup[i].zero.s == NULL) ? "" : "]");
        snprintf(one, SIZEPRINT, "%s%s%i%s", (quad.quadrup[i].one.s == NULL) ? "" : "[", (quad.quadrup[i].one.s != NULL && quad.quadrup[i].one.s->onstack_reg_label == 1) ? "<sp>" : (quad.quadrup[i].one.s != NULL && quad.quadrup[i].one.s->onstack_reg_label == 2) ? "R"
                                                                                                                                                                                 : (quad.quadrup[i].one.s != NULL && quad.quadrup[i].one.s->onstack_reg_label == 3)   ? "la"
                                                                                                                                                                                                                                                                      : "",
                 (quad.quadrup[i].one.s == NULL) ? quad.quadrup[i].one.value : (int)quad.quadrup[i].one.s->memory_place, (quad.quadrup[i].one.s == NULL) ? "" : "]");
        snprintf(two, SIZEPRINT, "%s%s%i%s", (quad.quadrup[i].two.s == NULL) ? "" : "[", (quad.quadrup[i].two.s != NULL && quad.quadrup[i].two.s->onstack_reg_label == 1) ? "<sp>" : (quad.quadrup[i].two.s != NULL && quad.quadrup[i].two.s->onstack_reg_label == 2) ? "R"
                                                                                                                                                                                 : (quad.quadrup[i].two.s != NULL && quad.quadrup[i].two.s->onstack_reg_label == 3)   ? "la"
                                                                                                                                                                                                                                                                      : "",
                 (quad.quadrup[i].two.s == NULL) ? quad.quadrup[i].two.value : (int)quad.quadrup[i].two.s->memory_place, (quad.quadrup[i].two.s == NULL) ? "" : "]");

        switch (quad.quadrup[i].instruction)
        {
        case GOTO:
            printf("goto %s\n", zero);
            break;

        case AFF:
            printf(" %s:= %s", zero, one);
            switch (quad.quadrup[i].type)
            {
            case 0:
                break;
            case 1:
                printf(" +%s", two);
                break;
            case 2:
                printf(" -%s", two);
                break;
            case 3:
                printf(" *%s", two);
                break;
            case 4:
                printf(" /%s", two);
                break;
            default:
                printf(" ??%i", quad.quadrup[i].type);
                break;
            }
            printf("\n");
            break;

        case IF:
            printf("%s", one);
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
                printf(" ??%i", quad.quadrup[i].type);
                break;
            }
            printf("%s goto %s\n", two, zero);
            break;

        case SYS:
            printf("sys %i\n", quad.quadrup[i].zero.value);
            break;

        case CALL:
            printf("jal %s\n", (char *)(quad.quadrup[i].zero.s));
            break;

        default:
            printf("?(%i)\n", quad.quadrup[i].instruction);
            break;
        }
    }
}

void casepush(struct symbole *s, int addr)
{
    struct casestack *head = malloc(sizeof(struct casestack));
    if (!head)
    {
        fprintf(stderr, "Error malloc (casepush)\n");
        exit(2);
    }
    head->s = s;
    head->addr = addr;
    head->tail = casestack;
    casestack = head;
}

struct addval casepop(void)
{
    if (!casestack)
    {
        fprintf(stderr, "Error casestack is empty\n");
        exit(4);
    }
    struct addval ret;
    ret.s = casestack->s;
    ret.value = casestack->addr;
    struct casestack *temp = casestack->tail;
    free(casestack);
    casestack = temp;

    return ret;
}

struct addval casetop(void)
{
    if (!casestack)
    {
        fprintf(stderr, "Error casestack is empty\n");
        exit(4);
    }

    struct addval ret;
    ret.s = casestack->s;
    ret.value = casestack->addr;
    return ret;
}

void freequad(void)
{
    free(quad.quadrup);
}