#include "main.h"

unsigned int _memcpy(bufferS *out_put, const char *source, unsigned int n);
void free_buffer(bufferS *out_put);
bufferS *init_buffer(void);

/**
 * _memcpy - Copies n bytes from memory area source to
 *           the buffer contained in a bufferS struct.
 * @out_put: A bufferS struct.
 * @source: A pointer to the memory area to copy.
 * @n: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(bufferS *out_put, const char *source, unsigned int n)
{
	unsigned int inde;

	for (inde = 0; inde < n; inde++)
	{
		*(out_put->buffer) = *(source + inde);
		(out_put->length)++;

		if (out_put->length == 1024)
		{
			write(1, out_put->start, out_put->length);
			out_put->buffer = out_put->start;
			out_put->length = 0;
		}

		else
			(out_put->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a bufferS struct.
 * @out_put: The bufferS struct to be freed.
 */
void free_buffer(bufferS *out_put)
{
	free(out_put->start);
	free(out_put);
}

/**
 * init_buffer - Initializes a variable of struct type bufferS.
 *
 * Return: A pointer to the initialized bufferS.
 */
bufferS *init_buffer(void)
{
	bufferS *out_put;

	out_put = malloc(sizeof(bufferS));
	if (out_put == NULL)
		return (NULL);

	out_put->buffer = malloc(sizeof(char) * 1024);
	if (out_put->buffer == NULL)
	{
		free(out_put);
		return (NULL);
	}

	out_put->start = out_put->buffer;
	out_put->length = 0;

	return (out_put);
}

