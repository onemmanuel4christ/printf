#include "main.h"

unsigned int conv_x(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_X(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);

/**
 * conve_x - Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_x(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	unsigned long int num;
	unsigned int reti = 0;
	char *leads = "0x";

	if (length == LONG)
		num = va_arg(list, unsigned long int);
	else
		num = va_arg(list, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		reti += _memcpy(out_put, leads, 2);

	if (!(num == 0 && precis == 0))
		reti += conv_ubase(out_put, num, "0123456789abcdef",
				flags, width, precis);

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_X - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_X(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	unsigned long int num;
	unsigned int reti = 0;
	char *lead = "0X";

	if (length == LONG)
		num = va_arg(list, unsigned long);
	else
		num = va_arg(list, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		reti += _memcpy(out_put, lead, 2);

	if (!(num == 0 && precis == 0))
		reti += conv_ubase(out_put, num, "0123456789ABCDEF",
				flags, width, precis);

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}
