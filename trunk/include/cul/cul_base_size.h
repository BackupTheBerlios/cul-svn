#if !defined(CUL_BASE_SIZE_H)
#define CUL_BASE_SIZE_H

#include <cul/cul_global_base.h>
#include <cul/cul_base_common.h>
#include <cul/cul_mem.h>
#include <stdio.h>

/* Allocation */

static inline size_t *cul_unew(size_t size);
static inline size_t *cul_uresize(size_t *data, size_t size);
static inline void cul_ufree(size_t *data);
static inline void cul_ufree_null(size_t **data);

/* Copy */

void cul_ucopy(size_t *data_a, const size_t *data_b, size_t size);
void cul_ucopy_overlap(size_t *data_a, const size_t *data_b, size_t size);
void cul_ucopy_stride(size_t *data_a, const size_t *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_ucopy_tda(size_t *data_a, const size_t *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);

void cul_uswap(size_t *data_a, size_t *data_b, size_t size);
void cul_uswap_stride(size_t *data_a, size_t *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_uswap_tda(size_t *data_a, size_t *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_uswap_pos(size_t *data, size_t i, size_t j);

void cul_ureverse(size_t *data, size_t size);
void cul_ureverse_stride(size_t *data, size_t size, size_t stride);
void cul_upermutation(size_t *data, size_t size);
void cul_upermutation_stride(size_t *data, size_t size, size_t stride);

/* I/O */

cul_bool cul_uprintf_stream(const char *format, const char *separator, const size_t *data, size_t size);
cul_bool cul_uprintf_stream_stride(const char *format, const char *separator, const size_t *data, size_t size, size_t stride);
cul_bool cul_ufprintf(FILE *stream, const char *format, const char *separator, const size_t *data, size_t size);
cul_bool cul_ufprintf_stride(FILE *stream, const char *format, const char *separator, const size_t *data, size_t size, size_t strid);
cul_bool cul_ufscanf(FILE *stream, const char *format, const char *separator, const size_t *data, size_t size);
cul_bool cul_ufscanf_stride(FILE *stream, const char *format, const char *separator, const size_t *data, size_t size, size_t stride);

cul_bool cul_ufwrite(FILE *stream, const size_t *data, size_t size);
cul_bool cul_ufwrite_stride(FILE *stream, const size_t *data, size_t size, size_t stride);
cul_bool cul_ufread(FILE *stream, const size_t *data, size_t size);
cul_bool cul_ufread_stride(FILE *stream, const size_t *data, size_t size, size_t stride);

/* Min/Max */

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

/* Operators */

void cul_uset_all(size_t *data, size_t size, size_t value);
void cul_uset_all_stride(size_t *data, size_t size, size_t stride, size_t value);
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

/* Statistics */

double cul_usum(const size_t *data, size_t size);
double cul_usum_stride(const size_t *data, size_t size, size_t stride);
double cul_umean(const size_t *data, size_t size);
double cul_umean_stride(const size_t *data, size_t size, size_t stride);
double cul_uvariance(const size_t *data, size_t size, double mean);
double cul_uvariance_stride(const size_t *data, size_t size, size_t stride, double mean);

/* Basic Algorithms */

/* Search */
size_t *cul_ulfind(size_t key, size_t *data, size_t size, cul_eq_f *eq);
size_t *cul_ulfind_stride(size_t key, size_t *data, size_t size, size_t stride, cul_eq_f *eq);
size_t *cul_ubfind(size_t key, size_t *data, size_t size, cul_cmp_f *cmp);
size_t *cul_ubfind_stride(size_t key, size_t *data, size_t size, size_t stride, cul_cmp_f *cmp);
size_t *cul_ulfind_eq(size_t key, size_t *data, size_t size);
size_t *cul_ubfind_eq(size_t key, size_t *data, size_t size);
/* Sort */
void cul_usort(size_t *data, size_t size, cul_cmp_f *cmp);
void cul_usort_stride(size_t *data, size_t size, size_t stride, cul_cmp_f *cmp);
void cul_usort_asc(size_t *data, size_t size);
void cul_usort_asc_stride(size_t *data, size_t size, size_t stride);
void cul_usort_desc(size_t *data, size_t size);
void cul_usort_desc_stride(size_t *data, size_t size, size_t stride);
/* Unique */
size_t *cul_uunique(size_t *data, size_t size, cul_eq_f *eq);
size_t *cul_uunique_stride(size_t *data, size_t size, size_t stride, cul_eq_f *eq);
size_t *cul_uunique_eq(size_t *data, size_t size);
size_t *cul_uunique_eq_stride(size_t *data, size_t size, size_t stride);

/* Inline definitions */

static inline size_t *cul_unew(size_t size) {
	return (size_t *)cul_malloc(size * sizeof(size_t));
}

static inline size_t *cul_uresize(size_t *data, size_t size) {
	return (size_t *)cul_realloc(data, size * sizeof(size_t));
}

static inline void cul_ufree(size_t *data) {
	cul_free(data);
}

static inline void cul_ufree_null(size_t **data) {
	cul_free(*data);
	*data = NULL;
}

static inline void cul_uswap_pos(size_t *data, size_t i, size_t j) {
	size_t tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

static inline size_t cul_umin_pair(size_t a, size_t b) {
	return a < b ? a : b;
}

static inline size_t cul_umax_pair(size_t a, size_t b) {
	return a > b ? a : b;
}

#endif
