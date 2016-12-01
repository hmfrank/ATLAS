#ifndef ATLAS_AVLTREE_H
#define ATLAS_AVLTREE_H

/**
 * @file AvlTree.h
 *
 * Contains the struct definitions of `struct AvlNode` and `struct AvlTree`, as well as related function prototypes.
 */

#include <stddef.h>

/**
 * Represents a node in a balanced AVL tree. This struct is only there to be used by `struct AvlTree`. If you want to
 * do something with AVL trees, you should use `struct AvlTree`.
 *
 * @see AvlTree
 */
struct AvlNode
{
	/**
	 * The value of the current node.
	 */
	void *value;

	/**
	 * Points to the left child node.
	 */
	struct AvlNode *left;

	/**
	 * Points to the right child node.
	 */
	struct AvlNode *right;

	// char balance factor
};

/**
 * Represents an balanced AVL tree. An AVL tree is a data structure for storing ordered sets (at least in this
 * implementation every element occures at most once in the tree). Searching, inserting and deleting elements can be
 * done in logarithmic time (with respect to the number of elements stored in the tree).
 *
 * You should always call `avlReset()` before and after you use an AVL tree.
 *
 * Methods of this struct start with "avl".
 *
 * @see https://en.wikipedia.org/wiki/AVL_tree
 * @see avlReset()
 * @see avlContains()
 * @see avlDelete()
 * @see avlInsert()
 * @see avlIsEmpty()
 */
struct AvlTree
{
	/**
	 * Points to a comparrison function for the tree elements.
	 *
	 * @return 0, if both arguments are equal<br/>
	 * &lt; 1, if the first argument is less than the second one<br/>
	 * &gt; 1, if the first argument is greater than the second one
	 */
	int (*compare)(const void *, const void *);

	/**
	 * Points to the root node of the tree, or `NULL` if the tree is empty.
	 */
	struct AvlNode *root;
};

/**
 * Frees all memory used by the tree itself (not the actual data) and initializes an empty tree.
 * If `_this` is `NULL`, nothing happens.
 *
 * You should always call `avlReset()` before and after you use an AVL tree.
 *
 * @param _this Points to the tree that gets resetted.
 * @param compare The comparrison function for the tree. It `compare` is `NULL` the comparrison function of the tree
 * gets initialized to a dummy function, that always returns 0.
 *
 * @see AvlTree::compare
 */
void avlReset(struct AvlTree *_this, int (*compare)(const void *, const void *));

/**
 * Checks if a tree contains a specific item.
 *
 * If you want to check if an item is in the tree before inserting it, then it's faster to call `avlInsert()` right
 * away, an check the return value.
 *
 * @param _this Points to the tree to inspect.
 * @param item The item that is searched in the tree.
 * @return 0 if `item` was not found in the tree<br/>
 * 1, if `item` was found in the tree
 */
int avlContains(struct AvlTree *_this, void *item);

/**
 *	Deletes an item from an AVL tree and rebalances the tree.
 *
 * @param _this Points to the tree to remove the item from.
 * @param item The item to remove.
 * @return 1, if the item was successfully removed<br/>
 * 0, if the item was not removed, because it was not in the tree, in the first place
 */
int avlDelete(struct AvlTree *_this, void *item);

/**
 * Inserts an item into an AVL tree and rebalances the tree. If the item is already in the tree, nothing happens.
 *
 * @param _this Points to the tree to insert the item in.
 * @param key The item to insert.
 * @return 1, if the item was successfully added<br/>
 * 0 is the item was not added or `_this` is `NULL`.
 */
int avlInsert(struct AvlTree *_this, void *item);

/**
 * Checks if the given tree contains any elements, at all.
 *
 * @param _this Points to the tree to inspect.
 * @return non-zero, if `_this` is an empty tree or if `_this` is `NULL`<br/>
 * 0, otherwise
 */
inline int avlIsEmpty(struct AvlTree *_this)
{
	return _this == NULL ? 1 : (_this->root == NULL);
}

#endif //ATLAS_AVLTREE_H
