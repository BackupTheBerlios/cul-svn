ATOM *FUNCTION(lfind)(ATOM key, ATOM *data, size_t size, cul_eq_f *eq) {
	ATOM *const end = data + size;
	for( ; data < end; ++data)
#if !defined(TEMPLATE_CUL_PTR)
		if( eq(data, &key) )
#else
		if( eq(*data, key) )
#endif
			break;
	return data == end? NULL: data;
}

ATOM *FUNCTION(lfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_eq_f *eq) {
	ATOM *const end = data + size * stride;
	for( ; data < end; data += stride)
#if !defined(TEMPLATE_CUL_PTR)
			if( eq(data, &key) )
#else
			if( eq(*data, key) )
#endif
				break;
	return data == end? NULL: data;
}

ATOM *FUNCTION(bfind)(ATOM key, ATOM *data, size_t size, cul_cmp_f *cmp) {
	ATOM *end = data + size;
	int cmp_res;
	for( size >>= 1; size > 0; size >>= 1) {
#if !defined(TEMPLATE_CUL_PTR)
		cmp_res = cmp((data + size), &key);
#else
		cmp_res = cmp(*(data + size), key);
#endif
		if( cmp_res < 0 ) {
			data += size + 1;
			size = end - data;
		}
		else if( cmp_res > 0 )
			end = data + size;
		else
			return data + size;
	}
#if !defined(TEMPLATE_CUL_PTR)
	if( cmp(data, &key) == 0 )
#else
	if( cmp(*data, key) == 0 )
#endif
		return data;
	return NULL;
}

ATOM *FUNCTION(bfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp) {
	ATOM *end = data + size * stride;
	int cmp_res;
	for( size >>= 1; size > 0 ; size >>= 1) {
#if !defined(TEMPLATE_CUL_PTR)
		cmp_res = cmp((data + size * stride), &key);
#else
		cmp_res = cmp(*(data + size * stride), key);
#endif
		if( cmp_res < 0 ) {
			data += (size + 1) * stride;
			size = (end - data) / stride;
		}
		else if( cmp_res > 0 )
			end = data + size * stride;
		else
			return data + size * stride;
	}
#if !defined(TEMPLATE_CUL_PTR)
	if( cmp(data, &key) == 0 )
#else
	if( cmp(*data, key) == 0 )
#endif
		return data;
	return NULL;
}

#if !defined(TEMPLATE_CUL_PTR)
	ATOM *FUNCTION(lfind_eq)(ATOM key, ATOM *data, size_t size) {
		ATOM *const end = data + size;
		for( ; data < end; ++data)
			if( *data == key )
				break;
		return data == end? NULL: data;
	}

	ATOM *FUNCTION(bfind_eq)(ATOM key, ATOM *data, size_t size) {
		ATOM *end = data + size;
		for( size >>= 1; size > 0; size >>= 1) {
			const ATOM val = *(data + size);
			if( val < key ) {
				data += size + 1;
				size = end - data;
			}
			else if( val > key )
				end = data + size;
			else
				return data + size;
		}
		if( *data == key )
			return data;
		return NULL;
	}
#endif /* !defined(TEMPLATE_CUL_PTR) */
