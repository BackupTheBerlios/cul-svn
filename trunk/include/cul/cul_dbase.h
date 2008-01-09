#ifndef __CUL_DBASE_H__
#define __CUL_DBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

double   cul_dmin                 (const double *data, size_t size);
double   cul_dmin_stride          (const double *data, size_t size, size_t stride);
static inline double cul_dmin_2   (double value_a, double value_b);
size_t   cul_dmin_index           (const double *data, size_t size);
size_t   cul_dmin_index_stride    (const double *data, size_t size, size_t stride);
double   cul_dmax                 (const double *data, size_t size);
double   cul_dmax_stride          (const double *data, size_t size, size_t stride);
static inline double cul_dmax_2   (double value_a, double value_b);
size_t   cul_dmax_index           (const double *data, size_t size);
size_t   cul_dmax_index_stride    (const double *data, size_t size, size_t stride);
void     cul_dminmax              (const double *data, size_t size, double *min, double *max);
void     cul_dminmax_stride       (const double *data, size_t size, size_t stride, double *min, double *max);
void     cul_dminmax_index        (const double *data, size_t size, size_t *min_index, size_t *max_index);
void     cul_dminmax_index_stride (const double *data, size_t size, size_t stride, size_t *min_index, size_t *max_index);

void     cul_dsort_asc            (double *data, size_t size);
void     cul_dsort_asc_stride     (double *data, size_t size, size_t stride);
void     cul_dsort_desc           (double *data, size_t size);
void     cul_dsort_desc_stride    (double *data, size_t size, size_t stride);
double  *cul_dunique              (double *data, size_t size);
double  *cul_dfind                (const double *data, size_t size, double key);
double  *cul_dbfind               (const double *data, size_t size, double key);

cul_bool cul_dfprintf             (FILE *stream, const double *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_dfprintf_stride      (FILE *stream, const double *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_dfscanf              (FILE *stream, const double *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_dfscanf_stride       (FILE *stream, const double *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline double cul_dmin_2(double value_a, double value_b) {
	return value_a < value_b ? value_a : value_b;
}

static inline double cul_dmax_2(double value_a, double value_b) {
	return value_a > value_b ? value_a : value_b;
}

#endif /* __CUL_DBASE_H__ */
