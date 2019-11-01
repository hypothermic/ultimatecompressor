#include <glib.h>

#include "../core/archive.h"

int main(int argc, char **argv) {
    g_print("TODO\n");

    uc_archive_t archive = s7z;
    const ArchiveFunc func = uc_archive_func_get(&archive);
    func(NULL);
}