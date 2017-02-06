#include <stddef.h>

#ifndef ATLAS_GLOBALS_H
#define ATLAS_GLOBALS_H

/**
 * The maximum number of days the program can store information about.
 */
extern const size_t MAX_N_DAYS;

/**
 * Specifies weather or not the table header is shown.
 */
extern const int SHOW_TABLE_HEADER;

/**
 * Specifies whether or not the total count is shown.
 */
extern const int SHOW_TOTAL_COUNT;

/**
 * Specifies whether or not the date column is shown.
 */
extern const int SHOW_DATE;

/**
 * Specifies whether or not the number of requests column is shown.
 */
extern const int SHOW_REQUESTS;

/**
 * Specifies whether or not the number of unique IPs column ("USERS") is shown.
 */
extern const int SHOW_USERS;

/**
 * Specifies whether or not the in-bytes column is shown.
 */
extern const int SHOW_IN_BYTES;

/**
 * Specifies whether or note the out-bytes column is shown.
 */
extern const int SHOW_OUT_BYTES;

/**
 * Reads the command line arguments and sets the global variables accordingly.
 * @param argc The number of command line arguments.
 * @param argv Array of command line arguments.
 */
void parseCommandLineArguments(int argc, char **argv);

#endif //ATLAS_GLOBALS_H
