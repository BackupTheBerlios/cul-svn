#ifndef __CUL_UBASE_H__
#define __CUL_UBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void cul_uzero(size_t *data, size_t size);

void cul_ucopy(size_t *data_a, const size_t *data_b, size_t size);
void cul_ucopy_overlap(size_t *data_a, const size_t *data_b, size_t size);
void cul_ucopy_stride(size_t *data_a, const size_t *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_ucopy_tda(size_t *data_a, const size_t *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b);

void cul_uswap(size_t *data_a, size_t *data_b, size_t size);
void cul_uswap_stride(size_t *data_a, size_t *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_uswap_tda(size_t *data_a, size_t *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
void cul_upermute(size_t *data, const size_t *permutation, size_t size);
void cul_upermute_stride(size_t *data, const size_t *permutation, size_t size, size_t stride);
void cul_ureverse(size_t *data, size_t size);
void cul_ureverse_stride(size_t *data, size_t size, size_t stride);

void cul_uset(size_t *data, size_t size, size_t value);
void cul_uset_stride(size_t *data, size_t size, size_t stride, size_t value);
void cul_uadd_scalar(size_t *data, size_t size, size_t value);
void cul_uadd_scalar_stride(size_t *data, size_t size, size_t stride, size_t value);
void cul_umul_scalar(size_t *data, size_t size, size_t value);
void cul_umul_scalar_stride(size_t *data, size_t size, size_t stride, size_t value);

void cul_uadd(size_t *data_out, const size_t *data, size_t size);
void cul_uadd_stride(size_t *data_out, const size_t *data, size_t size, size_t stride_out, size_t stride);
void cul_usub(size_t *data_out, const size_t *data, size_t size);
void cul_usub_stride(size_t *data_out, const size_t *data, size_t size, size_t stride_out, size_t stride);
void cul_umul(size_t *data_out, const size_t *data, size_t size);
void cul_umul_stride(size_t *data_out, const size_t *data, size_t size, size_t stride_out, size_t stride);
void cul_udiv(size_t *data_out, const size_t *data, size_t size);
void cul_udiv_stride(size_t *data_out, const size_t *data, size_t size, size_t stride_out, size_t stride);

double cul_usum(const size_t *data, size_t size);
double cul_usum_stride(const size_t *data, size_t size, size_t stride);
double cul_umean(const size_t *data, size_t size);
double cul_umean_stride(const size_t *data, size_t size, size_t stride);
double cul_uvariance(const size_t *data, size_t size, double mean);
double cul_uvariance_stride(const size_t *data, size_t size, size_t stride, double mean);

size_t cul_umin(const size_t *data, size_t size);
size_t cul_umin_stride(const size_t *data, size_t size, size_t stride);
static inline size_t cul_umin_pair(size_t a, size_t b);
size_t cul_umin_index(const size_t *data, size_t size);
size_t cul_umin_index_stride(const size_t *data, size_t size, size_t stride);

size_t cul_umax(const size_t *data, size_t size);
size_t cul_umax_stride(const size_t *data, size_t size, size_t stride);
static inline size_t cul_umax_pair(size_t a, size_t b);
size_t cul_umax_index(const size_t *data, size_t size);
size_t cul_umax_index_stride(const size_t *data, size_t size, size_t stride);

void cul_uminmax(const size_t *data, size_t size, size_t *min, size_t *max);
void cul_uminmax_stride(const size_t *data, size_t size, size_t stride, size_t *min, size_t *max);
void cul_uminmax_index(const size_t *data, size_t size, size_t *min_index, size_t *max_index);
void cul_uminmax_index_stride(const size_t *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void cul_usort_asc(size_t *data, size_t size);
void cul_usort_asc_stride(size_t *data, size_t size, size_t stride);
void cul_usort_desc(size_t *data, size_t size);
void cul_usort_desc_stride(size_t *data, size_t size, size_t stride);
size_t *cul_uunique(size_t *data, size_t size);
size_t *cul_uunique_stride(size_t *data, size_t size, size_t stride);
size_t *cul_ufind(const size_t *data, size_t size, size_t key);
size_t *cul_ufind_stride(const size_t *data, size_t size, size_t stride, size_t key);
size_t *cul_ubfind(const size_t *data, size_t size, size_t key);
size_t *cul_ubfind_stride(const size_t *data, size_t size, size_t stride, size_t key);

cul_bool cul_ufprintf(FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufprintf_stride(FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf(FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf_stride(FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

cul_bool cul_ufwrite(FILE *stream, const size_t *data, size_t size);
cul_bool cul_ufwrite_stride(FILE *stream, const size_t *data, size_t size, size_t stride);
cul_bool cul_ufread(FILE *stream, const size_t *data, size_t size);
cul_bool cul_ufread_stride(FILE *stream, const size_t *data, size_t size, size_t stride);

/* implementations */

static inline size_t cul_umin_pair(size_t a, size_t b) {
	return a < b ? a : b;
}

static inline size_t cul_umax_pair(size_t a, size_t b) {
	return a > b ? a : b;
}

#endif /* CUL_UBASE_H */
