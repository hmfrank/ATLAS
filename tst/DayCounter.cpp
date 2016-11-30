#include <cstring>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/DayCounter.h"
}

TEST_CASE("day counter add log entry", "[src/DayCounter.c/dcAddLogEntry]")
{
	struct DayCounter counter;
	struct LogEntry entry0;
	struct LogEntry entry1;
	entry0.remote_address = (char*)"127.0.0.1";
	entry0.request_size = 420;
	entry0.response_size = 1337;
	entry1.remote_address = (char*)"example.com";
	entry1.request_size = 12;
	entry1.response_size = 100;

	memset(&counter, 0, sizeof(struct DayCounter));

	REQUIRE_NOTHROW(dcAddLogEntry(NULL, NULL));
	REQUIRE_NOTHROW(dcAddLogEntry(NULL, &entry0));
	REQUIRE_NOTHROW(dcAddLogEntry(&counter, NULL));

	dcAddLogEntry(&counter, &entry0);

	REQUIRE(counter.n_requests == 1);
	// REQUIRE(counter.n_users == 1);
	REQUIRE(counter.n_bytes_in == 420);
	REQUIRE(counter.n_bytes_out == 1337);

	dcAddLogEntry(&counter, &entry1);
	dcAddLogEntry(&counter, &entry0);

	REQUIRE(counter.n_requests == 3);
	// REQUIRE(counter.n_users == 2);
	REQUIRE(counter.n_bytes_in == 852);
	REQUIRE(counter.n_bytes_out == 2774);
}