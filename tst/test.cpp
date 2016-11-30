#include <climits>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

// TODO: run valigrind memory leak tests

TEST_CASE("architecture tests", "[architecture]")
{
	// for day in struct Date
	REQUIRE(UCHAR_MAX >= 31);
	// for year in struct Date
	REQUIRE(USHRT_MAX >= 9999);
	// for implementation of dtToNewString
	REQUIRE(USHRT_MAX <= 99999);
	REQUIRE(UCHAR_MAX <= 99999);
	// for implementation of parseLogEntry
	REQUIRE(LLONG_MAX >= 9999);
}