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

int prNext(struct PreReader *this)
{
	if (this == NULL)
		return EOF;
	if (this->read_pos > PREREADER_BUFFER_SIZE || this->write_pos > PREREADER_BUFFER_SIZE)
		return EOF;
	if (this->read_pos > this->write_pos)
		return EOF;

	// if there are no new bytes, reload
	if (this->read_pos == this->write_pos)
	{
		this->read_pos = 0;
		this->write_pos = fread(this->buffer, sizeof(char), PREREADER_BUFFER_SIZE, this->file);

		if (this->write_pos == 0)
			return EOF;
	}

	return this->buffer[this->read_pos++];
}