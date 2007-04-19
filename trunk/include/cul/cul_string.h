#ifndef CUL_STRING_H
#define CUL_STRING_H

#include <cul/cul_global.h>
#include <cul/cul_list.h>

#define CUL_STRING(ptr) ((CulString *)(ptr))

typedef struct _CulString CulString;

/** \brief CulString is manged string structure.
 *  
 * CulString is similar to standard C string, except that it automatically
 * changes its size during various operations like text insert, cut or trim.
 * All operation are invatiant to null bytes so it can be used to hold binary
 * data . On other hand it can also be used as standard C string as it end 
 * always with null character.
 */
struct _CulString {
	char *str;       /**< points to actual character data */
	size_t size;     /**< size in bytes of string, not including terminating nul byte */
	size_t reserved; /**< actual reserved memory for given string */
};

/** \brief NULL CulString string.
 * 
 * CulStringNULL is a NULL CulString that could be used as initializer or 
 * empty string argument.
 */
static const CulString CulStringNULL = {NULL, 0, 0};

static inline cul_bool cul_string_isnull(const CulString *s);
static inline cul_bool cul_string_isempty(const CulString *s);

static inline CulString *cul_string_new_struct(void);
static inline void cul_string_free_struct(CulString *s);
static inline CulString *cul_string_init_struct(CulString *s, size_t size, size_t reserved, char *str);

CulString *cul_string_new(const CulString *string);
CulString *cul_string_new_empty();
CulString *cul_string_new_printf(const char *format, ...);
CulString *cul_string_new_str(const char *str);
CulString *cul_string_new_block(const char *block, size_t size);

void cul_string_free(CulString *s);

CulString *cul_string_clean(CulString *s);
CulString *cul_string_clear(CulString *s);
CulString *cul_string_resize(CulString *s, size_t size);
CulString *cul_string_reserve(CulString *s, size_t size);
CulString *cul_string_shrink(CulString *s);

CulString *cul_string_copy(CulString *s, const CulString *copy);
CulString *cul_string_copy_str(CulString *s, const char *copy);
CulString *cul_string_copy_block(CulString *s, const char *copy, size_t size);

CulString *cul_string_append(CulString *s, const CulString *append);
CulString *cul_string_append_printf(CulString *s, const char *format, ...);
CulString *cul_string_append_str(CulString *s, const char *append);
CulString *cul_string_prepend(CulString *s, const CulString *prepend);
CulString *cul_string_prepend_printf(CulString *s, const char *format, ...);
CulString *cul_string_prepend_str(CulString *s, const char *prepend);

CulString *cul_string_insert(CulString *s, size_t pos, const CulString *insert);
CulString *cul_string_insert_printf(CulString *s, size_t size, const char *format, ...);
CulString *cul_string_insert_str(CulString *s, size_t pos, const char *insert);
CulString *cul_string_insert_block(CulString *s, size_t pos, const char *insert, size_t size);

CulString *cul_string_cut(CulString *s, size_t pos, size_t size);
CulString *cul_string_cut_begin(CulString *s, size_t size);
CulString *cul_string_cut_end(CulString *s, size_t size);

int cul_string_compare(const CulString *s, const CulString *compare);
int cul_string_compare_str(const CulString *s, const char *compare);
int cul_string_compare_block(const CulString *s, const char *compare, size_t size);

int cul_string_subcompare(const CulString *s, size_t pos, const CulString *compare);
int cul_string_subcompare_str(const CulString *s, size_t pos, const char *compare);
int cul_string_subcompare_block(const CulString *s, size_t pos, const char *compare, size_t size);

cul_bool cul_string_equal(const CulString *s, const CulString *compare);
cul_bool cul_string_equal_str(const CulString *s, const char *compare);
cul_bool cul_string_start_with(const CulString *s, const CulString *prefix);
cul_bool cul_string_start_with_str(const CulString *s, const char *prefix);
cul_bool cul_string_end_with(const CulString *s, const CulString *postfix);
cul_bool cul_string_end_with_str(const CulString *s, const char *postfix);

CulString *cul_string_trim(CulString *s);
CulString *cul_string_trim_left(CulString *s);
CulString *cul_string_trim_right(CulString *s);

CulList *cul_string_split(const CulString *s, const char *delimiter);

/* implemenations */

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

static inline CulString *cul_string_init_struct(CulString *s, size_t size, size_t reserved, char *str) {
	s->str = str;
	s->size = size;
	s->reserved = reserved;
	return s;
}

#endif /* CUL_STRING_H */
