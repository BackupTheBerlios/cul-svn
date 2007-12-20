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

cul_ptr  cul_pdetach          (cul_ptr *data, size_t size, cul_clone_f *clone_f);
cul_ptr  cul_pdetach_stride   (cul_ptr *data, size_t size, size_t stride, cul_clone_f *clone_f);
cul_ptr  cul_pdetach_tda      (cul_ptr *data, size_t size, size_t tda_size, size_t tda, cul_clone_f *clone_f);

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
void     cul_peach            (const cul_ptr *data, size_t size, cul_each_f *each_f, cul_ptr user_data);
void     cul_peach_stride     (const cul_ptr *data, size_t size, size_t stride, cul_each_f *each_f, cul_ptr user_data);

/* implementations */

#endif /* __CUL_PBASE_H__ */
