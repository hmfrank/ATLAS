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
 * Don't access this struct directly (except you know what you're doing). Use the methods, defined in PreReader.h,
 * instead.
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

#endif //ATLAS_PREREADER_H
