#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int _printf(const char *format, ...)
{
    int i, j, len = 0;
    char *buffer;
    int buffer_size = 1024;
    va_list args; /* Ceci va contenir la liste des arguments */

    if (format == NULL)
    {
        return (-1);
    }

    buffer = malloc(buffer_size); /* Alloue un buffer initial de 1024 octets */
    if (buffer == NULL)
    {
        return (-1);
    }

    va_start(args, format); /* Prépare la liste des arguments */

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
            {
                char c = va_arg(args, int); /* Récupère le caractère (promu à int) */
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
                char *str = va_arg(args, char *);
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
            else if (format[i] == 'd' || format[i] == 'i')
            {
                int num = va_arg(args, int);
                char num_str[12]; /* Tampon temporaire pour l'entier, taille suffisante pour un int */
                int num_len = snprintf(num_str, sizeof(num_str), "%d", num); /* Convertit l'entier en chaîne */
                for ( j = 0; j < num_len; j++)
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
                    buffer[len++] = num_str[j];
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

    if (len > 0)
    {
        write(STDOUT_FILENO, buffer, len);
    }

    free(buffer);
    return len;
}
