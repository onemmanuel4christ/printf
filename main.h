#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* programme flags */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* size */
#define S_LONG 2
#define S_SHORT 1

int _printf(const char *format, ...);


int getFlags(const char *formatString, int *currentIndex)
int getWidth(const char *format, int *i, va_list list);
int getPrecision(const char *format, int *i, va_list list);
int getSize(const char *formatString, int *currentIndex);
int handlePrint(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/* Funtions to print chars and strings */
int printCharacter(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printString(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier);
int printPercent(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier);

/* Functions to print numbers */
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
	int activeFlags, char flagChar, int fieldWidth, int precision, int sizeSpecifier);

/* Function to print non printable characters */
int printCharacter(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier);

/* Funcion to print memory address */
int printPercent(va_list args, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int sizeSpecifier);

int writeChar(char c, char buffer[], int flags, int width, int precision, int size);
#endif
