#ifndef ATLAS_COUNTER_H
#define ATLAS_COUNTER_H

/**
 * @file Counter.h
 *
 * Contains the definition of `struct Counter` as well as the prototypes of its methods.
 *
 * @see Counter.c
 */

#include "LogEntry.h"
#include "DistinctCounter.h"
/**
 * Stores accumulated information about many log entries.
 *
 * You should always call `ctrInit()` before and `ctrFree()` after using a `Counter`.
 *
 * Methods of this struct start with "ctr".
 *
 * @see ctrInit()
 * @see ctrFree()
 * @see ctrAddLogEntry()
 * @see ctrCountUsers()
 */
struct Counter
{
	/**
	 * Number of requests.
	 */
	unsigned int n_requests;

	/**
	 * Number of bytes received.
	 */
	unsigned long long int n_bytes_in;

	/**
	 * Number of bytes sent.
	 */
	unsigned long long int n_bytes_out;

	/**
	 * Counter to count the number of unique users.
	 */
	struct DistinctCounter user_counter;
};

/**
 * Initializes an empty counter.
 *
 * @param this_ Points to the counter that gets initialized.
 * @return 0 on success, non-zero on failure.
 */
int ctrInit(struct Counter *this_);

/**
 * Frees all resources used by a given counter.
 *
 * @param this_ Points to the counter to be freed.
 */
void ctrFree(struct Counter *this_);

/**
 * Adds some of the information stored in a log entry to a counter.
 *
 * If either one of the two parameters is `NULL`, nothing happens.
 *
 * @param this_ Pointer to a counter to add to.
 * @param entry Pointer to the log entry to get the information from.
 */
void ctrAddLogEntry(struct Counter *this_, struct LogEntry *entry);

/**
 * Returns the number of unique users that were counted.
 *
 * @param this_ Points to the counter that counted the users.
 * @return Number of unique users that were counted or `0`, if `this_` is `NULL`.
 */
size_t ctrCountUsers(struct Counter *this_);

#endif //ATLAS_COUNTER_H
