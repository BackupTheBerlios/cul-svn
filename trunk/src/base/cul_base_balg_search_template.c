#ifndef TEMPLATE_CUL_PTR
	ATOM *FUNCTION(lfind)(ATOM key, ATOM *data, size_t size) {
		ATOM *const end = data + size;
		for( ; data < end; ++data)
			if( *data == key )
				return data;
		return NULL;
	}

	ATOM *FUNCTION(lfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride) {
		ATOM *const end = data + size * stride;
		for( ; data < end; data += stride)
			if( *data == key )
				return data;
		return NULL;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM *FUNCTION(lfind)(ATOM key, ATOM *data, size_t size, cul_eq_f *eq) {
		ATOM *const end = data + size;
		for( ; data < end; ++data)
			if( eq(data, &key) )
				return data;
		return NULL;
	}

	ATOM *FUNCTION(lfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_eq_f *eq) {
		ATOM *const end = data + size * stride;
		for( ; data < end; data += stride)
			if( eq(data, &key) )
				return data;
		return NULL;
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM *FUNCTION(bfind)(ATOM key, ATOM *data, size_t size) {
		ATOM *end = data + size;
		for( size >>= 1; size > 0; size >>= 1) {
			const ATOM val = *(data + size);
			if( val < key ) {
				data += size + 1;
				size = end - data;
			}	else if( val > key )
				end = data + size;
			else
				return data + size;
		}
		if( *data == key )
			return data;
		return NULL;
	}

	ATOM *FUNCTION(bfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride) {
		ATOM *end = data + size * stride;
		for( size >>= 1; size > 0 ; size >>= 1) {
			const ATOM val = *(data + size * stride);
			if( val < key ) {
				data += (size + 1) * stride;
				size = (end - data) / stride;
			}	else if( val > key )
				end = data + size * stride;
			else
				return data + size * stride;
		}
		if( *data == key )
			return data;
		return NULL;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM *FUNCTION(bfind)(ATOM key, ATOM *data, size_t size, cul_cmp_f *cmp) {
		ATOM *end = data + size;
		for( size >>= 1; size > 0; size >>= 1) {
			int cmp_res = cmp(*(data + size), &key);
			if( cmp_res < 0 ) {
				data += size + 1;
				size = end - data;
			}
			else if( cmp_res > 0 )
				end = data + size;
			else
				return data + size;
		}
		if( cmp(*data, key) == 0 )
			return data;
		return NULL;
	}

	ATOM *FUNCTION(bfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp) {
		ATOM *end = data + size * stride;
		for( size >>= 1; size > 0 ; size >>= 1) {
			int cmp_res = cmp(*(data + size * stride), &key);
			if( cmp_res < 0 ) {
				data += (size + 1) * stride;
				size = (end - data) / stride;
			}
			else if( cmp_res > 0 )
				end = data + size * stride;
			else
				return data + size * stride;
		}
		if( cmp(*data, key) == 0 )
			return data;
		return NULL;
	}
#endif /* TEMPLATE_CUL_PTR */
