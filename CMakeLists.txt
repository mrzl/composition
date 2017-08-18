cmake_minimum_required(VERSION 3.5)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dependencies/cmake")
include(helper)

AddGTestAndGMock()

project(path)

add_subdirectory(src)

add_custom_target(run_test1
        COMMAND ${CMAKE_SOURCE_DIR}/src/applications/bin/test1
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

add_custom_target(mousehook
        COMMAND ${CMAKE_SOURCE_DIR}/src/mousehook/bin/hook
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

# This must always be last!
include(CPack)