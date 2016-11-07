#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"

extern "C"
{
#include "../inc/PreReader.h"
};

// TODO: test prNext()

TEST_CASE("PreReader initialization", "[prInit]")
{
	// some random file
	FILE *file = stdin;
	struct PreReader pr;

	prInit(&pr, file);

	REQUIRE(pr.file == file);
	REQUIRE(pr.read_pos == 0);
	REQUIRE(pr.write_pos == 0);
}