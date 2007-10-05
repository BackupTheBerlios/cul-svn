#ifndef __CUL_STR_TYPE_H__
#define __CUL_STR_TYPE_H__

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
	CUL_STRT_XDIGIT = 1 << 10
};

extern const uint16_t *const cul_str_type_ascii;

static inline int cul_isspace (int character);
static inline int cul_isgraph (int character);
static inline int cul_isprint (int character);
static inline int cul_ispunct (int character);
static inline int cul_isalnum (int character);
static inline int cul_isalpha (int character);
static inline int cul_isdigit (int character);
static inline int cul_isxdigit(int character);
static inline int cul_isupper (int character);
static inline int cul_islower (int character);

static inline int cul_tolower (int character);
static inline int cul_toupper (int character);

/* implementations */

static inline int cul_isspace(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_SPACE) != 0 );
}

static inline int cul_isgraph(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_GRAPH) != 0 );
}

static inline int cul_isprint(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_PRINT) != 0 );
}

static inline int cul_ispunct(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_PUNCT) != 0 );
}

static inline int cul_isalnum(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_ALNUM) != 0 );
}

static inline int cul_isalpha(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_ALPHA) != 0 );
}

static inline int cul_isdigit(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_DIGIT) != 0 );
}

static inline int cul_isxdigit(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_XDIGIT) != 0 );
}

static inline int cul_isupper(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_UPPER) != 0 );
}

static inline int cul_islower(int c) {
	return ( (cul_str_type_ascii[ (uint8_t)c ] & CUL_STRT_LOWER) != 0 );
}

static inline int cul_tolower(int c) {
	return cul_islower(c)? c: c - 'A' + 'a';
}

static inline int cul_toupper(int c) {
	return cul_isupper(c)? c: c - 'a' + 'A';
}

#endif /* __CUL_STR_TYPE_H__ */
