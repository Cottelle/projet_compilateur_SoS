#ifndef USEFULL
#define USEFULL

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>




/**
 * Create a buf like with snprintf allocated the buf
 */
char *createbuf(char *format, ...);


/**
 * My realloc fun
*/
char *myrealloc(char *buf, int new_size,int old_size);





#endif