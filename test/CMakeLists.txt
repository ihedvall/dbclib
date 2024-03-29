# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT

project(TestDbc
        VERSION 1.0
        DESCRIPTION "Google unit tests for the DBC library"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(test_dbc
        testread.cpp testread.h
        test_dbchelper.cpp)

target_include_directories(test_dbc PRIVATE
        ../src )

if (MINGW)
    target_link_options(test_dbc PRIVATE -static -fstack-protector)
elseif (MSVC)
    target_compile_definitions(test_dbc PRIVATE -D_WIN32_WINNT=0x0A00)
endif ()

target_link_libraries(test_dbc PRIVATE dbc)
target_link_libraries(test_dbc PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_dbc)


