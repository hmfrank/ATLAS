#ifndef ATLAS_PARSE_H
#define ATLAS_PARSE_H

#include <stdio.h>
#include "LogEntry.h"

// TODO: add log format to docu

/**
 * @file parse.h
 *
 * Contains function prototypes for parsing a log file.
 */

/**
 * Parses a line of a log file to create a LogEntry.
 * If the function succeeds (returns 0), the strings in `*result` are allocated on the heap using `malloc`, so make sure
 * you free them, when you don't need them anymore.
 *
 * @param stream The file stream to read from.
 * @param result A pointer to where the result is gonna be stored.
 * @return Status code with the following meaning:<br>
 * 0 = success<br>
 * -1 = invalid parameter (e.g. `NULL`)<br>
 * 1 = parsing error (wrong format or `EOF` reached)
 * 2 = malloc error
 */
int parseLogEntry(FILE *stream, struct LogEntry *result);

#endif //ATLAS_PARSE_H
