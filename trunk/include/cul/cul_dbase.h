#ifndef __CUL_DBASE_H__
#define __CUL_DBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void     cul_dsort_asc            (double *data, size_t size);
void     cul_dsort_asc_stride     (double *data, size_t size, size_t stride);
void     cul_dsort_desc           (double *data, size_t size);
void     cul_dsort_desc_stride    (double *data, size_t size, size_t stride);
double  *cul_dunique              (double *data, size_t size);
double  *cul_dfind                (const double *data, size_t size, double key);
double  *cul_dbfind               (const double *data, size_t size, double key);

/* implementations */

#endif /* __CUL_DBASE_H__ */
