#include <glib/gstdio.h>
#include <fcntl.h>

#ifndef ERR_NONE
#include "error.h"
#endif

#include "mode.h"

gboolean uc_mode_COMPRESS_perform(const gchar** input_files, const gchar* output_destination, const uc_archive_t* format) {
    // Check if output file already exists; do not overwrite
    VPRINT_DEBUG("Checking if location \"%s\" is valid", output_destination);
    if (g_access(output_destination, O_RDONLY) == 0) {
        UC_QUIT_WITH_VERR(ERR_CAT_PERFORM_MODE, ERR_DESTINATION_EXISTS, output_destination)
    }

    // Create a new archive for writing into
    VPRINT_DEBUG("Creating new \"%s\" archive at location \"%s\"\n", uc_archive_to_str(format), output_destination);
    ArchiveHandle archive_handle = uc_archive_get_func_new(format)(output_destination);

    // Loop over each input file
    for (int i = 0; input_files[i]; i++) {
        const gchar* input_file = input_files[i];

        // If file doesn't exist or user doesn't have permission to read file
        VPRINT_DEBUG("Checking read access for input file \"%s\"", input_file);
        if (g_access(input_file, O_RDONLY) != 0) {
            UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_FILE_NOT_READABLE, input_file)
            break;
        }

        // Read file into byte array
        gsize length;
        gchar* content;
        VPRINT_DEBUG("Reading input file \"%s\"", input_file);
        if (!g_file_get_contents(input_file, &content, &length, NULL)) {
            UC_VPRINTERR(ERR_CAT_PERFORM_MODE, ERR_FILE_READ_FAILED, input_file)
            break;
        }

        VPRINT_DEBUG("Writing file \"%s\" into archive \"%s\"", input_file, output_destination);
        uc_archive_get_func_write_file(format)(archive_handle, input_file, content);

        g_free(content);
        VPRINT_DEBUG("Finished processing file \"%s\"\n", input_file);
    }

    // Free the archive struct
    VPRINT_DEBUG("Closing \"%s\" archive at location \"%s\"\n", uc_archive_to_str(format), output_destination);
    uc_archive_get_func_close(format)(archive_handle);

    return TRUE;
}