#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(copy)(ATOM *data_a, const ATOM *data_b, size_t size) {
		memcpy(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_overlap)(ATOM *data_a, const ATOM *data_b, size_t size) {
		memmove(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_stride)(ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
		const ATOM *const end = data_b + size * stride_b;
		for( ; data_b < end; data_a += stride_a, data_b += stride_b)
			*data_a = *data_b;
	}

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b) {
		const ATOM *const end = data_b + size;

		/* move through all rows */
		for(; data_b < end; data_a += tda_a, data_b += tda_b)
			/* copy single row */
			memcpy(data_a, data_b, tda_size*sizeof(ATOM));
	}

#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(copy)(ATOM *data_a, const ATOM *data_b, size_t size, cul_cpy_f *cpy_item) {
		const ATOM *const end = data_b + size;
		for( ; data_b < end; ++data_a, ++data_b)
			*data_a = cpy_item(*data_b);
	}

	void FUNCTION(copy_overlap)(ATOM *data_a, const ATOM *data_b, size_t size, cul_cpy_f *cpy_item) {
		if( data_b < data_a ) {
			const ATOM *const end = data_b + size;
			for( ; data_b < end; ++data_a, ++data_b)
				*data_a = cpy_item(*data_b);
		}
		else {
			const ATOM *const start = data_b;
			for( data_a += size - 1, data_b += size - 1; data_b >= start; --data_a, --data_b)
				*data_a = cpy_item(*data_b);
		}
	}

	void FUNCTION(copy_stride)(ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b, cul_cpy_f *cpy_item) {
		const ATOM *const end = data_b + size * stride_b;
		for( ; data_b < end; data_a += stride_a, data_b += stride_b)
			*data_a = cpy_item(*data_b);
	}

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b, cul_cpy_f *cpy_item) {
		const ATOM *const end = data_b + size, *tda_end;
		const size_t tda_size_b = tda_b;

		/* adjust tda jumps */
		tda_a -= tda_size;
		tda_b -= tda_size;

		/* move through all rows */
		for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_size_b) {
			/* copy one row */
			for( ; data_b < tda_end; ++data_a, ++data_b)
				*data_a = cpy_item(*data_b);
			/* adjust size, possible empty space */
			data_a += tda_a;
			data_b += tda_b;
		}
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	int FUNCTION(compare)(const ATOM *data_a, const ATOM *data_b, size_t size) {
		return memcmp(data_a, data_b, size*sizeof(ATOM));
	}

	int FUNCTION(compare_stride)(const ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
		const ATOM *const end = data_b + size * stride_b;
		for( ; data_b < end; data_a += stride_a, data_b += stride_b)
			if( *data_a != *data_b ) {
				if( *data_a > *data_b )
					return 1;
				return -1;
			}
		return 0;
	}

	int FUNCTION(compare_tda)(const ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b) {
		const ATOM *const end = data_b + size;

		/* move through all rows */
		for(int cmp; data_b < end; data_a += tda_a, data_b += tda_b)
			/* check single row */
			if( (cmp = memcmp(data_a, data_b, tda_size*sizeof(ATOM)) ) )
				return cmp;
		return 0;
	}
#else /* TEMPLATE_CUL_PTR */
	int FUNCTION(compare)(const ATOM *data_a, const ATOM *data_b, size_t size, cul_cmp_f *cmp_f) {
		const ATOM *const end = data_b + size;
		for(int cmp; data_b < end; ++data_a, ++data_b)
			if( (cmp = cmp_f(data_a, data_b)) )
				return cmp > 0? 1: -1;
		return 0;
	}

	int FUNCTION(compare_stride)(const ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b, cul_cmp_f *cmp_f) {
		const ATOM *const end = data_b + size * stride_b;
		for(int cmp; data_b < end; data_a += stride_a, data_b += stride_b)
			if( (cmp = cmp_f(data_a, data_b)) )
				return cmp > 0? 1: -1;
		return 0;
	}

	int FUNCTION(compare_tda)(const ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b, cul_cmp_f *cmp_f) {
		const ATOM *const end = data_b + size, *tda_end;
		const size_t tda_size_b = tda_b;

		/* adjust tda jumps */
		tda_a -= tda_size;
		tda_b -= tda_size;

		/* move through all rows */
		for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_size_b) {
			/* copy one row */
			for(int cmp; data_b < tda_end; ++data_a, ++data_b)
				if( (cmp = cmp_f(data_a, data_b)) )
					return cmp > 0? 1: -1;
			/* adjust size, possible empty space */
			data_a += tda_a;
			data_b += tda_b;
		}
		return 0;
	}
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(swap)(ATOM *data_a, ATOM *data_b, size_t size) {
	ATOM tmp, *const end = data_a + size;
	for( ; data_a < end; ++data_a, ++data_b)
		CUL_SWAP(*data_a, *data_b, tmp);
}

void FUNCTION(swap_stride)(ATOM *data_a, ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
	ATOM tmp, *const end = data_a + size * stride_a;
	for( ; data_a < end; data_a += stride_a, data_b += stride_b)
		CUL_SWAP(*data_a, *data_b, tmp);
}

