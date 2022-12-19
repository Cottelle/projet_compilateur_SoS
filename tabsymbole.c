

#include "tabsymbole.h"

struct tabsymbole tabsymbole;

unsigned int findtable(char *id, int create)
{
    for (int i = 0; i < tabsymbole.size; i++)
    {
        if (tabsymbole.tab[i].used && strcmp(id, tabsymbole.tab[i].name) == 0)
            return i;
        if (!(tabsymbole.tab[i].used))
        {
            if (!create)
                return -1;
            tabsymbole.tab[i].name = id;
            tabsymbole.tab[i].IsInt = create - 1;
            tabsymbole.tab[i].used = 1;
            return i;
        }
    }
    if (create)
    {
        void *temp = realloc(tabsymbole.tab, (tabsymbole.size + 1) * 2);
        if (!temp)
        {
            free(tabsymbole.tab);
            exit(1);
        }
        tabsymbole.tab = temp;
        int place = tabsymbole.size;
        tabsymbole.size = (tabsymbole.size + 1) * 2;
        tabsymbole.tab[place].name = id;
        tabsymbole.tab[place].IsInt = create - 1;
        tabsymbole.tab[place].used = 1;

        return place;
    }
    return -1;
}