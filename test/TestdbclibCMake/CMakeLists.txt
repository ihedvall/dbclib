cmake_minimum_required(VERSION 3.20)
project(dbcLibExample
        VERSION 1.0
        DESCRIPTION "Test find_package dbclib"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(dbc REQUIRED)

add_executable(TestdbcCMake ${CMAKE_CURRENT_SOURCE_DIR}/../../docs/dbclibexample.cpp)
target_compile_definitions(TestdbcCMake PRIVATE DBC_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../docs/example.dbc")
target_link_libraries(TestdbcCMake Dbc::dbc)
