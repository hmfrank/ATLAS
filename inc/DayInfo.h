#ifndef ATLAS_DAYINFO_H
#define ATLAS_DAYINFO_H

/**
 * Stores log information about a single day.
 */
struct DayInfo
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