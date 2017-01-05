#include <stdlib.h>
#include <string.h>
#include "../inc/DistinctCounter.h"

/**
 * @file DistinctCounter.c
 *
 * Contains implementations of the functions defined in DistinctCounter.h, as well as some static helper functions.
 */

int strCompare(const void *a, const void *b)
{
	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	return strcmp((const char *)a, (const char *)b);
}

/**
 * @param this must not be `NULL`
 * @return 0 on success, non-zero on failure
 */
static int dstInitAvlTree(struct DistinctCounter *this, int (*compare)(const void *, const void *))
{
	this->counter.avl_tree = malloc(sizeof(struct AvlTree));
	if (this->counter.avl_tree == NULL)
		return 1;

	avlInit(this->counter.avl_tree, compare);

	this->type = AVL_TREE;
	this->to_free = NULL;

	return 0;
}

/**
 * @param this must not be `NULL`
 */
static inline void dstFreeAvlTree(struct DistinctCounter *this)
{
	avlFree(this->counter.avl_tree);
	free(this->counter.avl_tree);
	tflReset(&this->to_free);
}

/**
 * @param this must not be `NULL`
 */
static inline void dstAddAvlTree(struct DistinctCounter *this, char *item)
{
	// copy string
	char *copy = malloc(( strlen(item) + 1) * sizeof(*copy));
	if (copy == NULL)
		return;

	strcpy(copy, item);
	tflAdd(&this->to_free, copy);

	avlInsert(this->counter.avl_tree, copy);
}

/**
 * @param this must not be `NULL`
 */
static inline size_t dstCountAvlTree(struct DistinctCounter *this)
{
	return this->counter.avl_tree->count;
}

int dstInit(struct DistinctCounter *this, int type, union DstInitInfo *init_info)
{
	if (this == NULL)
		return 1;
	if (init_info == NULL)
		return 1;

	switch (type)
	{
		case AVL_TREE:
			return dstInitAvlTree(this, &strCompare);
		default:
			return 1;
	}
}

void dstFree(struct DistinctCounter *this)
{
	if (this == NULL)
		return;

	switch (this->type)
	{
		case AVL_TREE:
			dstFreeAvlTree(this);
			break;
	}
}

void dstAdd(struct DistinctCounter *this, char *item)
{
	if (this == NULL)
		return;

	switch (this->type)
	{
		case AVL_TREE:
			dstAddAvlTree(this, item);
			break;
	}
}

size_t dstCount(struct DistinctCounter *this)
{
	if (this == NULL)
		return 0;

	switch (this->type)
	{
		case AVL_TREE:
			return dstCountAvlTree(this);
		default:
			return 0;
	}
}