#ifndef ATLAS_LOGENTRY_H
#define ATLAS_LOGENTRY_H

/**
 * @file LogEntry.h
 *
 * Contains the definition of `struct LogEntry`, as well as prototypes of its methods.
 *
 * @see LogEntry.c
 */

#include "Date.h"

/**
 * Contains all HTTP request methods.
 */
enum HttpMethod
{
	HTTP_UNKNOWN = 0,
	HTTP_CONNECT,
	HTTP_DELETE,
	HTTP_GET,
	HTTP_HEAD,
	HTTP_OPTIONS,
	HTTP_POST,
	HTTP_PUT,
	HTTP_TRACE
};

/**
 * Represents a single entry in the server log.
 * Such an entry is usually the result of a client request and server response and is stored in a single line in the log
 * file.
 *
 * Methods of this struct start with "lge".
 *
 * @see lgeFreeStrings()
 */
struct LogEntry
{
	/**
	 * The date the request was made.
	 */
	struct Date date;

	/**
	 * The HTTP method used in the client request.
	 */
	unsigned short http_method;

	/**
	 * The HTTP status code of the server response.
	 */
	unsigned short http_status;

	/**
	 * The size of the client request in bytes.
	 */
	unsigned int request_size;

	/**
	 * The size of the server response in bytes.
	 */
	unsigned int response_size;


	/**
	 * The address of the client.
	 * This can be an IP address (as string) or a hostname.
	 */
	char *remote_address;

	/**
	 * The URL path of the requested file.
	 * Contains no URL parameters.
	 */
	char *requested_file;

	/**
	 * The site the client comes from.
	 * Most browser send this information with the request, by default. If no referer was sent with the request, this
	 * field can point to some dummy strin like `"-"` or `""`.
	 */
	char *referer;
};

/**
 * Frees all the strings in a LogEntry.
 *
 * @param _this Pointer to the LogEntry which strings get freed.
 */
void lgeFreeStrings(struct LogEntry *_this);

#endif //ATLAS_LOGENTRY_H
