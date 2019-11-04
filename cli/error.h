#ifndef ULTIMATECOMPRESSOR_ERROR_H
#define ULTIMATECOMPRESSOR_ERROR_H

#include "../core/macro.h"

/**
 * A list with all error codes and relating messages
 */
#define FOREACH_ERROR(FUNC) \
            /* - Individual errors - */ \
            FUNC(0,   ERR_NONE,                     The executable exited gracefully          ) \
            FUNC(1,   ERR_PARSE_OPTIONS,            Failed to parse option context            ) \
            FUNC(2,   ERR_INPUT_UNSPECIFIED,        Input files/paths unspecified             ) \
            FUNC(3,   ERR_OUTPUT_UNSPECIFIED,       Output file/path unspecified              ) \
            FUNC(4,   ERR_FORMAT_UNSPECIFIED,       Archive format unspecified                ) \
            FUNC(5,   ERR_FORMAT_NOT_SUPPORTED,     Archive format not supported              ) \
            FUNC(6,   ERR_FORMAT_NOT_FOUND,         No matching archive format for            ) \
            FUNC(7,   ERR_MODE_NOT_SPECIFIED,       One [1] operating mode must be specified  ) \
            /* - Error categories - */ \
            FUNC(400, ERR_CAT_PARSING_ARGS,         Error while parsing arguments             ) \

FOREACH_ERROR(GENERATE_CONSTANT_INT)
FOREACH_ERROR(GENERATE_CONSTANT_STRING)

/**
 * Prints the error messages related to their indexes using g_printerr().
 */
#define UC_PRINTERR(CAT, ERR) \
        g_printerr("%s: %s\n", CAT ##_STR , ERR ## _STR);

/**
 * Prints the error messages related to their indexes using g_printerr().<br />
 * Variadic arguments may be used
 */
#define UC_VPRINTERR(CAT, ERR, ...) \
        g_printerr("%s: %s (%s)\n", CAT ##_STR , ERR ## _STR, __VA_ARGS__);

#define UC_QUIT_GRACEFUL() \
        exit( ERR_NONE ); return ERR_NONE;

/**
 * Performs UC_PRINTERR using the specified parameters and then quits with the according error code.
 */
#define UC_QUIT_WITH_ERR(CAT, ERR) \
        UC_PRINTERR(CAT, ERR) exit( ERR ) ; return ( ERR );

/**
 * Performs UC_PRINTERR using the specified parameters and then quits with the according error code.<br />
 * Variadic arguments may be used
 */
#define UC_QUIT_WITH_VERR(CAT, ERR, ...) \
        UC_VPRINTERR(CAT, ERR, __VA_ARGS__) exit( ERR ) ; return ( ERR );

#endif //ULTIMATECOMPRESSOR_ERROR_H
