# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(MdfViewer
        VERSION 1.0
        DESCRIPTION "Simple DBC file browser"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include("../script/boost.cmake")
include("../script/utillib.cmake")
include("../script/mdflib.cmake")

add_executable(dbcview
        src/dbcviewer.cpp src/dbcviewer.h
        src/mainframe.cpp src/mainframe.h
        src/dbcdocument.cpp src/dbcdocument.h
        src/dbcview.cpp src/dbcview.h
        src/dbcviewer.rc
        src/childframe.cpp src/childframe.h
        src/windowid.h
        src/signalobserverlistview.cpp src/signalobserverlistview.h
        src/signalobserverframe.cpp src/signalobserverframe.h src/protocoldialog.cpp src/protocoldialog.h)


target_include_directories(dbcview PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_include_directories(dbcview PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(dbcview PRIVATE util)
target_include_directories(dbcview PRIVATE mdf)
target_include_directories(dbcview PRIVATE dbc)

target_compile_definitions(dbcview PRIVATE XML_STATIC)

if (MINGW)
target_link_options(dbcview PRIVATE -mwindows -static -fstack-protector)
endif()

if (MSVC)
target_link_options(dbcview PRIVATE /SUBSYSTEM:WINDOWS)
target_compile_definitions(dbcview PRIVATE _WIN32_WINNT=0x0A00)
endif()

target_link_libraries(dbcview PRIVATE dbc)
target_link_libraries(dbcview PRIVATE util)
if (MDFLIB_LOCAL_FETCH)
    target_link_libraries(dbcview PRIVATE mdf)
else()
    target_link_libraries(dbcview PRIVATE Upstream::mdf)
endif()
target_link_libraries(dbcview PRIVATE ${wxWidgets_LIBRARIES})
target_link_libraries(dbcview PRIVATE ${Boost_LIBRARIES})

if (MINGW)
    target_link_libraries(dbcview PRIVATE iconv)
endif()

if (WIN32)
target_link_libraries(dbcview PRIVATE bcrypt)
target_link_libraries(dbcview PRIVATE ws2_32)
endif()
