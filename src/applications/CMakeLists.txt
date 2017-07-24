cmake_minimum_required(VERSION 3.1)

include(${CMAKE_SOURCE_DIR}/dependencies/cmake/helper.cmake)

set(OF_ROOT "${CMAKE_SOURCE_DIR}/dependencies/of/" CACHE PATH "The root directory of ofnode/of project.")
include(${OF_ROOT}/openFrameworks.cmake)

set(APP test1)
SearchFolderForSourceAndHeaderFiles(${APP})

include_directories(${CMAKE_SOURCE_DIR}/src/modules/)

add_executable(${APP}
        ${${APP}_SOURCES}
        ${${APP}_HEADERS}
        )

add_dependencies(${APP} path)
target_link_libraries(${APP} path ${OPENFRAMEWORKS_LIBRARIES})
set_target_properties(${APP} PROPERTIES FOLDER "applications")
