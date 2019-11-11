#add_subdirectory(../core ../lib_build)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/deps)
include(${CMAKE_SOURCE_DIR}/deps/ValaPrecompile.cmake)
include(${CMAKE_SOURCE_DIR}/deps/GLibProgramHandlers.cmake)

find_package(Vala REQUIRED)

glib_compile_resources(GLIB_RESOURCES_LIB
    source
        window.gresource.xml
)

glib_compile_resources(RESOURCE_DIALOG_FORMAT
    source
        dialog_format.gresource.xml
)

vala_precompile(
    VALA_C VALA_PRECOMPILE_TARGET
        AbstractDialog.vala
        Action.vala
        Archive.vala
        ArrayList.vala
        Callback.vala
        DialogAction.vala
        FileListBoxRow.vala
        FormatDialog.vala
        UltimateCompressor.vala
        Window.vala
    PACKAGES
        gtk+-3.0
        posix
    OPTIONS
        --thread
        --enable-experimental-non-null
        --gresources=${CMAKE_CURRENT_SOURCE_DIR}/window.gresource.xml
        --gresources=${CMAKE_CURRENT_SOURCE_DIR}/dialog_format.gresource.xml
#    CUSTOM_VAPIS
#        some_vapi.vapi
    GENERATE_VAPI
        ucvapi
    GENERATE_HEADER
        ucgui
)

add_executable(ucgui main.c ${VALA_C} ${GLIB_RESOURCES_LIB} ${RESOURCE_DIALOG_FORMAT})
target_link_libraries(ucgui uccore)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(ucgui PkgConfig::deps)