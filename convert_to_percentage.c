#include "main.h"

unsigned int conv_c(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_percent(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_p(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
/**
 * @conv_di - Saves a signed int representation of a numeric argument in a struct's buffer.The va_list 
 * @list points to the argument that needs to be converted.
 * Modifiers for flags are 
 * @flags: the flags of the programs
 * @width is a width modifier. 
 * @precis: A precision-related modifier. 
 * @length is a length modifier. Character array in a bufferS struct, 
 * @out_put.Returns the number of bytes that were added to the buffer.
 */
unsigned int conv_c(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char c;
	unsigned int reti = 0;

	(void)precis;
	(void)length;

	c = va_arg(list, int);

	reti += print_width(out_put, reti	, flags, width);
	reti += _memcpy(out_put, &c, 1);
	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int conv_percent(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char percent = '%';
	unsigned int reti = 0;

	(void)list;
	(void)precis;
	(void)length;

	reti += print_width(out_put, reti, flags, width);
	reti += _memcpy(out_put, &percent, 1);
	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_p(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int reti = 0;

	(void)length;

	address = va_arg(list, unsigned long int);
	if (address == '\0')
		return (_memcpy(out_put, null, 5));

	flags |= 32;
	reti += conv_ubase(out_put, address, "0123456789abcdef",
			flags, width, precis);
	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}
