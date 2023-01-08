#include "usefull.h"


char *createbuf(char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    char *buf=NULL;

    int size = vsnprintf(buf,0,format,ap)+1;

    if(!(buf=malloc(size)))
    {
        fprintf(stderr,"Error malloc creatbuf\n");
        exit(2);
    }
    va_end(ap);
    va_start(ap, format);

 
    if(vsnprintf(buf,size,format,ap)!=size-1)
    {
        fprintf(stderr,"Error vsnprintf (size =%i) \n",size-1);
        exit(2);
    }
    return buf;
}



char *myrealloc(char *buf, int new_size, int old_size)
{
    char *temp = malloc(new_size);
    if (!temp)
    {
        fprintf(stderr,"Error malloc \n");
        exit(2);
    }
    for(int i=0;i<old_size && i<new_size;i++)
        temp[i]= buf[i];
    free(buf);
    return temp;
}