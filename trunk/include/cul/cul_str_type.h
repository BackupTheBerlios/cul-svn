#if !defined(CUL_STR_TYPE_H)
#define CUL_STR_TYPE_H

#include <cul/cul_global.h>
#include <ctype.h>

/* internal use type */
typedef enum _CulStrType CulStrType;
enum _CulStringType {
	CUL_STRT_ALNUM  = 1 << 0,
	CUL_STRT_ALPHA  = 1 << 1,
	CUL_STRT_CNTRL  = 1 << 2,
	CUL_STRT_DIGIT  = 1 << 3,
	CUL_STRT_GRAPH  = 1 << 4,
	CUL_STRT_LOWER  = 1 << 5,
	CUL_STRT_PRINT  = 1 << 6,
	CUL_STRT_PUNCT  = 1 << 7,
	CUL_STRT_SPACE  = 1 << 8,
	CUL_STRT_UPPER  = 1 << 9,
	CUL_STRT_WHITE  = 1 << 10,
	CUL_STRT_XDIGIT = 1 << 11
};

extern const uint16_t *const cul_str_type_ascii;

static inline int cul_isspace(int c);
static inline int cul_isspace_ascii(int c);
static inline int cul_iswhite_ascii(int c);

static inline int cul_isupper(int c);
static inline int cul_isupper_ascii(int c);
static inline int cul_islower(int c);
static inline int cul_islower_ascii(int c);

static inline int cul_tolower(int c);
static inline int cul_tolower_ascii(int c);
static inline int cul_toupper(int c);
static inline int cul_toupper_ascii(int c);

/* implementations */

static inline int cul_isspace(int c) {
	return isspace(c);
}

static inline int cul_isspace_ascii(int c) {
	return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_SPACE) != 0 );
}

static inline int cul_iswhite_ascii(int c) {
	return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_WHITE) != 0 );
}

static inline int cul_isupper(int c) {
	return isupper(c);
}

static inline int cul_isupper_ascii(int c) {
	return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_UPPER) != 0 );
}

static inline int cul_islower(int c) {
	return islower(c);
}

static inline int cul_islower_ascii(int c) {
	return ( (cul_string_type_ascii[ (uint8_t)c ] & CUL_STRING_LOWER) != 0 );
}

static inline int cul_tolower(int c) {
	return tolower(c);
}

static inline int cul_tolower_ascii(int c) {
	return cul_islower_ascii(c)? c - 'a' + 'A': c;
}

static inline int cul_toupper(int c) {
	return toupper(c);
}

static inline int cul_toupper_ascii(int c) {
	return cul_isupper_ascii(c)? c - 'A' + 'a': c;
}

#endif
