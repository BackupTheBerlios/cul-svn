#ifndef CUL_DBASE_H
#define CUL_DBASE_H

#include <cul/cul_base_global.h>
#include <stdio.h>

void cul_dcopy(double *data_a, const double *data_b, size_t size);
void cul_dcopy_overlap(double *data_a, const double *data_b, size_t size);
void cul_dcopy_stride(double *data_a, const double *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_dcopy_tda(double *data_a, const double *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b);

int cul_dcompare(double *data_a, double *data_b, size_t size);
int cul_dcompare_stride(double *data_a, double *data_b, size_t size, size_t stride_a, size_t stride_b);
int cul_dcompare_tda(double *data_a, double *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b);

void cul_dswap(double *data_a, double *data_b, size_t size);
void cul_dswap_stride(double *data_a, double *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_dswap_tda(double *data_a, double *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_dswap_pos(double *data, size_t i, size_t j);
void cul_dpermute(double *data, const size_t *permutation, size_t size);
void cul_dpermute_stride(double *data, const size_t *permutation, size_t size, size_t stride);
void cul_dreverse(double *data, size_t size);
void cul_dreverse_stride(double *data, size_t size, size_t stride);

double cul_dmin(const double *data, size_t size);
double cul_dmin_stride(const double *data, size_t size, size_t stride);
static inline double cul_dmin_pair(double a, double b);
size_t cul_dmin_index(const double *data, size_t size);
size_t cul_dmin_index_stride(const double *data, size_t size, size_t stride);

double cul_dmax(const double *data, size_t size);
double cul_dmax_stride(const double *data, size_t size, size_t stride);
static inline double cul_dmax_pair(double a, double b);
size_t cul_dmax_index(const double *data, size_t size);
size_t cul_dmax_index_stride(const double *data, size_t size, size_t stride);

void cul_dminmax(const double *data, size_t size, double *min, double *max);
void cul_dminmax_stride(const double *data, size_t size, size_t stride, double *min, double *max);
void cul_dminmax_index(const double *data, size_t size, size_t *min_index, size_t *max_index);
void cul_dminmax_index_stride(const double *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void cul_dset_all(double *data, size_t size, double value);
void cul_dset_all_stride(double *data, size_t size, size_t stride, double value);
void cul_dadd_scalar(double *data, size_t size, double value);
void cul_dadd_scalar_stride(double *data, size_t size, size_t stride, double value);
void cul_dmul_scalar(double *data, size_t size, double value);
void cul_dmul_scalar_stride(double *data, size_t size, size_t stride, double value);

void cul_dadd(double *data_out, const double *data, size_t size);
void cul_dadd_stride(double *data_out, const double *data, size_t size, size_t stride_out, size_t stride);
void cul_dsub(double *data_out, const double *data, size_t size);
void cul_dsub_stride(double *data_out, const double *data, size_t size, size_t stride_out, size_t stride);
void cul_dmul(double *data_out, const double *data, size_t size);
void cul_dmul_stride(double *data_out, const double *data, size_t size, size_t stride_out, size_t stride);
void cul_ddiv(double *data_out, const double *data, size_t size);
void cul_ddiv_stride(double *data_out, const double *data, size_t size, size_t stride_out, size_t stride);

double cul_dsum(const double *data, size_t size);
double cul_dsum_stride(const double *data, size_t size, size_t stride);
double cul_dmean(const double *data, size_t size);
double cul_dmean_stride(const double *data, size_t size, size_t stride);
double cul_dvariance(const double *data, size_t size, double mean);
double cul_dvariance_stride(const double *data, size_t size, size_t stride, double mean);

double *cul_dlfind(double key, double *data, size_t size);
double *cul_dlfind_stride(double key, double *data, size_t size, size_t stride);
double *cul_dbfind(double key, double *data, size_t size);
double *cul_dbfind_stride(double key, double *data, size_t size, size_t stride);
void cul_dsort_asc(double *data, size_t size);
void cul_dsort_asc_stride(double *data, size_t size, size_t stride);
void cul_dsort_desc(double *data, size_t size);
void cul_dsort_desc_stride(double *data, size_t size, size_t stride);
double *cul_dunique(double *data, size_t size);
double *cul_dunique_stride(double *data, size_t size, size_t stride);

cul_bool cul_dfprintf(FILE *stream, const char *format, const char *separator, const double *data, size_t size);
cul_bool cul_dfprintf_stride(FILE *stream, const char *format, const char *separator, const double *data, size_t size, size_t strid);
cul_bool cul_dfscanf(FILE *stream, const char *format, const char *separator, const double *data, size_t size);
cul_bool cul_dfscanf_stride(FILE *stream, const char *format, const char *separator, const double *data, size_t size, size_t stride);

cul_bool cul_dfwrite(FILE *stream, const double *data, size_t size);
cul_bool cul_dfwrite_stride(FILE *stream, const double *data, size_t size, size_t stride);
cul_bool cul_dfread(FILE *stream, const double *data, size_t size);
cul_bool cul_dfread_stride(FILE *stream, const double *data, size_t size, size_t stride);

/* implementations */

static inline void cul_dswap_pos(double *data, size_t i, size_t j) {
	double tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

static inline double cul_dmin_pair(double a, double b) {
	return a < b ? a : b;
}

static inline double cul_dmax_pair(double a, double b) {
	return a > b ? a : b;
}

#endif /* CUL_DBASE_H */
