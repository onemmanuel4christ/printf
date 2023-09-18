#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * printUnsignedNumber - Prints an unsigned number
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed.
 */
int printUnsignedNumber(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	int i = OUTPUT_BUFFER_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convertSizeUnsigned(num, sizeSpecifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (writeUnsigned(0, i, outputBuffer, activeFlags, fieldWidth, precision, sizeSpecifier));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * printOctalNumber - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printOctalNumber(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	int i = OUTPUT_BUFFER_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(fieldWidth);

	num = convertSizeUnsigned(num, sizeSpecifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (activeFlags & F_HASH && initNum != 0)
		outputBuffer[i--] = '0';

	i++;

	return (writeUnsigned(0, i, outputBuffer, activeFlags, fieldWidth, precision, sizeSpecifier));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * printHexadecimalNumber - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimalNumber(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	return (printHexadecimal(args, "0123456789abcdef", outputBuffer,
		activeFlags, 'x', fieldWidth, precision, sizeSpecifier));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * printHexadecimalNumberUpper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimalNumberUpper(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	return (printHexadecimal(args, "0123456789ABCDEF", outputBuffer,
		activeFlags, 'X', fieldWidth, precision, sizeSpecifier));
}

/************** PRINT HEX NUMBER IN LOWER OR UPPER **************/
/**
 * printHexadecimal - Prints a hexadecimal number in lower or upper case
 * @args: List of arguments
 * @mapTo: Array of values to map the number to
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @flagChar: Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimal(va_list args, char mapTo[], char outputBuffer[],
	int activeFlags, char flagChar, int fieldWidth, int precision, int sizeSpecifier)
{
	int i = OUTPUT_BUFFER_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(fieldWidth);

	num = convertSizeUnsigned(num, sizeSpecifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[OUTPUT_BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = mapTo[num % 16];
		num /= 16;
	}

	if (activeFlags & F_HASH && initNum != 0)
	{
		outputBuffer[i--] = flagChar;
		outputBuffer[i--] = '0';
	}

	i++;

	return (writeUnsigned(0, i, outputBuffer, activeFlags, fieldWidth, precision, sizeSpecifier));
}

