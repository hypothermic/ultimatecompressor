#include "method.h"

#include "archive.h"

static const char* _uc_arc_str[] = {
        FOREACH_ARCHIVE(GENERATE_STRING)
};

static const ArchiveFunc _uc_arc_func_ptrs[] = {
        FOREACH_ARCHIVE(GENERATE_FUNC_ENUM)
};

const ArchiveFunc uc_archive_func_get(const uc_archive_t* method) {
    return _uc_arc_func_ptrs[*method];
}

const gchar* uc_archive_to_str(const uc_archive_t* method) {
    return _uc_arc_str[*method];
}