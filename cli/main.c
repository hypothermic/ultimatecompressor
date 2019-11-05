#include <glib.h>

#include "../core/error.h"

#include "../core/archive.h"
#include "../core/mode.h"

#define __DEBUG__ TRUE

/**
 * Which mode to perform.<br />
 * Only a single one, and exactly one, of these must be true.
 */
static gboolean arg_compress   = FALSE,
                arg_decompress = FALSE;

static gchar** arg_input_file_array = NULL;
static gchar*  arg_output_file      = NULL;
static gchar*  arg_archive_format   = NULL;

static const GOptionEntry command_entries[] = {
        /* --- Mode; exactly one (1) of these must be used --- */
        {"compress",    'c', G_OPTION_FLAG_NONE,   G_OPTION_ARG_NONE,           &arg_compress,
                "Activates the compress mode", NULL},
        {"decompress",  'd', G_OPTION_FLAG_NONE,   G_OPTION_ARG_NONE,           &arg_decompress,
                "Activates the decompress mode", NULL},

        /* --- Mode options; these are required --- */
        {"input",       'i', G_OPTION_FLAG_NONE,   G_OPTION_ARG_FILENAME_ARRAY, &arg_input_file_array,
                "The files that will be copied into the output archive", NULL},
        {"output",      'o', G_OPTION_FLAG_NONE,   G_OPTION_ARG_FILENAME,       &arg_output_file,
                "Where to store the output archive", NULL},

        {"format",      'f', G_OPTION_FLAG_NONE,   G_OPTION_ARG_STRING,         &arg_archive_format,
                "Which archive format to use", NULL},

        {NULL}
};

int main(int argc, char **argv) {
    GError *error = NULL;
    GOptionContext *option_context;
    uc_archive_t format = _UC_ARCHIVE_MAX;

    g_print("\nUltimateCompressor CLI v%s build %s\n", UC_API_VERSION, UC_BUILD_VERSION);

#ifdef UC_DEBUG_ENABLED
    g_print("Debug mode is enabled. You may see detailed messages in stderr.\n\n");
#endif

    // Parse args
    option_context = g_option_context_new(NULL);
    g_option_context_add_main_entries(option_context, command_entries, NULL);
    if (!g_option_context_parse(option_context, &argc, &argv, &error)) {
        g_printerr("%s: %s\n", argv[0], error->message);
        return ERR_PARSE_OPTIONS;
    }
    g_option_context_free(option_context);

    // Check args
    if (!arg_input_file_array) {
        UC_QUIT_WITH_ERR(ERR_CAT_PARSING_ARGS, ERR_INPUT_UNSPECIFIED)
    }
    if (!arg_output_file) {
        UC_QUIT_WITH_ERR(ERR_CAT_PARSING_ARGS, ERR_OUTPUT_UNSPECIFIED)
    }
    if (!arg_archive_format) {
        UC_QUIT_WITH_VERR(ERR_CAT_PARSING_ARGS, ERR_FORMAT_UNSPECIFIED, "ZIP")
    }

    // If the archive format is found, check if format is not disabled
    FOR_EACH_ARCHIVE {
        if (strcmp(uc_archive_to_str(&archive), arg_archive_format) == 0) {
            if (uc_archive_get_func_is_supported(&archive)()) {
                format = archive;
            } else {
                UC_QUIT_WITH_VERR(ERR_CAT_PARSING_ARGS, ERR_FORMAT_NOT_SUPPORTED, uc_archive_to_str(&archive))
            }
        }
    }

    // If the archive format is not found, quit
    if (!format || format == _UC_ARCHIVE_MAX) {
        UC_QUIT_WITH_VERR(ERR_CAT_PARSING_ARGS, ERR_FORMAT_NOT_FOUND, arg_archive_format)
    }

    // If no modes are specified, quit
    // If more than 1 mode is specified, quit
    if (arg_compress == arg_decompress) {
        UC_QUIT_WITH_ERR(ERR_CAT_PARSING_ARGS, ERR_MODE_NOT_SPECIFIED)
    }

    // TODO un-hardcode in case we get more modes
    uc_mode_t mode = COMPRESS;
    if (arg_decompress) {
        mode = DECOMPRESS;
    }

    uc_mode_func_perform(&mode)((const gchar **) arg_input_file_array, arg_output_file, &format);

    // For good measure...
    if (error != NULL) {
        g_error_free(error);
    }
    g_strfreev(arg_input_file_array);
    g_free(arg_output_file);
    g_free(arg_archive_format);

    UC_QUIT_GRACEFUL()
}