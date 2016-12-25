#ifndef ATLAS_DAYINFO_H
#define ATLAS_DAYINFO_H

/**
 * @file DayCounter.h
 *
 * Contains the definition of `struct DayCounter` as well as the prototypes of its methods.
 *
 * @see DayCounter.c
 */

#include "LogEntry.h"
#include "DistinctCounter.h"
/**
 * Stores log information about a single day.
 *
 * You should always call `dcInit()` before and `dcFree()` after using a `DayCounter`.
 *
 * Methods of this struct start with "dc".
 *
 * @see dcInit()
 * @see dcFree()
 * @see dcAddLogEntry()
 * @see dcCountUsers()
 */
struct DayCounter
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
 * Initializes an empty day counter.
 *
 * @param this_ Points to the day counter that gets initialized.
 * @param date The date of the new counter.
 * @return 0 on success, non-zero on failure.
 */
int dcInit(struct DayCounter *this_);

/**
 * Frees all resources used by a given day counter.
 *
 * @param this_ Points to the day counter to be freed.
 */
void dcFree(struct DayCounter *this_);

/**
 * Adds some of the information stored in a LogEntry to a DayCounter.
 *
 * *NOTE:* This function does not check, if the date in `entry` matches with the date in `this_`.
 *
 * If either one of the two parameters is `NULL`, nothing happens.
 *
 * @param this_ Pointer to a DayCounter to add to.
 * @param entry Pointer to the LogEntry to get the information from.
 */
void dcAddLogEntry(struct DayCounter *this_, struct LogEntry *entry);

/**
 * Returns the number of unique users that were counted.
 *
 * @param this_ Points to the day counter that counted the users.
 * @return Number of unique users that were counted or `0`, if `this_` is `NULL`.
 */
size_t dcCountUsers(struct DayCounter *this_);

#endif //ATLAS_DAYINFO_H
