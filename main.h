#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define UNUSED(x) (void)(x)
#define OUTPUT_BUFFER_SIZE 1024

#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

#define S_LONG 2
#define S_SHORT 1

/**
 * struct format - Struct op
 *
 * @format: The format.
 * @function: The function associated.
 */
struct format
{
	char format;
	int (*function)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct format fmt_t - Struct op
 *
 * @format: The format.
 * @fm_t: The function associated.
 */
typedef struct format fmt_t;

int _printf(const char *format, ...);
int getFlags(const char *formatString, int *currentIndex);
int getWidth(const char *format, int *currentIndex, va_list list);
int getPrecision(const char *format, int *currentIndex, va_list list);
int getSize(const char *formatString, int *currentIndex);
int handlePrint(const char *fmt, int *i,
		va_list list, char buffer[], int flags, int width, int precision, int size);
int printCharacter(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printString(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printPercent(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printInteger(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printBinary(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printUnsignedNumber(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printOctalNumber(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printHexadecimalNumber(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printHexadecimalNumberUpper(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printHexadecimal(va_list args, char mapTo[], char outputBuffer[],
		int activeFlags, char flagChar, int fieldWidth,
		int precision, int sizeSpecifier);
int printCharacter(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printPercent(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int writeChar(char c, char buffer[], int flags,
		int width, int precision, int size);
int isPrintable(char c);
int appendHexaCode(char asciiCode, char buffer[], int startIndex);
int isDigit(char c);
long int convertSizeNumber(long int num, int size);
long int convertSizeUnsigned(unsigned long int num, int size);
int writeChar(char c, char buffer[],
		int flags, int width, int precision, int size);
int writeNumber(int isNegative, int ind, char buffer[],
		int flags, int width, int precision, int size);
int writeNum(int ind, char buffer[],
		int flags, int width, int prec,
		int length, char paddingChar, char extraChar);
int writePointer(char buffer[], int ind, int length,
		int width, int flags, char paddingChar, char extraChar, int paddingStart);
int writeUnsigned(int isNegative, int ind,
		char buffer[], int flags, int width, int precision, int size);
int printNonPrintable(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printPointer(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printReverse(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printRot13String(va_list args, char outputBuffer[],
		int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
void print_buffer(char buffer[], int *buff_ind);

#endif
