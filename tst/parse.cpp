#include <cstring>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/parse.h"
extern unsigned short toHttpMethod(const char *str);
extern unsigned char toMonth(const char *str);
}

// TODO: more tests for parseLogEntry()

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

// TODO: test too long input
TEST_CASE("parse log entry", "[src/parse.c/parseLogEntry]")
{
	struct LogEntry entry;
	FILE *file;

	// normal log line
	const char *s0 = "12.34.56.78 - [23/Dec/2016:18:36:27 +0000] GET 200 394 992 \"/public/\" \"-\"";
	file = fmemopen((char*)s0, strlen(s0), "r");

	REQUIRE(parseLogEntry(file, NULL) == -1);
	REQUIRE(parseLogEntry(NULL, &entry) == -1);
	REQUIRE(parseLogEntry(NULL, NULL) == -1);

	REQUIRE(parseLogEntry(file, &entry) == 0);
	REQUIRE(entry.date.day == 23);
	REQUIRE(entry.date.month == 12);
	REQUIRE(entry.date.year == 2016);
	REQUIRE(entry.http_method == HTTP_GET);
	REQUIRE(entry.http_status == 200);
	REQUIRE(entry.request_size == 394);
	REQUIRE(entry.response_size == 992);
	REQUIRE(strcmp(entry.remote_address, "12.34.56.78") == 0);
	REQUIRE(strcmp(entry.requested_file, "/public/") == 0);
	REQUIRE(strcmp(entry.referer, "-") == 0);

	lgeFreeStrings(&entry);
	fclose(file);

	// very strange but still valid log line
	const char *s1 = "fancy.url.com !@#$ [12/mAR/9999:4:2:0 +1337] %^&* 999 4294967295 0 \"-\" \"https://example.com/\"";
	file = fmemopen((char*)s1, strlen(s1), "r");

	REQUIRE(parseLogEntry(file, &entry) == 0);
	REQUIRE(entry.date.day == 12);
	REQUIRE(entry.date.month == 3);
	REQUIRE(entry.date.year == 9999);
	REQUIRE(entry.http_method == HTTP_UNKNOWN);
	REQUIRE(entry.http_status == 999);
	REQUIRE(entry.request_size == 4294967295);
	REQUIRE(entry.response_size == 0);
	REQUIRE(strcmp(entry.remote_address, "fancy.url.com") == 0);
	REQUIRE(strcmp(entry.requested_file, "-") == 0);
	REQUIRE(strcmp(entry.referer, "https://example.com/") == 0);

	lgeFreeStrings(&entry);
	fclose(file);

	// invalid format (year >= 10000)
	//const char *s2 = "[3/Oct/10000:4:2:0 +1337]#8.8.8.8#mike#200#257#2395#/index.html##GET";
	const char *s2 = "8.8.8.8 mike [3/Oct/10000:4:2:0 +1337] GET 200 257 2395 \"index.html\" \"-\"";
	file = fmemopen((char*)s2, strlen(s2), "r");

	REQUIRE(parseLogEntry(file, &entry) == 1);

	fclose(file);
}

