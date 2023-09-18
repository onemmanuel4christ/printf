#include "main.h"

/************************* PRINT CHARACTER *************************/

/**
 * printCharacter - Prints a character
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printCharacter(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	char character = va_arg(args, int);

	return (handleWriteChar(character, outputBuffer, activeFlags, fieldWidth, precision, sizeSpecifier));
}

/************************* PRINT STRING *************************/
/**
 * printString - Prints a string
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printString(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(sizeSpecifier);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (fieldWidth > length)
	{
		if (activeFlags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = fieldWidth - length; i > 0; i--)
				write(1, " ", 1);
			return (fieldWidth);
		}
		else
		{
			for (i = fieldWidth - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (fieldWidth);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * printPercent - Prints a percent sign
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printPercent(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	UNUSED(args);
	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(sizeSpecifier);
	return (write(1, "%%", 1));
}

/************************* PRINT INTEGER *************************/
/**
 * printInteger - Print integer
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printInteger(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	int i = OUTPUT_BUFFER_SIZE - 2;
	int isNegative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convertSizeNumber(n, sizeSpecifier);

	if (n == 0)
		outputBuffer[i--] = '0';

	outputBuffer[OUTPUT_BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		isNegative = 1;
	}

	while (num > 0)
	{
		outputBuffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (writeNumber(isNegative, i, outputBuffer, activeFlags, fieldWidth, precision, sizeSpecifier));
}

/************************* PRINT BINARY *************************/
/**
 * printBinary - Prints an unsigned number in binary
 * @args: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @activeFlags:  Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: Number of characters printed
 */
int printBinary(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(sizeSpecifier);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char binaryChar = '0' + a[i];

			write(1, &binaryChar, 1);
			count++;
		}
	}
	return (count);
}
