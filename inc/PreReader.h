#ifndef ATLAS_PREREADER_H
#define ATLAS_PREREADER_H

#include <stdio.h>

/**
 * @file PreReader.h
 *
 * Contains the `struct PreReader` and prototypes of its methods.
 * @see PreReader
 */

#define PREREADER_BUFFER_SIZE 1024

/**
 * This struct is used to pre-read data from a file that is about to be parsed.
 * The PreReader reads large blocks of a file at once and buffers them in memory (which is more efficient than reading
 * it byte by byte, as the parser does). The parser however, which uses a PreReader, can then read
 * byte by byte from the memory buffer of the PreReader.
 *
 * Don't access this struct directly (except you know what you're doing). Use the methods (those that start with pr),
 * defined in PreReader.h, instead.
 */
struct PreReader
{
	/**
	 * Pointer to the file to read from.
	 */
	FILE *file;
	/**
	 * Indicates the current position to read from `buffer`.
	 */
	size_t read_pos;
	/*
	 * Indicates the current position to write to in `buffer`.
	 */
	size_t write_pos;
	/**
	 * Buffer to store the pre-read data in.
	 */
	char buffer[PREREADER_BUFFER_SIZE];
};

/**
 * Initializes the PreReader.
 * Sets the file, resets all the pointers and that kinda stuff. This method should be called before the PreReader is
 * used.
 *
 * If either one of the parameters is `NULL` nothing happens.
 *
 * @param this Pointer to the PreReader that gets initialized.
 * @param file File to let the PreReader read from.
 */
void prInit(struct PreReader *this, FILE *file);

/**
 * Returns the next byte in the buffer.
 * If there is nothing new in the buffer, the next block is read from the underlying file. If the file is at its end,
 * `EOF` is returned.
 *
 * If `this` is `NULL`, `EOF` is returned
 *
 * @param this Pointer to the PreReader to read from.
 * @return The next character in the buffer, or `EOF` if there are no new characters.
 */
int prNext(struct PreReader *this);


#endif //ATLAS_PREREADER_H
