/**
 * @file LogStats.c
 *
 * Contains the implementation of the functions defined in LogStats.h.
 *
 * @see LogStats.h
 */

#include <stdlib.h>
#include <string.h>
#include "../inc/globals.h"
#include "../inc/LogStats.h"

/**
 * Prints the table header to `stream`.
 *
 * @param stream not `NULL`
 */
static void printHeader(FILE *stream)
{
	if (SHOW_DATE)      fprintf(stream, "%10s ", "DATE");
	if (SHOW_REQUESTS)  fprintf(stream, "%10s ", "REQUESTS");
	if (SHOW_USERS)     fprintf(stream, "%10s ", "USERS");
	if (SHOW_IN_BYTES)  fprintf(stream, "%10s ", "IN");
	if (SHOW_OUT_BYTES) fprintf(stream, "%10s ", "OUT");

	fprintf(stream, "\n");
}

/**
 * Prints a table row to `stream` with the data from `counter`.
 *
 * @param date not `NULL`
 * @param counter not `NULL`
 * @param stream not `NULL`
 */
static void printRow(const char *date, struct Counter *counter, FILE *stream)
{
	if (SHOW_DATE)      fprintf(stream, "%10s ", date);
	if (SHOW_REQUESTS)  fprintf(stream, "%10u ", counter->n_requests);
	if (SHOW_USERS)     fprintf(stream, "%10u ", ctrCountUsers(counter));
	if (SHOW_IN_BYTES)  fprintf(stream, "%10llu ", counter->n_bytes_in);
	if (SHOW_OUT_BYTES) fprintf(stream, "%10llu ", counter->n_bytes_out);

	fprintf(stream, "\n");
}

struct LogStats *lgsCreate(size_t capacity)
{
	struct LogStats *stats;

	// allocate struct itself
	stats = malloc(sizeof(struct LogStats));
	if (stats == NULL)
		return NULL;

	// create the total counter
	if (ctrInit(&stats->total_counter) != 0)
	{
		free(stats);
		return NULL;
	}

	// allocate key array
	stats->keys = malloc(capacity * sizeof(char*));
	if (stats->keys == NULL)
	{
		ctrFree(&stats->total_counter);
		free(stats);
		return NULL;
	}

	// initialize hash table
	memset(&stats->hash_table, 0, sizeof(stats->hash_table));

	if (hcreate_r(2 * capacity, &stats->hash_table) == 0)
	{
		ctrFree(&stats->total_counter);
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
		// destroy total counter
		ctrFree(&this->total_counter);

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

	// add log entry to day counter
	ctrAddLogEntry(found->data, entry);

	// add to total counter
	ctrAddLogEntry(&this->total_counter, entry);

	return 0;
}

void lgsPrint(struct LogStats *this, FILE *stream)
{
	if (this == NULL)
		return;
	if (stream == NULL)
		return;

	if (SHOW_TABLE_HEADER)
	{
		printHeader(stream);
	}

	// print days
	for (size_t i = 0; i < this->length; i++)
	{
		ENTRY kv_pair = { .key = this->keys[i], .data = NULL };
		ENTRY *found;
		struct Counter *counter;

		hsearch_r(kv_pair, FIND, &found, &this->hash_table);

		if (found != NULL) // should always be the case
		{
			counter = found->data;
			printRow(found->key, counter, stream);
		}
	}

	// print total counter
	if (SHOW_TOTAL_COUNT)
	{
		printRow("all", &this->total_counter, stream);
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