#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/ToFreeList.h"
}

TEST_CASE("to-free list", "[src/ToFreeList.c]")
{
	struct ToFreeList *list = NULL;

	REQUIRE(tflAdd(NULL, NULL));
	REQUIRE(tflAdd(NULL, list));
	REQUIRE(tflAdd(&list, NULL));

	void *ptr = malloc(42);
	REQUIRE(ptr != NULL);
	REQUIRE_FALSE(tflAdd(&list, ptr));

	REQUIRE_NOTHROW(tflReset(&list));
}