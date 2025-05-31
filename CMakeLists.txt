# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
include(CMakePrintHelpers)

if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    set(USE_VCPKG OFF)
else()
    set(USE_VCPKG ON)
endif()

option(BUILD_SHARED_LIBS "Static libraries are preferred" OFF)
option(DBC_DOC "If doxygen is installed, then build documentation in Release mode" OFF)
option(DBC_TOOLS "Building applications" OFF)
option(DBC_TEST "Building unit test" ON)
option(DBC_PYTHON "Building Python module" OFF)
option(DBC_FLEX "Building Flex and Bison source code" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(DBC_TEST AND USE_VCPKG)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()


project(dbclib
        VERSION 1.0
        DESCRIPTION "CAN DBC C++ library."
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)

if (DBC_TOOLS)
    include(script/boost.cmake)
    include(script/zlib.cmake)
    include(script/utillib.cmake)
    include(script/mdflib.cmake)
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

if (BISON_FOUND AND DBC_FLEX)
    BISON_TARGET(DBC_PARSER src/dbcparser.y ${CMAKE_CURRENT_SOURCE_DIR}/src/dbcparser.cpp
            COMPILE_FLAGS "")
    cmake_print_variables(BISON_DBC_PARSER_DEFINED
            BISON_DBC_PARSER_INPUT
            BISON_DBC_PARSER_OUTPUT_SOURCE
            BISON_DBC_PARSER_OUTPUT_HEADER
            BISON_DBC_PARSER_OUTPUTS
            BISON_DBC_PARSER_COMPILE_FLAGS
            BISON_INCLUDE_DIRS)
endif ()

if (FLEX_FOUND AND DBC_FLEX)
    FLEX_TARGET(DBC_SCANNER src/dbcflexer.l ${CMAKE_CURRENT_SOURCE_DIR}/src/dbcflexer.cpp)
    cmake_print_variables(FLEX_DBC_SCANNER_DEFINED
            FLEX_DBC_SCANNER_OUTPUTS
            FLEX_DBC_SCANNER_INPUT
            FLEX_DBC_SCANNER_OUTPUT_HEADER
            FLEX_INCLUDE_DIRS)
    # Copy FlexLexer.h. This is a dirty trick to avoid flex/bison installation in windows build
    file(COPY_FILE ${FLEX_INCLUDE_DIRS}/FlexLexer.h ${CMAKE_CURRENT_SOURCE_DIR}/src/FlexLexer.h)
endif ()

if (FLEX_FOUND AND BISON_FOUND AND DBC_FLEX)
    ADD_FLEX_BISON_DEPENDENCY(DBC_SCANNER DBC_PARSER)
endif()

set(DBC_HEADERS
    include/dbc/attribute.h
    include/dbc/dbcfile.h
    include/dbc/dbcmessage.h
    include/dbc/envvar.h
    include/dbc/isampleobserver.h
    include/dbc/message.h
    include/dbc/network.h
    include/dbc/node.h
    include/dbc/signal.h
    include/dbc/signalgroup.h
    include/dbc/signalobserver.h
)

add_library(dbc
        src/dbcparser.cpp src/dbcparser.hpp
        src/FlexLexer.h src/dbcflexer.cpp
        ${DBC_HEADERS}
        src/attribute.cpp
        src/network.cpp
        src/envvar.cpp
        src/node.cpp
        src/message.cpp
        src/signal.cpp
        src/signalgroup.cpp
        src/dbcscanner.cpp src/dbcscanner.h
        src/dbcfile.cpp
        src/dbchelper.cpp src/dbchelper.h
        src/dbcmessage.cpp include/dbc/dbcmessage.h
        include/dbc/isampleobserver.h
        src/signalobserver.cpp include/dbc/signalobserver.h)

target_include_directories(dbc PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
       )
target_include_directories(dbc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

cmake_print_properties(TARGETS dbc PROPERTIES INCLUDE_DIRECTORIES)

if (MSVC)
    target_compile_definitions(dbc PRIVATE _WIN32_WINNT=0x0A00)
endif ()

if (DBC_PYTHON)
    find_package(Python3 COMPONENTS Interpreter Development)
    cmake_print_properties(TARGETS Python3::Python PROPERTIES
            NAME
            LOCATION
            INTERFACE_INCLUDE_DIRECTORIES)

    cmake_print_variables(
            Python3_FOUND
            Python3_INCLUDE_DIRS
            Python3_RUNTIME_LIBRARY_DIRS)

    add_subdirectory(extern/pybind11)
    add_subdirectory(python)
endif()

if (wxWidgets_FOUND AND DBC_TOOLS)
    add_subdirectory(dbcviewer)
endif ()

if (DBC_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()

if (DOXYGEN_FOUND AND (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease") AND DBC_DOC)
    set(DOXYGEN_RECURSIVE NO)
    set(DOXYGEN_REPEAT_BRIEF NO)
    set(DOXYGEN_PROJECT_NAME "DbcLib")
    set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen/dbclib.css)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/manual)
    doxygen_add_docs(doc_libdbc ALL
            include/dbc doxygen
            COMMENT "DBC Library generating API documentation with Doxygen")
endif ()


##################################################################################
#####  Packaging and installation  ###############################################
##################################################################################
# install headers
# FILE_SET makes problems with GTest
#if (${CMAKE_MINOR_VERSION} GREATER_EQUAL 23)
#    target_sources(dbc PUBLIC
#                        FILE_SET HEADERS
#                        TYPE HEADERS
#                        BASE_DIRS include/dbc
#                        FILES ${HEADERS})
#else()
    if (WIN32)
        install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/dbc DESTINATION dbc/include)
    else()
        install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/dbc DESTINATION include)
    endif()
#endif()

if (WIN32)
    install(TARGETS dbc
            EXPORT dbcTargets
            LIBRARY DESTINATION dbc/lib
            ARCHIVE DESTINATION dbc/lib
            RUNTIME DESTINATION dbc/bin
#            FILE_SET HEADERS DESTINATION dbc/include
    )
else()
    install(TARGETS dbc
            EXPORT dbcTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
#            PUBLIC_HEADER
#            FILE_SET HEADERS DESTINATION include/dbc
        )
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
    Dbc::
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
