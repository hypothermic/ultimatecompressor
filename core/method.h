#ifndef ULTIMATECOMPRESSOR_METHOD_H
#define ULTIMATECOMPRESSOR_METHOD_H

#include <glib.h>

#include "macro.h"

#define FOREACH_ARCHIVE(METHOD)         \
        METHOD(SEVENZIP)                \
        METHOD(ZIP)                     \
        METHOD(TAR)                     \
        METHOD(RAR)

#define FOREACH_COMPRESSION(METHOD)     \
        METHOD(ZIP)                     \
        METHOD(TAR)                     \
        METHOD(RAR)

typedef enum _uc_archive {
    FOREACH_ARCHIVE(GENERATE_ENUM)
} uc_archive_t;

const gchar* uc_archive_to_str(const uc_archive_t* method);

#endif //ULTIMATECOMPRESSOR_METHOD_H
