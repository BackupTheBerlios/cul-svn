#ifndef TEMPLATE_CUL_PTR
	ATOM * FUNCTION(unique)(ATOM *data, size_t size) {
		ATOM *cur = data + 1, *const end = data + size;
		for(++data; data < end; ++data) {
			if( *(data - 1) == *data )
				continue;
			*cur = *data;
			++cur;
		}
		return cur;
	}

	ATOM * FUNCTION(unique_stride)(ATOM *data, size_t size, size_t stride) {
		ATOM *cur = data + stride, * const end = data + size * stride;
		for( data += stride; data < end; data += stride) {
			if( *(data - stride) == *data )
				continue;
			*cur = *data;
			cur += stride;
		}
		return cur;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM * FUNCTION(unique)(ATOM *data, size_t size, cul_eq_f *eq) {
		ATOM *cur = data + 1, *const end = data + size;
		for(++data; data < end; ++data) {
			if( eq(data - 1, data) )
				continue;
			*cur = *data;
			++cur;
		}
		return cur;
	}

	ATOM * FUNCTION(unique_stride)(ATOM *data, size_t size, size_t stride, cul_eq_f *eq) {
		ATOM *cur = data + stride, *const end = data + size * stride;
		for( data += stride; data < end; data += stride) {
			if( eq(data - stride, data) )
				continue;
			*cur = *data;
			cur += stride;
		}
		return cur;
	}
#endif /* TEMPLATE_CUL_PTR */
