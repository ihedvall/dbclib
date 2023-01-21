cmake_minimum_required(VERSION 3.20)
project(dbcLibExample
        VERSION 1.0
        DESCRIPTION "Test find_package dbclib"
        LANGUAGES CXX)

find_package(dbc REQUIRED)

set(EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../docs)

add_executable(TestdbcCMake ${EXAMPLE_PATH}/dbclibexample.cpp)
target_compile_definitions(TestdbcCMake ${EXAMPLE_PATH}/example.dbc)
target_link_libraries(TestdbcCMake Upstream::dbclib)
