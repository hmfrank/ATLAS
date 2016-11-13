#include <stdio.h>
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