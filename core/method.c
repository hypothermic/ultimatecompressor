#include "method.h"

#include "archive.h"

// TODO use macros for this........

static const char* _uc_arc_str[] = {
        FOREACH_ARCHIVE(GENERATE_STRING)
};

static const NewArchiveFunc _uc_arc_func_new_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_NEW_ENUM)
};

static const ExtractArchiveFunc _uc_arc_func_extract_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_EXTRACT_ENUM)
};

static const IsSupportedFunc _uc_arc_func_is_supported_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_IS_SUPPORTED_ENUM)
};

static const OpenArchiveFunc _uc_arc_func_open_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_OPEN_ENUM)
};

static const CloseArchiveFunc _uc_arc_func_close_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_CLOSE_ENUM)
};

static const WriteToFileArchiveFunc _uc_arc_func_write_file_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_WRITEFILE_ENUM)
};

const NewArchiveFunc uc_archive_get_func_new(const uc_archive_t* method) {
    return _uc_arc_func_new_ptrs[*method];
}

const OpenArchiveFunc uc_archive_get_func_open(const uc_archive_t* method) {
    return _uc_arc_func_open_ptrs[*method];
}

const ExtractArchiveFunc uc_archive_get_func_extract(const uc_archive_t* method) {
    return _uc_arc_func_extract_ptrs[*method];
}

const CloseArchiveFunc uc_archive_get_func_close(const uc_archive_t* method) {
    return _uc_arc_func_close_ptrs[*method];
}

const WriteToFileArchiveFunc uc_archive_get_func_write_file(const uc_archive_t* method) {
    return _uc_arc_func_write_file_ptrs[*method];
}

const IsSupportedFunc uc_archive_get_func_is_supported(const uc_archive_t* method) {
    return _uc_arc_func_is_supported_ptrs[*method];
}

const gchar* uc_archive_to_str(const uc_archive_t* method) {
    return _uc_arc_str[*method];
}