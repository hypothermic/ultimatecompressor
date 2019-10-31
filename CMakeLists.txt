cmake_minimum_required(VERSION 3.13)
project(ultimatecompressor C)

set(CMAKE_C_STANDARD 11)

set(PROJECT_WEB "https://github.com/hypothermic/ultimatecompressor")
set(PROJECT_BUGS "https://github.com/hypothermic/ultimatecompressor")
set(GETTEXT_PACKAGE ${PROJECT_NAME})
set(UC_VERSION_MAJOR 1)
set(UC_VERSION_MINOR 0)
set(UC_VERSION_REVISION 0)
set(UC_VERSION_API "1.0")

option(BUILD_CLI "Whether to build the CLI executable (uc) or not." ON)
option(BUILD_GUI "Whether to build the GUI application or not."     ON)

# Always build the core
add_subdirectory(core)

# If desired, build the executable
if(BUILD_CLI)
    add_subdirectory(cli)
endif()

# If desired, build the GUI
#if(BUILD_GUI)
#    add_subdirectory(gui)
#endif()