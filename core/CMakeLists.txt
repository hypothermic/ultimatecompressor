configure_file("build.h.in" "build.h" @ONLY)

add_library(uccore build.h macro.h method.h method.c archive_zip.c archive.h)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(uccore PkgConfig::deps)