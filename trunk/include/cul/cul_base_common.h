#if !defined(CUL_BASE_COMMON_H)
#define CUL_BASE_COMMON_H

#include <cul/cul_global_base.h>
#include <stdio.h>

static inline size_t cul_matrix_pos(size_t x, size_t y, size_t width);

int cul_fscanf_skip_line(FILE *stream);

/* implementations */

static inline size_t cul_matrix_pos(size_t x, size_t y, size_t width) {
	return y * width + x;
}

#endif
