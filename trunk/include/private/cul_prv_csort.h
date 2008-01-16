#ifndef __CUL_PRV_CSORT_H__
#define __CUL_PRV_CSORT_H__

#include <cul/cul_core.h>

void cul_csort_asc       (char *data, size_t size);
void cul_csort_asc_stride(char *data, size_t size, size_t stride);
void cul_csort_dsc       (char *data, size_t size);
void cul_csort_dsc_stride(char *data, size_t size, size_t stride);

#endif /* __CUL_PRV_CSORT_H__ */
