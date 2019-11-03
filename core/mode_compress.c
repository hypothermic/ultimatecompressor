#include <glib/gstdio.h>
#include <fcntl.h>
#include "mode.h"

gboolean uc_mode_COMPRESS_perform(gchar** input_files, gsize input_files_len, gchar* output_destination, uc_archive_t* format) {
    // Loop over each input file
    for (gchar** pargv = input_files; *pargv != input_files[input_files_len]; pargv++) {
        g_print("> Processing input file \"%s\"\n", *pargv);

        // If file doesn't exist or user doesn't have permission to read file
        if (g_access(*pargv, O_RDONLY) != 0) {
            g_print("  - error: unable to read file \"%s\"\n", *pargv);
            break;
        }

        gsize length;
        gchar* content;
        if (!g_file_get_contents(*pargv, &content, &length, NULL)) {
            g_print("  - error: while reading file \"%s\"\n", *pargv);
            break;
        }

        //parse_raw(content);
        g_free(content);
        g_print("  - finished\n\n");
    }
}