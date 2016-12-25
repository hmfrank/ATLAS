/**
 * @file LogEntry.c
 *
 * Contains the implementatoins of the methods defined in LogEntry.h.
 *
 * @see LogEntry.h
 */

#include <stdlib.h>
#include <string.h>
#include "../inc/LogEntry.h"

int lgeEquals(struct LogEntry *a, struct LogEntry *b)
{
	if (a == b)
	{
		return 1;
	}
	else if (a == NULL || b == NULL)
	{
		return 0;
	}

	int strEquals(const char *s, const char *t)
	{
		if (s == NULL)
		{
			return t == NULL;
		}
		else
		{
			if (t == NULL)
			{
				return 0;
			}
			else
			{
				return !strcmp(s, t);
			}
		}
	}

	return strcmp(a->date, b->date) == 0 &&
        a->http_method == b->http_method &&
        a->http_status == b->http_status &&
        a->request_size == b->request_size &&
        a->response_size == b->response_size &&
	    strEquals(a->remote_address, b->remote_address) &&
	    strEquals(a->requested_file, b->requested_file) &&
	    strEquals(a->referer, b->referer);
}

void lgeFreeStrings(struct LogEntry *this)
{
	if (this == NULL)
		return;

	if (this->remote_address != NULL) free((char*)this->remote_address);
	if (this->requested_file != NULL) free((char*)this->requested_file);
	if (this->referer != NULL) free((char*)this->referer);
}
