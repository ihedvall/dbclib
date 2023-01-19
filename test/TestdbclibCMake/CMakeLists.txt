cmake_minimum_required(VERSION 3.20)
project(dbcLibExample
        VERSION 1.0
        DESCRIPTION "Test find_package dbclib"
        LANGUAGES CXX)

find_package(dbclib REQUIRED)

add_executable(TestMDFCMake ../../docs/dbclibexample.cpp)
target_link_libraries(TestMDFCMake Upstream::dbclib)
