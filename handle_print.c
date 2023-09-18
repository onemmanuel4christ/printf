#include "main.h"

/**
 * handlePrint - Prints an argument based on its type
 * @format: Format of the arguments that will be printed
 * @index: Current index in the format string
 * @args: Arguments to be printed
 * @outputBuffer: Buffer array to handle print
 * @activeFlags: Calculates active flags
 * @fieldWidth: Field width
 * @precision: Precision specification
 * @sizeSpecifier: Size specifier
 * Return: 1 or 2;
 */
int handlePrint(const char *format, int *index, va_list args, char
		outputBuffer[], int activeFlags, int fieldWidth,
		int precision, int sizeSpecifier)
{
	int i, unknownLength = 0, printedChars = -1;
	fmt_t formatTypes[] = {
		{'c', printCharacter}, {'s', printString}, {'%', printPercent},
		{'i', printInteger}, {'d', printInteger}, {'b', printBinary},
		{'u', printUnsignedNumber}, {'o', printOctalNumber}, {'x', printHexadecimalNumber},
		{'X', printHexadecimalNumberUpper}, {'p', printPointer}, {'S', printNonPrintable},
		{'r', printReverse}, {'R', printRot13String}, {'\0', NULL}
	};
	for (i = 0; formatTypes[i].format != '\0'; i++)
		if (format[*index] == formatTypes[i].format)
			return (formatTypes[i].function(args, outputBuffer, activeFlags,
						fieldWidth, precision, sizeSpecifier));

	if (formatTypes[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknownLength += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknownLength += write(1, " ", 1);
		else if (fieldWidth)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknownLength += write(1, &format[*index], 1);
		return (unknownLength);
	}
	return (printedChars);
}
