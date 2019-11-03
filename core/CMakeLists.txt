add_library(uccore build.h macro.h method.h method.c archive.h archive_s7z.c archive_zip.c archive_tar.c archive_rar.c build.h mode.c mode.h mode_compress.c mode_decompress.c)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(uccore PkgConfig::deps)