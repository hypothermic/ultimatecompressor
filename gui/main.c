#include <glib.h>

#include "../core/error.h"

#define __DEBUG__ UC_DEBUG_ENABLED

int main(int argc, char **argv) {
    g_print("\nUltimateCompressor GUI v%s build %s\n", UC_API_VERSION, UC_BUILD_VERSION);
}