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

		memset(&(this->data[this->length]), 0, sizeof(this->data[0]));
		this->data[this->length].date = entry->date;

		i = (ssize_t)this->length;
		this->length++;
	}

	// add information to the entry
	dcAddLogEntry(this->data + i, entry);

	return 0;
}

void lgsPrint(struct LogStats *this, FILE *stream)
{
	if (this == NULL)
		return;
	if (stream == NULL)
		return;

	// print header
	fprintf(stream, "%10s %10s %10s %10s\n", "DATE", "REQUESTS", "IN", "OUT");

	// print data
	for (size_t i = 0; i < this->length; i++)
	{
		struct DayCounter counter = this->data[i];
		char str[18];

		dtToString(&counter.date, str);
		fprintf(stream, "%10s %10u %10llu %10llu", str, counter.n_requests, counter.n_bytes_in, counter.n_bytes_out);
	}
}

void lgsSort(struct LogStats *this)
{
	if (this == NULL)
		return;

	int compare(const void *x, const void *y)
	{
		return dtCompare(&((struct DayCounter *)x)->date, &((struct DayCounter *)y)->date);
	}

	qsort(this->data, sizeof(this->data[0]), this->length, compare);
}