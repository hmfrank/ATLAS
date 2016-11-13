cmake_minimum_required(VERSION 3.5)
project(atlas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_ATLAS src/main.c src/LogEntry.c inc/LogEntry.h inc/Date.h src/parse.c inc/parse.h)
set(SOURCE_FILES_UTEST src/test.cpp src/LogEntry.c inc/LogEntry.h inc/Date.h src/parse.c inc/parse.h)
add_executable(atlas ${SOURCE_FILES_ATLAS})
add_executable(utest ${SOURCE_FILES_UTEST})
