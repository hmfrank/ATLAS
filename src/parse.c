/**
 * @file parse.c
 *
 * Contains implementations of the functions defined in parse.h plus some helper functions.
 *
 * @see parse.h
 */

#include <limits.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../inc/parse.h"

/**
 * The size of the line buffer used in `parseLogEntry()`.
 */
#define PARSER_LINEBUFFER_SIZE 1024

/**
 * Converts a string to a HTTP method constant.
 * The constants defined in LogEntry.h are used.
 *
 * @see LogEntry.h
 *
 * @param str A string that represents a HTTP method. If `str` is `NULL`, `HTTP_UNKNOWN` is returned.
 * @return the constant for the  HTTP method, `str` represents.
 */
unsigned short toHttpMethod(const char *str)
{
	if (str == NULL) return HTTP_UNKNOWN;
	else if (!strcasecmp(str, "CONNECT")) return HTTP_CONNECT;
	else if (!strcasecmp(str, "DELETE")) return HTTP_DELETE;
	else if (!strcasecmp(str, "GET")) return HTTP_GET;
	else if (!strcasecmp(str, "HEAD")) return HTTP_HEAD;
	else if (!strcasecmp(str, "OPTIONS")) return HTTP_OPTIONS;
	else if (!strcasecmp(str, "POST")) return HTTP_POST;
	else if (!strcasecmp(str, "PUT")) return HTTP_PUT;
	else if (!strcasecmp(str, "TRACE")) return HTTP_TRACE;
	else return HTTP_UNKNOWN;
}

/**
 * Converts a string to a month number.
 *
 * @param str the first 3 characters of the month name (not case sensitive)
 * @return the month number (1 - 12) or 0 on failure.
 */
unsigned char toMonth(const char *str)
{
	if (str == NULL)
		return 0;

	if (!strcasecmp(str, "jan")) return 1;
	else if (!strcasecmp(str, "feb")) return 2;
	else if (!strcasecmp(str, "mar")) return 3;
	else if (!strcasecmp(str, "apr")) return 4;
	else if (!strcasecmp(str, "may")) return 5;
	else if (!strcasecmp(str, "jun")) return 6;
	else if (!strcasecmp(str, "jul")) return 7;
	else if (!strcasecmp(str, "aug")) return 8;
	else if (!strcasecmp(str, "sep")) return 9;
	else if (!strcasecmp(str, "oct")) return 10;
	else if (!strcasecmp(str, "nov")) return 11;
	else if (!strcasecmp(str, "dec")) return 12;
	else return 0;
}

// TODO: remove duplicates
int parseLogEntry(FILE *stream, struct LogEntry *result)
{
	if (stream == NULL)
		return -1;
	if (result == NULL)
		return -1;

	char buffer[PARSER_LINEBUFFER_SIZE];
	char *ptr;
	long long int l;

	char *remote_address;
	char *requested_file;
	char *referer;

	// read line into buffer
	if (fgets(buffer, PARSER_LINEBUFFER_SIZE, stream) == NULL)
		return 1;

	// check if buffer was long enough
	ptr = strchr(buffer, '\n');
	if (ptr == NULL && strlen(buffer) >= PARSER_LINEBUFFER_SIZE - 1)
		return 1;
	else if (ptr != NULL)
		*ptr = '\0';

	// parse remote address
	remote_address = strtok(buffer, " ");
	if (remote_address == NULL)
		return 1;

	// parse HTTP-Auth user
	if (strtok(NULL, " ") == NULL)
		return 1;

	// parse day
	ptr = strtok(NULL, "/");
	if (ptr == NULL)
		return 1;
	if (*(ptr++) != '[')
		return 1;

	l = strtoll(ptr, &ptr, 10);
	if (*ptr != '\0')
		return 1;
	if (l < 1 || l > 31)
		return 1;

	result->date.day = (unsigned char)l;

	// parse month
	ptr = strtok(NULL, "/");
	if (ptr == NULL)
		return 1;

	result->date.month = toMonth(ptr);
	if (result->date.month == 0)
		return 1;

	// parse year
	ptr = strtok(NULL, ":");
	if (ptr == NULL)
		return 1;

	l = strtoll(ptr, &ptr, 10);
	if (*ptr != '\0')
		return 1;
	if (l < 0 || l > 9999)
		return 1;
	result->date.year = (unsigned short)l;

	// ignore time
	if (strtok(NULL, "]") == NULL)
		return 1;

	// parse HTTP method
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;

	result->http_method = toHttpMethod(ptr);

	// parse HTTP status
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;

	l = strtoll(ptr, &ptr, 10);
	if (*ptr != '\0')
		return 1;
	if (l < 0 || l > 9999)
		return 1;
	result->http_status = (unsigned short)l;

	// parse request size
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;

	l = strtoll(ptr, &ptr, 10);
	if (*ptr != '\0')
		return 1;
	if (l < 0 || l > UINT_MAX)
		return 1;
	result->request_size = (unsigned int)l;

	// parse response size
	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;

	l = strtoll(ptr, &ptr, 10);
	if (*ptr != '\0')
		return 1;
	if (l < 0 || l > UINT_MAX)
		return 1;
	result->response_size = (unsigned int)l;

	// parse requested file
	requested_file = strtok(NULL, "\"");
	if (requested_file == NULL)
		return 1;

	// parse referer
	if (strtok(NULL, "\"") == NULL)
		return 1;

	referer = strtok(NULL, "\"");
	if (referer == NULL)
		return 1;

	// allocate memory for the strings
	result->remote_address = malloc(strlen(remote_address) + 1);
	result->requested_file = malloc(strlen(requested_file) + 1);
	result->referer = malloc(strlen(referer) + 1);

	if (result->remote_address == NULL || result->requested_file == NULL || result->referer == NULL)
	{
		if (result->remote_address != NULL)
			free(result->remote_address);
		if (result->requested_file != NULL)
			free(result->requested_file);
		if (result->referer != NULL)
			free(result->referer);

		return 2;
	}

	strcpy(result->remote_address, remote_address);
	strcpy(result->requested_file, requested_file);
	strcpy(result->referer, referer);

	return 0;
}
