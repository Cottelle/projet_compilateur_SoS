

#include "tabsymbole.h"

struct tabsymbole tabsymbole;

char memory[MEMORYSIZE];
unsigned int cur_memory;

symbole *findtable(char *id, int create)
{
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
            tabsymbole.tab[i].memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place
            tabsymbole.tab[i].nb = 1;
            tabsymbole.tab[i].fun = -1;
            return &tabsymbole.tab[i];
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
        tabsymbole.tab[place].nb = 1;
        tabsymbole.tab[place].fun = -1;
        tabsymbole.tab[place].memory_place = writememory((char *)&bidon, CELLSIZE); // reserved the place

        return &tabsymbole.tab[place];
    }
    return NULL;
}

symbole *createsymbole(symbole *s)
{
    int bidon = 789;
    symbole *sprime = findtable(s->name, 1);
    sprime->used = 1;
    sprime->isint = s->isint;
    sprime->nb = s->nb;
    sprime->fun = s->fun;
    sprime->memory_place = writememory((char *)&bidon, CELLSIZE);
    cur_memory += (s->nb - 1) * CELLSIZE;


    return sprime;
}

symbole simples(void)
{
    symbole s;
    s.fun=-1;
    s.name = NULL;
    s.nb =1;
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

void inmemory(unsigned int place,char *buf,int sizebuf)
{
    for (int i=0;i<sizebuf;i++)
        memory[i+place] = buf[i]; 
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
    printf("\n");
}
