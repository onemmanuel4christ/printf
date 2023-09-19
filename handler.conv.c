#include "main.h"

unsigned char handle_flags(const char *flag, char *inde);
unsigned char handle_length(const char *modif, char *inde);
int handle_width(va_list args, const char *modif, char *inde);
int handle_precision(va_list args, const char *modif, char *inde);
unsigned int (*handle_specifiers(const char *specif))(va_list, bufferS *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @inde: An index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_flags(const char *flag, char *inde)
{
	int i, j;
	unsigned char reti = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*inde)++;
				if (reti == 0)
					reti = flags[j].value;
				else
					reti |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (reti);
}

/**
 * handle_length - Matches length modifiers with their corresponding value.
 * @modif: A pointer to a potential length modifier.
 * @inde: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_length(const char *modif, char *inde)
{
	if (*modif == 'h')
	{
		(*inde)++;
		return (SHORT);
	}

	else if (*modif == 'l')
	{
		(*inde)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modif: A pointer to a potential width modifier.
 * @inde: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int handle_width(va_list args, const char *modif, char *inde)
{
	int value = 0;

	while ((*modif >= '0' && *modif <= '9') || (*modif == '*'))
	{
		(inde)++;

		if (*modif == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modif - '0');
		modif++;
	}

	return (value);
}

/**
 * handle_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modif: A pointer to a potential precision modifier.
 * @inde: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int handle_precision(va_list args, const char *modif, char *inde)
{
	int value = 0;

	if (*modif != '.')
		return (-1);

	modif++;
	(*inde)++;

	if ((*modif <= '0' || *modif > '9') &&
			*modif != '*')
	{
		if (*modif == '0')
			(*inde)++;
		return (0);
	}

	while ((*modif >= '0' && *modif <= '9') ||
			(*modif == '*'))
	{
		(*inde)++;

		if (*modif == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modif - '0');
		modif++;
	}

	return (value);
}

/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @specif: A pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specif))(va_list, bufferS *,
		unsigned char, int, int, unsigned char)
{
	int i;
	conv_t convert[] = {
		{'c', conv_c},
		{'S', conv_S},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_percent},
		{'b', conv_b},
		{'u', conv_u},
		{'o', conv_o},
		{'x', conv_x},
		{'X', conv_X},
		{'s', conv_s},
		{'p', conv_p},
		{'r', conv_r},
		{'R', conv_R},
		{0, NULL}
	};

	for (i = 0; convert[i].func; i++)
	{
		if (convert[i].specif == *specif)
			return (convert[i].func);
	}

	return (NULL);
}

