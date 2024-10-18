# Copyright 2024 Ingemar Hedvall
# SPDX-License-Identifier: MIT
include (FetchContent)
if (NOT MdfLib_FOUND)
    FetchContent_Declare(mdflib
            GIT_REPOSITORY https://github.com/ihedvall/mdflib.git
            GIT_TAG HEAD)
    set(MDF_BUILD_DOC OFF CACHE  BOOL "" FORCE)
    set(MDF_BUILD_TEST OFF CACHE  BOOL "" FORCE)
    set(MDF_BUILD_TOOLS OFF CACHE  BOOL "" FORCE)
    set(MDF_BUILD_SHARED_LIB OFF CACHE  BOOL "" FORCE)
    set(MDF_BUILD_SHARED_LIB_NET OFF CACHE  BOOL "" FORCE)
    set(MDF_BUILD_SHARED_LIB_EXAMPLE OFF CACHE  BOOL "" FORCE)

    FetchContent_MakeAvailable(mdflib)

    message(STATUS "MDFLIB Populated: " ${mdflib_POPULATED})
    message(STATUS "MDFLIB Source Dir: " ${mdflib_SOURCE_DIR})
    message(STATUS "MDFLIB Binary Dir: " ${mdflib_BINARY_DIR})
    set(MDFLIB_LOCAL_FETCH 1)
endif()
