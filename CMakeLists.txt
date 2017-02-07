cmake_minimum_required(VERSION 3.5)
project(atlas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -Wall -Wextra -Werror -I lib/ -I lib/AuD/inc/ -D _GNU_SOURCE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -Werror -I lib/ -I lib/AuD/inc/")

include_directories(${CMAKE_SOURCE_DIR}/lib/ ${CMAKE_SOURCE_DIR}/lib/AuD/inc/)

set(SOURCE_FILES_ATLAS
        src/Counter.c src/DistinctCounter.c src/LogEntry.c src/LogStats.c src/parse.c src/ToFreeList.c src/globals.c src/main.c
        inc/Counter.h inc/DistinctCounter.h inc/LogEntry.h inc/LogStats.h inc/parse.h inc/ToFreeList.h inc/globals.h
        lib/AuD/inc/AvlTree.h)
set(SOURCE_FILES_UTEST
        src/Counter.c src/DistinctCounter.c src/LogEntry.c src/LogStats.c src/parse.c src/ToFreeList.c src/globals.c
        inc/Counter.h inc/DistinctCounter.h inc/LogEntry.h inc/LogStats.h inc/parse.h inc/ToFreeList.h inc/globals.h
        tst/Counter.cpp tst/DistinctCounter.cpp tst/LogEntry.cpp tst/LogStats.cpp tst/parse.cpp tst/test.cpp tst/ToFreeList.cpp tst/globals.cpp
		lib/AuD/inc/AvlTree.h)

add_executable(atlas ${SOURCE_FILES_ATLAS})
add_executable(utest ${SOURCE_FILES_UTEST})

target_link_libraries(atlas ${CMAKE_SOURCE_DIR}/lib/libaud.a)
target_link_libraries(utest ${CMAKE_SOURCE_DIR}/lib/libaud.a)

# TODO: fix CMakeLists.txt