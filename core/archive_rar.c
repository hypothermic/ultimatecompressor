#include "archive.h"

#include <glib.h>

void* uc_arc_rar_new(gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void* uc_arc_rar_open(gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void uc_arc_rar_close(void* handle) {
    g_printerr(G_STRLOC "TODO");
}

void uc_arc_rar_write_file(void* handle, const gchar* file_path, const gchar* content) {
    g_printerr(G_STRLOC "TODO");
}

gboolean uc_arc_rar_is_supported() {
    return FALSE;
}