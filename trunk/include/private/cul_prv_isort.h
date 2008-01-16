#ifndef __CUL_PRV_ISORT_H__
#define __CUL_PRV_ISORT_H__

#include <cul/cul_core.h>

void cul_isort_asc       (int *data, size_t size);
void cul_isort_asc_stride(int *data, size_t size, size_t stride);
void cul_isort_dsc       (int *data, size_t size);
void cul_isort_dsc_stride(int *data, size_t size, size_t stride);

#endif /* __CUL_PRV_ISORT_H__ */

