#include <glib/gstdio.h>
#include <fcntl.h>

#ifndef ERR_NONE
#include "error.h"
#endif

#include "mode.h"

gboolean uc_mode_DECOMPRESS_perform(const gchar** input_files, const gchar* output_destination, const uc_archive_t* format) {
    // Check if output file already exists; do not overwrite
    VPRINT_DEBUG("Checking if location \"%s\" is valid", output_destination);
    if (g_access(output_destination, O_RDONLY) == 0) {
        // Warn the user, don't quit.
        UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_DESTINATION_EXISTS, output_destination)
    }

    // Loop over each input file
    for (int i = 0; input_files[i]; i++) {
        const gchar* input_file = input_files[i];

        // If file doesn't exist or user doesn't have permission to read file
        VPRINT_DEBUG("Checking read access for input file \"%s\"", input_file);
        if (g_access(input_file, O_RDONLY) != 0) {
            UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_FILE_NOT_READABLE, input_file)
            break;
        }

        VPRINT_DEBUG("Extracting file \"%s\" into folder \"%s\"", input_file, output_destination);
        uc_archive_get_func_extract(format)(input_file, output_destination);

        VPRINT_DEBUG("Finished processing file \"%s\"\n", input_file);
    }

    // Free the archive struct
    VPRINT_DEBUG("Finished decompressing archive(s) to location \"%s\"\n", output_destination);

    return TRUE;
}