#include <stdlib.h>
#include "../inc/LogEntry.h"

/**
 * @file LogEntry.c
 *
 * Contains the implementatoins of the methods defined in LogEntry.h.
 *
 * @see LogEntry.h.
 */

void lgeFreeStrings(struct LogEntry *this)
{
	if (this == NULL)
		return;

	if (this->remote_address != NULL) free(this->remote_address);
	if (this->username != NULL) free(this->username);
	if (this->requested_file != NULL) free(this->requested_file);
	if (this->referer != NULL) free(this->referer);
}
