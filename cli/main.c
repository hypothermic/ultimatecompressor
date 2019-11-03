#include <glib.h>

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
        return 1;
    }
    g_option_context_free(option_context);

    // Check args
    if (!arg_input_file_array) {
        g_printerr("%s: %s \n", "Error while parsing arguments", "Input files not specified");
        return 2;
    }
    if (!arg_output_file) {
        g_printerr("%s: %s \n", "Error while parsing arguments", "Output path not specified");
        return 3;
    }
    if (!arg_archive_format) {
        g_printerr("%s: %s \n", "Error while parsing arguments", "Archive format not specified");
        return 4;
    }

    FOR_EACH_ARCHIVE {
        if (strcmp(uc_archive_to_str(&archive), arg_archive_format) == 0) {
            if (uc_archive_get_func_is_supported(&archive)()) {
                format = archive;
            } else {
                g_printerr("%s: %s %s \n", "Error while parsing arguments", uc_archive_to_str(&archive), "archive format is not supported");
                return 5;
            }
        }
    }

    if (!format || format == _UC_ARCHIVE_MAX) {
        g_printerr("%s: %s \"%s\"\n", "Error while parsing arguments", "No format matching", arg_archive_format);
        return 6;
    }

    // For good measure...
    g_error_free(error);
    g_strfreev(arg_input_file_array);
    g_free(arg_output_file);
    g_free(arg_archive_format);
}