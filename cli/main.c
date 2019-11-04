#include <glib.h>

#include "error.h"

#include "../core/archive.h"
#include "../core/mode.h"

static gchar** arg_input_file_array;
static gchar*  arg_output_file;
static gchar*  arg_archive_format;

static const GOptionEntry command_entries[] = {
        {"input",       'i', G_OPTION_FLAG_NONE, G_OPTION_ARG_FILENAME_ARRAY, &arg_input_file_array,
                "The files that will be copied into the output archive", NULL},
        {"output",      'o', G_OPTION_FLAG_NONE, G_OPTION_ARG_FILENAME,       &arg_output_file,
                "Where to store the output archive", NULL},

        {"format",      'f', G_OPTION_FLAG_NONE, G_OPTION_ARG_STRING,         &arg_archive_format,
                "Which archive format to use", NULL},

        {NULL}
};

int main(int argc, char **argv) {
    GError *error = NULL;
    GOptionContext *option_context;
    uc_archive_t format = _UC_ARCHIVE_MAX;

    g_print("\nUltimateCompressor CLI v%s build %s\n", UC_API_VERSION, UC_BUILD_VERSION);

    // Parse args
    option_context = g_option_context_new("Main Arguments");
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

    // TODO do stuff here

    // For good measure...
    if (error != NULL) {
        g_error_free(error);
    }
    g_strfreev(arg_input_file_array);
    g_free(arg_output_file);
    g_free(arg_archive_format);

    UC_QUIT_GRACEFUL()
}