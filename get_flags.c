#include "main.h"

/**
 * calculateActiveFlags - A function that calculates active flags
 * @formatString: Formatted string in which to print the arguments
 * @currentIndex: take a parameter.
 * Return: Flags:
 */
int getFlags(const char *formatString, int *currentIndex)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int index, currentIdx;
    int flags = 0;
    const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (currentIdx = *currentIndex + 1; formatString[currentIdx] != '\0'; currentIdx++)
    {
        for (index = 0; FLAGS_CHARACTERS[index] != '\0'; index++)
        {
            if (formatString[currentIdx] == FLAGS_CHARACTERS[index])
            {
                flags |= FLAGS_ARRAY[index];
                break;
            }
        }

        if (FLAGS_CHARACTERS[index] == 0)
            break;
    }

    *currentIndex = currentIdx - 1;

    return flags;
}

