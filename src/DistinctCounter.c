#include <stdlib.h>
#include "../inc/DistinctCounter.h"

/**
 * @file DistinctCounter.c
 *
 * Contains implementations of the functions defined in DistinctCounter.h, as well as some static helper functions.
 */

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

	return 0;
}

/**
 * @param this must not be `NULL`
 */
static inline void dstFreeAvlTree(struct DistinctCounter *this)
{
	avlFree(this->counter.avl_tree);
}

/**
 * @param this must not be `NULL`
 */
static inline void dstAddAvlTree(struct DistinctCounter *this, void *item)
{
	avlInsert(this->counter.avl_tree, item);
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
			return dstInitAvlTree(this, init_info->avl_tree.compare);
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

void dstAdd(struct DistinctCounter *this, void *item)
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