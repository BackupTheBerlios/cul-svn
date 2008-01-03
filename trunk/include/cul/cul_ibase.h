#ifndef __CUL_IBASE_H__
#define __CUL_IBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void     cul_ipermute             (int *data, const size_t *permutation, size_t size);
void     cul_ipermute_stride      (int *data, const size_t *permutation, size_t size, size_t stride);
void     cul_ireverse             (int *data, size_t size);
void     cul_ireverse_stride      (int *data, size_t size, size_t stride);

void     cul_iset                 (int *data, size_t size, int value);
void     cul_iset_stride          (int *data, size_t size, size_t stride, int value);
void     cul_iset_tda             (int *data, size_t size, size_t tda_size, size_t tda, int value);
void     cul_iadd_constant        (int *data, size_t size, double value);
void     cul_iadd_constant_stride (int *data, size_t size, size_t stride, double value);
void     cul_iadd_constant_tda    (int *data, size_t size, size_t tda_size, size_t tda, double value);
void     cul_iscale               (int *data, size_t size, double value);
void     cul_iscale_stride        (int *data, size_t size, size_t stride, double value);
void     cul_iscale_tda           (int *data, size_t size, size_t tda_size, size_t tda, double value);
void     cul_izero                (int *data, size_t size);
void     cul_iadd                 (int *data, const int *other, size_t size);
void     cul_iadd_stride          (int *data, const int *other, size_t size, size_t stride, size_t other_stride);
void     cul_iadd_tda             (int *data, const int *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);
void     cul_isub                 (int *data, const int *other, size_t size);
void     cul_isub_stride          (int *data, const int *other, size_t size, size_t stride, size_t other_stride);
void     cul_isub_tda             (int *data, const int *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);
void     cul_imul                 (int *data, const int *other, size_t size);
void     cul_imul_stride          (int *data, const int *other, size_t size, size_t stride, size_t other_stride);
void     cul_imul_tda             (int *data, const int *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);
void     cul_idiv                 (int *data, const int *other, size_t size);
void     cul_idiv_stride          (int *data, const int *other, size_t size, size_t stride, size_t other_stride);
void     cul_idiv_tda             (int *data, const int *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);
int      cul_idot                 (int *data, const int *other, size_t size);
int      cul_idot_stride          (int *data, const int *other, size_t size, size_t stride, size_t other_stride);

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

double   cul_isum                 (const int *data, size_t size);
double   cul_isum_stride          (const int *data, size_t size, size_t stride);
double   cul_isum_tda             (const int *data, size_t size, size_t tda_size, size_t tda);
double   cul_imean                (const int *data, size_t size);
double   cul_imean_stride         (const int *data, size_t size, size_t stride);
double   cul_imean_tda            (const int *data, size_t size, size_t tda_size, size_t tda);
double   cul_ivariance            (const int *data, size_t size);
double   cul_ivariance_stride     (const int *data, size_t size, size_t stride);
double   cul_ivariance_tda        (const int *data, size_t size, size_t tda_size, size_t tda);
double   cul_ivariance_mean       (const int *data, size_t size, double mean);
double   cul_ivariance_mean_stride(const int *data, size_t size, size_t stride, double mean);
double   cul_ivariance_mean_tda   (const int *data, size_t size, size_t tda_size, size_t tda, double mean);

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
