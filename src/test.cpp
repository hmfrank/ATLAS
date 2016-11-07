#define CATCH_CONFIG_MAIN
#include "../inc/catch.hpp"

extern "C"
{
#include "../inc/PreReader.h"
};

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

TEST_CASE("PreReader get next char", "[prNext]")
{
	struct PreReader pr;
	char data[] = "abcdef\0\n\t\b!@#$";
	FILE *file = fmemopen(data, 14, "r");

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