void FUNCTION(swap_tda)(ATOM *data_a, ATOM *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b) {
	const size_t tda_b = tda_size + tda_stride_b;
	const ATOM *const end = data_b + size, *tda_end;
	ATOM tmp;

	/* move through all rows */
	for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_b) {
		/* copy one row */
		for( ; data_b < tda_end; ++data_a, ++data_b)
			CUL_SWAP(*data_a, *data_b, tmp);
		/* adjust size, tda_stride empty space */
		data_a += tda_stride_a;
		data_b += tda_stride_b;
	}
}

void FUNCTION(permute)(ATOM *data, const size_t *permutation, size_t size) {
	ATOM tmp;

	for( size_t k=0; k<size; ++k) {
		size_t k0, kn = permutation[k];

		for( k0 = kn; kn<k; k0 = kn)
			kn = permutation[ k0 ];

		if( kn == k )
			continue;

		CUL_SWAP(data[kn], data[k], tmp);
	}
}

void FUNCTION(permute_stride)(ATOM *data, const size_t *permutation, size_t size, size_t stride) {
	ATOM tmp;

	/* adjust size to actual number of items */
	size /= stride;

	for( size_t k=0; k<size; ++k) {
		size_t k0, kn = permutation[k];

		for( k0 = kn; kn<k; k0 = kn)
			kn = permutation[ k0 ];

		if( kn == k )
			continue;

		CUL_SWAP(data[kn*stride], data[k*stride], tmp);
	}
}

void FUNCTION(reverse)(ATOM *data, size_t size) {
	ATOM tmp, *end;
	for( end = data + size - 1; data < end; ++data, --end)
		CUL_SWAP(*data, *end, tmp);
}

void FUNCTION(reverse_stride)(ATOM *data, size_t size, size_t stride) {
	ATOM tmp, *end;
	for( end = data + (size - 1) * stride; data < end; data += stride, end -= stride)
		CUL_SWAP(*data, *end, tmp);
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(set_all)(ATOM *data, size_t size, ATOM value) {
		const ATOM *end = data + size;
		for( ; data < end; ++data)
			*data = value;
		return;
	}

	void FUNCTION(set_all_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride)
			*data = value;
		return;
	}

	void FUNCTION(add_scalar)(ATOM *data, size_t size, ATOM value) {
		const ATOM *end = data + size;
		for( ; data < end; ++data)
			*data += value;
		return;
	}

	void FUNCTION(add_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride)
			*data += value;
		return;
	}

	void FUNCTION(mul_scalar)(ATOM *data, size_t size, ATOM value) {
		const ATOM *end = data + size;
		for( ; data < end; ++data)
			*data *= value;
		return;
	}

	void FUNCTION(mul_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride)
			*data *= value;
		return;
	}

	void FUNCTION(add)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		for( ; data < end; ++data, ++data_out)
			*data_out += *data;
		return;
	}

	void FUNCTION(add_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride, data += stride_out)
			*data_out += *data;
		return;
	}

	void FUNCTION(sub)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		for( ; data < end; ++data, ++data_out)
			*data_out -= *data;
		return;
	}

	void FUNCTION(sub_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *end = data + size * stride;
		for(end = data + size; data < end; data += stride, data += stride_out)
			*data_out -= *data;
		return;
	}

	void FUNCTION(mul)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		for( ; data < end; ++data, ++data_out)
			*data_out *= *data;
		return;
	}

	void FUNCTION(mul_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride, data += stride_out)
			*data_out *= *data;
		return;
	}

	void FUNCTION(div)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		for( ; data < end; ++data, ++data_out)
			*data_out /= *data;
		return;
	}

	void FUNCTION(div_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *end = data + size * stride;
		for( ; data < end; data += stride, data += stride_out)
			*data_out /= *data;
		return;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	double FUNCTION(sum)(const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		double sum = 0.0;
		for(; data < end; ++data)
			sum += *data;
		return sum;
	}

	double FUNCTION(sum_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *end = data + size * stride;
		double sum = 0.0;
		for(; data < end; data += stride)
			sum += *data;
		return sum;
	}

	double FUNCTION(mean)(const ATOM *data, size_t size) {
		const ATOM *end = data + size;
		double mean = 0.0;
		for(; data < end; ++data)
			mean += *data;
		return mean /= size;
	}

	double FUNCTION(mean_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *end = data + size * stride;
		double mean = 0.0;
		for(; data < end; data += stride)
			mean += *data;
		return mean /= size;
	}

	double FUNCTION(variance)(const ATOM *data, size_t size, double mean) {
		const ATOM *end = data + size;
		double variance = 0.0;
		for(; data < end; ++data)
			variance += (*data - mean)*(*data - mean);
		return variance /= size;
	}

	double FUNCTION(variance_stride)(const ATOM *data, size_t size, size_t stride, double mean) {
		const ATOM *end = data + size * stride;
		double variance = 0.0;
		for(; data < end; data += stride)
			variance += (*data - mean)*(*data - mean);
		return variance /= size;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */
