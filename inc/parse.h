#ifndef ATLAS_PARSE_H
#define ATLAS_PARSE_H

/**
 * @file parse.h
 *
 * Contains function prototypes for parsing a log file.
 *
 * @see parse.c
 */

#include <stdio.h>
#include "LogEntry.h"

/**
 * Parses a line of a log file to create a LogEntry.
 * If the function succeeds, the strings in `*result` are allocated on the heap using `malloc`, so make sure
 * you free them, when you don't need them anymore.
 *
 * This function uses the following Apache web server log format: `%%h %%u %%t %%m %%s %%I %%O "%U" "%{Referer}i"`
 * For more information, see [mod_log_config - Apache HTTP Server Version 2.4](http://httpd.apache.org/docs/current/mod/mod_log_config.html).
 *
 * A typical log line might look like this: `12.34.56.78 - [23/Dec/2016:18:36:27 +0000] GET 200 394 992 "/public/" "-"`.
 *
 * @param stream The file stream to read from.
 * @param result A pointer to where the result is gonna be stored.
 * @return Status code with the following meaning:<br>
 * 0 = success<br>
 * -1 = invalid parameter (e.g. `NULL`)<br>
 * 1 = parsing error (wrong format or `EOF` reached)<br>
 * 2 = malloc error
 */
int parseLogEntry(FILE *stream, struct LogEntry *result);

#endif //ATLAS_PARSE_H
