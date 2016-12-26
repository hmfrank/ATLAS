cmake_minimum_required(VERSION 3.5)
project(atlas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -D _GNU_SOURCE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_ATLAS src/main.c src/LogEntry.c inc/LogEntry.h src/parse.c inc/parse.h inc/Counter.h inc/LogStats.h src/Counter.c src/LogStats.c lib/AvlTree.c lib/AvlTree.h src/DistinctCounter.c inc/DistinctCounter.h src/ToFreeList.c inc/ToFreeList.h)
set(SOURCE_FILES_UTEST tst/test.cpp lib/catch.hpp src/LogEntry.c inc/LogEntry.h src/parse.c inc/parse.h inc/Counter.h inc/LogStats.h src/Counter.c src/LogStats.c tst/Counter.cpp tst/LogStats.cpp tst/parse.cpp lib/AvlTree.c lib/AvlTree.h src/DistinctCounter.c inc/DistinctCounter.h tst/LogEntry.cpp src/ToFreeList.c inc/ToFreeList.h tst/ToFreeList.cpp)
add_executable(atlas ${SOURCE_FILES_ATLAS})
add_executable(utest ${SOURCE_FILES_UTEST})
