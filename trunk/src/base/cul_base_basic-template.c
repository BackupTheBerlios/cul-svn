#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(copy)(ATOM *data_a, const ATOM *data_b, size_t size) {
		memcpy(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_overlap)(ATOM *data_a, const ATOM *data_b, size_t size) {
		memmove(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_stride)(ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
		const ATOM *const last = data_b + size * stride_b;
		for(; data_b < last; data_a += stride_a, data_b += stride_b)
			*data_a = *data_b;
	}

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b) {
		const ATOM *const last = data_b + size;

		/* move through all rows */
		for(; data_b < last; data_a += tda_a, data_b += tda_b)
			/* copy single row */
			memcpy(data_a, data_b, tda_size*sizeof(ATOM));
	}

#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(copy)(ATOM *data_a, const ATOM *data_b, size_t size, cul_cpy_f *cpy_item) {
		const ATOM *const last = data_b + size;
		for(; data_b < last; ++data_a, ++data_b)
			*data_a = cpy_item(*data_b);
	}

	void FUNCTION(copy_overlap)(ATOM *data_a, const ATOM *data_b, size_t size, cul_cpy_f *cpy_item) {
		if( data_b < data_a ) {
			const ATOM *const last = data_b + size;
			for(; data_b < last; ++data_a, ++data_b)
				*data_a = cpy_item(*data_b);
		}
		else {
			const ATOM *const first = data_b;
			for(data_a += size - 1, data_b += size - 1; data_b >= first; --data_a, --data_b)
				*data_a = cpy_item(*data_b);
		}
	}

	void FUNCTION(copy_stride)(ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b, cul_cpy_f *cpy_item) {
		const ATOM *const last = data_b + size * stride_b;
		for(; data_b < last; data_a += stride_a, data_b += stride_b)
			*data_a = cpy_item(*data_b);
	}

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_a, size_t tda_b, cul_cpy_f *cpy_item) {
		const ATOM *const last = data_b + size, *tda_last = data_b + tda_size;
		const size_t tda_size_b = tda_b;

		/* adjust tda jumps */
		tda_a -= tda_size;
		tda_b -= tda_size;

		/* move through all rows */
		for(; data_b < last; tda_last += tda_size_b) {
			/* copy one row */
			for(; data_b < tda_last; ++data_a, ++data_b)
				*data_a = cpy_item(*data_b);
			/* adjust size, possible empty space */
			data_a += tda_a;
			data_b += tda_b;
		}
	}
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(swap)(ATOM *data_a, ATOM *data_b, size_t size) {
	ATOM tmp, *const last = data_a + size;
	for(; data_a < last; ++data_a, ++data_b)
		CUL_SWAP(*data_a, *data_b, tmp);
}

void FUNCTION(swap_stride)(ATOM *data_a, ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
	ATOM tmp, *const last = data_a + size * stride_a;
	for(; data_a < last; data_a += stride_a, data_b += stride_b)
		CUL_SWAP(*data_a, *data_b, tmp);
}

void FUNCTION(swap_tda)(ATOM *data_a, ATOM *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b) {
	const size_t tda_b = tda_size + tda_stride_b;
	const ATOM *const last = data_b + size, *tda_last = data_b + tda_size;
	ATOM tmp;

	/* move through all rows */
	for(; data_b < last; tda_last += tda_b) {
		/* copy one row */
		for(; data_b < tda_last; ++data_a, ++data_b)
			CUL_SWAP(*data_a, *data_b, tmp);
		/* adjust size, tda_stride empty space */
		data_a += tda_stride_a;
		data_b += tda_stride_b;
	}
}

void FUNCTION(permute)(ATOM *data, const size_t *permutation, size_t size) {
	ATOM tmp;

	for(size_t k=0; k<size; ++k) {
		size_t k0, kn = permutation[k];

		for(k0 = kn; kn<k; k0 = kn)
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

	for(size_t k=0; k<size; ++k) {
		size_t k0, kn = permutation[k];

		for(k0 = kn; kn<k; k0 = kn)
			kn = permutation[ k0 ];

		if( kn == k )
			continue;

		CUL_SWAP(data[kn*stride], data[k*stride], tmp);
	}
}

void FUNCTION(reverse)(ATOM *data, size_t size) {
	ATOM tmp, *last = data + size - 1;
	for(; data < last; ++data, --last)
		CUL_SWAP(*data, *last, tmp);
}

void FUNCTION(reverse_stride)(ATOM *data, size_t size, size_t stride) {
	ATOM tmp, *last = data + (size - 1) * stride;
	for(; data < last; data += stride, last -= stride)
		CUL_SWAP(*data, *last, tmp);
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(set_all)(ATOM *data, size_t size, ATOM value) {
		const ATOM *last = data + size;
		for(; data < last; ++data)
			*data = value;
		return;
	}

	void FUNCTION(set_all_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride)
			*data = value;
		return;
	}

	void FUNCTION(add_scalar)(ATOM *data, size_t size, ATOM value) {
		const ATOM *last = data + size;
		for(; data < last; ++data)
			*data += value;
		return;
	}

	void FUNCTION(add_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride)
			*data += value;
		return;
	}

	void FUNCTION(mul_scalar)(ATOM *data, size_t size, ATOM value) {
		const ATOM *last = data + size;
		for(; data < last; ++data)
			*data *= value;
		return;
	}

	void FUNCTION(mul_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride)
			*data *= value;
		return;
	}

	void FUNCTION(add)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		for(; data < last; ++data, ++data_out)
			*data_out += *data;
		return;
	}

	void FUNCTION(add_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride, data += stride_out)
			*data_out += *data;
		return;
	}

	void FUNCTION(sub)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		for(; data < last; ++data, ++data_out)
			*data_out -= *data;
		return;
	}

	void FUNCTION(sub_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride, data += stride_out)
			*data_out -= *data;
		return;
	}

	void FUNCTION(mul)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		for(; data < last; ++data, ++data_out)
			*data_out *= *data;
		return;
	}

	void FUNCTION(mul_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride, data += stride_out)
			*data_out *= *data;
		return;
	}

	void FUNCTION(div)(ATOM *data_out, const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		for(; data < last; ++data, ++data_out)
			*data_out /= *data;
		return;
	}

	void FUNCTION(div_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride, data += stride_out)
			*data_out /= *data;
		return;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	double FUNCTION(sum)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		double sum = 0.0;
		for(; data < last; ++data)
			sum += *data;
		return sum;
	}

	double FUNCTION(sum_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		double sum = 0.0;
		for(; data < last; data += stride)
			sum += *data;
		return sum;
	}

	double FUNCTION(mean)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		double mean = 0.0;
		for(; data < last; ++data)
			mean += *data;
		return mean /= size;
	}

	double FUNCTION(mean_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		double mean = 0.0;
		for(; data < last; data += stride)
			mean += *data;
		return mean /= size;
	}

	double FUNCTION(variance)(const ATOM *data, size_t size, double mean) {
		const ATOM *last = data + size;
		double variance = 0.0;
		for(; data < last; ++data)
			variance += (*data - mean)*(*data - mean);
		return variance /= size;
	}

	double FUNCTION(variance_stride)(const ATOM *data, size_t size, size_t stride, double mean) {
		const ATOM *last = data + size * stride;
		double variance = 0.0;
		for(; data < last; data += stride)
			variance += (*data - mean)*(*data - mean);
		return variance /= size;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */
