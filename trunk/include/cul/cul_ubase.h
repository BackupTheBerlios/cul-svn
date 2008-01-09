#ifndef __CUL_UBASE_H__
#define __CUL_UBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

size_t   cul_umin                 (const size_t *data, size_t size);
size_t   cul_umin_stride          (const size_t *data, size_t size, size_t stride);
static inline size_t cul_umin_2   (size_t value_a, size_t value_b);
size_t   cul_umin_index           (const size_t *data, size_t size);
size_t   cul_umin_index_stride    (const size_t *data, size_t size, size_t stride);
size_t   cul_umax                 (const size_t *data, size_t size);
size_t   cul_umax_stride          (const size_t *data, size_t size, size_t stride);
static inline size_t cul_umax_2   (size_t value_a, size_t value_b);
size_t   cul_umax_index           (const size_t *data, size_t size);
size_t   cul_umax_index_stride    (const size_t *data, size_t size, size_t stride);
void     cul_uminmax              (const size_t *data, size_t size, size_t *min, size_t *max);
void     cul_uminmax_stride       (const size_t *data, size_t size, size_t stride, size_t *min, size_t *max);
void     cul_uminmax_index        (const size_t *data, size_t size, size_t *min_index, size_t *max_index);
void     cul_uminmax_index_stride (const size_t *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void     cul_usort_asc            (size_t *data, size_t size);
void     cul_usort_asc_stride     (size_t *data, size_t size, size_t stride);
void     cul_usort_desc           (size_t *data, size_t size);
void     cul_usort_desc_stride    (size_t *data, size_t size, size_t stride);
size_t  *cul_uunique              (size_t *data, size_t size);
size_t  *cul_ufind                (const size_t *data, size_t size, size_t key);
size_t  *cul_ubfind               (const size_t *data, size_t size, size_t key);

cul_bool cul_ufprintf             (FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufprintf_stride      (FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf              (FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf_stride       (FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline size_t cul_umin_2(size_t value_a, size_t value_b) {
	return value_a < value_b ? value_a : value_b;
}

static inline size_t cul_umax_2(size_t value_a, size_t value_b) {
	return value_a > value_b ? value_a : value_b;
}

#endif /* __CUL_UBASE_H__ */
