/**
 * @file AvlTree.c
 *
 * Contains implementations of the functions defined in AvlTree.h.
 */

#include <stdlib.h>
#include "../inc/AvlTree.h"

// TODO: implement avlContains()
// TODO: implement avlDelete()
// TODO: implement avlInsert()

static int dummyCompare(const void *a, const void *b)
{
	// if I wrote `return 0;` the compiler would complain, because of unused parameters.
	return a - a + b - b;
}

/**
 * Frees the given node and child it's child nodes recursively.
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

void avlReset(struct AvlTree *this, int (*compare)(const void *, const void *))
{
	if (this == NULL)
		return;

	nodeFree(this->root);
	this->root = NULL;
	this->compare = compare == NULL ? &dummyCompare : compare;
}

int avlContains(struct AvlTree *this, void *item)
{
	if (this == NULL)
		return 0;

	struct AvlNode *current;
	int comp;

	current = this->root;

	while (current != NULL)
	{
		comp = this->compare(item, current->value);

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
			return 1;
		}
	}

	return 0;
}