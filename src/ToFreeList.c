#include <stdlib.h>
#include "../inc/ToFreeList.h"

/**
 * @file ToFreeList.c
 *
 * Contains implementations of the function defined in ToFreeList.h.
 */

int tflAdd(struct ToFreeList **this, void *allocated)
{
	if (this == NULL)
		return 1;
	if (allocated == NULL)
		return 1;

	struct ToFreeList *new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return 1;

	new->prev = *this;
	new->ptr = allocated;
	*this = new;

	return 0;
}

void tflReset(struct ToFreeList **this)
{
	if (this == NULL)
		return;

	struct ToFreeList *cur = *this;
	struct ToFreeList *prev;

	while (cur != NULL)
	{
		prev = cur->prev;

		free(cur->ptr);
		free(cur);

		cur = prev;
	}

	*this = NULL;
}