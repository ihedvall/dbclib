# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT

project(TestDbc
        VERSION 1.0
        DESCRIPTION "Google unit tests for the DBC library"
        LANGUAGES CXX)

add_executable(test_dbc
        testread.cpp testread.h
        test_dbchelper.cpp)

target_include_directories(test_dbc PRIVATE
        ../include
        ../src
        ${GTEST_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS})
target_include_directories(test_dbc PRIVATE ${FLEX_INCLUDE_DIRS})

if (MINGW)
    target_link_options(test_dbc PRIVATE -static -fstack-protector)
elseif (MSVC)
    target_compile_definitions(test_dbc PRIVATE -D_WIN32_WINNT=0x0A00)
endif ()

target_link_libraries(test_dbc PRIVATE dbc)
target_link_libraries(test_dbc PRIVATE ${GTEST_BOTH_LIBRARIES})

if (WIN32)
endif ()

include(GoogleTest)
gtest_discover_tests(test_dbc)


