/**
 * @file LogStats.c
 *
 * Contains the implementation of the functions defined in LogStats.h.
 *
 * @see LogStats.h
 */

#include <stdlib.h>
#include <string.h>
#include "../inc/LogStats.h"

struct LogStats *lgsCreate(size_t capacity)
{
	struct LogStats *stats;

	// allocate struct itself
	stats = malloc(sizeof(struct LogStats));
	if (stats == NULL)
		return NULL;

	// allocate key array
	stats->keys = malloc(capacity * sizeof(char*));
	if (stats->keys == NULL)
	{
		free(stats);
		return NULL;
	}

	// initialize hash table
	memset(&stats->hash_table, 0, sizeof(stats->hash_table));

	if (hcreate_r(2 * capacity, &stats->hash_table) == 0)
	{
		free(stats->keys);
		free(stats);
		return NULL;
	}

	// initialize other variables
	stats->capacity = capacity;
	stats->length = 0;

	return stats;
}

void lgsDestroy(struct LogStats *this)
{
	if (this != NULL)
	{
		// free key-value pairs
		for (size_t i = 0; i < this->length; i++)
		{
			ENTRY kv_pair = { .key = this->keys[i], .data = NULL };
			ENTRY *found = NULL;

			hsearch_r(kv_pair, FIND, &found, &this->hash_table);

			if (found != NULL)
			{
				ctrFree(found->data);
				free(found->data);
			}

			free(this->keys[i]);
		}

		// destroy hash table
		hdestroy_r(&this->hash_table);

		// free key array and this
		free(this->keys);
		free(this);
	}
}

int lgsAddLogEntry(struct LogStats *this, struct LogEntry *entry)
{
	if (this == NULL)
		return 1;
	if (entry == NULL)
		return 1;

	ENTRY kv_pair = { .key = entry->date, .data = NULL };
	ENTRY *found = NULL;

	hsearch_r(kv_pair, FIND, &found, &this->hash_table);

	// if key was not found
	if (found == NULL)
	{
		if (this->length >= this->capacity)
			return 2;

		// malloc key string and counter
		kv_pair.key = malloc(9 * sizeof(*kv_pair.key));
		kv_pair.data = malloc(sizeof(struct Counter));

		if (kv_pair.key == NULL || kv_pair.data == NULL)
		{
			if (kv_pair.key != NULL)
				free(kv_pair.key);
			if (kv_pair.data != NULL)
				free(kv_pair.data);

			return 3;
		}

		// init key string and counter
		strcpy(kv_pair.key, entry->date);
		ctrInit(kv_pair.data);

		// add key-value pair to hash table and key list
		hsearch_r(kv_pair, ENTER, &found, &this->hash_table);
		this->keys[this->length] = kv_pair.key;
		this->length++;
	}

	// add log entry to counter
	ctrAddLogEntry(found->data, entry);

	return 0;
}

void lgsPrint(struct LogStats *this, FILE *stream)
{
	if (this == NULL)
		return;
	if (stream == NULL)
		return;

	// print header
	fprintf(stream, "%10s %10s %10s %10s %10s\n", "DATE", "REQUESTS", "USERS", "IN", "OUT");

	// print data
	for (size_t i = 0; i < this->length; i++)
	{
		ENTRY kv_pair = { .key = this->keys[i], .data = NULL };
		ENTRY *found;
		struct Counter *counter;

		hsearch_r(kv_pair, FIND, &found, &this->hash_table);

		if (found != NULL) // should always be the case
		{
			counter = found->data;
			fprintf(stream, "%10s %10u %10u %10llu %10llu\n", found->key, counter->n_requests, ctrCountUsers(counter), counter->n_bytes_in, counter->n_bytes_out);
		}
	}
}

void lgsSort(struct LogStats *this)
{
	if (this == NULL)
		return;

	int compare(const void *x, const void *y)
	{
		return strcmp(*(const char **) x, *(const char **) y);
	}

	qsort(this->keys, this->length, sizeof(this->keys[0]), &compare);
}