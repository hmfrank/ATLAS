#include "../inc/PreReader.h"

/**
 * @file PreReader.c
 *
 * Contains implementations of all the methods defined in PreReader.h (not yet though).
 *
 * @see PreReader.h
 */

void prInit(struct PreReader *this, FILE *file)
{
	if (this == NULL)
		return;
	if (file == NULL)
		return;

	this->file = file;
	this->read_pos = 0;
	this->write_pos = 0;
}