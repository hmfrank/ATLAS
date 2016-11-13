#ifndef ATLAS_PARSE_H
#define ATLAS_PARSE_H

#include <stdio.h>
#include "LogEntry.h"

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
 * <b>Format:</b> <b>[</b>\<day\><b>/</b>\<month\><b>/</b>\<year\><b>:</b>\<time\><b>]#</b>\<remote_address\><b>#</b>\<username\><b>#</b>\<status_code\><b>#</b>\<request_size\><b>#</b>\<response_size\><b>#</b>\<requested_url\><b>#</b>\<referer\><b>#</b>\<http_method\>\<terminator\>
 * - \a day: 0 &le; \a day &le; 99
 * - \a month: jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec (not case sensitive)
 * - \a year: 0 &le; \a year &le; 9999
 * - \a time: must not contain `]` (is ignored anyway)
 * - \a remote_address: must not contain `#`
 * - \a username: must not contain `#`
 * - \a status_code: 0 &le; \a status_code &le; 999
 * - \a request_size: 0 &le; \a request_size &le; `UINT_MAX`
 * - \a response_size: 0 &le; \a response_size &le; `UINT_MAX`
 * - \a requested_url: must not contain `#`
 * - \a referer: must not contain `#`
 * - \a http_method: must not contain `#`
 * - \a terminator: `\n` or `EOF`
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
