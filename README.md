# DBC Library version 1.0

## Summary

The DBC library repository include a **C++ Library** that parses CAN database files (DBC) and a simple **DBC
Viewer**. The release 1.0 of the project support reading of DBC file. The DBC viewer can also read in MDF
CAN logger files and view its data.

## Building

The project uses CMAKE for building. The following third-party libraries are used and
needs to be downloaded and pre-built. 

- Boost Library. Required for the GUI applications.
- Flex and Bison. Required for the C++ library.
- WxWidgets Library. Required if the GUI applications should be built.
- Doxygen's application. Is required if the documentation should be built.
- Google Test Library. Is required for running and build the unit tests.

## License

The project uses the MIT license. See external LICENSE file in project root.
