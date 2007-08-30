#ifndef __CUL_PBASE_H__
#define __CUL_PBASE_H__

#include <cul/cul_base_global.h>

void     cul_pfree            (cul_ptr *data, size_t size, cul_free_f *free);

void     cul_pcopy            (cul_ptr *data, const cul_ptr *other, size_t size);
void     cul_pcopy_overlap    (cul_ptr *data, const cul_ptr *other, size_t size);
void     cul_pcopy_stride     (cul_ptr *data, const cul_ptr *other, size_t size, size_t stride, size_t other_stride);
void     cul_pcopy_tda        (cul_ptr *data, const cul_ptr *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);
void     cul_pswap            (cul_ptr *data, cul_ptr *other, size_t size);
void     cul_pswap_stride     (cul_ptr *data, cul_ptr *other, size_t size, size_t stride, size_t other_stride);
void     cul_pswap_tda        (cul_ptr *data, cul_ptr *other, size_t size, size_t tda_size, size_t tda, size_t other_tda);

cul_ptr  cul_pdetach          (cul_ptr *data, size_t size, cul_cpy_f *cpy_f);
cul_ptr  cul_pdetach_stride   (cul_ptr *data, size_t size, size_t stride, cul_cpy_f *cpy_f);
cul_ptr  cul_pdetach_tda      (cul_ptr *data, size_t size, size_t tda_size, size_t tda, cul_cpy_f *cpy_f);

void     cul_pset             (cul_ptr *data, size_t size, cul_ptr value);
void     cul_pset_stride      (cul_ptr *data, size_t size, size_t stride, cul_ptr value);
void     cul_pset_tda         (cul_ptr *data, size_t size, size_t tda_size, size_t tda, cul_ptr value);
void     cul_pzero            (cul_ptr *data, size_t size);

void     cul_ppermute         (cul_ptr *data, const size_t *permutation, size_t size);
void     cul_ppermute_stride  (cul_ptr *data, const size_t *permutation, size_t size, size_t stride);
void     cul_preverse         (cul_ptr *data, size_t size);
void     cul_preverse_stride  (cul_ptr *data, size_t size, size_t stride);

void     cul_psort            (cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
void     cul_psort_stride     (cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);
cul_ptr *cul_punique          (cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
cul_ptr *cul_punique_stride   (cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);
cul_ptr *cul_pfind            (const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pfind_stride     (const cul_ptr *data, size_t size, size_t stride, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pbfind           (const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pbfind_stride    (const cul_ptr *data, size_t size, size_t stride, cul_ptr key, cul_cmp_f *cmp_f);
void     cul_pforeach         (const cul_ptr *data, size_t size, cul_foreach_f *foreach_f, cul_ptr user_data);
void     cul_pforeach_stride  (const cul_ptr *data, size_t size, size_t stride, cul_foreach_f *foreach_f, cul_ptr user_data);

/* implementations */

#endif /* __CUL_PBASE_H__ */
