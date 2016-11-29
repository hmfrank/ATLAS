#ifndef ATLAS_DAYINFO_H
#define ATLAS_DAYINFO_H

#include "Date.h"
#include "LogEntry.h"

/**
 * @file DayCounter.h
 *
 * Contains the definition of `struct DayCounter` as well as the prototypes of its methods.
 *
 * @see DayCounter.c
 */

// TODO: keep track of which user was already added (bloom filter!)
/**
 * Stores log information about a single day.
 *
 * Methods of this struct start with "dc".
 *
 * @see dcAddLogEntry()
 */
struct DayCounter
{
	/**
	 * The date this struct sotores information about.
	 */
	struct Date date;

	/**
	 * Number of requests.
	 */
	unsigned int n_requests;

	/**
	 * Number of users.
	 */
	unsigned int n_users;

	/**
	 * Number of bytes received.
	 */
	unsigned long long int n_bytes_in;

	/**
	 * Number of bytes sent.
	 */
	unsigned long long int n_bytes_out;
};

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

#endif //ATLAS_DAYINFO_H
