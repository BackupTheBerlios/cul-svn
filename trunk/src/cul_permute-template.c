cul_errno FUNCTION(vector_permute)(TYPE(Vector) *this, const CulUVector *permutation) {
	if( this->size != permutation->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t *restrict permutation_data = permutation->data;
	ATOM tmp;

	const size_t size = this->size;
	for(size_t k = 0; k < size; ++k) {
		size_t k0, kn = permutation_data[k];

		for(k0 = kn; kn < k; k0 = kn)
			kn = permutation_data[ k0 ];

		if( kn == k )
			continue;

		CUL_SWAP(data[kn], data[k], tmp);
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_permute)(VIEW(Vector) *this, const CulUVector *permutation) {
	if( this->size != permutation->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t *restrict permutation_data = permutation->data;
	const size_t stride = this->stride, size = this->size;
	ATOM tmp;

	for(size_t k = 0; k < size; ++k) {
		size_t k0, kn = permutation_data[k];

		for(k0 = kn; kn < k; k0 = kn)
			kn = permutation_data[ k0 ];

		if( kn == k )
			continue;

		CUL_SWAP(data[kn * stride], data[k * stride], tmp);
	}

	return CUL_SUCCESS;
}

