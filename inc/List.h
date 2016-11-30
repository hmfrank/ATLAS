#ifndef ATLAS_LIST_H
#define ATLAS_LIST_H

#include <stddef.h>

/**
 * @file List.h
 *
 * Contains the definition of `struct List`, as well as the prototypes of its methods.
 */

/**
 * A variable length list of void pointers. This list has variable-length, however it does not reallocate memory when
 * it's full. This means that you can not add more items, than the capacity specified in `lstCreate`.
 *
 * Methods of the struct start with "lst".
 *
 * @see lstCreate()
 * @see lstDestroy()
 * @see lstAdd()
 */
struct List
{
	/**
	 * The maximum number of items that memory is allocated for.
	 */
	size_t capacity;

	/**
	 * The actual number of items in the list.
	 */
	size_t length;

	/**
	 * Points to the first element of the list (which is stored right behind the atucal struct in memory).
	 */
	void *data[0];
};

/**
 * Allocates memory for a new list.
 *
 * @param capacity The maximum number of items that memory is allocated for.
 * @return A pointer to the new list or `NULL` on failure.
 */
struct List *lstCreate(size_t capacity);

/**
 * Frees the memory used by the given list.
 *
 * *NOTE:* This function only frees the list itself, but not the memory where the individual elements of the list point
 * to.
 *
 * @param _this Points to the list to be freed.
 */
void lstDestroy(struct List *_this);

/**
 * Adds an item to a list.
 *
 * @param _this Points to the list to add the item to.
 * @param item The item to add to the list
 * @return 0 on success, non-zero on failure.
 */
int lstAdd(struct List *_this, void *item);

#endif //ATLAS_LIST_H
