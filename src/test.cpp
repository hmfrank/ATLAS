#define CATCH_CONFIG_MAIN

#include <climits>
#include "../lib/catch.hpp"

extern "C"
{
#include "../inc/Date.h"
#include "../inc/DayCounter.h"
#include "../inc/LogEntry.h"
#include "../inc/parse.h"
extern unsigned short toHttpMethod(const char *str);
extern unsigned char toMonth(const char *str);
};

// TODO: test struct LogStats

// TODO: more tests for parseLogEntry()

// TODO: run valigrind memory leak tests
// TODO: split test into multiple soruce files


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

//
// ============   Date.h   ==========
//
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

//
// ============   DayCounter.h   ==========
//
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

//
// ============   parse.h   ==========
//
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
	// format: %t#%h#%u#%s#%I#%O#%U#%{Referer}i#%m
	struct LogEntry entry;
	FILE *file;

	// normal log line
	const char *s0 = "[07/Nov/2016:17:40:56 +0000]#1.2.3.4#-#200#1112#3757#/index.html#/#GET";
	file = fmemopen((char*)s0, strlen(s0), "r");

	REQUIRE(parseLogEntry(file, NULL) == -1);
	REQUIRE(parseLogEntry(NULL, &entry) == -1);
	REQUIRE(parseLogEntry(NULL, NULL) == -1);

	REQUIRE(parseLogEntry(file, &entry) == 0);
	REQUIRE(entry.date.day == 7);
	REQUIRE(entry.date.month == 11);
	REQUIRE(entry.date.year == 2016);
	REQUIRE(entry.http_method == HTTP_GET);
	REQUIRE(entry.http_status == 200);
	REQUIRE(entry.request_size == 1112);
	REQUIRE(entry.response_size == 3757);
	REQUIRE(strcmp(entry.remote_address, "1.2.3.4") == 0);
	REQUIRE(strcmp(entry.username, "-") == 0);
	REQUIRE(strcmp(entry.requested_file, "/index.html") == 0);
	REQUIRE(strcmp(entry.referer, "/") == 0);

	lgeFreeStrings(&entry);
	fclose(file);

	// very strange but still valid log line
	const char *s1 = "[12/mAR/9999:4:2:0 +1337]#fancy.url.com##999#4294967295#0#/!@$%##";
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
	REQUIRE(strcmp(entry.username, "") == 0);
	REQUIRE(strcmp(entry.requested_file, "/!@$%") == 0);
	REQUIRE(strcmp(entry.referer, "") == 0);

	lgeFreeStrings(&entry);
	fclose(file);

	// invalid format (year >= 10000)
	const char *s2 = "[3/Oct/10000:4:2:0 +1337]#8.8.8.8#mike#200#257#2395#/index.html##GET";
	file = fmemopen((char*)s2, strlen(s2), "r");

	REQUIRE(parseLogEntry(file, &entry) == 1);

	fclose(file);
}
