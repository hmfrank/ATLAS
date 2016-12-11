#ifndef ATLAS_DISTINCTCOUNTER_H
#define ATLAS_DISTINCTCOUNTER_H

// TODO: write unit test

/**
 * @file DistinctCounter.h
 *
 * Contains the structure definition of `DistinctCounter`, as well as some related function prototypes.
 */

#include "../lib/AvlTree.h"

/**
 * List of all data structures, `struct DistinctCounter` can use.
 *
 * @see DistinctCounter
 */
enum DistinctCounterType
{
	AVL_TREE
};

/**
 * Counts the number of distinct items in a set. You can add items to the set and count them later. If a specific item
 * is added multiple times, it's only counted once. There are many data structures that can be used to accomplish this
 * behaviour, each with its own advantages and disadvantages. To fit your needs best, you can choose which data
 * data structure is used, when initializing a `DistinctCounter`.
 *
 * You should always call `dstInit()` before and `dstFree()` after you using a distinct counter.
 *
 * Methods of this struct start with "dst".
 *
 * @see dstInit()
 * @see dstFree()
 * @see dstAdd()
 * @see dstCount()
 *
 * ### Data Structures
 * #### AVL Tree [_wikipedia_](https://en.wikipedia.org/wiki/AVL_tree)
 * * space: O(n)
 * * insertion: O(log(n))
 * * counting: O(1)
 * * needs a comparison function
 * * infinitely extendible
 * * the count is _exact_
 *
 * Great, if you want the _exact_ number of items in the set.
 *
 * #### HyperLogLog [_wikipedia_](https://en.wikipedia.org/wiki/HyperLogLog)
 * * space: O(log(log(n))
 * * insertion: O(1)
 * * counting: O(1)
 * * needs a hash function
 * * technically has a maximum number of items, but this can be extremely huge
 * * the count is only an estimate (but can be very accurate)
 * * not implemented, yet
 *
 * Great for very huge sets.
 */
struct DistinctCounter
{
	/**
	 * The type of data structure that is used in this counter.
	 */
	int type;

	/**
	 * The actual data structure.
	 */
	union
	{
		struct AvlTree *avl_tree;
	} counter;
};

/**
 * Contains information for initializing a specific data structure used by `DistinctCounter`.
 * This structure is only used by `dstInit()` to pass init arguments.
 */
union DstInitInfo
{
	/**
	 * Init arguments for an AVL Tree.
	 */
	struct
	{
		/**
		 * @see avlInit()
		 * @see AvlTree::compare
		 */
		int (*compare)(const void *, const void *);
	} avl_tree;
};

/**
 * Initializes a `DistinctCounter`. That includes initializing and allocating everything for the internal data
 * structure, so that the counter is ready to use.
 *
 * This should be the first method you call, before doing anything else with a `DistinctCounter`.
 *
 * @param _this Points to the counter to initialize.
 * @param type Specifies the data structure that is used.
 * @param init_info Parameters needed to initialize the specific data structure.
 * @return 0 on success, non-zero on failure.
 */
int dstInit(struct DistinctCounter *_this, int type, union DstInitInfo *init_info);

/**
 * Frees all the resources used by a given `DistinctCounter`.
 *
 * To prevent memory leaks, you should always call `dstFree()`, when you don't need the counter anymore.
 *
 * @param _this Points to the counter that gets freed (this pointer itself is not freed).
 */
void dstFree(struct DistinctCounter *_this);

/**
 * Adds the given item to the counter.
 *
 * @param _this Points to the counter to add the item to.
 * @param item The item to add.
 */
void dstAdd(struct DistinctCounter *_this, void *item);

/**
 * Returns the number of distinct items in the set.
 *
 * NOTE: Depending on the data structure that is used, the returned value might not be 100% accurate.
 *
 * @param _this Points to the counter of the items.
 * @return The number of distinct items that were added to `_this`.
 */
size_t dstCount(struct DistinctCounter *_this);

#endif //ATLAS_DISTINCTCOUNTER_H
