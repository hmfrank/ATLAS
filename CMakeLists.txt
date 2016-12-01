cmake_minimum_required(VERSION 3.5)
project(atlas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_ATLAS src/main.c src/LogEntry.c inc/LogEntry.h inc/Date.h src/parse.c inc/parse.h src/Date.c inc/DayCounter.h inc/LogStats.h src/DayCounter.c src/LogStats.c src/List.c inc/List.h src/AvlTree.c inc/AvlTree.h)
set(SOURCE_FILES_UTEST tst/test.cpp lib/catch.hpp src/LogEntry.c inc/LogEntry.h inc/Date.h src/parse.c inc/parse.h src/Date.c inc/DayCounter.h inc/LogStats.h src/DayCounter.c src/LogStats.c tst/Date.cpp tst/DayCounter.cpp tst/LogStats.cpp tst/parse.cpp src/List.c inc/List.h tst/List.cpp src/AvlTree.c inc/AvlTree.h, tst/AvlTree.cpp)
add_executable(atlas ${SOURCE_FILES_ATLAS})
add_executable(utest ${SOURCE_FILES_UTEST})
