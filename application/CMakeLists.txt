cmake_minimum_required(VERSION 3.5)
project(composition)

set(CMAKE_CXX_STANDARD 14)

include_directories(../src)

add_library(path ../src/modules/path/path.cpp)

ADD_SUBDIRECTORY(lib/googletest-release-1.8.0/googletest build)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES main.cpp )
add_executable(composition ${SOURCE_FILES} src/path.cpp src/path.h)
target_link_libraries(composition gtest)