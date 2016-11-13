#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../inc/macros.h"
#include "../inc/parse.h"

/**
 * @file parse.c
 *
 * Contains implementations of the functions defined in parse.h plus some static helper functions.
 */

/**
 * The size of the line buffer used in `parseLogEntry()`.
 */
#define PARSER_LINEBUFFER_SIZE 1024

/**
 * Converts a string to a HTTP method constant.
 * The constants defined in Logresult->h are used.
 *
 * @see Logresult->h
 *
 * @param str A string that represents a HTTP method. If `str` is `NULL`, `HTTP_UNKNOWN` is returned.
 * @return the constant for the  HTTP method, `str` represents.
 */
static unsigned short toHttpMethod(const char *str)
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

static unsigned char toMonth(char *str)
{
	if (str == NULL)
		return 0;

	for (int i = 0; i < 3; i++)
		str[i] = (char)tolower(str[i]);

	if (!strcmp(str, "jan")) return 1;
	else if (!strcmp(str, "feb")) return 2;
	else if (!strcmp(str, "mar")) return 3;
	else if (!strcmp(str, "apr")) return 4;
	else if (!strcmp(str, "may")) return 5;
	else if (!strcmp(str, "jun")) return 6;
	else if (!strcmp(str, "jul")) return 7;
	else if (!strcmp(str, "aug")) return 8;
	else if (!strcmp(str, "sep")) return 9;
	else if (!strcmp(str, "oct")) return 10;
	else if (!strcmp(str, "nov")) return 11;
	else if (!strcmp(str, "dec")) return 12;
	else return 0;
}

// TODO: die datums-zahlen nicht groesser als y=9999, m=99, d=99 zulassen, oder vlt sogar m=12, d=31
// TODO: nochma durchdenken, was passiert, wenn der string kuerzer is, als gedacht
int parseLogEntry(FILE *stream, struct LogEntry *result)
{
	if (stream == NULL)
		return -1;
	if (result == NULL)
		return -1;

	// line buffer
	char buffer[PARSER_LINEBUFFER_SIZE];
	// pointer to the current position in buffer
	char *cur = buffer;
	char *end;
	// general purpose variables
	long long int l;
	size_t n;
	// to temporarily hold the strings
	char *remote_address;
	char *username;
	char *requested_file;
	char *referer;
	size_t n_remote_address;
	size_t n_username;
	size_t n_requested_file;
	size_t n_referer;

	// read line into buffer
	if (fgets(buffer, PARSER_LINEBUFFER_SIZE, stream) == NULL)
		return 1;
	if (strchr(buffer, '\n') == NULL && strlen(buffer) >= PARSER_LINEBUFFER_SIZE - 1)
		return 1;

	if (*(cur++) != '[')
		return 1;

	// read day
	l = strtoll(cur, &cur, 10);
	if (l < 0 || l > (long long int)UCHAR_MAX)
		return 1;
	result->date.day = (unsigned char)l;

	if (*(cur++) != '/')
		return 1;

	// read month
	end = strchr(cur, '/');
	if (end == NULL)
		return 1;
	*end = '\0';
	result->date.month = toMonth(cur);
	cur = end + 1;

	// read year
	l = strtoll(cur, &cur, 10);
	if (l < 0 || l > (long long int)USHRT_MAX)
		return 1;
	result->date.year = (unsigned short)l;

	while (*(cur++) != ']')
	{ }

	if (*(cur++) != '#')
		return 1;

	// read remote address
	end = strchr(cur, '#');
	if (end == NULL)
		return 1;
	*end = '\0';
	remote_address = cur;
	n_remote_address = end - cur;
	cur = end + 1;

	// read username
	end = strchr(cur, '#');
	if (end == NULL)
		return 1;
	*end = '\0';
	username = cur;
	n_username = end - cur;
	cur = end + 1;

	// read http status
	l = strtoll(cur, &cur, 10);
	if (l < 0 || l > (long long int)USHRT_MAX)
		return 1;
	result->http_status = (unsigned short)l;

	if (*(cur++) != '#')
		return 1;

	// read request size
	l = strtoll(cur, &cur, 10);
	if (l < 0 || l > (long long int)UINT_MAX)
		return 1;
	result->request_size = (unsigned int)l;

	if (*(cur++) != '#')
		return 1;

	// read response size
	l = strtoll(cur, &cur, 10);
	if (l < 0 || l > (long long int)UINT_MAX)
		return 1;
	result->response_size = (unsigned int)l;

	if (*(cur++) != '#')
		return 1;

	// read requested file
	end = strchr(cur, '#');
	if (end == NULL)
		return 1;
	*end = '\0';
	requested_file = cur;
	n_requested_file = end - cur;
	cur = end + 1;

	// read referer
	end = strchr(cur, '#');
	if (end == NULL)
		return 1;
	*end = '\0';
	referer = cur;
	n_referer = end - cur;
	cur = end + 1;

	n = strlen(cur);
	if (cur[n - 1] == '\n')
		cur[n - 1] = '\0';

	// read HTTP method
	result->http_method = toHttpMethod(cur);

	// alloc memory for the strings
	result->remote_address = malloc(n_remote_address + 1);
	result->username = malloc(n_username + 1);
	result->requested_file = malloc(n_requested_file + 1);
	result->referer = malloc(n_referer + 1);

	// free memory if at least one malloc failed
	if (result->remote_address == NULL || result->username == NULL || result->requested_file == NULL || result->referer == NULL)
	{
		if (result->remote_address != NULL) free(result->remote_address);
		if (result->username != NULL) free(result->username);
		if (result->requested_file != NULL) free(result->requested_file);
		if (result->referer != NULL) free(result->referer);

		return 2;
	}

	// copy strings into heap
	memcpy(result->remote_address, remote_address, n_remote_address + 1);
	memcpy(result->username, username, n_username + 1);
	memcpy(result->requested_file, requested_file, n_requested_file + 1);
	memcpy(result->referer, referer, n_referer + 1);

	return 0;
}
