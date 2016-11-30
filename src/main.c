#include <search.h>
#include <stdlib.h>
#include "../inc/LogStats.h"
#include "../inc/parse.h"

/**
 * @file main.c
 *
 * File that contains the main function.
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
	struct LogStats *stats;

	stats = lgsCreate(MAXN_DAYS);

	if (stats == NULL)
		errexit("Error!", 1);

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
			if (lgsAddLogEntry(stats, &entry) != 0)
				fprintf(stderr, "Can't add log entry to stats!\n");
		}
	}

	lgsSort(stats);
	lgsPrint(stats, stdout);

	lgsDestroy(stats);

	return 0;
}

void errexit(const char *message, int error)
{
	fputs(message, stderr);
	exit(error);
}
