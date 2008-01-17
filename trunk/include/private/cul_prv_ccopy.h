#ifndef __CUL_PRV_CCOPY_H__
#define __CUL_PRV_CCOPY_H__

#include <cul/cul_core.h>
#include <string.h>

static inline void cul_ccopy(char *data, const char *other, size_t size);
static inline void cul_cmove(char *data, const char *other, size_t size);

void cul_ccopy_stride       (char *data, const char *other, size_t size, size_t stride, size_t other_stride);
void cul_ccopy_stride_data  (char *data, const char *other, size_t size, size_t stride);
void cul_ccopy_stride_other (char *data, const char *other, size_t size, size_t other_stride);

void cul_ccopy_tda          (char *data, const char *other, size_t size_x, size_t size_y, size_t tda, size_t other_tda);

static inline void cul_ccopy(char *data, const char *other, size_t size) {
	memcpy(data, other, size*sizeof(char));
}

static inline void cul_cmove(char *data, const char *other, size_t size) {
	memmove(data, other, size*sizeof(char));
}

#endif /* __CUL_PRV_CSORT_H__ */

