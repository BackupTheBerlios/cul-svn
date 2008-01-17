#ifndef __CUL_PRV_DCOPY_H__
#define __CUL_PRV_DCOPY_H__

#include <cul/cul_core.h>
#include <string.h>

static inline void cul_dcopy(double *data, const double *other, size_t size);
static inline void cul_dmove(double *data, const double *other, size_t size);

void cul_dcopy_stride       (double *data, const double *other, size_t size, size_t stride, size_t other_stride);
void cul_dcopy_stride_data  (double *data, const double *other, size_t size, size_t stride);
void cul_dcopy_stride_other (double *data, const double *other, size_t size, size_t other_stride);

void cul_dcopy_tda          (double *data, const double *other, size_t size_x, size_t size_y, size_t tda, size_t other_tda);

static inline void cul_dcopy(double *data, const double *other, size_t size) {
	memcpy(data, other, size*sizeof(double));
}

static inline void cul_dmove(double *data, const double *other, size_t size) {
	memmove(data, other, size*sizeof(double));
}

#endif /* __CUL_PRV_DSORT_H__ */

