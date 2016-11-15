#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/Date.h"

/**
 * @file Date.c
 *
 * Contains implementations of the functions defined in Date.h.
 */

int dtToString(struct Date *this, char *buffer)
{
	if (this == NULL)
		return 0;
	if (buffer == NULL)
		return 0;

	return sprintf(buffer, "%04d/%02d/%02d", this->year, this->month, this->day);
}

char *dtToNewString(struct Date *this)
{
	// at most 5 chars for each number + 2 slashes + terminator
	char buffer[18];
	char *str;
	int length;

	length = dtToString(this, buffer);

	if (length < 0)
		return NULL;

	str = malloc((size_t)length + 1);

	if (str == NULL)
		return NULL;

	strcpy(str, buffer);
	return str;
}