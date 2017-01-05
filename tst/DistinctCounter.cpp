#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/DistinctCounter.h"
}

TEST_CASE("distinct counter avl tree", "[src/DistinctCounter.c]")
{
	struct DistinctCounter dc;
	union DstInitInfo info;

	REQUIRE(dstInit(NULL, AVL_TREE, NULL));
	REQUIRE(dstInit(NULL, AVL_TREE, &info));
	REQUIRE(dstInit(&dc, AVL_TREE, NULL));

	REQUIRE_FALSE(dstInit(&dc, AVL_TREE, &info));
	REQUIRE(dstCount(&dc) == 0);

	dstAdd(&dc, "a");
	REQUIRE(dstCount(&dc) == 1);

	dstAdd(&dc, "a");
	REQUIRE(dstCount(&dc) == 1);

	for (int i = 0; i < 1000; i++)
	{
		char str[4];
		sprintf(str, "%d", i);
		dstAdd(&dc, str);
	}

	REQUIRE(dstCount(&dc) == 1001);

	dstFree(&dc);
}