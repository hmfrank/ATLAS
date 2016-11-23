#ifndef ATLAS_LOGSTATS_H
#define ATLAS_LOGSTATS_H

#include <search.h>

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
	/**
	 * A hash table, that maps date strings to `struct DayCounter`-pointers that store information about each day.
	 */
	struct hsearch_data *htab;

	/**
	 * A list of all keys, in `htab`.
	 */
	char **keys;

	/**
	 * The maximum number of keys that can be stored in `keys`.
	 */
	size_t c_keys;

	/**
	 * The number of keys stored in `keys`.
	 */
	size_t n_keys;
};

#endif //ATLAS_LOGSTATS_H
