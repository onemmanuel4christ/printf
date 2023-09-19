#include "main.h"

/**
 * isPrintable - Checks if a character is printable
 * @c: Character to be checked
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int isPrintable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * appendHexaCode - Appends ASCII in hexadecimal code to buffer
 * @buffer: Array of characters
 * @startIndex: Index at which to start appending
 * @asciiCode: ASCII code
 *
 * Return: Always 3
 */
int appendHexaCode(char asciiCode, char buffer[], int startIndex)
{
	char mapTo[] = "0123456789ABCDEF";
	/* The hexadecimal code format is always 2 digits long */
	if (asciiCode < 0)
		asciiCode *= -1;

	buffer[startIndex++] = '\\';
	buffer[startIndex++] = 'x';

	buffer[startIndex++] = mapTo[asciiCode / 16];
	buffer[startIndex] = mapTo[asciiCode % 16];

	return (3);
}

/**
 * isDigit - Checks if a character is a digit
 * @c: Character to be checked
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convertSizeNumber - Casts a number to the specified size
 * @num: Number to be cast
 * @size: Size indicating the type to be cast
 *
 * Return: Casted value of num
 */
long int convertSizeNumber(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convertSizeUnsigned - Casts an unsigned number to the specified size
 * @num: Number to be cast
 * @size: Size indicating the type to be cast
 *
 * Return: Casted value of num
 */
long int convertSizeUnsigned(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
