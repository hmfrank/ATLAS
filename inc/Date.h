#ifndef ATLAS_DATE_H
#define ATLAS_DATE_H

#include <stddef.h>

/**
 * @file Date.h
 *
 * Contains the definition of `struct Date`, as well as prototypes of its methods.
 *
 * @see Date.c
 */

/**
 * Represents a date.
 * Only day, month, year, no time.
 *
 * Methods of this struct start with "dt".
 *
 * @see dtCompare()
 * @see dtToNewString()
 * @see dtToString()
 */
struct Date
{
	// the member variable have to be in this order in order for `dtCompare()` to work properly.
	unsigned short year;
	unsigned char month;
	unsigned char day;
};

/**
 * Compares two dates.
 *
 * @return 0 if both dates are equal or both dates are `NULL`.<br/>
 * &lt; 0 if `_this` is before `_that` or if only `_this` is `NULL`.<br/>
 * &gt; 0 if `_this` is after `_that` or if only `_that` is `NULL`.
 */
int dtCompare(struct Date *_this, struct Date *that);

/**
 * Same as dtToString but allocates a new string.
 *
 * @param _this The date that gets converted to a string.
 * @return Pointer to the newly allocated string, or `NULL` on failure.
 */
char *dtToNewString(struct Date *_this);

/**
 * Converts a Date to string.
 * The output format is: YYYY/MM/DD. So the resulting string should be 10 bytes long (not counting the null-terminator),
 * unless the year is greater than 9999 or day or month are greater than 99.
 *
 * @param _this The date that gets converted to a string.
 * @param buffer Points to the memory where the string is stored.
 * @return The length of the string (not counting the null-terminator), or a negative number on failure.
 */
int dtToString(struct Date *_this, char *buffer);

#endif //ATLAS_DATE_H
