#include <catch.hpp>
#include <cstring>

extern "C"
{
#include "../inc/globals.h"
}

TEST_CASE("parse command line args", "[src/globals.c]")
{
	char *argv[5] = { (char*)"./atlas" };

	parseCommandLineArguments(0, NULL);
	parseCommandLineArguments(3, argv);

	for (int i = 0; i < 256; i++)
	{
		char arg_r[7] = "-r=";
		char arg_c[9] = "-c=";
		argv[1] = arg_r;
		argv[2] = arg_c;

		if (i & 128) strcat(arg_c, "d");
		if (i & 64) strcat(arg_c, "r");
		if (i & 32) strcat(arg_c, "u");
		if (i & 16) strcat(arg_c, "i");
		if (i & 8) strcat(arg_c, "o");
		if (i & 4) strcat(arg_r, "h");
		if (i & 2) strcat(arg_r, "d");
		if (i & 1) strcat(arg_r, "t");

		parseCommandLineArguments(3, argv);

		REQUIRE(!!SHOW_DATE == !!(i & 128));
		REQUIRE(!!SHOW_REQUESTS == !!(i & 64));
		REQUIRE(!!SHOW_USERS == !!(i & 32));
		REQUIRE(!!SHOW_IN_BYTES == !!(i & 16));
		REQUIRE(!!SHOW_OUT_BYTES == !!(i & 8));
		REQUIRE(!!SHOW_TABLE_HEADER == !!(i & 4));
		REQUIRE(!!SHOW_DAYS == !!(i & 2));
		REQUIRE(!!SHOW_TOTAL_COUNT == !!(i & 1));
	}
}