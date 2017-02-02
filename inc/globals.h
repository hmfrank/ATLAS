#include <stddef.h>

#ifndef ATLAS_GLOBALS_H
#define ATLAS_GLOBALS_H

/**
 * The maximum number of days the program can store information about.
 */
extern const size_t MAX_N_DAYS;

void parseCommandLineArguments(int argc, char **argv);

#endif //ATLAS_GLOBALS_H
