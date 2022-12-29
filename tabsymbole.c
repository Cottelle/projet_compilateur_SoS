

#include "tabsymbole.h"

struct tabsymbole tabsymbole;
struct tabsymbolesp tabsymbolesp;

char memory[MEMORYSIZE];
unsigned int cur_memory;

char sp[MEMORYSIZE];
unsigned int cur_sp;

symbole *findtable(char *id, int create)
{
    symbole *s = spfindtable(id,0);
    if (s)
        return s;

    u_int32_t bidon = 798; // valeur au pif (juste pas nul car plus simple pour reperer)
    for (int i = 0; i < tabsymbole.size; i++)
    {
        if (tabsymbole.tab[i].used && strcmp(id, tabsymbole.tab[i].name) == 0)
            return &tabsymbole.tab[i];
        if (!(tabsymbole.tab[i].used))
        {
            if (!create)
                return NULL;
            tabsymbole.tab[i].name = id;
            tabsymbole.tab[i].used = 1;
            tabsymbole.tab[i].onstack = 0;
            tabsymbole.tab[i].memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place
            tabsymbole.tab[i].nb = 1;
            tabsymbole.tab[i].fun = -1;
            tabsymbole.tab[i].isint = 0;
            return &tabsymbole.tab[i];              //find if it is a local variable
        }
    }
    if (create)
    {
        void *temp = realloc(tabsymbole.tab, ((tabsymbole.size + 1) * 2) * sizeof(*tabsymbole.tab));
        if (!temp)
        {
            free(tabsymbole.tab);
            exit(1);
        }
        tabsymbole.tab = temp;
        int place = tabsymbole.size;
        tabsymbole.size = (tabsymbole.size + 1) * 2;
        tabsymbole.tab[place].name = id;
        tabsymbole.tab[place].used = 1;
        tabsymbole.tab[place].onstack = 0;
        tabsymbole.tab[place].nb = 1;
        tabsymbole.tab[place].fun = -1;
        tabsymbole.tab[place].isint = 0;
        tabsymbole.tab[place].memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place

        return &tabsymbole.tab[place];
    }
    return NULL;             //find if it is a local variable
}

symbole *createsymbole(symbole *s)
{
    int bidon = 789;
    symbole *sprime = findtable(s->name, 1);
    sprime->used = 1;
    sprime->isint = s->isint;
    sprime->nb = s->nb;
    sprime->onstack = 0;
    sprime->fun = s->fun;
    sprime->memory_place = writememory((char *)&bidon, CELLSIZE);
    cur_memory += (s->nb - 1) * CELLSIZE; // alocate the place for the tab

    return sprime;
}

symbole simples(void)
{
    symbole s;
    s.fun = -1;
    s.name = NULL;
    s.nb = 1;
    s.onstack = 0;
    s.isint = 0;
    return s;
}

unsigned int writememory(char *buf, int sizebuf)
{
    unsigned int ret = cur_memory;
    for (int i = 0; i != sizebuf; i++)
        memory[cur_memory++] = buf[i];

    return ret;
}

unsigned int writestringmemory(char *buf)
{
    unsigned int ret = cur_memory;
    int i = 0;
    while (buf[i] != '\0')
        memory[cur_memory++] = buf[i++];
    memory[cur_memory++] = '\0';

    return ret;
}

void inmemory(unsigned int place, char *buf, int sizebuf)
{
    for (int i = 0; i < sizebuf; i++)
        memory[i + place] = buf[i];
}

struct tabsymbolesp *nextstackcreate(void)
{

    struct tabsymbolesp *t = &tabsymbolesp;
    while (t->next != NULL)
        t = t->next;

    t->next = malloc(sizeof(*t));
    if (!t->next)
    {
        fprintf(stderr, "Error malloc\n");
        exit(1);
    }

    t->next->next = NULL;
    t->next->size = 0;
    t->next->tab = NULL;
    return t;
}

void popstacknext()
{
    struct tabsymbolesp *t = &tabsymbolesp;
    while (t->next->next != NULL)
        t = t->next;

    if (t->next->tab)
        cur_sp = t->next->tab[0].memory_place ; // On retreci la pile

    // Not free .... à mdeiter       il faut pas free totu de suite car les addr des "symbole" sont encore uilisé
    t->next = NULL;
}

struct symbole *spfindtable(char *id, int create)
{
    struct tabsymbolesp *tabsp = &tabsymbolesp;
    while (tabsp->next != NULL) // find the last
        tabsp = tabsp->next;

