#ifndef ATLAS_DAYINFO_H
#define ATLAS_DAYINFO_H

#include "LogEntry.h"

/**
 * @file DayCounter.h
 *
 * Contains the definition of `struct DayCounter`.
 */

// TODO: keep track of which user was already added (bloom filter!)
/**
 * Stores log information about a single day.
 */
struct DayCounter
{
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
 * If either one of the two parameters is `NULL`, nothing happens.
 *
 * @param this_ Pointer to a DayCounter to add to.
 * @param entry Pointer to the LogEntry to get the information from.
 */
void dcAddLogEntry(struct DayCounter *this_, struct LogEntry *entry);

#endif //ATLAS_DAYINFO_H
