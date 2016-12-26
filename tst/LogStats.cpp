#include <cstring>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/LogStats.h"
}

TEST_CASE("log stats create", "[src/LogStats.c/lgsCreate]")
{
	struct LogStats *stats;

	stats = lgsCreate(0);
	REQUIRE(stats != NULL);
	REQUIRE(stats->capacity == 0);
	REQUIRE(stats->length == 0);
	lgsDestroy(stats);

	stats = lgsCreate(41);
	REQUIRE(stats != NULL);
	REQUIRE(stats->capacity == 41);
	REQUIRE(stats->length == 0);
	lgsDestroy(stats);
}

TEST_CASE("log stats add log entry", "[src/LogStats.c/lgsAddLogEntry")
{
	struct LogStats *stats;
	struct LogEntry entry = { .date = "20160101", .http_method = HTTP_GET, .http_status = 200, .request_size = 123,
			.response_size = 4567, .remote_address = "sample.com", .requested_file = "/index.html", .referer = "-" };

	stats = lgsCreate(3);

	REQUIRE(lgsAddLogEntry(NULL, NULL) != 0);
	REQUIRE(lgsAddLogEntry(NULL, &entry) != 0);
	REQUIRE(lgsAddLogEntry(stats, NULL) != 0);

	for (int i = 0; i < 10; i++)
		lgsAddLogEntry(stats, &entry);

	REQUIRE(stats->length == 1);

	strcpy(entry.date, "20150101");

	lgsAddLogEntry(stats, &entry);
	REQUIRE(stats->length == 2);

	lgsDestroy(stats);
}

TEST_CASE("log stats sort", "[src/LogStats.c/lgsSort")
{
	struct LogStats *stats;
	struct LogEntry entry;
	const char *prev;

	stats = lgsCreate(12);

	int year = 2016;
	int month = 7;

	for (int day = 12; day >= 1; day--)
	{
		sprintf(entry.date, "%04d%02d%02d", year, month, day);
		lgsAddLogEntry(stats, &entry);
	}

	lgsSort(stats);

	// check if list is sorted by date
	prev = "00000001";
	for (size_t i = 0; i < stats->length; i++)
	{
		REQUIRE(strcmp(prev, stats->keys[i]) < 0);
		prev = stats->keys[i];
	}

	lgsDestroy(stats);
}