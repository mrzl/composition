cmake_minimum_required(VERSION 3.5)

function(AddGTestAndGMock)
    set(gtest_force_shared_crt ON CACHE BOOL "Use shared runtime for gtest")
    mark_as_advanced(gtest_force_shared_crt)
    add_subdirectory(dependencies/googletest-release-1.8.0/googlemock EXCLUDE_FROM_ALL)
    set_target_properties(gtest PROPERTIES FOLDER "dependencies")
    set_target_properties(gtest_main PROPERTIES FOLDER "dependencies")
    set_target_properties(gmock PROPERTIES FOLDER "dependencies")
endfunction()

function(SetCompilerDefinitions)
    set(CMAKE_CXX_STANDARD 14 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)

    # let all projects know that build is running under cmake
    add_definitions(-DCMAKE_BUILD)
    if(WIN32)
        add_definitions(-D_WIN32_WINNT=0x0501)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic " PARENT_SCOPE)
endfunction()

function(SearchFolderForSourceAndHeaderFiles SubLibraryName)
    set(PROJECTNAME ${SubLibraryName})
    file(GLOB_RECURSE ${PROJECTNAME}_SOURCES "${PROJECTNAME}/*.cpp")
    file(GLOB_RECURSE ${PROJECTNAME}_HEADERS "${PROJECTNAME}/*.h")

    set(resultVar ${PROJECTNAME})
    set(${resultVar}_SOURCES ${${PROJECTNAME}_SOURCES} PARENT_SCOPE)
    set(${resultVar}_HEADERS ${${PROJECTNAME}_HEADERS} PARENT_SCOPE)
endfunction()

function(GetSourceAndHeaderFilesForModule SubLibraryName)
    set(PROJECTNAME ${SubLibraryName})
    file(GLOB ${PROJECTNAME}_SOURCES "${PROJECTNAME}/source/*.cpp" "${PROJECTNAME}/source/*.h")
    file(GLOB ${PROJECTNAME}_HEADERS "${PROJECTNAME}/*.h")

    set(resultVar ${PROJECTNAME})
    set(${resultVar}_SOURCES ${${PROJECTNAME}_SOURCES} PARENT_SCOPE)
    set(${resultVar}_HEADERS ${${PROJECTNAME}_HEADERS} PARENT_SCOPE)
endfunction()

include(CMakeParseArguments)

function(AddGTestTarget)
    cmake_parse_arguments(
            PARSED_ARGS # prefix of output variables
            "" # list of names of the boolean arguments (only defined ones will be true)
            "NAME" # list of names of mono-valued arguments
            "DEPENDENCIES" # list of names of multi-valued arguments (output variables are lists)
            ${ARGN} # arguments of the function to parse, here we take the all original ones
    )
    # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_NAME)
        message(FATAL_ERROR "You must provide a name")
    endif()

    include(CTest)

    SearchFolderForSourceAndHeaderFiles(${PARSED_ARGS_NAME})

    add_executable(${PARSED_ARGS_NAME}
            ${${PARSED_ARGS_NAME}_SOURCES}
            ${${PARSED_ARGS_NAME}_HEADERS}
            )

    target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/googletest-release-1.8.0/googletest/include)
    target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/googletest-release-1.8.0/googlemock/include)

    source_group("Header" FILES ${${PARSED_ARGS_NAME}_HEADERS})
    source_group("Implementation" FILES ${${PARSED_ARGS_NAME}_SOURCES})

    add_dependencies(${PARSED_ARGS_NAME} gtest gmock gtest_main)
    target_link_libraries(${PARSED_ARGS_NAME} gtest gmock gtest_main)

    foreach(dps ${PARSED_ARGS_DEPENDENCIES})
        add_dependencies(${PARSED_ARGS_NAME} ${dps})
        target_link_libraries(${PARSED_ARGS_NAME} ${dps})
    endforeach()

    get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    add_test(NAME ${PARSED_ARGS_NAME} COMMAND ${PARSED_ARGS_NAME})
    set_target_properties(${PARSED_ARGS_NAME} PROPERTIES FOLDER ${DIRNAME})
endfunction()


function(AddModule)
    cmake_parse_arguments(
            PARSED_ARGS # prefix of output variables
            "" # list of names of the boolean arguments (only defined ones will be true)
            "NAME"
            "INTERNAL_DEPENDENCIES;EXTERNAL_DEPENDENCIES"
            ${ARGN} # arguments of the function to parse, here we take the all original ones
    )
    # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_NAME)
        message(FATAL_ERROR "You must provide a name")
    endif()

    set (MODULENAME ${PARSED_ARGS_NAME})

    GetSourceAndHeaderFilesForModule(${MODULENAME})

    add_library(${MODULENAME} STATIC
            ${${MODULENAME}_SOURCES} ${${MODULENAME}_HEADERS}
            )

    target_link_libraries(${MODULENAME})
    set_target_properties(${MODULENAME} PROPERTIES FOLDER "modules")

    source_group("Header" FILES ${${MODULENAME}_HEADERS})
    source_group("Implementation" FILES ${${MODULENAME}_SOURCES})

    foreach(dps ${PARSED_ARGS_INTERNAL_DEPENDENCIES})
        add_dependencies(${MODULENAME} ${dps})
        target_link_libraries(${MODULENAME} ${dps})
    endforeach()

    foreach(dps ${PARSED_ARGS_EXTERNAL_DEPENDENCIES})
        include("${dps}")
        target_include_directories(${MODULENAME} PUBLIC ${${dps}_INCLUDE_DIRS})
        target_compile_definitions(${MODULENAME} PUBLIC ${${dps}_DEFINITIONS})
        if(${dps}_LIBRARIES)
            target_link_libraries(${MODULENAME} ${${dps}_LIBRARIES})
        endif()
    endforeach()

    # unit tests
    AddGTestTarget(NAME ${MODULENAME}.test DEPENDENCIES ${MODULENAME})
endfunction()