#include "method.h"

#include "archive.h"

static const char* _uc_arc_str[] = {
        FOREACH_ARCHIVE(GENERATE_STRING)
};

static const NewArchiveFunc _uc_arc_func_new_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_NEW_ENUM)
};

static const IsSupportedFunc _uc_arc_func_is_supported_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_IS_SUPPORTED_ENUM)
};

const NewArchiveFunc uc_archive_get_func_new(const uc_archive_t* method) {
    return _uc_arc_func_new_ptrs[*method];
}

const IsSupportedFunc uc_archive_get_func_is_supported(const uc_archive_t* method) {
    return _uc_arc_func_is_supported_ptrs[*method];
}

const gchar* uc_archive_to_str(const uc_archive_t* method) {
    return _uc_arc_str[*method];
}