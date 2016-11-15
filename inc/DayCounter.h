#ifndef ATLAS_DAYINFO_H
#define ATLAS_DAYINFO_H

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

#endif //ATLAS_DAYINFO_H
