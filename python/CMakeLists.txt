# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # optional, ensure standard is supported
set(CMAKE_CXX_EXTENSIONS OFF)  # optional, keep compiler extensions off
set(CMAKE_DEBUG_POSTFIX "") # The import lib function doesn't accept the 'd' pos fix


cmake_print_properties(TARGETS Pytest::Pytest PROPERTIES
        NAME
        LOCATION)

cmake_print_properties(TARGETS pybind11::headers PROPERTIES
        NAME
        LOCATION
        INTERFACE_INCLUDE_DIRECTORIES
)
cmake_print_variables(pybind11_INCLUDE_DIRECTORIES)

project(pydbc_lib
        VERSION 1.0
        DESCRIPTION "CAN DBC Python Module."
        LANGUAGES CXX)


pybind11_add_module( pydbc MODULE
        src/pydbcmessage.cpp
        src/pyattribute.cpp
        src/pyenvvar.cpp
        src/pysignal.cpp
        src/pymessage.cpp
        src/pynode.cpp
        src/pynetwork.cpp
        src/pysignalgroup.cpp
        src/pydbcfile.cpp
        src/pysignalobserver.cpp
        src/pydbc.cpp src/pydbc.h )

cmake_print_variables(CMAKE_SOURCE_DIR)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
cmake_print_variables(CMAKE_BINARY_DIR)
cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
cmake_print_variables(Python3_EXECUTABLE)

target_include_directories(pydbc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(pydbc PRIVATE ${CMAKE_SOURCE_DIR}/extern/pybind11/include)

target_link_libraries(pydbc PRIVATE dbc)

cmake_print_properties(TARGETS pydbc PROPERTIES
        NAME
        INCLUDE_DIRECTORIES
)

if (DBC_TEST)

    # Need to copy the pyd modules to the virtual environment
    # so the CLION can handle the pytest properly
    file(GLOB module_files CONFIGURE_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/pydbc.* )

    foreach (pyfile ${module_files})
        add_custom_command(
                TARGET pydbc
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ARGS ${pyfile} "${CMAKE_SOURCE_DIR}/venv/Lib/site-packages"
        )
    endforeach ()


    # Add the test to the CTest. The pyd module is in the current binary dir,
    # so the pytest should run.
    enable_testing()
    add_test(NAME pydbc_test
            COMMAND ${Python3_EXECUTABLE} -m pytest --log-cli-level=0 ${CMAKE_CURRENT_SOURCE_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

    )

endif()