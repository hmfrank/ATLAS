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
 * Stores statistical information about an entire log file. Basically it's just an array of `struct DayCounter`, where
 * one `DayCounter` is stored for each day in the log.
 *
 * You should only create instances of `LogStats` using `lgsCreate()`. Also note that instances of this struct can only
 * be stored on the heap, not on the stack, because the memory for the array data is allocated right behind the actual
 * struct data. This means, that you'll always have to use a pointer to `struct LogStats`, which you can free with a
 * normal `free()` call.
 *
 * Methods of the struct start with "lgs".
 *
 * @see lgsCreate()
 * @see lgsAddLogEntry()
 * @see lgsPrint()
 * @see lgsSort()
 */
struct LogStats
{
	/**
	 * The maximum number of items that memory is allocated for.
	 */
	size_t capacity;

	/**
	 * The actual number of elements, that are stored in the array.
	 */
	size_t length;

	/**
	 * Points to the first element of the array (which is stored right behind the atucal struct in memory).
	 */
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
