#include "main.h"

/**
 * _putchar - ll
 * @count: ll
 * @args:kk
 * Return: 0
 */

int _putchar(int *count, va_list args)
{
	char c = va_arg(args, int);

	write (1, &c, 1);
}
