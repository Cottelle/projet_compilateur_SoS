

#include "tabsymbole.h"

struct tabsymbole tabsymbole;
struct tabsymbolesp tabsymbolesp;

char memory[MEMORYSIZE];
unsigned int cur_memory;

char sp[MEMORYSIZE];
unsigned int cur_sp;

struct symbole *findtable(char *id, int create)
{
    struct symbole *s = spfindtable(id, 0);
    if (s)
        return s;

    u_int32_t bidon = 798; // valeur au pif (juste pas nul car plus simple pour reperer)
    for (int i = 0; i < tabsymbole.size; i++)
    {
        if (tabsymbole.tab[i] && strcmp(id, tabsymbole.tab[i]->name) == 0)
            return tabsymbole.tab[i];
        if (!(tabsymbole.tab[i]))
        {
            if (!create)
                return NULL;

            tabsymbole.tab[i] = malloc(sizeof(struct symbole));
            if (!tabsymbole.tab[i])
            {
                fprintf(stderr, "Error malloc \n");
                exit(1);
            }

            tabsymbole.tab[i]->name = id;
            tabsymbole.tab[i]->onstack_reg = 0;
            tabsymbole.tab[i]->memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place
            tabsymbole.tab[i]->nb = 1;
            tabsymbole.tab[i]->fun = -1;
            tabsymbole.tab[i]->isint = 0;
            return tabsymbole.tab[i]; // find if it is a local variable
        }
    }
    if (create)
    {
        int new_size;
        if (tabsymbole.size == 0)
            new_size = 1;
        else
            new_size = tabsymbole.size * 2;
        struct symbole **temp = realloc(tabsymbole.tab, new_size * sizeof(struct symbole *));
        if (!temp)
        {
            free(tabsymbole.tab);
            exit(1);
        }

        memset(temp + tabsymbole.size, 0, (new_size - tabsymbole.size) * sizeof(struct symbole *));

        tabsymbole.tab = temp;
        int place = tabsymbole.size;
        tabsymbole.tab[place] = malloc(sizeof(struct symbole));
        if (!tabsymbole.tab[place])
        {
            fprintf(stderr, "Error malloc \n");
            exit(1);
        }

        tabsymbole.size = new_size;
        tabsymbole.tab[place]->name = id;
        tabsymbole.tab[place]->onstack_reg = 0;
        tabsymbole.tab[place]->nb = 1;
        tabsymbole.tab[place]->fun = -1;
        tabsymbole.tab[place]->isint = 0;
        tabsymbole.tab[place]->memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place

        return tabsymbole.tab[place];
    }
    return NULL; // find if it is a local variable
}

struct symbole *createsymbole(struct symbole *s)
{
    struct symbole *sprime = findtable(s->name, 1);
    sprime->isint = s->isint;
    sprime->nb = s->nb;
    sprime->onstack_reg = s->onstack_reg;
    sprime->fun = s->fun;
    for(unsigned int i=1;i<s->nb;i++)
    sprime->memory_place = writememory((char *)&i, CELLSIZE);
    // cur_memory += (s->nb - 1) * CELLSIZE; // alocate the place for the tab

    return sprime;
}

struct symbole simples(void)
{
    struct symbole s;
    s.fun = -1;
    s.name = NULL;
    s.nb = 1;
    s.onstack_reg = 0;
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
    {
        cur_sp = t->next->tab[0]->memory_place; // On retreci la pile
    }
    // Not free .... à mdeiter       il faut pas free totu de suite car les addr des "symbole" sont encore uilisé
    t->next = NULL;
}

struct symbole *spfindtable(char *id, int create)
{
    struct tabsymbolesp *tabsp = &tabsymbolesp;
    while (tabsp->next != NULL) // find the last
        tabsp = tabsp->next;

    u_int32_t bidon = 16 * 0xff; // valeur au pif (juste pas nul car plus simple pour reperer)
    for (int i = 0; i < tabsp->size; i++)
    {
        // if (!tabsp->tab[i]->name)
        //     continue;
        if (tabsp->tab[i] &&  strcmp(id, tabsp->tab[i]->name) == 0)
            return tabsp->tab[i];
        if (!(tabsp->tab[i]))
        {
            if (!create)
                return NULL;

            tabsp->tab[i] = calloc(1,sizeof(struct symbole));
            if (!tabsp->tab[i])
            {
                fprintf(stderr, "Error malloc \n");
                exit(1);
            }

            tabsp->tab[i]->name = id;
            tabsp->tab[i]->onstack_reg = 1;
            tabsp->tab[i]->isint = 0;
            tabsp->tab[i]->fun = -1; // always -1 (not function)
            tabsp->tab[i]->nb = 1;   // always 1

            tabsp->tab[i]->memory_place = writesp((char *)&bidon, CELLSIZE); // reserved the place
            return tabsp->tab[i];
        }
    }
    if (create)
    {
        int new_size =0;
        if(tabsp->size==0)
            new_size=1;
        else
            new_size = tabsp->size*2;

        struct symbole **temp = realloc(tabsp->tab, new_size * sizeof(struct symbole *));
        if (!temp)
        {
            free(tabsp->tab);
            exit(1);
        }

        memset(temp + tabsp->size, '\0', (new_size - tabsp->size) * sizeof(struct symbole *));


        tabsp->tab = temp;
  
        int place = tabsp->size;
        tabsp->tab[place] = calloc(1,sizeof(struct symbole));
        if (!tabsp->tab[place])
        {
            fprintf(stderr, "Error malloc \n");
            exit(1);
        }

        tabsp->size = new_size;
        tabsp->tab[place]->name = id;
        tabsp->tab[place]->onstack_reg = 1;
        tabsp->tab[place]->fun = -1; // always -1 (not function)
        tabsp->tab[place]->nb = 1;   // always 1
        tabsp->tab[place]->isint = 0;
        tabsp->tab[place]->memory_place = writesp((char *)&bidon, CELLSIZE); // reserved the place

        return tabsp->tab[place];
    }
    return NULL;
}

struct symbole *spcreatesymbole(struct symbole *s)
{
    struct symbole *sprime = spfindtable(s->name, 1);
    sprime->isint = s->isint;
    sprime->nb = 1;
    sprime->onstack_reg = 1;
    sprime->fun = -1;

    return sprime;
}

struct symbole spsimples(void)
{
    struct symbole s;
    s.fun = -1;
    s.name = NULL;
    s.nb = 1;
    s.onstack_reg = 1;
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


struct symbole *reg(int value)
{
    struct symbole *s = malloc(sizeof(struct symbole));
    if (!s)
    {
        fprintf(stderr,"Error malloc\n");
        exit(1);
    }

    s->onstack_reg=2;
    s->isint =value;
    s->memory_place =value;
    s->fun = -1;
    s->name = "Registre";
    s->nb = 1;

    return s;
}

void printtabsymbole(void)
{
    printf("\n Table symbole : \n");
    for (int i = 0; i < tabsymbole.size; i++)
        if (tabsymbole.tab[i])
            printf("-%i- %s [%i]\n", i, tabsymbole.tab[i]->name, tabsymbole.tab[i]->memory_place);

    printf("\nMemory\n");
    unsigned int nb0 = 0, i = 0;
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
