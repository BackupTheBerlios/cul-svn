#ifndef __CUL_PRV_USORT_H__
#define __CUL_PRV_USORT_H__

#include <cul/cul_core.h>

void cul_usort_asc       (size_t *data, size_t size);
void cul_usort_asc_stride(size_t *data, size_t size, size_t stride);
void cul_usort_dsc       (size_t *data, size_t size);
void cul_usort_dsc_stride(size_t *data, size_t size, size_t stride);

#endif /* __CUL_PRV_USORT_H__ */

