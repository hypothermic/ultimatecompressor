#include "archive.h"

#include <glib.h>

void* uc_arc_tar_new(const gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void* uc_arc_tar_open(const gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void uc_arc_tar_close(void* handle) {
    g_printerr(G_STRLOC "TODO");
}

void uc_arc_tar_write_file(void* handle, const gchar* file_path, const gchar* content) {
    g_printerr(G_STRLOC "TODO");
}

gboolean uc_arc_tar_is_supported() {
    return FALSE;
}