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