#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"

#define DATA_SEGMENT 0x10010000
#define TEXT_SEGMENT 0x00400000
void il2MIPS(struct quad quad, struct tabsymbole tabsymbole, struct labels labels,char *file);
