#if !defined(CUL_STRING_TYPE_H)
#define CUL_STRING_TYPE_H

#include <cul/cul_global.h>
#include <ctype.h>

/* internal use type */
typedef enum _CulStringType CulStringType;
enum _CulStringType {
	CUL_STRING_ALNUM  = 1 << 0,
	CUL_STRING_ALPHA  = 1 << 1,
	CUL_STRING_CNTRL  = 1 << 2,
	CUL_STRING_DIGIT  = 1 << 3,
	CUL_STRING_GRAPH  = 1 << 4,
	CUL_STRING_LOWER  = 1 << 5,
	CUL_STRING_PRINT  = 1 << 6,
	CUL_STRING_PUNCT  = 1 << 7,
	CUL_STRING_SPACE  = 1 << 8,
	CUL_STRING_UPPER  = 1 << 9,
	CUL_STRING_WHITE  = 1 << 10,
	CUL_STRING_XDIGIT = 1 << 11
};

extern const uint16_t *const cul_string_type_ascii;

static inline int cul_isspace(int c)                                            { return isspace(c); };
static inline int cul_isspace_ascii(int c)                                      { return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_SPACE) != 0 ); };
static inline int cul_iswhite_ascii(int c)                                      { return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_WHITE) != 0 ); };

#endif
