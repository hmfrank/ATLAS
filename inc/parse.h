#ifndef ATLAS_PARSE_H
#define ATLAS_PARSE_H

#include "LogEntry.h"
#include "PreReader.h"

// TODO: add log format to docu

/**
 * @file parse.h
 *
 * Contains function prototypes for parsing a log file.
 */

/**
 * Parses a line of a log file to create a LogEntry.
 *
 * @param reader The reader to read from (must be at a line start in the log file).
 * @param result A pointer to where the result is gonna be stored.
 * @return Status code with the following meaning:<br>
 * 0 = success<br>
 * -1 = invalid parameter (e.g. `NULL`)<br>
 * 1 = parsing error (wrong format or `EOF` reached)
 */
int parseLogEntry(struct PreReader *reader, struct LogEntry *result);

#endif //ATLAS_PARSE_H
