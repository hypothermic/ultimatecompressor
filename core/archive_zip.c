#include "archive.h"

#include <glib.h>

#include "../deps-zip/zip.h"

#define CAST_ZIP(HANDLE) (struct zip_t *) HANDLE

void* uc_arc_zip_new(const gchar* path) {
    return zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
}

void* uc_arc_zip_open(const gchar* path) {
    return zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
}

void uc_arc_zip_close(ArchiveHandle handle) {
    zip_close(CAST_ZIP(handle));
}

void uc_arc_zip_write_file(ArchiveHandle handle, const gchar* file_path, const gchar* content) {
    zip_entry_open(CAST_ZIP(handle), file_path);
    zip_entry_write(CAST_ZIP(handle), content, strlen(content));
    zip_entry_close(CAST_ZIP(handle));
}

gboolean uc_arc_zip_is_supported() {
    return TRUE;
}