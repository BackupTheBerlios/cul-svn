#if !defined(CUL_BASE_COMMON_H)
#define CUL_BASE_COMMON_H

#include <cul/cul_global_base.h>

static inline size_t cul_matrix_pos(size_t x, size_t y, size_t width);

/* implementations */

static inline size_t cul_matrix_pos(size_t x, size_t y, size_t width) {
	return y * width + x;
}

#endif
