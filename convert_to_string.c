#include "main.h"

unsigned int conv_s(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_S(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_r(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_R(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);

/**
 * conv_s - Converts an argument to a string and
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
unsigned int conv_s(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char *str, *null = "(null)";
	int SizeT;
	unsigned int reti = 0;

	(void)flags;
	(void)length;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(out_put, null, 6));

	for (SizeT = 0; *(str + SizeT);)
		SizeT++;

	reti += print_string_width(out_put, flags, width, precis, SizeT);

	precis = (precis == -1) ? SizeT : precis;
	while (*str != '\0' && precis > 0)
	{
		reti += _memcpy(out_put, str, 1);
		precis--;
		str++;
	}

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_s - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int conv_S(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int SizeT, index;
	unsigned int reti = 0;

	(void)length;
	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(out_put, null, 6));

	for (SizeT = 0; str[SizeT];)
		SizeT++;

	reti += print_string_width(out_put, flags, width, precis, SizeT);

	precis = (precis == -1) ? SizeT : precis;
	for (index = 0; *(str + index) != '\0' && index < precis; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			reti += _memcpy(out_put, hex, 2);
			if (*(str + index) < 16)
				reti += _memcpy(out_put, &zero, 1);
			reti += conv_ubase(out_put, *(str + index),
					"0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		reti += _memcpy(out_put, (str + index), 1);
	}

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @list: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A length modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_r(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char *str, *null = "(null)";
	int SizeT, end, i;
	unsigned int reti = 0;

	(void)flags;
	(void)length;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(out_put, null, 6));

	for (SizeT = 0; *(str + SizeT);)
		SizeT++;

	reti += print_string_width(out_put, flags, width, precis, SizeT);

	end = SizeT - 1;
	precis = (precis == -1) ? SizeT : precis;
	for (i = 0; end >= 0 && i < precis; i++)
	{
		reti += _memcpy(out_put, (str + end), 1);
		end--;
	}

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}

/**
 * conv_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @list: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 * @length: A lenth modifier.
 * @out_put: A bufferS struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_R(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, SizeT;
	unsigned int reti = 0;

	(void)flags;
	(void)length;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(out_put, null, 6));

	for (SizeT = 0; *(str + SizeT);)
		SizeT++;

	reti += print_string_width(out_put, flags, width, precis, SizeT);

	precis = (precis == -1) ? SizeT : precis;
	for (i = 0; *(str + i) != '\0' && i < precis; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				reti += _memcpy(out_put, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			reti += _memcpy(out_put, (str + i), 1);
	}

	reti += print_neg_width(out_put, reti, flags, width);

	return (reti);
}
