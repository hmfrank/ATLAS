/**
 * @file DayCounter.c
 *
 * Contains implementations of the functions defined in DayCounter.h.
 *
 * @see DayCounter.h
 */

#include <string.h>
#include "../inc/DayCounter.h"
#include "../inc/DistinctCounter.h"

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

int dcInit(struct DayCounter *this, struct Date date)
{
	if (this == NULL)
		return 1;

	union DstInitInfo counter_init_info;
	counter_init_info.avl_tree.compare = &strCompare;

	memset(this, 0, sizeof(struct DayCounter));
	this->date = date;
	return dstInit(&this->user_counter, AVL_TREE, &counter_init_info);
}

void dcFree(struct DayCounter *this)
{
	if (this == NULL)
		return;

	dstFree(&this->user_counter);
}

void dcAddLogEntry(struct DayCounter *this, struct LogEntry *entry)
{
	if (this == NULL)
		return;
	if (entry == NULL)
		return;

	this->n_requests++;
	this->n_bytes_in += entry->request_size;
	this->n_bytes_out += entry->response_size;
	dstAdd(&this->user_counter, entry->remote_address);
}

size_t dcCountUsers(struct DayCounter *this_)
{
	return this_ == NULL ? 0 : dstCount(&this_->user_counter);
}