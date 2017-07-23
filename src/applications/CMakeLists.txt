cmake_minimum_required(VERSION 3.0)

include(${CMAKE_SOURCE_DIR}/dependencies/cmake/helper.cmake)
#include(${CMAKE_SOURCE_DIR}/dependencies/cmake/GSP_asio.cmake)

set(APP test1)
SearchFolderForSourceAndHeaderFiles(${APP})

include_directories(${CMAKE_SOURCE_DIR}/src/modules/)

include_directories(${asio_INCLUDE_DIRS})

add_executable(${APP}
        ${${APP}_SOURCES}
        ${${APP}_HEADERS}
        )
add_dependencies(${APP} path)
target_link_libraries(${APP} path)
set_target_properties(${APP} PROPERTIES FOLDER "applications")
