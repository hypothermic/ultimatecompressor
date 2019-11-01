#add_subdirectory(../core ../lib_build)

add_executable(uccli main.c)
target_link_libraries(uccli uccore)

# GNOME libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtk+-3.0)
target_link_libraries(uccli PkgConfig::deps)