#ifndef ATLAS_LOGSTATS_H
#define ATLAS_LOGSTATS_H

#include <search.h>
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
	// TODO: specify struct LogStats
};

/**
 * Create a new `struct LogStats`.
 *
 * @param this_ Points to the where the new struct is stored.
 * @return 0 on success, non-zero on failure.
 */
int lgsCreate(struct LogStats *this_);

/**
 * Frees all resources used by a given `struct LogStats`.
 *
 * @param this_ Points to the `struct LogStats` which resources get freed.
 */
void lgsFreeResources(struct LogStats *this_);

/**
 * Adds the information of the given log entry to the stats.
 *
 * @param this_ Points to the `struct LogStats` that stores the statistics.
 * @param entry Points to the `struct LogEntry` which information shall be added to the stats.
 * @return 0 on success, non-zero on failure.
 */
int lgsAddLogEntry(struct LogStats *this_, struct LogEntry *entry);

#endif //ATLAS_LOGSTATS_H
