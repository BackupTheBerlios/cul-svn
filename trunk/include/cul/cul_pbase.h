#ifndef CUL_PBASE_H
#define CUL_PBASE_H

#include <cul/cul_base_global.h>
#include <stdio.h>

void cul_pcopy(cul_ptr *data_a, const cul_ptr *data_b, size_t size, cul_cpy_f *cpy_item);
void cul_pcopy_overlap(cul_ptr *data_a, const cul_ptr *data_b, size_t size, cul_cpy_f *cpy_item);
void cul_pcopy_stride(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b, cul_cpy_f *cpy_item);
void cul_pcopy_tda(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b, cul_cpy_f *cpy_item);

void cul_pswap(cul_ptr *data_a, cul_ptr *data_b, size_t size);
void cul_pswap_stride(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_pswap_tda(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_pswap_pos(cul_ptr *data_a, size_t i, size_t j);
void cul_ppermute(cul_ptr *data, const size_t *permutation, size_t size);
void cul_ppermute_stride(cul_ptr *data, const size_t *permutation, size_t size, size_t stride);
void cul_preverse(cul_ptr *data, size_t size);
void cul_preverse_stride(cul_ptr *data, size_t size, size_t stride);

cul_ptr *cul_plfind(cul_ptr key, cul_ptr *data, size_t size, cul_eq_f *eq);
cul_ptr *cul_plfind_stride(cul_ptr key, cul_ptr *data, size_t size, size_t stride, cul_eq_f *eq);
cul_ptr *cul_pbfind(cul_ptr key, cul_ptr *data, size_t size, cul_cmp_f *cmp);
cul_ptr *cul_pbfind_stride(cul_ptr key, cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp);
void cul_psort(cul_ptr *data, size_t size, cul_cmp_f *cmp);
void cul_psort_stride(cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp);
cul_ptr *cul_punique(cul_ptr *data, size_t size, cul_eq_f *eq);
cul_ptr *cul_punique_stride(cul_ptr *data, size_t size, size_t stride, cul_eq_f *eq);

/* implementations */

static inline void cul_pswap_pos(cul_ptr *data, size_t i, size_t j) {
	cul_ptr tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

#endif /* CUL_PBASE_H */
