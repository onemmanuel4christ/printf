#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * printPointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed.
 */
int printPointer(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	char extraChar = 0, paddingChar = ' ';
	int index = OUTPUT_BUFFER_SIZE - 2, length = 2,
	    paddingStart = 1; /* length=2, for '0x' */
	unsigned long address;
	char hexMap[] = "0123456789abcdef";
	void *pointer = va_arg(args, void *);

	UNUSED(fieldWidth);
	UNUSED(sizeSpecifier);

	if (pointer == NULL)
		return (write(1, "(nil)", 5));

	outputBuffer[OUTPUT_BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	address = (unsigned long)pointer;

	while (address > 0)
	{
		outputBuffer[index--] = hexMap[address % 16];
		address /= 16;
		length++;
	}

	if ((activeFlags & F_ZERO) && !(activeFlags & F_MINUS))
		paddingChar = '0';
	if (activeFlags & F_PLUS)
		extraChar = '+', length++;
	else if (activeFlags & F_SPACE)
		extraChar = ' ', length++;

	index++;

	return (writePointer(outputBuffer, index, length, fieldWidth,
				activeFlags, paddingChar, extraChar, paddingStart));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * printNonPrintable - Prints ASCII codes in
 * hexadecimal of non-printable characters
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printNonPrintable(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	int index = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(sizeSpecifier);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (isPrintable(str[index]))
			outputBuffer[index + offset] = str[index];
		else
			offset += appendHexaCode(str[index], outputBuffer, index + offset);

		index++;
	}

	outputBuffer[index + offset] = '\0';

	return (write(1, outputBuffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * printReverse - Prints a reversed string.
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */

int printReverse(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	char *str;
	int index, count = 0;

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(sizeSpecifier);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}

	for (index = 0; str[index]; index++)
		;

	for (index = index - 1; index >= 0; index--)
	{
		char character = str[index];

		write(1, &character, 1);
		count++;
	}
	return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * printRot13String - Print a string in ROT13.
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printRot13String(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	char x;
	char *str;
	unsigned int index, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(sizeSpecifier);

	if (str == NULL)
		str = "(AHYY)";
	for (index = 0; str[index]; index++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[index])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[index];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
