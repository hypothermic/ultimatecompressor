#include "mode.h"

static const ModePerformFunc _uc_mode_func_perform_ptrs[] = {
        FOREACH_MODE(GENERATE_FUNC_MODE_PERFORM_ENUM)
};

const ModePerformFunc uc_mode_func_perform(const uc_mode_t* mode) {
    return _uc_mode_func_perform_ptrs[*mode];
}