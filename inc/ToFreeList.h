#ifndef ATLAS_TOFREELIST_H
#define ATLAS_TOFREELIST_H

/**
 * @file ToFreeList.h
 *
 * Contains the definition of `struct ToFreeList`, as well as some related function prototypes.
 */

/**
 * A dynamic list of `void*`, that you can use to store pointers you want to free later.
 *
 * Since this structure is implemented as a reversed linked list, you always have to use a pointer to the struct. That
 * is a pointer to the last element of the list (a null pointer represents an empty list).
 *
 * Methods of this struct start with "tfl".
 *
 * @see tflAdd()
 * @see tflReset()
 */
struct ToFreeList
{
	void *ptr;
	struct ToFreeList *prev;
};

/**
 * Adds an item (void pointer) to the list. Null pointers are not added. Also, the added pointer has to be retrieved
 * from a `malloc()`, `calloc()`, or `realloc()` call, since it get passed to `free()`, when you call `tflFree()`.
 *
 * Since this function has to change your pointer to the last element, you have to pass a reference to that pointer.
 *
 * @param this_ Reference to the pointer to the last element.
 * @param allocated The item that gets added to the list.
 * @return 0 on success, non-zero on failure.
 */
int tflAdd(struct ToFreeList **this_, void *allocated);

/**
 * Frees all elements in the list, as well as the memory used by the list itself, and creates a new empty list (null
 * pointer).
 *
 * @param this_ Refernece to the pointer to the last element.
 */
void tflReset(struct ToFreeList **this_);

#endif //ATLAS_TOFREELIST_H
