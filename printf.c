#include "main.h"

/**
 * _printf - custom printf function with limited format specifiers
 * @format: the format string
 *
 * Return: the number of characters printed
 */

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            putchar(*format);
            count++;
        }
        else
        {
            format++;
            if (*format == 'c')
            {
                char c = va_arg(args, int);
                putchar(c);
                count++;
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);

                if (str == NULL)
                    str = "(null)";

                while (*str)
                {
                    putchar(*str);
                    str++;
                    count++;
                }
            }
            else if (*format == '%')
            {
                putchar('%');
                count++;
            }
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(args, int);
                printf("%d", num);
                count++;
            }
        }
        format++;
    }

    va_end(args);
    return count;
}
