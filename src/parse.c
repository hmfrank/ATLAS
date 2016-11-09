#include <stdlib.h>
#include <string.h>
#include "../inc/parse.h"

/**
 * @file parse.c
 *
 * Contains implementations of the functions defined in parse.h plus some static helper functions.
 */

/**
 * Reads a string from `reader` and writes it into `buffer`.
 * This function reads `reader` until `EOF` or one of the chars in `terminator` is read (including the string
 * 0-terminator) or the buffer is full.
 * The first character, that breaks the above condition (and therefore stopps the reading process) is still read. So
 * further reading from `reader` continues after that character.
 * The read string is stored in `buffer` and a 0-terminator is added.
 *
 * **WARNING:** Passing `NULL` to `reader` or `buffer` is undefined behaviour.
 *
 * @param reader Points to the reader to read from.
 * @param terminators A string of all characters, that make the reading stop, or `NULL` if there aren't any.
 * @param bufsize The number of bytes this function is allowed to write into `buffer`. In other words, the maximum
 * number of characters that are read from `reader`.
 * @param buffer A buffer to write the read string to.
 * @return The number of characters read.
 */
static size_t parseString(struct PreReader *reader, const char *terminators, size_t bufsize, char *buffer)
{
	if (bufsize == 0)
		return 0;

	int c;
	size_t n_buffer;

	for (n_buffer = 0; ; n_buffer++)
	{
		c = prNext(reader);

		if (n_buffer >= bufsize - 1)
			break;
		if (c == EOF)
			break;
		if ((terminators != NULL) && strchr(terminators, (char)c) != NULL)
			break;

		buffer[n_buffer] = (char)c;
	}

	buffer[n_buffer] = '\0';

	return n_buffer;
}