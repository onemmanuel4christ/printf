#include "main.h"

/**
 * print_string - ll
 * @count: ll
 * Return: ll
 */

int print_string(int *count, va_list args)
{
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = "(null)";

	int len = 0;

	while (*str)
	{
		len += write(1, str, 1);
		str++;
	}
	return (len);
}
