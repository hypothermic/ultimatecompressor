#ifndef ULTIMATECOMPRESSOR_METHOD_H
#define ULTIMATECOMPRESSOR_METHOD_H

#include <glib.h>

#include "macro.h"

#ifndef ArchiveHandle
typedef void* ArchiveHandle;
#endif

/**
 * Creates a new archive at <i>path</i>.
 *
 * @param path Absolute path to the new archive
 * @returns pointer to the implementation-dependant structure. TODO make generic structure
 */
typedef const ArchiveHandle (*NewArchiveFunc)         (const gchar* path);
typedef const ArchiveHandle (*OpenArchiveFunc)        (const gchar* path);
typedef void                (*CloseArchiveFunc)       (ArchiveHandle handle);
typedef void                (*WriteToFileArchiveFunc) (ArchiveHandle handle, const gchar* file_path, const gchar* content);
typedef gboolean            (*IsSupportedFunc)        (void);

#define FOREACH_ARCHIVE(METHOD)         \
        METHOD(s7z)                     \
        METHOD(zip)                     \
        METHOD(tar)                     \
        METHOD(rar)

#define FOREACH_COMPRESSION(METHOD)     \
        METHOD(ZIP)                     \
        METHOD(TAR)                     \
        METHOD(RAR)

#define FOR_EACH_ARCHIVE for (uc_archive_t archive = s7z; archive < _UC_ARCHIVE_MAX; archive++)

/**
 * Do not iterate this enum without using FOR_EACH_ARCHIVE.
 */
typedef enum _uc_archive {
    FOREACH_ARCHIVE(GENERATE_ENUM)
    _UC_ARCHIVE_MAX
} uc_archive_t;

const NewArchiveFunc uc_archive_get_func_new(const uc_archive_t* method);
const OpenArchiveFunc uc_archive_get_func_open(const uc_archive_t* method);
const CloseArchiveFunc uc_archive_get_func_close(const uc_archive_t* method);
const WriteToFileArchiveFunc uc_archive_get_func_write_file(const uc_archive_t* method);
const IsSupportedFunc uc_archive_get_func_is_supported(const uc_archive_t* method);
const gchar* uc_archive_to_str(const uc_archive_t* method);

#endif //ULTIMATECOMPRESSOR_METHOD_H
