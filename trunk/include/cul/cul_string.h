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
static inline void        cul_string_free_struct(CulString *this);
static inline CulString  *cul_string_init_struct(CulString *this, size_t size, size_t reserved, char *str);

static inline char       *cul_string_str        (CulString *this);
static inline const char *cul_string_const_str  (const CulString *this);
static inline size_t      cul_string_length     (const CulString *this);
static inline cul_bool    cul_string_isnull     (const CulString *this);
static inline cul_bool    cul_string_isempty    (const CulString *this);
cul_bool                  cul_string_isspace    (const CulString *this);

CulString *cul_string_new             (const CulString *string);
CulString *cul_string_new_empty       ();
CulString *cul_string_new_printf      (const char *format, ...);
CulString *cul_string_new_str         (const char *str);
CulString *cul_string_new_block       (const char *block, size_t size);
void       cul_string_free            (CulString *this);

CulString *cul_string_clean           (CulString *this);
CulString *cul_string_clear           (CulString *this);
CulString *cul_string_resize          (CulString *this, size_t size);
CulString *cul_string_reserve         (CulString *this, size_t size);
CulString *cul_string_shrink          (CulString *this);

CulString *cul_string_copy            (CulString *this, const CulString *copy);
CulString *cul_string_copy_str        (CulString *this, const char *copy);
CulString *cul_string_copy_block      (CulString *this, const char *copy, size_t size);

CulString *cul_string_append          (CulString *this, const CulString *append);
CulString *cul_string_append_printf   (CulString *this, const char *format, ...);
CulString *cul_string_append_str      (CulString *this, const char *append);
CulString *cul_string_prepend         (CulString *this, const CulString *prepend);
CulString *cul_string_prepend_printf  (CulString *this, const char *format, ...);
CulString *cul_string_prepend_str     (CulString *this, const char *prepend);

CulString *cul_string_insert          (CulString *this, size_t pos, const CulString *insert);
CulString *cul_string_insert_printf   (CulString *this, size_t pos, const char *format, ...);
CulString *cul_string_insert_str      (CulString *this, size_t pos, const char *insert);
CulString *cul_string_insert_block    (CulString *this, size_t pos, const char *insert, size_t size);

CulString *cul_string_cut             (CulString *this, size_t pos, size_t size);
CulString *cul_string_cut_begin       (CulString *this, size_t size);
CulString *cul_string_cut_end         (CulString *this, size_t size);

int        cul_string_compare         (const CulString *this, const CulString *compare);
int        cul_string_compare_str     (const CulString *this, const char *compare);
int        cul_string_compare_block   (const CulString *this, const char *compare, size_t size);

int        cul_string_subcompare      (const CulString *this, size_t pos, const CulString *compare);
int        cul_string_subcompare_str  (const CulString *this, size_t pos, const char *compare);
int        cul_string_subcompare_block(const CulString *this, size_t pos, const char *compare, size_t size);

cul_bool   cul_string_equal           (const CulString *this, const CulString *compare);
cul_bool   cul_string_equal_str       (const CulString *this, const char *compare);
cul_bool   cul_string_start_with      (const CulString *this, const CulString *prefix);
cul_bool   cul_string_start_with_str  (const CulString *this, const char *prefix);
cul_bool   cul_string_end_with        (const CulString *this, const CulString *postfix);
cul_bool   cul_string_end_with_str    (const CulString *this, const char *postfix);

CulString *cul_string_trim            (CulString *this);
CulString *cul_string_trim_left       (CulString *this);
CulString *cul_string_trim_right      (CulString *this);

CulList   *cul_string_split           (const CulString *this, const char *delimiter);

/* implemenations */

static inline CulString *cul_string_new_struct(void) {
	return cul_slab_new(sizeof(CulString));
}

static inline void cul_string_free_struct(CulString *this) {
	cul_slab_free(sizeof(CulString), this);
}

static inline CulString *cul_string_init_struct(CulString *this, size_t size, size_t reserved, char *str) {
	this->str = str;
	this->size = size;
	this->reserved = reserved;
	return this;
}

static inline char *cul_string_str(CulString *this) {
	return this->str;
}
static inline const char *cul_string_const_str(const CulString *this) {
	return this->str;
}

static inline size_t cul_string_length(const CulString *this) {
	return this->size;
}

static inline cul_bool cul_string_isnull(const CulString *this) {
	return this->str == NULL? CUL_TRUE: CUL_FALSE;
}

static inline cul_bool cul_string_isempty(const CulString *this) {
	return this->size == 0? CUL_TRUE: CUL_FALSE;
}

#endif /* __CUL_STRING_H__ */
