#include <cstring>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/Date.h"
}

TEST_CASE("date compare", "[src/Date.c/dtCompare]")
{
	struct Date d0 = { .year = 2016, .month = 1, .day = 10 };
	struct Date d1 = { .year = 2016, .month = 1, .day = 11 };
	struct Date d2 = { .year = 2016, .month = 2, .day = 10 };
	struct Date d3 = { .year = 2017, .month = 1, .day = 10 };

	REQUIRE(dtCompare(NULL, NULL) == 0);
	REQUIRE(dtCompare(NULL, &d0) < 0);
	REQUIRE(dtCompare(&d1, NULL) > 0);
	REQUIRE(dtCompare(&d3, &d3) == 0);
	REQUIRE(dtCompare(&d0, &d1) < 0);
	REQUIRE(dtCompare(&d0, &d2) < 0);
	REQUIRE(dtCompare(&d0, &d3) < 0);
	REQUIRE(dtCompare(&d3, &d0) > 0);
	REQUIRE(dtCompare(&d3, &d2) > 0);
}

TEST_CASE("date to new string", "[src/Date.c/dtToNewString]")
{
	char *str;
	struct Date d0 = {.year = 2016, .month = 12, .day = 24};

	REQUIRE(dtToNewString(NULL) == NULL);
	str = dtToNewString(&d0);
	REQUIRE(strcmp("2016/12/24", str) == 0);
	free(str);
}

TEST_CASE("date to string", "[src/Date.c/dtToString]")
{
	char buffer[64];
	char str0[] = "2016/12/24";
	struct Date d0 = {.year = 2016, .month = 12, .day = 24};

	REQUIRE(dtToString(NULL, NULL) < 0);
	REQUIRE(dtToString(NULL, buffer) < 0);
	REQUIRE(dtToString(&d0, NULL) < 0);
	REQUIRE(dtToString(&d0, buffer) == strlen(str0));
	REQUIRE(strcmp(buffer, str0) == 0);
}