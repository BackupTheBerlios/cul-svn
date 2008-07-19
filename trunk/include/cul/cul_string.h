#ifndef __CUL_STRING_H__
#define __CUL_STRING_H__

#include <cul/cul_global.h>
#include <cul/cul_list.h>

#define CUL_STRING(ptr) ((CulString *)(ptr))

typedef struct _CulString CulString;

/** CulString is manged string structure.
 *  
 * CulString is similar to standard C string, except that it automatically
 * changes its size during various operations like text insert, cut or trim.
 * All operation are invatiant to null bytes so it can be used to hold binary
 * data. On other hand it can also be used as standard C string as it end 
 * always with null character.
 */
struct _CulString {
	char *str;       /* points to actual character data */
	size_t size;     /* size in bytes of string, not including terminating nul byte */
	size_t reserved; /* actual reserved memory for given string */
};

/** NULL CulString structure.
 * 
 * CulStringNULL is a NULL CulString that could be used as initializer or 
 * empty string argument.
 */
static const CulString CulStringNULL = {NULL, 0, 0};

static inline CulString  *cul_string_new_struct ();
static inline void        cul_string_free_struct(CulString *string);
static inline CulString  *cul_string_init_struct(CulString *string, char *str, size_t size, size_t reserved);

static inline char       *cul_string_str        (CulString *string);
static inline const char *cul_string_const_str  (const CulString *string);
static inline size_t      cul_string_length     (const CulString *string);
static inline cul_bool    cul_string_isnull     (const CulString *string);
static inline cul_bool    cul_string_isempty    (const CulString *string);
cul_bool                  cul_string_isspace    (const CulString *string);

CulString *cul_string_new             (const CulString *string);
CulString *cul_string_new_empty       ();
CulString *cul_string_new_printf      (const char *format, ...);
CulString *cul_string_new_str         (const char *str);
CulString *cul_string_new_block       (const char *block, size_t size);
void       cul_string_free            (CulString *string);

CulString *cul_string_clean           (CulString *string);
CulString *cul_string_clear           (CulString *string);
CulString *cul_string_resize          (CulString *string, size_t size);
CulString *cul_string_reserve         (CulString *string, size_t size);
CulString *cul_string_shrink          (CulString *string);

CulString *cul_string_copy            (CulString *string, const CulString *copy);
CulString *cul_string_copy_str        (CulString *string, const char *copy);
CulString *cul_string_copy_block      (CulString *string, const char *copy, size_t size);

CulString *cul_string_append          (CulString *string, const CulString *append);
CulString *cul_string_append_printf   (CulString *string, const char *format, ...);
CulString *cul_string_append_str      (CulString *string, const char *append);
CulString *cul_string_prepend         (CulString *string, const CulString *prepend);
CulString *cul_string_prepend_printf  (CulString *string, const char *format, ...);
CulString *cul_string_prepend_str     (CulString *string, const char *prepend);

CulString *cul_string_insert          (CulString *string, size_t pos, const CulString *insert);
CulString *cul_string_insert_printf   (CulString *string, size_t pos, const char *format, ...);
CulString *cul_string_insert_str      (CulString *string, size_t pos, const char *insert);
CulString *cul_string_insert_block    (CulString *string, size_t pos, const char *insert, size_t size);

CulString *cul_string_cut             (CulString *string, size_t pos, size_t size);
CulString *cul_string_cut_begin       (CulString *string, size_t size);
CulString *cul_string_cut_end         (CulString *string, size_t size);

int        cul_string_compare         (const CulString *string, const CulString *compare);
int        cul_string_compare_str     (const CulString *string, const char *compare);
int        cul_string_compare_block   (const CulString *string, const char *compare, size_t size);

int        cul_string_subcompare      (const CulString *string, size_t pos, const CulString *compare);
int        cul_string_subcompare_str  (const CulString *string, size_t pos, const char *compare);
int        cul_string_subcompare_block(const CulString *string, size_t pos, const char *compare, size_t size);

cul_bool   cul_string_equal           (const CulString *string, const CulString *compare);
cul_bool   cul_string_equal_str       (const CulString *string, const char *compare);
cul_bool   cul_string_start_with      (const CulString *string, const CulString *prefix);
cul_bool   cul_string_start_with_str  (const CulString *string, const char *prefix);
cul_bool   cul_string_end_with        (const CulString *string, const CulString *postfix);
cul_bool   cul_string_end_with_str    (const CulString *string, const char *postfix);

CulString *cul_string_trim            (CulString *string);
CulString *cul_string_trim_left       (CulString *string);
CulString *cul_string_trim_right      (CulString *string);

CulList   *cul_string_split           (const CulString *string, const char *delimiter);

/* implemenations */

static inline CulString *cul_string_new_struct() {
	return cul_slab_new(sizeof(CulString));
}

static inline void cul_string_free_struct(CulString *string) {
	cul_slab_free(sizeof(CulString), string);
}

static inline CulString *cul_string_init_struct(CulString *string, char *str, size_t size, size_t reserved) {
	string->str = str;
	string->size = size;
	string->reserved = reserved;
	return string;
}

static inline char *cul_string_str(CulString *string) {
	return string->str;
}
static inline const char *cul_string_const_str(const CulString *string) {
	return string->str;
}

static inline size_t cul_string_length(const CulString *string) {
	return string->size;
}

static inline cul_bool cul_string_isnull(const CulString *string) {
	return string->str == NULL? CUL_TRUE: CUL_FALSE;
}

static inline cul_bool cul_string_isempty(const CulString *string) {
	return string->size == 0? CUL_TRUE: CUL_FALSE;
}

#endif /* __CUL_STRING_H__ */
