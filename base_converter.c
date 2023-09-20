#include "main.h"
unsigned int conv_sbase(bufferS * out_put, long int numb, char *baseC,
		unsigned char flags, int width, int precis);
unsigned int conv_ubase(bufferS *out_put,
		unsigned long int numb, char *baseC,
		unsigned char flags, int width, int precis);

/**
 * conv_sbase - Converts a signed long to the specified base and stores
 *              the result in a buffer contained within a struct.
 * @out_put: A bufferS struct containing a character array.
 * @numb: The signed long to be converted.
 * @baseC: A pointer to a string specifying the base for conversion.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */

unsigned int conv_sbase(bufferS *out_put, long int numb, char *baseC,
		unsigned char flags, int width, int precis)
{
	int sizeT;
	char digit, pad = '0';
	unsigned int reti = 1;

	for (sizeT = 0; *(baseC + sizeT);)
		sizeT++;

	if (numb >= sizeT || numb <= -sizeT)
		reti += conv_sbase(out_put, numb / sizeT, baseC,
				flags, width - 1, precis - 1);

	else
	{
		for (; precis > 1; precis--, width--)
			reti += _memcpy(out_put, &pad, 1);

		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				reti += _memcpy(out_put, &pad, 1);
		}
	}

	digit = baseC[(numb < 0 ? -1 : 1) * (numb % sizeT)];
	_memcpy(out_put, &digit, 1);

	return (reti);
}


/**
 * conv_ubase - Converts an unsigned long to the specified base and
 *              stores the result in a buffer contained within a struct.
 * @out_put: A buffer_t struct containing a character array.
 * @numb: The unsigned long to be converted.
 * @baseC: A pointer to a string specifying the base for conversion.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precis: A precision modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */

unsigned int conv_ubase(bufferS *out_put, unsigned long int numb, char *baseC,
		unsigned char flags, int width, int precis)
{
	unsigned int sizeT, reti = 1;
	char digit, pad = '0', *leads = "0x";

	for (sizeT = 0; (*baseC + sizeT);)
		sizeT++;

	if (numb >= sizeT)
		reti += conv_ubase(out_put, numb / sizeT, baseC,
				flags, width - 1, precis - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			width -= 2;
			precis -= 2;
		}
		for (; precis > 1; precis--, width--) /* Handle precision */
			reti += _memcpy(out_put, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				reti += _memcpy(out_put, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			reti += _memcpy(out_put, leads, 2);
	}

	digit = baseC[(numb % sizeT)];
	_memcpy(out_put, &digit, 1);

	return (reti);
}

