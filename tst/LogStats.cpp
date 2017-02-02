#include <cstring>
#include <catch.hpp>

extern "C"
{
#include "../inc/LogStats.h"
}

TEST_CASE("log stats", "[src/LogStats.c]")
{
	struct LogStats *stats;

	SECTION("log stats create", "[src/LogStats.c/lgsCreate]")
	{
		stats = lgsCreate(0);
		REQUIRE(stats != NULL);
		REQUIRE(stats->capacity == 0);
		REQUIRE(stats->length == 0);
		lgsDestroy(stats);
	}

	stats = lgsCreate(41);
	REQUIRE(stats != NULL);
	REQUIRE(stats->capacity == 41);
	REQUIRE(stats->length == 0);

	SECTION("log stats add log entry", "[src/LogStats.c/lgsAddLogEntry]")
	{
		struct LogEntry entry = { .date = "20160101", .http_method = HTTP_GET, .http_status = 200, .request_size = 123,
				.response_size = 4567, .remote_address = "sample.com", .requested_file = "/index.html", .referer = "-" };

		REQUIRE(lgsAddLogEntry(NULL, NULL) != 0);
		REQUIRE(lgsAddLogEntry(NULL, &entry) != 0);
		REQUIRE(lgsAddLogEntry(stats, NULL) != 0);

		for (int i = 0; i < 10; i++)
			lgsAddLogEntry(stats, &entry);

		REQUIRE(stats->length == 1);

		strcpy(entry.date, "20150101");

		lgsAddLogEntry(stats, &entry);
		REQUIRE(stats->length == 2);
	}

	SECTION("log stats sort", "[src/LogStats.c/lgsSort]")
	{
		struct LogEntry entry;
		const char *prev;

		entry.remote_address = "0.4.2.0";

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
	}

	lgsDestroy(stats);
}
