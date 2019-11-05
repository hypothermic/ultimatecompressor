#ifndef ULTIMATECOMPRESSOR_MODE_H
#define ULTIMATECOMPRESSOR_MODE_H

#include <glib.h>

#include "archive.h"
#include "macro.h"

typedef gboolean (*ModePerformFunc) (const gchar** input_files, const gchar* output_destination, const uc_archive_t* format);

#define FOREACH_MODE(MODE)                 \
        MODE(COMPRESS)                     \
        MODE(DECOMPRESS)

FOREACH_MODE(GENERATE_FUNC_MODE_PERFORM);

#define FOR_EACH_MODE for (uc_mode_t mode = COMPRESS; mode < _UC_MODE_MAX; mode++)

/**
 * Do not iterate this enum without using FOR_EACH_ARCHIVE.
 */
typedef enum _uc_mode {
    FOREACH_MODE(GENERATE_ENUM)
    _UC_MODE_MAX
} uc_mode_t;

const ModePerformFunc uc_mode_func_perform(const uc_mode_t* mode);

#endif //ULTIMATECOMPRESSOR_MODE_H
