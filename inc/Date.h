#ifndef ATLAS_DATE_H
#define ATLAS_DATE_H

#include <stddef.h>

/**
 * @file Date.h
 *
 * Contains the definition of `struct Date`.
 *
 * @see struct Date
 */

/**
 * Represents a date.
 * Only day, month, year, no time.
 */
struct Date
{
	unsigned char day;
	unsigned char month;
	unsigned short year;
};

/**
 * Converts a Date to string.
 * The output format is: YYYY/MM/DD. So the resulting string should be 10 bytes long (not counting the null-terminator),
 * unless the year is greater than 9999 or day or month are greater than 99.
 *
 * @param _this The date that gets converted to a string.
 * @param buffer Points to the area where the string is stored.
 * @return The length of the string (not counting the null-terminator), or a negative number on failure.
 */
int dtToString(struct Date *_this, char *buffer);

#endif //ATLAS_DATE_H
