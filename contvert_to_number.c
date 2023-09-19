#include "main.h"

unsigned int conv_di(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_b(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_u(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_o(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);

/**
 * @conv_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_di(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	long int d, copy;
	unsigned int reti = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (length == LONG)
		d = va_arg(list, long int);
	else
		d = va_arg(list, int);
	if (length == SHORT)
		d = (short)d;

	if (SPACE_FLAG == 1 && d >= 0)
		reti += _memcpy(out_put, &space, 1);

	if (precis <= 0 && NEG_FLAG == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			reti += _memcpy(out_put, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			reti += _memcpy(out_put, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
			reti += _memcpy(out_put, &pad, 1);
	}

	if (ZERO_FLAG == 0 && d < 0)
		reti += _memcpy(out_put, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		reti += _memcpy(out_put, &plus, 1);

	if (!(d == 0 && precis == 0))
		reti += conv_ubase(out_put, d, "0123456789",
				flags, 0, precis);

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_b - Converts an unsigned int argument to binary
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
unsigned int conv_b(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	unsigned int numb;

	numb = va_arg(list, unsigned int);

	(void)length;

	return (conv_ubase(out_put, numb, "01", flags, width, precis));
}

/**
 * conv_o - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_o(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	unsigned long int numb;
	unsigned int reti = 0;
	char zero = '0';

	if (length == LONG)
		numb = va_arg(list, unsigned long int);
	else
		numb = va_arg(list, unsigned int);
	if (length == SHORT)
		numb = (unsigned short)numb;

	if (HASH_FLAG == 1 && numb != 0)
		reti += _memcpy(out_put, &zero, 1);

	if (!(numb == 0 && precis == 0))
		reti += conv_ubase(out_put, numb, "01234567",
				flags, width, precis);

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_u(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	unsigned long int numb;
	unsigned int reti = 0;

	if (length == LONG)
		numb = va_arg(list, unsigned long int);
	else
		numb = va_arg(list, unsigned int);
	if (length == SHORT)
		numb = (unsigned short)numb;

	if (!(numb == 0 && precis == 0))
		reti += conv_ubase(out_put, numb, "0123456789",
				flags, width, precis);

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

