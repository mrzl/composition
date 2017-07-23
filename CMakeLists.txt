cmake_minimum_required(VERSION 3.5)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dependencies/cmake")
include(helper)

AddGTestAndGMock()

project(path)

add_subdirectory(src)

# This must always be last!
include(CPack)