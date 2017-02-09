/**
 * @file Counter.c
 *
 * Contains implementations of the functions defined in Counter.h.
 *
 * @see Counter.h
 */

#include <string.h>
#include "../inc/Counter.h"
#include "../inc/globals.h"

int ctrInit(struct Counter *this)
{
	if (this == NULL)
		return 1;

	union DstInitInfo counter_init_info;

	memset(this, 0, sizeof(struct Counter));
	return dstInit(&this->user_counter, METHOD, &counter_init_info);
}

void ctrFree(struct Counter *this)
{
	if (this == NULL)
		return;

	dstFree(&this->user_counter);
}

void ctrAddLogEntry(struct Counter *this, struct LogEntry *entry)
{
	if (this == NULL)
		return;
	if (entry == NULL)
		return;

	this->n_requests++;
	this->n_bytes_in += entry->request_size;
	this->n_bytes_out += entry->response_size;
	dstAdd(&this->user_counter, (void*)entry->remote_address);
}

size_t ctrCountUsers(struct Counter *this_)
{
	return this_ == NULL ? 0 : dstCount(&this_->user_counter);
}