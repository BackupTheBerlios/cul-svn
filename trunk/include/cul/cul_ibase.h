#ifndef __CUL_IBASE_H__
#define __CUL_IBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

int      cul_imin                 (const int *data, size_t size);
int      cul_imin_stride          (const int *data, size_t size, size_t stride);
static inline int cul_imin_2      (int value_a, int value_b);
size_t   cul_imin_index           (const int *data, size_t size);
size_t   cul_imin_index_stride    (const int *data, size_t size, size_t stride);
int      cul_imax                 (const int *data, size_t size);
int      cul_imax_stride          (const int *data, size_t size, size_t stride);
static inline int cul_imax_2      (int value_a, int value_b);
size_t   cul_imax_index           (const int *data, size_t size);
size_t   cul_imax_index_stride    (const int *data, size_t size, size_t stride);
void     cul_iminmax              (const int *data, size_t size, int *min, int *max);
void     cul_iminmax_stride       (const int *data, size_t size, size_t stride, int *min, int *max);
void     cul_iminmax_index        (const int *data, size_t size, size_t *min_index, size_t *max_index);
void     cul_iminmax_index_stride (const int *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void     cul_isort_asc            (int *data, size_t size);
void     cul_isort_asc_stride     (int *data, size_t size, size_t stride);
void     cul_isort_desc           (int *data, size_t size);
void     cul_isort_desc_stride    (int *data, size_t size, size_t stride);
int     *cul_iunique              (int *data, size_t size);
int     *cul_ifind                (const int *data, size_t size, int key);
int     *cul_ibfind               (const int *data, size_t size, int key);

cul_bool cul_ifprintf             (FILE *stream, const int *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifprintf_stride      (FILE *stream, const int *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifscanf              (FILE *stream, const int *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifscanf_stride       (FILE *stream, const int *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline int cul_imin_2(int value_a, int value_b) {
	return value_a < value_b ? value_a : value_b;
}

static inline int cul_imax_2(int value_a, int value_b) {
	return value_a > value_b ? value_a : value_b;
}

#endif /* __CUL_IBASE_H__ */
