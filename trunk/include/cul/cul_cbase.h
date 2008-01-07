#ifndef __CUL_CBASE_H__
#define __CUL_CBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

char     cul_cmin                 (const char *data, size_t size);
char     cul_cmin_stride          (const char *data, size_t size, size_t stride);
static inline char cul_cmin_2     (char value_a, char value_b);
size_t   cul_cmin_index           (const char *data, size_t size);
size_t   cul_cmin_index_stride    (const char *data, size_t size, size_t stride);
char     cul_cmax                 (const char *data, size_t size);
char     cul_cmax_stride          (const char *data, size_t size, size_t stride);
static inline char cul_cmax_2     (char value_a, char value_b);
size_t   cul_cmax_index           (const char *data, size_t size);
size_t   cul_cmax_index_stride    (const char *data, size_t size, size_t stride);
void     cul_cminmax              (const char *data, size_t size, char *min, char *max);
void     cul_cminmax_stride       (const char *data, size_t size, size_t stride, char *min, char *max);
void     cul_cminmax_index        (const char *data, size_t size, size_t *min_index, size_t *max_index);
void     cul_cminmax_index_stride (const char *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

double   cul_csum                 (const char *data, size_t size);
double   cul_csum_stride          (const char *data, size_t size, size_t stride);
double   cul_csum_tda             (const char *data, size_t size, size_t tda_size, size_t tda);
double   cul_cmean                (const char *data, size_t size);
double   cul_cmean_stride         (const char *data, size_t size, size_t stride);
double   cul_cmean_tda            (const char *data, size_t size, size_t tda_size, size_t tda);
double   cul_cvariance            (const char *data, size_t size);
double   cul_cvariance_stride     (const char *data, size_t size, size_t stride);
double   cul_cvariance_tda        (const char *data, size_t size, size_t tda_size, size_t tda);
double   cul_cvariance_mean       (const char *data, size_t size, double mean);
double   cul_cvariance_mean_stride(const char *data, size_t size, size_t stride, double mean);
double   cul_cvariance_mean_tda   (const char *data, size_t size, size_t tda_size, size_t tda, double mean);

void     cul_csort_asc            (char *data, size_t size);
void     cul_csort_asc_stride     (char *data, size_t size, size_t stride);
void     cul_csort_desc           (char *data, size_t size);
void     cul_csort_desc_stride    (char *data, size_t size, size_t stride);
char    *cul_cunique              (char *data, size_t size);
char    *cul_cfind                (const char *data, size_t size, char key);
char    *cul_cbfind               (const char *data, size_t size, char key);

cul_bool cul_cfprintf             (FILE *stream, const char *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfprintf_stride      (FILE *stream, const char *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfscanf              (FILE *stream, const char *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfscanf_stride       (FILE *stream, const char *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implemenations */

static inline char cul_cmin_2(char value_a, char value_b) {
	return value_a < value_b ? value_a : value_b;
}

static inline char cul_cmax_2(char value_a, char value_b) {
	return value_a > value_b ? value_a : value_b;
}

#endif /* __CUL_CBASE_H__ */
