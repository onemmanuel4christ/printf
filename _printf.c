#include "main.h"

void cleanup(va_list list, bufferS *out_put);
int run_printf(const char *format, va_list list, bufferS *out_put);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @list: A va_list of arguments provided to _printf.
 * @out_put: A bufferS struct.
 */
void cleanup(va_list list, bufferS *out_put)
{
	va_end(list);
	write(1, out_put->start, out_put->length);
	free_buffer(out_put);
}

/**
 * run_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @out_put: A bufferS struct containing a buffer.
 * @list: A va_list of arguments.
 *
 * Return: The number of characters stored to out_put.
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
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
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
