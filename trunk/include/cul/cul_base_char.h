#ifndef CUL_BASE_CHAR_H
#define CUL_BASE_CHAR_H

#include <cul/cul_global_base.h>
#include <stdio.h>

void cul_ccopy(char *data_a, const char *data_b, size_t size);
void cul_ccopy_overlap(char *data_a, const char *data_b, size_t size);
void cul_ccopy_stride(char *data_a, const char *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_ccopy_tda(char *data_a, const char *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);

void cul_cswap(char *data_a, char *data_b, size_t size);
void cul_cswap_stride(char *data_a, char *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_cswap_tda(char *data_a, char *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_cswap_pos(char *data, size_t i, size_t j);

void cul_creverse(char *data, size_t size);
void cul_creverse_stride(char *data, size_t size, size_t stride);
void cul_cpermutation(char *data, size_t size);
void cul_cpermutation_stride(char *data, size_t size, size_t stride);

cul_bool cul_cfprintf(FILE *stream, const char *format, const char *separator, const char *data, size_t size);
cul_bool cul_cfprintf_stride(FILE *stream, const char *format, const char *separator, const char *data, size_t size, size_t strid);
cul_bool cul_cfscanf(FILE *stream, const char *format, const char *separator, const char *data, size_t size);
cul_bool cul_cfscanf_stride(FILE *stream, const char *format, const char *separator, const char *data, size_t size, size_t stride);

cul_bool cul_cfwrite(FILE *stream, const char *data, size_t size);
cul_bool cul_cfwrite_stride(FILE *stream, const char *data, size_t size, size_t stride);
cul_bool cul_cfread(FILE *stream, const char *data, size_t size);
cul_bool cul_cfread_stride(FILE *stream, const char *data, size_t size, size_t stride);

char cul_cmin(const char *data, size_t size);
char cul_cmin_stride(const char *data, size_t size, size_t stride);
static inline char cul_cmin_pair(char a, char b);
size_t cul_cmin_index(const char *data, size_t size);
size_t cul_cmin_index_stride(const char *data, size_t size, size_t stride);

char cul_cmax(const char *data, size_t size);
char cul_cmax_stride(const char *data, size_t size, size_t stride);
static inline char cul_cmax_pair(char a, char b);
size_t cul_cmax_index(const char *data, size_t size);
size_t cul_cmax_index_stride(const char *data, size_t size, size_t stride);

void cul_cminmax(const char *data, size_t size, char *min, char *max);
void cul_cminmax_stride(const char *data, size_t size, size_t stride, char *min, char *max);
void cul_cminmax_index(const char *data, size_t size, size_t *min_index, size_t *max_index);
void cul_cminmax_index_stride(const char *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void cul_cset_all(char *data, size_t size, char value);
void cul_cset_all_stride(char *data, size_t size, size_t stride, char value);
void cul_cadd_scalar(char *data, size_t size, char value);
void cul_cadd_scalar_stride(char *data, size_t size, size_t stride, char value);
void cul_cmul_scalar(char *data, size_t size, char value);
void cul_cmul_scalar_stride(char *data, size_t size, size_t stride, char value);

void cul_cadd(char *data_out, const char *data, size_t size);
void cul_cadd_stride(char *data_out, const char *data, size_t size, size_t stride_out, size_t stride);
void cul_csub(char *data_out, const char *data, size_t size);
void cul_csub_stride(char *data_out, const char *data, size_t size, size_t stride_out, size_t stride);
void cul_cmul(char *data_out, const char *data, size_t size);
void cul_cmul_stride(char *data_out, const char *data, size_t size, size_t stride_out, size_t stride);
void cul_cdiv(char *data_out, const char *data, size_t size);
void cul_cdiv_stride(char *data_out, const char *data, size_t size, size_t stride_out, size_t stride);

double cul_csum(const char *data, size_t size);
double cul_csum_stride(const char *data, size_t size, size_t stride);
double cul_cmean(const char *data, size_t size);
double cul_cmean_stride(const char *data, size_t size, size_t stride);
double cul_cvariance(const char *data, size_t size, double mean);
double cul_cvariance_stride(const char *data, size_t size, size_t stride, double mean);

char *cul_clfind(char key, char *data, size_t size);
char *cul_clfind_stride(char key, char *data, size_t size, size_t stride);
char *cul_cbfind(char key, char *data, size_t size);
char *cul_cbfind_stride(char key, char *data, size_t size, size_t stride);
void cul_csort_asc(char *data, size_t size);
void cul_csort_asc_stride(char *data, size_t size, size_t stride);
void cul_csort_desc(char *data, size_t size);
void cul_csort_desc_stride(char *data, size_t size, size_t stride);
char *cul_cunique(char *data, size_t size);
char *cul_cunique_stride(char *data, size_t size, size_t stride);

/* implemenations */

static inline void cul_cswap_pos(char *data, size_t i, size_t j) {
	char tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

static inline char cul_cmin_pair(char a, char b) {
	return a < b ? a : b;
}

static inline char cul_cmax_pair(char a, char b) {
	return a > b ? a : b;
}

#endif /* CUL_BASE_CHAR_H */
