#ifndef CUL_PBASE_H
#define CUL_PBASE_H

#include <cul/cul_base_global.h>
#include <stdio.h>

void cul_pfree(cul_ptr *data, size_t size, cul_free_f *free);

void cul_pcopy(cul_ptr *data_a, const cul_ptr *data_b, size_t size);
void cul_pcopy_overlap(cul_ptr *data_a, const cul_ptr *data_b, size_t size);
void cul_pcopy_stride(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_pcopy_tda(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b);

cul_ptr cul_pdetach(cul_ptr *data, size_t size, cul_cpy_f *cpy_f);
cul_ptr cul_pdetach_stride(cul_ptr *data, size_t size, size_t stride, cul_cpy_f *cpy_f);
cul_ptr cul_pdetach_tda(cul_ptr *data, size_t size, size_t tda_size, size_t tda, cul_cpy_f *cpy_f);

void cul_pswap(cul_ptr *data_a, cul_ptr *data_b, size_t size);
void cul_pswap_stride(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_pswap_tda(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
void cul_ppermute(cul_ptr *data, const size_t *permutation, size_t size);
void cul_ppermute_stride(cul_ptr *data, const size_t *permutation, size_t size, size_t stride);
void cul_preverse(cul_ptr *data, size_t size);
void cul_preverse_stride(cul_ptr *data, size_t size, size_t stride);

void cul_pset(cul_ptr *data, size_t size, cul_ptr value);
void cul_pset_stride(cul_ptr *data, size_t size, size_t stride, cul_ptr value);

void cul_psort(cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
void cul_psort_stride(cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);
cul_ptr *cul_punique(cul_ptr *data, size_t size, cul_cmp_f *cmp_f);
cul_ptr *cul_punique_stride(cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp_f);
cul_ptr *cul_pfind(const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pfind_stride(const cul_ptr *data, size_t size, size_t stride, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pbfind(const cul_ptr *data, size_t size, cul_ptr key, cul_cmp_f *cmp_f);
cul_ptr *cul_pbfind_stride(const cul_ptr *data, size_t size, size_t stride, cul_ptr key, cul_cmp_f *cmp_f);

/* implementations */

#endif /* CUL_PBASE_H */
