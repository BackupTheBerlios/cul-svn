#ifndef __CUL_PRV_UCOPY_H__
#define __CUL_PRV_UCOPY_H__

#include <cul/cul_core.h>
#include <string.h>

static inline void cul_ucopy(size_t *data, const size_t *other, size_t size);
static inline void cul_umove(size_t *data, const size_t *other, size_t size);

void cul_ucopy_stride       (size_t *data, const size_t *other, size_t size, size_t stride, size_t other_stride);
void cul_ucopy_stride_data  (size_t *data, const size_t *other, size_t size, size_t stride);
void cul_ucopy_stride_other (size_t *data, const size_t *other, size_t size, size_t other_stride);

void cul_ucopy_tda          (size_t *data, const size_t *other, size_t size_x, size_t size_y, size_t tda, size_t other_tda);

static inline void cul_ucopy(size_t *data, const size_t *other, size_t size) {
	memcpy(data, other, size*sizeof(size_t));
}

static inline void cul_umove(size_t *data, const size_t *other, size_t size) {
	memmove(data, other, size*sizeof(size_t));
}

#endif /* __CUL_PRV_USORT_H__ */

