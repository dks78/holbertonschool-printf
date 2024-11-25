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
                _putchar(c);
            }
            else if (format[i] == 's') 
            {
                char *str = va_arg(args, char*);
                while (*str)
                {
                    _putchar(*str);
                    str++;
                }
            }
            else if (format[i] == '%')
            {
                _putchar('%');
            }
            else
            {
                _putchar('%');
                _putchar(format[i]);
            }
        }
        else
        {
            _putchar(format[i]);
        }
    }

    va_end(args);

    return 0;
}
