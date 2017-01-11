#include <cstring>
#include <catch.hpp>

extern "C"
{
#include "../inc/parse.h"
extern unsigned short toHttpMethod(const char *str);
extern long toMonth(const char *str);
}

TEST_CASE("to HTTP method", "[src/parse.c/toHttpMethod]")
{
	REQUIRE(toHttpMethod(NULL) == HTTP_UNKNOWN);
	REQUIRE(toHttpMethod("CONNECT") == HTTP_CONNECT);
	REQUIRE(toHttpMethod("delete") == HTTP_DELETE);
	REQUIRE(toHttpMethod("gET") == HTTP_GET);
	REQUIRE(toHttpMethod("HeAd") == HTTP_HEAD);
	REQUIRE(toHttpMethod("optIons") == HTTP_OPTIONS);
	REQUIRE(toHttpMethod("POST") == HTTP_POST);
	REQUIRE(toHttpMethod("put") == HTTP_PUT);
	REQUIRE(toHttpMethod("tRaCe") == HTTP_TRACE);
	REQUIRE(toHttpMethod("GETS") == HTTP_UNKNOWN);
	REQUIRE(toHttpMethod("") == HTTP_UNKNOWN);
}

TEST_CASE("to month", "[src/parse.c/toMonth]")
{
	REQUIRE(toMonth(NULL) == 0);

	REQUIRE(toMonth("jan") == 1);
	REQUIRE(toMonth("feB") == 2);
	REQUIRE(toMonth("mAr") == 3);
	REQUIRE(toMonth("aPR") == 4);
	REQUIRE(toMonth("May") == 5);
	REQUIRE(toMonth("JuN") == 6);
	REQUIRE(toMonth("JUl") == 7);
	REQUIRE(toMonth("AUG") == 8);
	REQUIRE(toMonth("sep") == 9);
	REQUIRE(toMonth("ocT") == 10);
	REQUIRE(toMonth("nOv") == 11);
	REQUIRE(toMonth("dEC") == 12);

	REQUIRE(toMonth("august") == 0);
	REQUIRE(toMonth("") == 0);
}

const char *createTooLongInput()
{
	static char too_long[1025];
	const char *str = "12.34.56.78 - [23/Dec/2016:18:36:27 +0000] GET 200 394 992 \"/public/\" \"-\"";

	memset(too_long, ' ', 1025);
	too_long[1024] = '\0';

	strcpy(too_long, str);
	too_long[strlen(str)] = ' ';

	return too_long;
}

TEST_CASE("parse log entry", "[src/parse.c/parseLogEntry]")
{
	struct TestDataRecord
	{
		// input string
		const char *input;

		// expected return value
		int expected;

		// expected result
		struct LogEntry result;
	};

	struct LogEntry dummy;

	struct TestDataRecord data[] = {
		{
			.input = "12.34.56.78 - [23/Dec/2016:18:36:27 +0000] GET 200 394 992 \"/public/\" \"-\"",
			.expected = 0,
			.result = { .date = "20161223", .http_method = HTTP_GET, .http_status = 200, .request_size = 394,
					.response_size = 992, .remote_address = "12.34.56.78", .requested_file = "/public/", .referer = "-" }
		},
		{
			.input = "fancy.url.com !@#$ [2/mAR/9999:4:2:0 +1337] %^&* 999 4294967295 0 \"-\" \"https://example.com/\"",
			.expected = 0,
			.result = { .date = "99990302", .http_method = HTTP_UNKNOWN, .http_status = 999, .request_size = 4294967295,
					.response_size = 0, .remote_address = "fancy.url.com", .requested_file = "-",
					.referer = "https://example.com/" }
		},
		{
			.input = "8.8.8.8 mike [3/Oct/10000:4:2:0 +1337] GET 200 257 2395 \"index.html\" \"-\"",
			.expected = 1,
			.result = dummy
		},
		{
			.input = "abc - [32/jan/2000:12:00:00 + 1000] GET 200 257 2395 \"index.html\" \"-\"",
			.expected  = 1,
			.result = dummy
		},
		{
			.input = "1.2.3.4 - [1/jan/2000:12:00:00 + 1000] GET 200 25 \"index.html\" \"-\"",
			.expected  = 1,
			.result = dummy
		},
		{
			.input = "1.2.3.4 - [1/jan/2000:12:00:00 + 1000] GET 200 one 1337 \"index.html\" \"-\"",
			.expected  = 1,
			.result = dummy
		},
		{
			.input = createTooLongInput(),
			.expected  = 1,
			.result = dummy
		}
	};

	struct LogEntry entry;
	FILE *file;

	for (size_t i = 0; i < sizeof(data) / sizeof(*data); i++)
	{
		struct TestDataRecord *test_data = data + i;

		file = fmemopen((char*)test_data->input, strlen(test_data->input), "r");
		REQUIRE(file != NULL);

		if (i == 0)
			REQUIRE(parseLogEntry(file, NULL) == -1);

		REQUIRE(parseLogEntry(file, &entry) == test_data->expected);

		if (test_data->expected == 0)
		{
			REQUIRE(lgeEquals(&entry, &test_data->result));

			lgeFreeStrings(&entry);
		}

		fclose(file);
	}

	REQUIRE(parseLogEntry(NULL, &entry) == -1);
	REQUIRE(parseLogEntry(NULL, NULL) == -1);
}

