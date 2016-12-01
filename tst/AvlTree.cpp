#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/AvlTree.h"
}

int compare(const void *a, const void *b)
{
	return (int)a - (int)b;
}

TEST_CASE("avl tree contains, delete, insert, is empty", "[inc/AvlTree.h/avlContains, inc/AvlTree.h/avlDelete, inc/AvlTree.h/avlInsert, inc/AvlTree.h/avlIsEmpty]")
{
	struct AvlTree tree;

	REQUIRE_NOTHROW(avlReset(NULL, NULL));
	REQUIRE_FALSE(avlContains(NULL, (void*)1));
	REQUIRE_FALSE(avlDelete(NULL, (void*)1));
	REQUIRE_FALSE(avlInsert(NULL, (void*)1));
	REQUIRE(avlIsEmpty(NULL));

	avlReset(&tree, &compare);
	REQUIRE(avlIsEmpty(&tree));

	for (int i = 0; i < 10; i++)
		REQUIRE(avlInsert(&tree, (void*)i));

	for (int i = 0; i < 10; i++)
		REQUIRE(avlContains(&tree, (void*)i));

	REQUIRE_FALSE(avlIsEmpty(&tree));
	REQUIRE_FALSE(avlInsert(&tree, (void*)2));
	REQUIRE_FALSE(avlContains(&tree, (void*)-1));
	REQUIRE_FALSE(avlDelete(&tree, (void*)-2));

	for (int i = 0; i < 10; i++)
		REQUIRE(avlDelete(&tree, (void*)i));

	REQUIRE(avlIsEmpty(&tree));

	for (int i = 0; i > -10; i--)
		avlInsert(&tree, (void*)i);

	avlReset(&tree, NULL);
	REQUIRE(avlIsEmpty(&tree));
}