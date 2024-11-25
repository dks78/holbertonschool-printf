#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

int _printf(const char *format, ...)
{
    int i;
    va_list args;

    if (format == NULL)
    {
        return (-1);
    }

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;

            if (format[i] == 'c')
            {
                char c = va_arg(args, int);
                putchar(c);
            }
            else if (format[i] == 's') 
            {
                char *str = va_arg(args, char*);
                while (*str)
                {
                    putchar(*str);
                    str++;
                }
            }
            else if (format[i] == '%')
            {
                putchar('%');
            }
            else
            {
                putchar('%');
                putchar(format[i]);
            }
        }
        else
        {
            putchar(format[i]);
        }
    }

    va_end(args);

    return 0;
}
