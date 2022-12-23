

#include "tabsymbole.h"

struct tabsymbole tabsymbole;

char memory[MEMORYSIZE];
unsigned int cur_memory;

unsigned int findtable(char *id, int create)
{
    u_int32_t place = 798; // valeur au pif (juste pas nul car plus simple pour reperer)
    for (int i = 0; i < tabsymbole.size; i++)
    {
        if (tabsymbole.tab[i].used && strcmp(id, tabsymbole.tab[i].name) == 0)
            return tabsymbole.tab[i].memory_place;
        if (!(tabsymbole.tab[i].used))
        {
            if (!create)
                return -1;
            tabsymbole.tab[i].name = id;
            tabsymbole.tab[i].used = 1;
            tabsymbole.tab[i].memory_place = writememory((char *)&place, 4); // reserved the place
            return tabsymbole.tab[i].memory_place;
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
        tabsymbole.tab[place].memory_place = writememory((char *)&place, 4); // reserved the place

        return tabsymbole.tab[place].memory_place;
    }
    return -1;
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
        if (!((i+1)%8))
            printf("\n");
        
        if (memory[i] == '\0')
            nb0++;
        else
            nb0 = 0;
        i++;
    }
    printf("\n");
}
