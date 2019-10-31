#include "method.h"

#include "archive.h"

typedef guchar* (*ArchiveFunc)(guchar*);

static const char* _uc_archive_str[] = {
        FOREACH_ARCHIVE(GENERATE_STRING)
};

static const ArchiveFunc _arc_func_ptrs[] = {
        uc_arc_zip
};

const gchar* uc_archive_to_str(const uc_archive_t* method) {
    return _uc_archive_str[*method];
}