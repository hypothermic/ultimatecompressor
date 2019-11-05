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

gboolean uc_arc_tar_extract(const gchar* path, const gchar* dest) {
    g_printerr(G_STRLOC "TODO");
    return FALSE;
}

void uc_arc_tar_write_file(ArchiveHandle handle, const gchar* file_path, const gchar* content) {
    g_printerr(G_STRLOC "TODO");
}

void uc_arc_tar_close(ArchiveHandle handle) {
    g_printerr(G_STRLOC "TODO");
}

gboolean uc_arc_tar_is_supported() {
    return FALSE;
}