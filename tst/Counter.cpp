#include <cstring>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/Counter.h"
}

TEST_CASE("day counter add log entry", "[src/Counter.c/ctrAddLogEntry]")
{
	struct Counter counter;
	struct LogEntry entry0;
	struct LogEntry entry1;
	struct Date date = { .year = 0, .month = 0, .day = 0 };
	entry0.remote_address = (char*)"127.0.0.1";
	entry0.request_size = 420;
	entry0.response_size = 1337;
	entry1.remote_address = (char*)"example.com";
	entry1.request_size = 12;
	entry1.response_size = 100;

	REQUIRE(ctrInit(NULL, date) != 0);

	REQUIRE(ctrInit(&counter, date) == 0);

	REQUIRE_NOTHROW(ctrAddLogEntry(NULL, NULL));
	REQUIRE_NOTHROW(ctrAddLogEntry(NULL, &entry0));
	REQUIRE_NOTHROW(ctrAddLogEntry(&counter, NULL));

	ctrAddLogEntry(&counter, &entry0);

	REQUIRE(counter.n_requests == 1);
	REQUIRE(ctrCountUsers(&counter) == 1);
	REQUIRE(counter.n_bytes_in == 420);
	REQUIRE(counter.n_bytes_out == 1337);

	ctrAddLogEntry(&counter, &entry1);
	ctrAddLogEntry(&counter, &entry0);

	REQUIRE(counter.n_requests == 3);
	REQUIRE(ctrCountUsers(&counter) == 2);
	REQUIRE(counter.n_bytes_in == 852);
	REQUIRE(counter.n_bytes_out == 2774);

	REQUIRE_NOTHROW(ctrFree(&counter));
}