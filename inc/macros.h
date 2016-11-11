/**
 * @file macros.h
 *
 * This file contains global macros for the entire project and is included by all .c-files.
 * Note that if you change something in this file, the whole project gets recompiled, because every .c-file depends on it.
 */

#define DEBUG
#define TEST

#ifdef TEST
// to test static functions (i don't use the static keyword for anything else)
#define static
#endif
