#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/LogStats.h"
}

TEST_CASE("log stats create", "[src/LogStats.c/lgsCreate]")
{
	struct LogStats *stats;

	stats = lgsCreate(0);
	REQUIRE(stats->capacity == 0);
	REQUIRE(stats->length == 0);
	lgsDestroy(stats);

	stats = lgsCreate(41);
	REQUIRE(stats->capacity == 41);
	REQUIRE(stats->length == 0);
	lgsDestroy(stats);
}

TEST_CASE("log stats add log entry", "[src/LogStats.c/lgsAddLogEntry")
{
	struct LogStats *stats;
	struct LogEntry entry;
	struct Date date0 = { .year = 2016, .month = 1, .day = 1 };
	struct Date date1 = { .year = 2015, .month = 1, .day = 1 };

	stats = lgsCreate(3);
	entry.date = date0;
	entry.http_method = HTTP_GET;
	entry.http_status = 200;
	entry.request_size = 123;
	entry.response_size = 4567;
	entry.remote_address = (char*)"sample.com";
	entry.requested_file = (char*)"/index.html";
	entry.referer = (char*)"";

	REQUIRE(lgsAddLogEntry(NULL, NULL) != 0);
	REQUIRE(lgsAddLogEntry(NULL, &entry) != 0);
	REQUIRE(lgsAddLogEntry(stats, NULL) != 0);

	for (int i = 0; i < 10; i++)
	lgsAddLogEntry(stats, &entry);

	REQUIRE(stats->length == 1);

	entry.date = date1;

	lgsAddLogEntry(stats, &entry);
	REQUIRE(stats->length == 2);

	lgsDestroy(stats);
}

TEST_CASE("log stats sort", "[src/LogStats.c/lgsSort")
{
	struct LogStats *stats;
	struct LogEntry entry;
	struct Date prev;

	stats = lgsCreate(12);

	for (int i = 11; i >= 0; i--)
	{
		entry.date = (struct Date){ .year = 2016, .month = 7, .day = (unsigned char)(20 - i) };

		lgsAddLogEntry(stats, &entry);
	}

	lgsSort(stats);

	// check if list is sorted by date
	prev = (struct Date){ .year = 0, .month = 1, .day = 1 };
	for (size_t i = 0; i < stats->length; i++)
	{
		REQUIRE(dtCompare(&prev, &(stats->data[i].date)) < 0);
		prev = stats->data[i].date;
	}

	lgsDestroy(stats);
}