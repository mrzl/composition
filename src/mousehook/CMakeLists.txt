cmake_minimum_required(VERSION 3.1)

include(${CMAKE_SOURCE_DIR}/dependencies/cmake/helper.cmake)

include(${OF_ROOT}/openFrameworks.cmake)

set(APP hook)
SearchFolderForSourceAndHeaderFiles(${APP})

include_directories(${CMAKE_SOURCE_DIR}/src/modules/)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_executable(${APP}
        ${${APP}_SOURCES}
        ${${APP}_HEADERS}
        )

add_dependencies(${APP} path)
target_link_libraries(${APP} path)
set_target_properties(${APP} PROPERTIES FOLDER "mousehook")
