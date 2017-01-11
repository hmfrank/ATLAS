#include <climits>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// TODO: run valigrind memory leak tests

TEST_CASE("architecture tests", "[architecture]")
{
	// for http_method in struct LogEntry
	REQUIRE(USHRT_MAX >= 999);
	// for implementation of parseLogEntry()
	REQUIRE(LONG_MAX >= 9999);
	// for implementation of parseLogEntry()
	REQUIRE(UINT_MAX <= LLONG_MAX);
}
