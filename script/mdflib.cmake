include (FetchContent)
FetchContent_Declare(mdflib
        GIT_REPOSITORY https://github.com/ihedvall/mdflib.git
        GIT_TAG HEAD)
set(MDF_DOC OFF)
set(MDF_TEST OFF)
set(MDF_TOOLS OFF)
FetchContent_MakeAvailable(mdflib)

message(STATUS "MDFLIB Populated: " ${mdflib_POPULATED})
message(STATUS "MDFLIB Source Dir: " ${mdflib_SOURCE_DIR})
message(STATUS "MDFLIB Binary Dir: " ${mdflib_BINARY_DIR})