if (WIN32)
    # on windows use precompiled boost - see boost directory for build instructions
    set(boost_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/include)
    set(boost_LIBRARIES
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_atomic-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_chrono-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_date_time-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_filesystem-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_log_setup-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_log-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_regex-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_system-vc120-mt-1_64.lib
            optimized ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_thread-vc120-mt-1_64.lib

            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_atomic-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_chrono-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_date_time-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_filesystem-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_log_setup-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_log-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_regex-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_system-vc120-mt-gd-1_64.lib
            debug ${CMAKE_SOURCE_DIR}/dependencies/boost-1.64.0/lib/libboost_thread-vc120-mt-gd-1_64.lib
            )
    set(boost_DEFINITIONS "-DBOOST_USE_WINAPI_VERSION=0x0501")
else()
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost 1.58.0 REQUIRED COMPONENTS atomic date_time iostreams system filesystem thread log chrono)

    find_package(Threads)

    if(Boost_FOUND)
        set(boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
        #set(boost_LIBRARIES
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_atomic.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_chrono.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_container.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_context.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_date_time.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_filesystem.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_iostreams.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_log.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_system.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_thread.a"
        #        "C:\\Users\\schwittlickm\\Downloads\\mingw64-posix\\mingw64\\lib\\libboost_timer.a"

#                ${CMAKE_THREAD_LIBS_INIT})
        set(boost_DEFINITIONS ${Boost_DEFINITIONS} -DBOOST_ALL_DYN_LINK)
    else()
        message(STATUS "Boost not found")
    endif()
endif()
