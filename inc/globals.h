#include <stddef.h>

#ifndef ATLAS_GLOBALS_H
#define ATLAS_GLOBALS_H

/**
 * The maximum number of days the program can store information about.
 */
extern size_t const * const MAX_N_DAYS;

/**
 * Specifies whether or not the table header is shown.
 */
extern int const * const SHOW_TABLE_HEADER;

/**
 * Specifies whether or not the days columns are shown.
 */
extern int const * const SHOW_DAYS;

/**
 * Specifies whether or not the total count is shown.
 */
extern int const * const SHOW_TOTAL_COUNT;

/**
 * Specifies whether or not the date column is shown.
 */
extern int const * const SHOW_DATE;

/**
 * Specifies whether or not the number of requests column is shown.
 */
extern int const * const SHOW_REQUESTS;

/**
 * Specifies whether or not the number of unique IPs column ("USERS") is shown.
 */
extern int const * const SHOW_USERS;

/**
 * Specifies whether or not the in-bytes column is shown.
 */
extern int const * const SHOW_IN_BYTES;

/**
 * Specifies whether or note the out-bytes column is shown.
 */
extern int const * const SHOW_OUT_BYTES;

/**
 * Specifies the data structure used to count the number of unique users.
 */
extern int const * const METHOD;

#define MAX_N_DAYS (*MAX_N_DAYS)
#define SHOW_TABLE_HEADER (*SHOW_TABLE_HEADER)
#define SHOW_DAYS (*SHOW_DAYS)
#define SHOW_TOTAL_COUNT (*SHOW_TOTAL_COUNT)
#define SHOW_DATE (*SHOW_DATE)
#define SHOW_REQUESTS (*SHOW_REQUESTS)
#define SHOW_USERS (*SHOW_USERS)
#define SHOW_IN_BYTES (*SHOW_IN_BYTES)
#define SHOW_OUT_BYTES (*SHOW_OUT_BYTES)
#define METHOD (*METHOD)

/**
 * Reads the command line arguments and sets the global variables accordingly.
 * @param argc The number of command line arguments.
 * @param argv Array of command line arguments.
 */
void parseCommandLineArguments(int argc, char **argv);

#endif //ATLAS_GLOBALS_H
