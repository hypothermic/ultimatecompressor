#add_subdirectory(../core ../lib_build)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/deps)
include(${CMAKE_SOURCE_DIR}/deps/ValaPrecompile.cmake)
include(${CMAKE_SOURCE_DIR}/deps/GLibProgramHandlers.cmake)

find_package(Vala REQUIRED)

glib_compile_resources(GLIB_RESOURCES_LIB
    source
        res.gresource.xml
)

vala_precompile(
    VALA_C
        Application.vala
        ArrayList.vala
        Callback.vala
        FileListBoxRow.vala
        Window.vala
    PACKAGES
        gtk+-3.0
        posix
    OPTIONS
        --thread
        --gresources=${CMAKE_CURRENT_SOURCE_DIR}/res.gresource.xml
#    CUSTOM_VAPIS
#        some_vapi.vapi
    GENERATE_VAPI
        ucvapi
    GENERATE_HEADER
        ucgui
)

add_executable(ucgui main.c ${VALA_C} ${GLIB_RESOURCES_LIB})
target_link_libraries(ucgui uccore)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(ucgui PkgConfig::deps)