#ifndef ATLAS_DATE_H
#define ATLAS_DATE_H

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

#endif //ATLAS_DATE_H
