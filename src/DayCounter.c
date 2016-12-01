/**
 * @file DayCounter.c
 *
 * Contains implementations of the functions defined in DayCounter.h.
 *
 * @see DayCounter.h
 */

#include "../inc/DayCounter.h"

void dcAddLogEntry(struct DayCounter *this, struct LogEntry *entry)
{
	if (this == NULL)
		return;
	if (entry == NULL)
		return;

	this->n_requests++;
	// TODO: increment dc->n_useres
	this->n_bytes_in += entry->request_size;
	this->n_bytes_out += entry->response_size;
}