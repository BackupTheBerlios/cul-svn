#ifndef __CUL_PRV_ICOPY_H__
#define __CUL_PRV_ICOPY_H__

#include <cul/cul_core.h>
#include <string.h>

static inline void cul_icopy(int *data, const int *other, size_t size);
static inline void cul_imove(int *data, const int *other, size_t size);

void cul_icopy_stride       (int *data, const int *other, size_t size, size_t stride, size_t other_stride);
void cul_icopy_stride_data  (int *data, const int *other, size_t size, size_t stride);
void cul_icopy_stride_other (int *data, const int *other, size_t size, size_t other_stride);

void cul_icopy_tda          (int *data, const int *other, size_t size_x, size_t size_y, size_t tda, size_t other_tda);

static inline void cul_icopy(int *data, const int *other, size_t size) {
	memcpy(data, other, size*sizeof(int));
}

static inline void cul_imove(int *data, const int *other, size_t size) {
	memmove(data, other, size*sizeof(int));
}

#endif /* __CUL_PRV_ISORT_H__ */

