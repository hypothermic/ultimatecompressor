#add_subdirectory(../core ../lib_build)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/deps)
include(${CMAKE_SOURCE_DIR}/deps/ValaPrecompile.cmake)

find_package(Vala REQUIRED)

#list(APPEND VALA_COMPILER_FLAGS "--gresources=${CMAKE_CURRENT_SOURCE_DIR}/res.gresource.xml")

vala_precompile(
    VALA_C
        Application.vala
        Window.vala
    PACKAGES
        gtk+-3.0
        posix
    OPTIONS
        --thread
        --gresources=${CMAKE_CURRENT_SOURCE_DIR}/res.gresource.xml
        --gresourcesdir=${CMAKE_CURRENT_SOURCE_DIR}/gui
#    CUSTOM_VAPIS
#        some_vapi.vapi
#    GENERATE_VAPI
#        myvapi
#    GENERATE_HEADER
#        myheader
)

add_executable(ucgui main.c ${VALA_C})
target_link_libraries(ucgui uccore)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(ucgui PkgConfig::deps)

target_link_libraries(ucgui Vala)