#include "archive.h"

#include <glib.h>

#include "../deps-zip/zip.h"

void* uc_arc_zip_new(gchar* path) {
    return zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
}

void* uc_arc_zip_open(gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void uc_arc_zip_close(void* handle) {
    g_printerr(G_STRLOC "TODO");
}

gboolean uc_arc_zip_is_supported() {
    return TRUE;
}