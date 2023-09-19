#include "main.h"

unsigned int print_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width);
unsigned int print_string_width(bufferS *out_put,
		unsigned char flags, int width, int precis, int sizeT);
unsigned int print_neg_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width);

/**
 * print_width - Stores leading spaces to a buffer for a width modifier.
 * @out_put: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int reti = 0;
	char width_mod = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0;)
			reti += _memcpy(out_put, &width_mod, 1);
	}

	return (reti);
}

/**
 * print_string_width - Stores leading spaces to a buffer for a width modifier.
 * @out_put: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @sizeT: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_string_width(bufferS *out_put,
		unsigned char flags, int width, int precis, int sizeT)
{
	unsigned int reti = 0;
	char width_mod = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (precis == -1) ? sizeT : precis;
		for (; width > 0; width--)
			reti += _memcpy(out_put, &width_mod, 1);
	}

	return (reti);
}

/**
 * print_neg_width - Stores trailing spaces to a buffer for a '-' flag.
 * @out_put: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_neg_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int reti = 0;
	char width_mod = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			reti += _memcpy(out_put, &width_mod, 1);
	}

	return (reti);
}
