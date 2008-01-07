#ifndef __CUL_PBASE_H__
#define __CUL_PBASE_H__

#include <cul/cul_base_global.h>

void     cul_psort            (cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
void     cul_psort_stride     (cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);
cul_ptr *cul_punique          (cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
cul_ptr *cul_pfind            (const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pbfind           (const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);

/* implementations */

#endif /* __CUL_PBASE_H__ */
