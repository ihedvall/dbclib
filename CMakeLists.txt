# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(dbcLib
        VERSION 1.0
        DESCRIPTION "CAN DBC C++ library."
        LANGUAGES CXX)

option(CMAKE_SHARED_LIBS "Static libraries are preferred" OFF)
option(DBC_DOC "If doxygen is installed, then build documentation in Release mode" OFF)
option(DBC_TOOLS "Building applications" ON)
option(DBC_TEST "Building unit test" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX d)

include(CMakePrintHelpers)

if (DBC_TOOLS)
include(script/wxwidgets.cmake)
endif()

if (DBC_TEST)
include(script/googletest.cmake)
endif()

if (DBC_DOC)
include(script/doxygen.cmake)
endif()

include(script/flex.cmake)
include(script/bison.cmake)

if (BISON_FOUND)
    BISON_TARGET(DBC_PARSER src/dbcparser.y ${CMAKE_CURRENT_SOURCE_DIR}/src/dbcparser.cpp
            COMPILE_FLAGS "")
    cmake_print_variables(BISON_DBC_PARSER_DEFINED
            BISON_DBC_PARSER_INPUT
            BISON_DBC_PARSER_OUTPUT_SOURCE
            BISON_DBC_PARSER_OUTPUT_HEADER
            BISON_DBC_PARSER_OUTPUTS
            BISON_DBC_PARSER_COMPILE_FLAGS)
endif ()

if (FLEX_FOUND)
    FLEX_TARGET(DBC_SCANNER src/dbcflexer.l ${CMAKE_CURRENT_SOURCE_DIR}/src/dbcflexer.cpp)
    cmake_print_variables(FLEX_DBC_SCANNER_DEFINED
            FLEX_DBC_SCANNER_OUTPUTS
            FLEX_DBC_SCANNER_INPUT
            FLEX_DBC_SCANNER_OUTPUT_HEADER)
endif ()

ADD_FLEX_BISON_DEPENDENCY(DBC_SCANNER DBC_PARSER)

add_library(dbc STATIC
        ${BISON_DBC_PARSER_OUTPUTS}
        ${FLEX_DBC_SCANNER_OUTPUTS}
        src/attribute.cpp include/dbc/attribute.h
        src/network.cpp include/dbc/network.h
        src/envvar.cpp include/dbc/envvar.h
        src/node.cpp include/dbc/node.h
        src/message.cpp include/dbc/message.h
        src/signal.cpp include/dbc/signal.h
        src/signalgroup.cpp include/dbc/signalgroup.h
        src/dbcscanner.cpp src/dbcscanner.h
        src/dbcfile.cpp include/dbc/dbcfile.h
        src/dbchelper.cpp src/dbchelper.h src/dbcmessage.cpp include/dbc/dbcmessage.h include/dbc/isampleobserver.h src/signalobserver.cpp include/dbc/signalobserver.h)

target_include_directories(dbc PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
target_include_directories(dbc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# target_include_directories(dbc PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(dbc PRIVATE ${FLEX_INCLUDE_DIRS})

cmake_print_properties(TARGETS dbc PROPERTIES INCLUDE_DIRECTORIES)

if (MSVC)
    target_compile_definitions(dbc PRIVATE _WIN32_WINNT=0x0A00)
endif ()

# set(DBC_PUBLIC_HEADERS *** )

# set_target_properties(dbc PROPERTIES PUBLIC_HEADER "${DBCL_PUBLIC_HEADERS}")
# get_target_property(PH dbc PUBLIC_HEADER)
# message(STATUS "DBC Target Includes: " "${PH}")
if (DBC_TOOLS)
#    add_subdirectory(listend)
endif ()

if (wxWidgets_FOUND AND DBC_TOOLS)
    add_subdirectory(dbcviewer)
endif ()

if (GTEST_FOUND AND DBC_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()

if (DOXYGEN_FOUND AND (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease") AND DBC_DOC)
    set(DOXYGEN_RECURSIVE NO)
    set(DOXYGEN_REPEAT_BRIEF NO)
    set(DOXYGEN_PROJECT_NAME "DbcLib")
    set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen/dbclib.css)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/manual)
#    doxygen_add_docs(doc_libdbc ALL
#            include/dbc doxygen
#            COMMENT "DBC Library generating API documentation with Doxygen")
endif ()

if (WIN32)
    install(TARGETS dbc
            EXPORT dbcTargets
            LIBRARY DESTINATION dbc/lib
            ARCHIVE DESTINATION dbc/lib
            RUNTIME DESTINATION dbc/bin
            PUBLIC_HEADER DESTINATION dbc/include)
else()
    install(TARGETS dbc
            EXPORT dbcTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            PUBLIC_HEADER DESTINATION include/dbclib)
endif()

include(CMakePackageConfigHelpers)

set(CONFIG_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/dbc/dbcConfigVersion.cmake")
# generate *Version.cmake
write_basic_package_version_file(
        ${CONFIG_VERSION_FILE}
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion)

# Export dbcTargets to file *Targets.cmake
export(EXPORT dbcTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/libdbc/dbcTargets.cmake"
  NAMESPACE Upstream::
)

set(ConfigPackageLocation lib/cmake/dbc)
set(CONFIG_CMAKE "${CMAKE_CURRENT_BINARY_DIR}/dbc/dbcConfig.cmake")
# create final dbc *Config.make file
# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dbcConfig.cmake.in"
  ${CONFIG_CMAKE}
  INSTALL_DESTINATION ${ConfigPackageLocation}
)

# install *Targets.cmake
install(EXPORT dbcTargets
  FILE
    dbcTargets.cmake
  NAMESPACE
    Upstream::
  DESTINATION
    ${ConfigPackageLocation}
)

# Install *Version.cmake and *Config.cmake
install(
  FILES
    ${CONFIG_VERSION_FILE}
    ${CONFIG_CMAKE}
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