    for(int i=0;i<tabsp->size;i++)
        if(tabsp->tab[i].used)
            printf("-%i- %s [%i]\n",i,tabsp->tab[i].name,tabsp->tab[i].memory_place);

    u_int32_t bidon = 16 * 0xff; // valeur au pif (juste pas nul car plus simple pour reperer)
    for (int i = 0; i < tabsp->size; i++)
    {
        if (tabsp->tab[i].used && strcmp(id, tabsp->tab[i].name) == 0)
            return &tabsp->tab[i];
        if (!(tabsp->tab[i].used))
        {
            if (!create)
                return NULL;
            tabsp->tab[i].name = id;
            tabsp->tab[i].used = 1;
            tabsp->tab[i].onstack = 1;
            tabsp->tab[i].isint = 0;
            tabsp->tab[i].fun = -1; // always -1 (not function)
            tabsp->tab[i].nb = 1;   // always 1

            tabsp->tab[i].memory_place = writesp((char *)&bidon, CELLSIZE); // reserved the place
            return &tabsp->tab[i];
        }
    }
    if (create)
    {
        void *temp = realloc(tabsp->tab, ((tabsp->size + 1) * 2) * sizeof(*tabsp->tab));
        if (!temp)
        {
            free(tabsp->tab);
            exit(1);
        }
        tabsp->tab = temp;
        int place = tabsp->size;
        tabsp->size = (tabsp->size + 1) * 2;
        tabsp->tab[place].name = id;
        tabsp->tab[place].used = 1;
        tabsp->tab[place].onstack = 1;
        tabsp->tab[place].fun = -1; // always -1 (not function)
        tabsp->tab[place].nb = 1;   // always 1
        tabsp->tab[place].isint = 0;
        tabsp->tab[place].memory_place = writesp((char *)&bidon, CELLSIZE); // reserved the place

        return &tabsp->tab[place];
    }
    return NULL;
}

struct symbole *spcreatesymbole(struct symbole *s)
{
    struct tabsymbolesp *tabsp = &tabsymbolesp;
    while (tabsp->next != NULL) // find the last
        tabsp = tabsp->next;

    int bidon = 789;
    struct symbole *sprime = spfindtable(s->name, 1);
    sprime->used = 1;
    sprime->isint = s->isint;
    sprime->nb = 1;
    sprime->onstack = 1;
    sprime->fun = -1;
    sprime->memory_place = writememory((char *)&bidon, CELLSIZE);
    return sprime;
}

struct symbole spsimples(void)
{
    struct symbole s;
    s.fun = -1;
    s.name = NULL;
    s.nb = 1;
    s.onstack = 1;
    s.isint = 0;
    return s;
}

unsigned int writesp(char *buf, int sizebuf)
{
    unsigned int ret = cur_sp;
    for (int i = 0; i != sizebuf; i++)
        sp[cur_sp++] = buf[i];

    return ret;
}

unsigned int writestringsp(char *buf)
{
    unsigned int ret = cur_sp;
    int i = 0;
    while (buf[i] != '\0')
        sp[cur_sp++] = buf[i++];
    sp[cur_sp++] = '\0';

    return ret;
}

void insp(unsigned int place, char *buf, int sizebuf)
{
    for (int i = 0; i < sizebuf; i++)
        sp[i + place] = buf[i];
}

void printtabsymbole(void)
{
    printf("\n Table symbole : \n");
    for (int i = 0; i < tabsymbole.size; i++)
        if (tabsymbole.tab[i].used)
            printf("-%i- %s [%i]\n", i, tabsymbole.tab[i].name, tabsymbole.tab[i].memory_place);


    printf("\nMemory\n");
    int nb0 = 0, i = 0;
    while (i < cur_memory && i < MEMORYSIZE && nb0 < 10)
    {
        printf("%3x ", memory[i]);
        if (!((i + 1) % 8))
            printf("\n");

        if (memory[i] == '\0')
            nb0++;
        else
            nb0 = 0;
        i++;
    }

    printf("\nSTACK\n");
    nb0 = 0;
    i = 0;
    while (i < cur_sp && i < MEMORYSIZE && nb0 < 10)
    {
        printf("%2x ", (unsigned char)sp[i]);
        if (!((i + 1) % 8))
            printf("\n");

        if (sp[i] == '\0')
            nb0++;
        else
            nb0 = 0;
        i++;
    }

    printf("\n");
}
