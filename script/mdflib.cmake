find_package(MdfLib)
if (NOT MdfLib_FOUND)
    include (FetchContent)
    FetchContent_Declare(mdflib
            GIT_REPOSITORY https://github.com/ihedvall/mdflib.git
            GIT_TAG HEAD)
    set(MDF_BUILD_DOC OFF)
    set(MDF_BUILD_TEST OFF)
    set(MDF_BUILD_TOOLS OFF)
    set(MDF_BUILD_SHARED_LIB OFF)
    set(MDF_BUILD_SHARED_LIB_NET OFF)
    set(MDF_BUILD_SHARED_LIB_EXAMPLE OFF)
    FetchContent_MakeAvailable(mdflib)

    message(STATUS "MDFLIB Populated: " ${mdflib_POPULATED})
    message(STATUS "MDFLIB Source Dir: " ${mdflib_SOURCE_DIR})
    message(STATUS "MDFLIB Binary Dir: " ${mdflib_BINARY_DIR})
    set(MDFLIB_LOCAL_FETCH 1)
endif()
