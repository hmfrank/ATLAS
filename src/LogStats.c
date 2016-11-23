#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../inc/LogStats.h"

/**
 * @file LogStats.c
 *
 * Contains the implementation of the functions defined in LogStats.h.
 */

struct LogStats *lgsCreate(size_t capacity)
{
	struct LogStats *stats;

	stats = malloc(sizeof(struct LogStats) + capacity * sizeof(stats->data[0]));

	if (stats == NULL)
		return NULL;

	stats->capacity = capacity;
	stats->length = 0;

	return stats;
}

int lgsAddLogEntry(struct LogStats *this, struct LogEntry *entry)
{
	if (this == NULL)
		return 1;
	if (entry == NULL)
		return 1;

	ssize_t i;

	// check if there's already an entry for the given date
	for (i = this->length - 1; i >= 0; i--)
	{
		if (dtCompare(&(this->data[0].date), &(entry->date)) == 0)
			break;
	}

	// if no entry was found, create a new one
	if (i < 0)
	{
		if (this->length >= this->capacity)
			return 2;

		this->data[this->length].date = entry->date;
		memset(&(this->data[this->length].counter), 0, sizeof(this->data[0].counter));

		i = (ssize_t)this->length;
		this->length++;
	}

	// add information to the entry
	dcAddLogEntry(&(this->data[i].counter), entry);

	return 0;
}