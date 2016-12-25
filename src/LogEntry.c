/**
 * @file LogEntry.c
 *
 * Contains the implementatoins of the methods defined in LogEntry.h.
 *
 * @see LogEntry.h
 */

#include <stdlib.h>
#include "../inc/LogEntry.h"

void lgeFreeStrings(struct LogEntry *this)
{
	if (this == NULL)
		return;

	if (this->remote_address != NULL) free((char*)this->remote_address);
	if (this->requested_file != NULL) free((char*)this->requested_file);
	if (this->referer != NULL) free((char*)this->referer);
}
