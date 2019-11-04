#include "archive.h"

#include <glib.h>

void* uc_arc_s7z_new(gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void* uc_arc_s7z_open(gchar* path) {
    g_printerr(G_STRLOC "TODO");
    return NULL;
}

void uc_arc_s7z_close(void* handle) {
    g_printerr(G_STRLOC "TODO");
}

gboolean uc_arc_s7z_is_supported() {
    return FALSE;
}