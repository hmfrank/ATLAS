/**
 * @file Counter.c
 *
 * Contains implementations of the functions defined in Counter.h.
 *
 * @see Counter.h
 */

#include <string.h>
#include "../inc/Counter.h"

int strCompare(const void *a, const void *b)
{
	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	return strcmp((const char *)a, (const char *)b);
}

int ctrInit(struct Counter *this)
{
	if (this == NULL)
		return 1;

	union DstInitInfo counter_init_info;
	counter_init_info.avl_tree.compare = &strCompare;

	memset(this, 0, sizeof(struct Counter));
	return dstInit(&this->user_counter, AVL_TREE, &counter_init_info);
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