#include "archive.h"

#include <glib.h>

#include "../deps-zip/zip.h"

void* uc_arc_zip_new(gchar* path) {
    return zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
}

void* uc_arc_zip_open(gchar* path) {
    return zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
}

void uc_arc_zip_close(void* handle) {
    zip_close(handle);
}

void uc_arc_zip_write_file(void* handle, const gchar* file_path, const gchar* content) {
    zip_entry_open(handle, file_path);
    zip_entry_write(handle, content, strlen(content));
    zip_entry_close(handle);
}

gboolean uc_arc_zip_is_supported() {
    return TRUE;
}