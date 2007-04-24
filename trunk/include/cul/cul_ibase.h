#ifndef CUL_IBASE_H
#define CUL_IBASE_H

#include <cul/cul_base_global.h>
#include <stdio.h>

void cul_icopy(int *data_a, const int *data_b, size_t size);
void cul_icopy_overlap(int *data_a, const int *data_b, size_t size);
void cul_icopy_stride(int *data_a, const int *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_icopy_tda(int *data_a, const int *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);

void cul_iswap(int *data_a, int *data_b, size_t size);
void cul_iswap_stride(int *data_a, int *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_iswap_tda(int *data_a, int *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_iswap_pos(int *data_a, size_t i, size_t j);
void cul_ipermute(int *data, size_t *permutation, size_t size);
void cul_ipermute_stride(int *data, size_t *permutation, size_t size, size_t stride);
void cul_ireverse(int *data, size_t size);
void cul_ireverse_stride(int *data, size_t size, size_t stride);

int cul_imin(const int *data, size_t size);
int cul_imin_stride(const int *data, size_t size, size_t stride);
static inline int cul_imin_pair(int a, int b);
size_t cul_imin_index(const int *data, size_t size);
size_t cul_imin_index_stride(const int *data, size_t size, size_t stride);

int cul_imax(const int *data, size_t size);
int cul_imax_stride(const int *data, size_t size, size_t stride);
static inline int cul_imax_pair(int a, int b);
size_t cul_imax_index(const int *data, size_t size);
size_t cul_imax_index_stride(const int *data, size_t size, size_t stride);

void cul_iminmax(const int *data, size_t size, int *min, int *max);
void cul_iminmax_stride(const int *data, size_t size, size_t stride, int *min, int *max);
void cul_iminmax_index(const int *data, size_t size, size_t *min_index, size_t *max_index);
void cul_iminmax_index_stride(const int *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void cul_iset_all(int *data, size_t size, int value);
void cul_iset_all_stride(int *data, size_t size, size_t stride, int value);
void cul_iadd_scalar(int *data, size_t size, int value);
void cul_iadd_scalar_stride(int *data, size_t size, size_t stride, int value);
void cul_imul_scalar(int *data, size_t size, int value);
void cul_imul_scalar_stride(int *data, size_t size, size_t stride, int value);

void cul_iadd(int *data_out, const int *data, size_t size);
void cul_iadd_stride(int *data_out, const int *data, size_t size, size_t stride_out, size_t stride);
void cul_isub(int *data_out, const int *data, size_t size);
void cul_isub_stride(int *data_out, const int *data, size_t size, size_t stride_out, size_t stride);
void cul_imul(int *data_out, const int *data, size_t size);
void cul_imul_stride(int *data_out, const int *data, size_t size, size_t stride_out, size_t stride);
void cul_idiv(int *data_out, const int *data, size_t size);
void cul_idiv_stride(int *data_out, const int *data, size_t size, size_t stride_out, size_t stride);

double cul_isum(const int *data, size_t size);
double cul_isum_stride(const int *data, size_t size, size_t stride);
double cul_imean(const int *data, size_t size);
double cul_imean_stride(const int *data, size_t size, size_t stride);
double cul_ivariance(const int *data, size_t size, double mean);
double cul_ivariance_stride(const int *data, size_t size, size_t stride, double mean);

int *cul_ilfind(int key, int *data, size_t size);
int *cul_ilfind_stride(int key, int *data, size_t size, size_t stride);
int *cul_ibfind(int key, int *data, size_t size);
int *cul_ibfind_stride(int key, int *data, size_t size, size_t stride);
void cul_isort_asc(int *data, size_t size);
void cul_isort_asc_stride(int *data, size_t size, size_t stride);
void cul_isort_desc(int *data, size_t size);
void cul_isort_desc_stride(int *data, size_t size, size_t stride);
int *cul_iunique(int *data, size_t size);
int *cul_iunique_stride(int *data, size_t size, size_t stride);

cul_bool cul_ifprintf(FILE *stream, const char *format, const char *separator, const int *data, size_t size);
cul_bool cul_ifprintf_stride(FILE *stream, const char *format, const char *separator, const int *data, size_t size, size_t strid);
cul_bool cul_ifscanf(FILE *stream, const char *format, const char *separator, const int *data, size_t size);
cul_bool cul_ifscanf_stride(FILE *stream, const char *format, const char *separator, const int *data, size_t size, size_t stride);

cul_bool cul_ifwrite(FILE *stream, const int *data, size_t size);
cul_bool cul_ifwrite_stride(FILE *stream, const int *data, size_t size, size_t stride);
cul_bool cul_ifread(FILE *stream, const int *data, size_t size);
cul_bool cul_ifread_stride(FILE *stream, const int *data, size_t size, size_t stride);

/* implementations */

static inline void cul_iswap_pos(int *data, size_t i, size_t j) {
	int tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

static inline int cul_imin_pair(int a, int b) {
	return a < b ? a : b;
}

static inline int cul_imax_pair(int a, int b) {
	return a > b ? a : b;
}

#endif /* CUL_IBASE_H */
