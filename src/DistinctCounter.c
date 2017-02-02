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

void hash(const void *item, size_t h, void *buffer)
{
	if (item == NULL)
	{
		for (size_t i = 0; i < h; i++)
			((char*)buffer)[i] = 0;

		return;
	}

	const unsigned char *string = item;
	unsigned int seed = 5381;
	unsigned char c;

	while ((c = *(string++)) != '\0')
		seed = seed * 33 + c;

	srand(seed);

	for (size_t i = 0; i < h; i++)
	{
		((char*)buffer)[i] = (char)rand();
	}
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
 * @param r SMALL|MEDIUM|LARGE
 * @param b 4 < b < sizeof(size_t) * CHAR_BIT
 * @return 0 on success, non-zero on failure
 */
static int dstInitHyperLogLog(struct DistinctCounter *this, unsigned char r, unsigned char b, void (*hash)(const void*, size_t, void*))
{
	this->counter.hyperloglog = malloc(sizeof(struct HyperLogLog));
	if (this->counter.hyperloglog == NULL)
		return 1;

	hllInit(this->counter.hyperloglog, r, b, hash);

	this->type = HYPERLOGLOG;
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
static inline void dstFreeHyperLogLog(struct DistinctCounter *this)
{
	hllFree(this->counter.hyperloglog);
	free(this->counter.hyperloglog);
}

/**
 * @param this must not be `NULL`
 * @param item must not be `NULL`
 */
static inline void dstAddAvlTree(struct DistinctCounter *this, const char *item)
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
 * @param item must not be `NULL`
 */
static inline void dstAddHyperLogLog(struct DistinctCounter *this, const char *item)
{
	hllAdd(this->counter.hyperloglog, (const void *)item);
}

/**
 * @param this must not be `NULL`
 */
static inline size_t dstCountAvlTree(struct DistinctCounter *this)
{
	return this->counter.avl_tree->count;
}

static inline size_t dstCountHyperLogLog(struct DistinctCounter *this)
{
	return (size_t)(this->counter.hyperloglog);
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
		case HYPERLOGLOG:
			return dstInitHyperLogLog(this, SMALL, 12, &hash);
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
		case HYPERLOGLOG:
			dstFreeHyperLogLog(this);
			break;
	}
}

void dstAdd(struct DistinctCounter *this, const char *item)
{
	if (this == NULL)
		return;
	if (item == NULL)
		return;

	switch (this->type)
	{
		case AVL_TREE:
			dstAddAvlTree(this, item);
			break;
		case HYPERLOGLOG:
			dstAddHyperLogLog(this, item);
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
		case HYPERLOGLOG:
			return dstCountHyperLogLog(this);
		default:
			return 0;
	}
}