#ifndef ATLAS_LOGSTATS_H
#define ATLAS_LOGSTATS_H

#include <search.h>
#include <stdio.h>
#include "Date.h"
#include "DayCounter.h"
#include "LogEntry.h"

/**
 * @file LogStats.h
 *
 * Contains the definition of `struct LogStats`, as well as some related function prototypes.
 */

/**
 * Stores statistical information about an entire log file.
 */
struct LogStats
{
	size_t capacity;
	size_t length;

	struct DayCounter data[0];
};

/**
 * Allocates and initializes a new LogStats.
 * To prevent memory leaks, make sure you call `free()` on the returned pointer, once you don't need it anymore.
 *
 * @param capacity The maximum number of days, that can be stored in the new LogStats.
 * @return Pointer to the newly allocated struct or `NULL` on failure.
 */
struct LogStats *lgsCreate(size_t capacity);

/**
 * Adds the information about the given log entry to the stats.
 *
 * @param _this Points to the LogStats that stores the statistics.
 * @param entry Points to the LogEntry which information shall be added to the stats.
 * @return 0 on success, non-zero on failure.
 */
int lgsAddLogEntry(struct LogStats *_this, struct LogEntry *entry);

/**
 * Writes the data collected in `_this` to `stream` in a nice, readable format.
 * If either of the parameters is `NULL`, nothing happens.
 *
 * @param _this Points to the LogStats that shall be printed.
 * @param stream The stream to write to.
 */
void lgsPrint(struct LogStats *_this, FILE *stream);

/**
 * Sorts the internal data of the stats by date.
 * @param _this The LogStats to be sorted.
 */
void lgsSort(struct LogStats *_this);

#endif //ATLAS_LOGSTATS_H
