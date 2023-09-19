#include "main.h"

void cleanup(va_list list, bufferS *out_put);
int run_printf(const char *format, va_list list, bufferS *out_put);
int _printf(const char *format, ...);

/**
 * cleanup - Performs cleanup operations for _printf.
 * @list: A va_list of arguments provided to _printf.
 * @o: An optional parameter (not described in the comment).
 */

void cleanup(va_list list, bufferS *out_put)
{
	va_end(list);
	write(1, out_put->start, out_put->length);
	free_buffer(out_put);
}

/**
 * run_printf - Processes the format string for _printf.
 * @format: The character string to print, which may contain formatting directives.
 * @out_put: A bufferS struct containing a buffer for output.
 * @list: A va_list of arguments.
 *
 * Return: The count of characters that were stored in out_put.
 */

int run_printf(const char *format, va_list list, bufferS *out_put)
{
	int i, width, precis, reti = 0;
	char temp;
	unsigned char flags, length;
	unsigned int (*f)(va_list, bufferS *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		length = 0;
		if (*(format + i) == '%')
		{
			temp = 0;
			flags = handle_flags(format + i + 1, &temp);
			width = handle_width(list, format + i + temp + 1, &temp);
			precis = handle_precision(list, format + i + temp + 1,
					&temp);
			length = handle_length(format + i + temp + 1, &temp);

			f = handle_specifiers(format + i + temp + 1);
			if (f != NULL)
			{
				i += temp + 1;
				reti += f(list, out_put, flags, width, precis, length);
				continue;
			}
			else if (*(format + i + temp + 1) == '\0')
			{
				reti = -1;
				break;
			}
		}
		reti += _memcpy(out_put, (format + i), 1);
		i += (length != 0) ? 1 : 0;
	}
	cleanup(list, out_put);
	return (reti);
}

/**
 * _printf - Displays a formatted string.
 * @format: A character string to be printed, which may include formatting directives.
 *
 * Return: The count of characters that were printed.
 */

int _printf(const char *format, ...)
{
	bufferS *output;
	va_list list;
	int reti;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(list, format);

	reti = run_printf(format, list, output);

	return (reti);
}
