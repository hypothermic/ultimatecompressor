#ifndef MAGTUBE_MACRO_H
#define MAGTUBE_MACRO_H

// Include build.h for reading UC_DEBUG_ENABLED
#include "build.h"

#define GENERATE_STRING(NAME) #NAME,
#define GENERATE_ENUM(NAME) NAME,

#define GENERATE_CONSTANT_INT(VALUE, NAME, ...) \
        const int NAME = VALUE ;

#define GENERATE_EXTERN_CONSTANT_INT(UNUSED, NAME, ...) \
        extern const int NAME ;

#define GENERATE_CONSTANT_STRING(UNUSED, NAME, VALUE, ...) \
        const gchar* NAME ## _STR = #VALUE ;

#define GENERATE_EXTERN_CONSTANT_STRING(UNUSED, NAME, ...) \
        extern const gchar* NAME ## _STR ;

#define GENERATE_FUNC_ENUM(NAME)  \
        uc_arc_ ## NAME,

#define GENERATE_FUNC_NEW_ENUM(NAME)  \
        uc_arc_ ## NAME ## _new,

#define GENERATE_FUNC_NEW(NAME) \
        ArchiveHandle uc_arc_ ## NAME ## _new (const gchar* path);

#define GENERATE_FUNC_OPEN_ENUM(NAME)  \
        uc_arc_ ## NAME ## _open,

#define GENERATE_FUNC_OPEN(NAME) \
        ArchiveHandle uc_arc_ ## NAME ## _open (const gchar* path);

#define GENERATE_FUNC_CLOSE_ENUM(NAME)  \
        uc_arc_ ## NAME ## _close,

#define GENERATE_FUNC_CLOSE(NAME) \
        void uc_arc_ ## NAME ## _close (ArchiveHandle handle);

#define GENERATE_FUNC_WRITEFILE_ENUM(NAME)  \
        uc_arc_ ## NAME ## _write_file,

#define GENERATE_FUNC_WRITEFILE(NAME) \
        void uc_arc_ ## NAME ## _write_file (ArchiveHandle handle, const gchar* file_path, const gchar* content);

#define GENERATE_FUNC_IS_SUPPORTED(NAME) \
        gboolean uc_arc_ ## NAME ## _is_supported ();

#define GENERATE_FUNC_IS_SUPPORTED_ENUM(NAME)  \
        uc_arc_ ## NAME ## _is_supported,

#define GENERATE_FUNC_MODE_PERFORM(NAME) \
        gboolean uc_mode_ ## NAME ## _perform (gchar** input_files, gsize input_files_len, gchar* output_destination, uc_archive_t* format);

#define GENERATE_FUNC_MODE_PERFORM_ENUM(NAME) \
        uc_mode_ ## NAME ## _perform,

#define GENERATE_SWITCH(NAME) \
        case ## NAME: ## return [NAME]; break;

#ifdef UC_DEBUG_ENABLED

#define PRINT_DEBUG(MESSAGE) \
        g_printerr(G_STRLOC ": " MESSAGE "\n");

#define VPRINT_DEBUG(MESSAGE, ...) \
        g_printerr(G_STRLOC ": " MESSAGE "\n", __VA_ARGS__);

#else

#define PRINT_DEBUG(MESSAGE)
#define VPRINT_DEBUG(MESSAGE, ...)

#endif

#endif //MAGTUBE_MACRO_H
