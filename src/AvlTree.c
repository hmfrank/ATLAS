/**
 * @file AvlTree.c
 *
 * Contains implementations of the functions defined in AvlTree.h, as well as some static helper functions.
 */

#include <stdlib.h>
#include "../inc/AvlTree.h"

// TODO: rebalancing!

/**
 * This function is used as comparrison function, is `avlInit()` is passed `NULL` for the argument `compare`.
 *
 * @return 0
 */
int dummyCompare(const void *a, const void *b)
{
	// if I wrote `return 0;` the compiler would complain, because of unused parameters.
	return a - a + b - b;
}

/**
 * Allocates and initializes a new `AvlNode` with a given value and all pointer set to `NULL`.
 *
 * @param value The value of the new node.
 * @return Pointer to the newly allocated node, or `NULL` on failure.
 */
static struct AvlNode *nodeCreate(void *value)
{
	struct AvlNode *node;

	node = malloc(sizeof(struct AvlNode));
	if (node == NULL)
		return NULL;

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->value = value;

	return node;
}

/**
 * Searches for an item in a tree. If the item was not found and `insert` is non-zero, then a new node is
 * allocated and inserted into the tree (no rebalancing!).
 *
 * @param tree Points to the tree to search in.
 * @param item The item to search/insert.
 * @param insert This parameter specifies what happens, if the item was not found. If `insert` is `0`, nothing happens.
 * If it's not 0, the item get inserted into the tree.
 * @return `NULL`, if `tree` is `NULL`, or if the item was not found or couldn't be inserted (e.g. due to a malloc error).<br/>
 * Otherwise a pointer to the found/inserted item is returned.
 */
static struct AvlNode *nodeSearch(struct AvlTree *tree, void *item, int insert)
{
	if (tree == NULL)
		return NULL;

	// special case of an empty tree
	if (tree->root == NULL)
	{
		if (insert)
			return tree->root = nodeCreate(item);
		else
			return NULL;
	}

	struct AvlNode *parent;
	struct AvlNode *current;
	int comp;

	current = tree->root;

	// find where the new node has to be inserted
	while (current != NULL)
	{
		parent = current;
		comp = tree->compare(item, current->value);

		if (comp < 0)
		{
			current = current->left;
		}
		else if (comp > 0)
		{
			current = current->right;
		}
		else
		{
			// node already exists
			return current;
		}
	}

	// insert the new node
	if (insert)
	{
		current = nodeCreate(item);

		if (current != NULL)
		{
			if (comp < 0)
				parent->left = current;
			else
				parent->right = current;

			current->parent = parent;
		}
	}

	return current;
}

/**
 * Frees the given node and it's child nodes recursively.
 *
 * @param node Points to the node to be freed.
 */
static void nodeFree(struct AvlNode *node)
{
	if (node == NULL)
		return;

	nodeFree(node->left);
	nodeFree(node->right);
	free(node);
}

void avlInit(struct AvlTree *this, int (*compare)(const void *, const void *))
{
	if (this == NULL)
		return;

	this->root = NULL;
	this->compare = compare == NULL ? &dummyCompare : compare;
}

void avlFree(struct AvlTree *this)
{
	if (this == NULL)
		return;

	nodeFree(this->root);
}

int avlContains(struct AvlTree *this, void *item)
{
	return nodeSearch(this, item, 0) != NULL;
}

int avlInsert(struct AvlTree *this, void *item)
{
	struct AvlNode *new_node;

	new_node = nodeSearch(this, item, 1);
	if (new_node == NULL)
		return 0;

	// TODO: rebalance tree
	return 1;
}