cmake_minimum_required(VERSION 3.5)
project(composition_test)

ADD_SUBDIRECTORY(../lib/googletest-release-1.8.0/googletest build)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library(path ../src/path.cpp)

add_executable( runUnitTests path.test.cpp )
target_link_libraries(runUnitTests gtest gtest_main path)
add_test( runUnitTests runUnitTests )