#include "usefull.h"


char *createbuf(char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    char *buf=NULL;

    int size = vsnprintf(buf,0,format,ap)+1;

    if(!(buf=realloc(buf,size)))
    {
        fprintf(stderr,"Error malloc creatbuf\n");
        exit(1);
    }
    va_end(ap);
    va_start(ap, format);

 
    vsnprintf(buf,size,format,ap);
    return buf;
}