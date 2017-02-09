#include <catch.hpp>
#include <cstring>

extern "C"
{
#include "../inc/DistinctCounter.h"
#include "../inc/globals.h"
}

TEST_CASE("parse command line args", "[src/globals.c]")
{
	char *argv[5] = { (char*)"./atlas" };

	parseCommandLineArguments(0, NULL);
	parseCommandLineArguments(3, argv);

	for (int i = 0; i < 256; i++)
	{
		char arg_r[11];
		char arg_c[16];

		strcpy(arg_r, i & 8 ? "-r=" : "--rows=");
		strcpy(arg_c, i & 1 ? "-c=" : "--columns=");

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

	// test --days
	argv[1] = (char*)"-d=0";
	parseCommandLineArguments(2, argv);
	REQUIRE(MAX_N_DAYS == 0);

	argv[1] = (char*)"--days=-1";
	parseCommandLineArguments(2, argv);
	REQUIRE(MAX_N_DAYS == 1);

	argv[1] = (char*)"--days=-420";
	parseCommandLineArguments(2, argv);
	REQUIRE(MAX_N_DAYS == 420);

	argv[1] = (char*)"--days=1337";
	parseCommandLineArguments(2, argv);
	REQUIRE(MAX_N_DAYS == 1337);

	// test --method
	argv[1] = (char*)"-m=AVL-Tree";
	parseCommandLineArguments(2, argv);
	REQUIRE(METHOD == AVL_TREE);

	argv[1] = (char*)"--method=a";
	parseCommandLineArguments(2, argv);
	REQUIRE(METHOD == AVL_TREE);

	argv[1] = (char*)"-m=hll";
	parseCommandLineArguments(2, argv);
	REQUIRE(METHOD == HYPERLOGLOG);

	argv[1] = (char*)"--method=HyperLogLog";
	parseCommandLineArguments(2, argv);
	REQUIRE(METHOD == HYPERLOGLOG);
}