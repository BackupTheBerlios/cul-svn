#ifndef __CUL_PRV_PCOPY_H__
#define __CUL_PRV_PCOPY_H__

#include <cul/cul_core.h>
#include <string.h>

static inline void cul_pcopy(cul_ptr *data, const cul_ptr *other, size_t size);
static inline void cul_pmove(cul_ptr *data, const cul_ptr *other, size_t size);

void cul_pcopy_stride       (cul_ptr *data, const cul_ptr *other, size_t size, size_t stride, size_t other_stride);
void cul_pcopy_stride_data  (cul_ptr *data, const cul_ptr *other, size_t size, size_t stride);
void cul_pcopy_stride_other (cul_ptr *data, const cul_ptr *other, size_t size, size_t other_stride);

void cul_pcopy_tda          (cul_ptr *data, const cul_ptr *other, size_t size_x, size_t size_y, size_t tda, size_t other_tda);

static inline void cul_pcopy(cul_ptr *data, const cul_ptr *other, size_t size) {
	memcpy(data, other, size*sizeof(cul_ptr));
}

static inline void cul_pmove(cul_ptr *data, const cul_ptr *other, size_t size) {
	memmove(data, other, size*sizeof(cul_ptr));
}

#endif /* __CUL_PRV_PSORT_H__ */

