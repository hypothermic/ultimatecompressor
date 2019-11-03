#ifndef MAGTUBE_MACRO_H
#define MAGTUBE_MACRO_H

#define GENERATE_STRING(NAME) #NAME,
#define GENERATE_ENUM(NAME) NAME,

#define GENERATE_FUNC_ENUM(NAME)  \
         uc_arc_ ## NAME,

#define GENERATE_FUNC_NEW_ENUM(NAME)  \
         uc_arc_ ## NAME ## _new,

#define GENERATE_FUNC_NEW(NAME) \
        void* uc_arc_ ## NAME ## _new (gchar* path);

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

#endif //MAGTUBE_MACRO_H
