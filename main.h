#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @length: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int length;
} bufferS;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct conv_s
{
	unsigned char specif;
	unsigned int (*func)(va_list, bufferS *,
			unsigned char, int, int, unsigned char);
} conv_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int conv_c(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_percent(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_p(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_x(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_X(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_di(va_list list, bufferS *out_put,
			unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_b(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_u(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_o(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_S(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_r(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_R(va_list list, bufferS *out_put,
		unsigned char flags, int width, int precis, unsigned char length);
unsigned int conv_s(va_list list, bufferS *out_put,
                unsigned char flags, int width, int precis, unsigned char length);

/* Handlers */
unsigned char handle_flags(const char *flag, char *inde);
unsigned char handle_length(const char *modif, char *inde);
int handle_width(va_list args, const char *modif, char *inde);
int handle_precision(va_list args, const char *modif, char *inde);
unsigned int (*handle_specifiers(const char *specif))(va_list, bufferS *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width);
unsigned int print_string_width(bufferS *out_put,
		unsigned char flags, int width, int precis, int sizeT);
unsigned int print_neg_width(bufferS *out_put, unsigned int printed,
		unsigned char flags, int width);

/* Helper Functions */
unsigned int _memcpy(bufferS *out_put, const char *source, unsigned int n);
void free_buffer(bufferS *out_put);
bufferS *init_buffer(void);
unsigned int conv_base(bufferS *out_put, long int numb, char *baseC,
		unsigned char flags, int width, int precis);
unsigned int conv_ubase(bufferS *out_put,
		unsigned long int numb, char *baseC,
		unsigned char flags, int width, int precis);

#endif
