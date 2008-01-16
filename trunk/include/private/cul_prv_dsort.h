#ifndef __CUL_PRV_DSORT_H__
#define __CUL_PRV_DSORT_H__

#include <cul/cul_core.h>

void cul_dsort_asc       (double *data, size_t size);
void cul_dsort_asc_stride(double *data, size_t size, size_t stride);
void cul_dsort_dsc       (double *data, size_t size);
void cul_dsort_dsc_stride(double *data, size_t size, size_t stride);

#endif /* __CUL_PRV_DSORT_H__ */

