#include "main.h"

/**
 * writeChar - Prints a character
 * @c: Character to be printed
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int writeChar(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0;
	char paddingChar = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddingChar = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFSIZ - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFSIZ - i - 2] = paddingChar;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFSIZ - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFSIZ - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * writeNumber - Writes a number
 * @isNegative: Indicator if the number is negative
 * @ind: Index where the number starts in the buffer
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int writeNumber(int isNegative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFSIZ - ind - 1;
	char paddingChar = ' ', extraChar = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (isNegative)
		extraChar = '-';
	else if (flags & F_PLUS)
		extraChar = '+';
	else if (flags & F_SPACE)
		extraChar = ' ';

	return (writeNum(ind, buffer, flags, width, precision,
				length, paddingChar, extraChar));
}

/**
 * writeNum - Write a number using a buffer
 * @ind: Index where the number starts in the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width specifier
 * @prec: Precision specifier
 * @length: Number length
 * @paddingChar: Padding character
 * @extraChar: Extra character
 *
 * Return: Number of characters printed.
 */
int writeNum(int ind, char buffer[],
		int flags, int width, int prec,
		int length, char paddingChar, char extraChar)
{
	int i, paddingStart = 1;

	if (prec == 0 && ind == BUFSIZ - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no characters are printed */
	if (prec == 0 && ind == BUFSIZ - 2 && buffer[ind] == '0')
		buffer[ind] = paddingChar = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		paddingChar = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extraChar != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddingChar == ' ')/* Assign extra char to left of buffer */
		{
			if (extraChar)
				buffer[--ind] = extraChar;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')/* extra char to left of buffer */
		{
			if (extraChar)
				buffer[--ind] = extraChar;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0')/* extra char to left of padding */
		{
			if (extraChar)
				buffer[--paddingStart] = extraChar;
			return (write(1, &buffer[paddingStart], i - paddingStart) +
					write(1, &buffer[ind], length - (1 - paddingStart)));
		}
	}
	if (extraChar)
		buffer[--ind] = extraChar;
	return (write(1, &buffer[ind], length));
}

/**
 * writeUnsigned - Writes an unsigned number
 * @isNegative: Number indicating if the num is negative
 * @ind: Index where the number starts in the buffer
 * @buffer: Buffer array to handle print
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters written.
 */
int writeUnsigned(int isNegative, int ind,
		char buffer[], int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int length = BUFSIZ - ind - 1, i = 0;
	char paddingChar = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && ind == BUFSIZ - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no characters are printed */

	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = paddingChar;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * writePointer - Writes a memory address
 * @buffer: Array of characters
 * @ind: Index where the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @paddingChar: Character representing the padding
 * @extraChar: Extra character
 * @paddingStart: Index where padding should start
 *
 * Return: Number of characters written.
 */
int writePointer(char buffer[], int ind, int length,
		int width, int flags, char paddingChar, char extraChar, int paddingStart)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddingChar == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extraChar)
				buffer[--ind] = extraChar;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extraChar)
				buffer[--ind] = extraChar;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0')/* extra char to left of padding */
		{
			if (extraChar)
				buffer[--paddingStart] = extraChar;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddingStart], i - paddingStart) +
					write(1, &buffer[ind], length - (1 - paddingStart) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extraChar)
		buffer[--ind] = extraChar;
	return (write(1, &buffer[ind], BUFSIZ - ind - 1));
}
