#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"

extern "C"
{
#include "../inc/Date.h"
#include "../inc/LogEntry.h"
#include "../inc/macros.h"
#include "../inc/parse.h"
#include "../inc/PreReader.h"
};

/*
extern unsigned short toHttpMethod(const char *str);
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
*/

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
	const char *s1 = "[255/mAR/65535:4:2:0 +1337]#fancy.url.com##65535#4294967295#0#/!@$%##";
	file = fmemopen((char*)s1, strlen(s1), "r");

	REQUIRE(parseLogEntry(file, &entry) == 0);
	REQUIRE(entry.date.day == 255);
	REQUIRE(entry.date.month == 3);
	REQUIRE(entry.date.year == 65535);
	REQUIRE(entry.http_method == HTTP_UNKNOWN);
	REQUIRE(entry.http_status == 65535);
	REQUIRE(entry.request_size == 4294967295);
	REQUIRE(entry.response_size == 0);
	REQUIRE(strcmp(entry.remote_address, "fancy.url.com") == 0);
	REQUIRE(strcmp(entry.username, "") == 0);
	REQUIRE(strcmp(entry.requested_file, "/!@$%") == 0);
	REQUIRE(strcmp(entry.referer, "") == 0);

	lgeFreeStrings(&entry);
	fclose(file);

	// invalid format (negative year)
	const char *s2 = "[3/Oct/-1:4:2:0 +1337]#8.8.8.8#mike#200#257#2395#/index.html##GET";
	file = fmemopen((char*)s2, strlen(s2), "r");

	REQUIRE(parseLogEntry(file, &entry) == 1);

	fclose(file);
}

TEST_CASE("PreReader initialization", "[src/PreReader.c/prInit]")
{
	// some random file
	FILE *file = stdin;
	struct PreReader pr;

	prInit(&pr, file);

	REQUIRE(pr.file == file);
	REQUIRE(pr.read_pos == 0);
	REQUIRE(pr.write_pos == 0);
}

TEST_CASE("PreReader get next char", "[src/PreReader.c/prNext]")
{
	struct PreReader pr;
	const char *data = "abcdef\0\n\t\b!@#$";
	FILE *file = fmemopen((void*)data, 14, "r");

	REQUIRE(file != NULL);
	prInit(&pr, file);

	// test normal reading
	for (int i = 0; i < 14; i++)
		REQUIRE(prNext(&pr) == (int)(data)[i]);

	REQUIRE(prNext(&pr) == EOF);
	REQUIRE(prNext(&pr) == EOF);

	// test invalid parameter
	REQUIRE(prNext(NULL) == EOF);

	fseek(pr.file, 0, SEEK_SET);
	pr.write_pos = 0;
	pr.read_pos = 1;
	REQUIRE(prNext(&pr) == EOF);

	pr.write_pos = PREREADER_BUFFER_SIZE;
	pr.read_pos = 6;
	REQUIRE(prNext(&pr) == 0);

	pr.write_pos = PREREADER_BUFFER_SIZE + 1;
	REQUIRE(prNext(&pr) == EOF);

	// close file
	REQUIRE(fclose(file) == 0);

	// test reload
	char bigdata[PREREADER_BUFFER_SIZE + 1];
	bigdata[PREREADER_BUFFER_SIZE - 1] = 'A';
	bigdata[PREREADER_BUFFER_SIZE] = 'B';
	file = fmemopen(bigdata, PREREADER_BUFFER_SIZE + 1, "r");

	REQUIRE(file != NULL);
	prInit(&pr, file);

	for (int i = 0; i < PREREADER_BUFFER_SIZE + 1; i++)
		REQUIRE(prNext(&pr) == (int)bigdata[i]);

	REQUIRE(prNext(&pr) == EOF);
	REQUIRE(prNext(&pr) == EOF);
}
