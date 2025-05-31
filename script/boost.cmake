# Copyright 2021 Ingemar Hedvall
# SPDX-License-Identifier: MIT

if (NOT Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_ARCHITECTURE -x64)
    set(Boost_NO_WARN_NEW_VERSIONS ON)
    set(Boost_DEBUG OFF)
    if(POLICY CMP0167)
        cmake_policy(SET CMP0167 OLD)
    endif()

    if (COMP_DIR)
        set(Boost_ROOT ${COMP_DIR}/boost/latest)
    endif()
    find_package(Boost REQUIRED COMPONENTS filesystem system locale program_options process)
endif()

message(STATUS "Boost Found: " ${Boost_FOUND})
message(STATUS "Boost Version: " ${Boost_VERSION_STRING})
message(STATUS "Boost Include Dirs: " ${Boost_INCLUDE_DIRS})
message(STATUS "Boost Library Dirs: " ${Boost_LIBRARY_DIRS})
message(STATUS "Boost Libraries: " ${Boost_LIBRARIES})