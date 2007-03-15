#ifndef CUL_STRING_H
#define CUL_STRING_H

#include <cul/cul_global.h>
#include <cul/cul_str.h>
#include <cul/cul_list.h>

#define CUL_STRING(ptr) ((CulString *)(ptr))

typedef struct _CulString CulString;

/**
 * CulString is similar to standard C string, except that it automatically
 * changes its size during various operations like text insert, cut or trim.
 * All operation are invatiant to nul bytes so it can be used to hold binary
 * data. On other hand it can also be used as standard C string.
 */
struct _CulString {
	char *str;       /**< points to actual character data */
	size_t size;     /**< size in bytes of string, not including terminating nul byte */
	size_t reserved; /**< actual reserved memory for given string */
};

static const CulString CulStringNULL = {NULL, 0, 0};

/* Access and Checks */

static inline size_t cul_string_size(const CulString *s);
static inline size_t cul_string_reserved(const CulString *s);
static inline char *cul_string_c_str(CulString *s);
static inline const char *cul_string_const_c_str(const CulString *s);

static inline cul_bool cul_string_isnull(const CulString *s);
static inline cul_bool cul_string_isempty(const CulString *s);

/* Allocation */

static inline CulString *cul_string_new_struct(void);
static inline void cul_string_free_struct(CulString *s);
static inline CulString *cul_string_init_all(CulString *s, size_t size, size_t reserved, char *str);

CulString *cul_string_new(const CulString *string);
CulString *cul_string_new_empty();
CulString *cul_string_new_printf(const char *format, ...);
CulString *cul_string_new_raw(const char *string);
CulString *cul_string_new_raw_size(const char *string, size_t size);
CulString *cul_string_new_size(size_t size);

void cul_string_free(CulString *s);

/* Resize */

CulString *cul_string_clean(CulString *s);
CulString *cul_string_clear(CulString *s);
CulString *cul_string_resize(CulString *s, size_t size);
CulString *cul_string_reserve(CulString *s, size_t size);
CulString *cul_string_shrink(CulString *s);

/* Copy */

CulString *cul_string_copy(CulString *s, const CulString *copy);
CulString *cul_string_copy_raw(CulString *s, const char *copy);
CulString *cul_string_copy_raw_size(CulString *s, const char *copy, size_t size);

/* Insert/Cut */

CulString *cul_string_append(CulString *s, const CulString *append);
CulString *cul_string_append_printf(CulString *s, const char *format, ...);
CulString *cul_string_append_raw(CulString *s, const char *append);
CulString *cul_string_prepend(CulString *s, const CulString *prepend);
CulString *cul_string_prepend_printf(CulString *s, const char *format, ...);
CulString *cul_string_prepend_raw(CulString *s, const char *prepend);
CulString *cul_string_insert(CulString *s, size_t pos, const CulString *insert);
CulString *cul_string_insert_printf(CulString *s, size_t size, const char *format, ...);
CulString *cul_string_insert_raw(CulString *s, size_t pos, const char *insert);
CulString *cul_string_insert_raw_size(CulString *s, size_t pos, const char *insert, size_t size);

CulString *cul_string_cut(CulString *s, size_t x, size_t size);
CulString *cul_string_cut_begin(CulString *s, size_t size);
CulString *cul_string_cut_end(CulString *s, size_t size);

/* Check */

cul_bool cul_string_start_with(const CulString *s, const CulString *prefix);
cul_bool cul_string_start_with_raw(const CulString *s, const char *prefix);
cul_bool cul_string_end_with(const CulString *s, const CulString *postfix);
cul_bool cul_string_end_with_raw(const CulString *s, const char *postfix);
cul_bool cul_string_equal(const CulString *s, const CulString *compare);
cul_bool cul_string_equal_raw(const CulString *s, const char *compare);

/* Misc */

CulString *cul_string_trim(CulString *s);
CulString *cul_string_trim_left(CulString *s);
CulString *cul_string_trim_right(CulString *s);

CulList *cul_string_split(const CulString *s, const char *delimiter);

/* implemenations */

static inline size_t cul_string_size(const CulString *s) {
	return s->size;
}

static inline size_t cul_string_reserved(const CulString *s) {
	return s->reserved;
}

static inline char *cul_string_c_str(CulString *s) {
	return s->str;
}

static inline const char *cul_string_const_c_str(const CulString *s) {
	return s->str;
}

static inline cul_bool cul_string_isnull(const CulString *s) {
	return s->str == NULL? CUL_TRUE: CUL_FALSE;
}

static inline cul_bool cul_string_isempty(const CulString *s) {
	return s->size == 0? CUL_TRUE: CUL_FALSE;
}

static inline CulString *cul_string_new_struct(void) {
	return cul_slab_new(sizeof(CulString));
}

static inline void cul_string_free_struct(CulString *s) {
	cul_slab_free(sizeof(CulString), s);
}

static inline CulString *cul_string_init_all(CulString *s, size_t size, size_t reserved, char *str) {
	s->str = str;
	s->size = size;
	s->reserved = reserved;
	return s;
}

#endif /* CUL_STRING_H */
