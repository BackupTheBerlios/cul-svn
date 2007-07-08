#include <cul/cul_permutation.h>
#include <cul/cul_ubase.h>

cul_bool cul_permutation_valid(const CulUVector *p) {
	const size_t *restrict data = p->data;

	const size_t size = p->size;
	for( size_t i=0; i<size; ++i) {
		/* check for item value */
		if( data[i] >= size )
			return CUL_FALSE;

		/* check for duplicates */
		for(size_t j=0; j<i; ++j) if( data[j] == data[i] )
			return CUL_FALSE;
	}
	return CUL_TRUE;
}

void cul_permutation_identity(CulUVector *p) {
	size_t *restrict data = p->data;

	const size_t size = p->size;
	for( size_t i=0; i<size; ++i)
		data[i] = i;
}

void cul_permutation_shuffle(CulUVector *p, const CulRng *rng) {
	size_t *restrict data = p->data;
	size_t tmp, pos;

	for(size_t i = p->size - 1; i > 0; --i) {
		pos = cul_rng_get_real(rng) * (i+1);
		CUL_SWAP(data[i], data[pos], tmp);
	}
}

void cul_permutation_reverse(CulUVector *p) {
	size_t *restrict data = p->data;
	size_t tmp, pos;

	const size_t size = p->size;
	const size_t half = size >> 1;

	for(size_t i = 0; i < half; ++i) {
		pos = size - i - 1;
		CUL_SWAP(data[i], data[pos], tmp);
	}
}
