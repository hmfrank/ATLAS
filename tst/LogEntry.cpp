#include <catch.hpp>

extern "C"
{
#include "../inc/LogEntry.h"
}

TEST_CASE("log entry equals", "[src/LogEntry.c/lgeEquals]")
{
	struct LogEntry e0 = { .date = "20161223", .http_method = HTTP_GET, .http_status = 200, .request_size = 394,
			.response_size = 993, .remote_address = "12.34.56.78", .requested_file = "/public/", .referer = "-" };
	struct LogEntry e1 = e0;

	REQUIRE(lgeEquals(NULL, NULL));
	REQUIRE_FALSE(lgeEquals(NULL, &e0));
	REQUIRE_FALSE(lgeEquals(&e1, NULL));
	REQUIRE(lgeEquals(&e0, &e0));
	REQUIRE(lgeEquals(&e0, &e1));
	REQUIRE(lgeEquals(&e1, &e0));
}
