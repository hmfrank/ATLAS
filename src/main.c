#include <search.h>
#include <stdlib.h>
#include "../inc/LogStats.h"
#include "../inc/parse.h"

/**
 * @file main.c
 *
 * File that contains the main function.
 *
 * @see main
 */

/**
 * The maximum number of days the program can store information about.
 */
size_t MAXN_DAYS = 42;

/**
 * Prints an error message to `stderr` and exits the program.
 *
 * @param message The message to print on `strerr`.
 * @param error The error code that is returned to the OS.
 */
void errexit(const char *message, int error);

/**
 * The main entry point of the program.
 * This is the first function that is called, when the program starts.
 *
 * @param argc Number of command line arguments.
 * @param argv List of all command line arguments.
 * @return A status code (0 means success, anything else means something went wrong).
 */
int main()
{
	struct LogStats stats;

	if (lgsCreate(&stats))
		errexit("Some error occurred.", 1);

	// read log entries from stream, until EOF
	while (1)
	{
		struct LogEntry entry;

		if (parseLogEntry(stdin, &entry))
		{
			if (feof(stdin))
				break;

			fprintf(stderr, "invalid entry!\n");
		}
		else
		{
			lgsAddLogEntry(&stats, &entry);
		}
	}

	lgsFreeResources(&stats);

	return 0;

	/*
	// sort keys
	int _strcmp(const void * a, const void *b)
	{
		return strcmp(*(const char **)a, *(const char **)b);
	}
	qsort(keys, n_keys, sizeof(char*), _strcmp);

	// print data and free memory
	printf("%10s %10s %10s %10s\n", "DATE", "REQUESTS", "IN", "OUT");
	for (size_t i = 0; i < n_keys; i++)
	{
		ENTRY entry = { .key = keys[i] };
		ENTRY *ptr = hsearch(entry, FIND);

		if (ptr != NULL)
		{
			struct DayCounter *counter = (struct DayCounter*)ptr->data;

			printf("%10s %10d %10llu %10llu\n", ptr->key, counter->n_requests, counter->n_bytes_in, counter->n_bytes_out);

			free(ptr->data);
		}
	}
	*/
}

void errexit(const char *message, int error)
{
	fputs(message, stderr);
	exit(error);
}
