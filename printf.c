#include <stdarg.h>
#include <unistd.h>
#include "printf.h"
int _printf(const char *format, ...)
{
    int i;
    if(format == NULL)
    {
        return (-1);
    }
    for( i = 0; i < format; i++)
}