
#include "../inc/parse.h"

/**
 * @file main.c
 *
 * File that contains the main function.
 *
 * @see main
 */

/**
 * The main entry point of the program.
 * This is the first function that is called, when the program starts.
 *
 * @param argc Number of command line arguments.
 * @param argv List of all command line arguments.
 * @return A status code (0 means success, anything else means something went wrong).
 */
int main(int argc, char **argv)
{
	struct LogEntry e;
	int n = 0;

	while (1)
	{
		if (parseLogEntry(stdin, &e) != 0)
		{
			if (feof(stdin))
				break;

			fprintf(stderr, "invalid format in line #%d\n", n);
			return 1;
		}
		else
		{
			n++;
		}
	}

	printf("%d log entries read\n", n);

	return 0;
}
