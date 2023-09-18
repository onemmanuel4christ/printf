#include "main.h"

/**
 * get_size- Calculates the size to cast the argument
 * @formatString: Formatted string in which to print the arguments
 * @currentIndex: List of arguments to be printed.
 *
 * Return: Precision.
 */

int get_size(const char *formatString, int *currentIndex)
{
	int currentIdx = *currentIndex + 1;

	int size = 0;

	if (formatString[currentIdx] == 'l')
		size = S_LONG;

	else if (formatString[currentIdx] == 'h')
		size = S_SHORT;

			if (size == 0)
				*currentIndex = currentIdx - 1;
			else
				*currentIndex = currentIdx;
return (size);
}
