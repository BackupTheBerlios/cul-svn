#ifndef __CUL_PRV_PSORT_H__
#define __CUL_PRV_PSORT_H__

#include <cul/cul_core.h>

void cul_psort       (cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
void cul_psort_stride(cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);

#endif /* __CUL_PRV_PSORT_H__ */

