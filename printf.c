#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int _printf(const char *format, ...)
{
    int i, len = 0;
    char *buffer;
    int buffer_size = 1024;
    va_list args;

    if (format == NULL)
    {
        return (-1);
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL)
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
                if (len >= buffer_size - 1)
                {
                    buffer_size *= 2;
                    buffer = realloc(buffer, buffer_size);
                    if (buffer == NULL)
                    {
                        va_end(args);
                        return (-1);
                    }
                }
                buffer[len++] = c;
            }
            else if (format[i] == 's') 
            {
                char *str = va_arg(args, char*);
                while (*str) 
                {
                    if (len >= buffer_size - 1)
                    {
                        buffer_size *= 2;
                        buffer = realloc(buffer, buffer_size);
                        if (buffer == NULL)
                        {
                            va_end(args);
                            return (-1);
                        }
                    }
                    buffer[len++] = *str++;
                }
            }
            else if (format[i] == '%') 
            {
                if (len >= buffer_size - 1)
                {
                    buffer_size *= 2;
                    buffer = realloc(buffer, buffer_size);
                    if (buffer == NULL)
                    {
                        va_end(args);
                        return (-1);
                    }
                }
                buffer[len++] = '%';
            } 
            else 
            {
                if (len >= buffer_size - 2)
                {
                    buffer_size *= 2;
                    buffer = realloc(buffer, buffer_size);
                    if (buffer == NULL)
                    {
                        va_end(args);
                        return (-1);
                    }
                }
                buffer[len++] = '%';
                buffer[len++] = format[i];
            }
        } 
        else 
        {
            if (len >= buffer_size - 1)
            {
                buffer_size *= 2;
                buffer = realloc(buffer, buffer_size);
                if (buffer == NULL)
                {
                    va_end(args);
                    return (-1);
                }
            }
            buffer[len++] = format[i];
        }
    }

    va_end(args);

    buffer[len] = '\0';
    for (i = 0; i < len; i++)
    {
        _putchar(buffer[i]);
    }

    free(buffer);
    return len;
}
