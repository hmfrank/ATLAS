#ifndef ATLAS_LOGSTATS_H
#define ATLAS_LOGSTATS_H

/**
 * @file LogStats.h
 *
 * Contains the definition of `struct LogStats`, as well as some related function prototypes.
 */

#include <search.h>
#include <stdio.h>
#include "Counter.h"
#include "LogEntry.h"

/**
 * Stores statistical information about an entire log file, especially about each day in the log.
 *
 * You should only create instances of `LogStats` using `lgsCreate()` and when you don't need them anymore, pass them to
 * `lgsDestroy()`.
 *
 * Methods of the struct start with "lgs".
 *
 * @see lgsCreate()
 * @see lgsDestroy()
 * @see lgsAddLogEntry()
 * @see lgsPrint()
 * @see lgsSort()
 */
struct LogStats
{
	/**
	 * Global counter for the entire log.
	 */
	struct Counter total_counter;

	/**
	 * The maximum number of items that memory is allocated for.
	 */
	size_t capacity;

	/**
	 * The actual number of key-value-pairs, that are stored in the hash table.
	 */
	size_t length;

	/**
	 * Hash table that maps date-strings to counters, so we can have a counter for each day.
	 */
	struct hsearch_data hash_table;

	/**
	 * Array of keys that are inserted into the hase table.
	 */
	char **keys;
};

/**
 * Allocates and initializes a new LogStats.
 * To prevent memory leaks, make sure you call `lgsDestroy()` on the returned pointer, once you don't need it anymore.
 *
 * @param capacity The maximum number of days, that can be stored in the new LogStats.
 * @return Pointer to the newly allocated struct or `NULL` on failure.
 */
struct LogStats *lgsCreate(size_t capacity);

/**
 * Frees all the memory used by the given stats.
 * If `_this` is `NULL`, nothing happens.
 *
 * @param _this Points to the LogStats that are freed.
 */
void lgsDestroy(struct LogStats *_this);

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
