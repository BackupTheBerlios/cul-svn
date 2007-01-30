#if !defined(CUL_BASE_PTR_H)
#define CUL_BASE_PTR_H

#include <cul/cul_global_base.h>
#include <cul/cul_base_common.h>
#include <cul/cul_mem.h>
#include <stdio.h>

/* Allocation */

static inline cul_ptr *cul_pnew(size_t size);
static inline cul_ptr *cul_presize(cul_ptr *data, size_t size);
static inline void cul_pfree(cul_ptr *data);
static inline void cul_pfree_null(cul_ptr **data);
static inline void cul_pfree_items(cul_ptr *data, size_t size, cul_free_f *free_item);
static inline void cul_pfree_items_null(cul_ptr **data, size_t size, cul_free_f *free_item);

/* Copy */

void cul_pcopy(cul_ptr *data_a, const cul_ptr *data_b, size_t size, cul_cpy_f *cpy_item);
void cul_pcopy_overlap(cul_ptr *data_a, const cul_ptr *data_b, size_t size, cul_cpy_f *cpy_item);
void cul_pcopy_stride(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b, cul_cpy_f *cpy_item);
void cul_pcopy_tda(cul_ptr *data_a, const cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b, cul_cpy_f *cpy_item);

void cul_pswap(cul_ptr *data_a, cul_ptr *data_b, size_t size);
void cul_pswap_stride(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t stride_a, size_t stride_b);
void cul_pswap_tda(cul_ptr *data_a, cul_ptr *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b);
static inline void cul_pswap_pos(cul_ptr *data_a, size_t i, size_t j);

void cul_preverse(cul_ptr *data, size_t size);
void cul_preverse_stride(cul_ptr *data, size_t size, size_t stride);
void cul_ppermutation(cul_ptr *data, size_t size);
void cul_ppermutation_stride(cul_ptr *data, size_t size, size_t stride);

/* Basic Algorithms */

/* Search */
cul_ptr *cul_plfind(cul_ptr key, cul_ptr *data, size_t size, cul_eq_f *eq);
cul_ptr *cul_plfind_stride(cul_ptr key, cul_ptr *data, size_t size, size_t stride, cul_eq_f *eq);
cul_ptr *cul_pbfind(cul_ptr key, cul_ptr *data, size_t size, cul_cmp_f *cmp);
cul_ptr *cul_pbfind_stride(cul_ptr key, cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp);
/* Sort */
void cul_psort(cul_ptr *data, size_t size, cul_cmp_f *cmp);
void cul_psort_stride(cul_ptr *data, size_t size, size_t stride, cul_cmp_f *cmp);
/* Unique */
cul_ptr *cul_punique(cul_ptr *data, size_t size, cul_eq_f *eq);
cul_ptr *cul_punique_stride(cul_ptr *data, size_t size, size_t stride, cul_eq_f *eq);

/* Inline definitions */

static inline cul_ptr *cul_pnew(size_t size) {
	return (cul_ptr *)cul_malloc(size * sizeof(cul_ptr));
}

static inline cul_ptr *cul_presize(cul_ptr *data, size_t size) {
	return (cul_ptr *)cul_realloc(data, size * sizeof(cul_ptr));
}

static inline void cul_pfree(cul_ptr *data) {
	cul_free(data);
}

static inline void cul_pfree_null(cul_ptr **data) {
	cul_free(*data);
	*data = NULL;
}

static inline void cul_pfree_items(cul_ptr *data, size_t size, cul_free_f *free_item) {
	if( free_item != NULL )
		while( size-- > 0 )
			free_item(data[size]);
	cul_free(data);
}

static inline void cul_pfree_items_null(cul_ptr **data, size_t size, cul_free_f *free_item) {
	cul_pfree_items(*data, size, free_item);
	*data = NULL;
}

static inline void cul_pswap_pos(cul_ptr *data, size_t i, size_t j) {
	cul_ptr tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

#endif
