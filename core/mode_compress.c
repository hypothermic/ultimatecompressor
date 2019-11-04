#include <glib/gstdio.h>
#include <fcntl.h>

#ifndef ERR_NONE
#include "error.h"
#endif

#include "mode.h"

gboolean uc_mode_COMPRESS_perform(gchar** input_files, gsize input_files_len, gchar* output_destination, uc_archive_t* format) {
    // Loop over each input file
    for (int i = 0; input_files[i]; i++) {
        gchar* input_file = input_files[i];
        VPRINT_DEBUG(G_STRLOC ": Processing input file \"%s\"\n", input_file);

        // If file doesn't exist or user doesn't have permission to read file
        if (g_access(input_file, O_RDONLY) != 0) {
            UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_FILE_NOT_READABLE, input_file);
            break;
        }

        // Read file into byte array
        gsize length;
        gchar* content;
        if (!g_file_get_contents(input_file, &content, &length, NULL)) {
            UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_FILE_READ_FAILED, input_file);
            break;
        }

        //parse_raw(content);

        g_free(content);
        PRINT_DEBUG(G_STRLOC ": finished\n\n");
    }
    return TRUE;
}