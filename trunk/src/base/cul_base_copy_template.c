#if !defined(TEMPLATE_CUL_PTR)
	void FUNCTION(copy)(ATOM *data_a, const ATOM *data_b, size_t size) {
		cul_memcpy(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_overlap)(ATOM *data_a, const ATOM *data_b, size_t size) {
		cul_memmove(data_a, data_b, size*sizeof(ATOM));
	}

	void FUNCTION(copy_stride)(ATOM *data_a, const ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
		const ATOM *const end = data_b + size * stride_b;
		for( ; data_b < end; data_a += stride_a, data_b += stride_b)
			*data_a = *data_b;
	}

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b) {
		const size_t tda_b = tda_size + tda_stride_b;
		const ATOM *const end = data_b + size, *tda_end;

		/* move through all rows */
		for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_b) {
			/* copy one row */
			for( ; data_b < tda_end; ++data_a, ++data_b)
				*data_a = *data_b;
			/* adjust size, tda_stride empty space */
			data_a += tda_stride_a;
			data_b += tda_stride_b;
		}
	}
#else
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

	void FUNCTION(copy_tda)(ATOM *data_a, const ATOM *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b, cul_cpy_f *cpy_item) {
		const size_t tda_b = tda_size + tda_stride_b;
		const ATOM *const end = data_b + size, *tda_end;

		/* move through all rows */
		for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_b) {
			/* copy one row */
			for( ; data_b < tda_end; ++data_a, ++data_b)
				*data_a = cpy_item(*data_b);
			/* adjust size, tda_stride empty space */
			data_a += tda_stride_a;
			data_b += tda_stride_b;
		}
	}
#endif /* !defined(TEMPLATE_CUL_PTR) */

void FUNCTION(swap)(ATOM *data_a, ATOM *data_b, size_t size) {
	ATOM tmp, *const end = data_a + size;
	for( ; data_a < end; ++data_a, ++data_b) {
		tmp = *data_a;
		*data_a = *data_b;
		*data_b = tmp;
	}
}

void FUNCTION(swap_stride)(ATOM *data_a, ATOM *data_b, size_t size, size_t stride_a, size_t stride_b) {
	ATOM tmp, *const end = data_a + size * stride_a;
	for( ; data_a < end; data_a += stride_a, data_b += stride_b) {
		tmp = *data_a;
		*data_a = *data_b;
		*data_b = tmp;
	}
}

void FUNCTION(swap_tda)(ATOM *data_a, ATOM *data_b, size_t size, size_t tda_size, size_t tda_stride_a, size_t tda_stride_b) {
	const size_t tda_b = tda_size + tda_stride_b;
	const ATOM *const end = data_b + size, *tda_end;
	ATOM tmp;

	/* move through all rows */
	for( tda_end = data_b + tda_size; data_b < end; tda_end += tda_b) {
		/* copy one row */
		for( ; data_b < tda_end; ++data_a, ++data_b) {
			tmp = *data_a;
			*data_a = *data_b;
			*data_b = tmp;
		}
		/* adjust size, tda_stride empty space */
		data_a += tda_stride_a;
		data_b += tda_stride_b;
	}
}

void FUNCTION(swap_pos)(ATOM *data, size_t i, size_t j) {
	ATOM tmp;

	tmp = *(data + i);
	*(data + i) = *(data + j);
	*(data + j) = tmp;
}

void FUNCTION(reverse)(ATOM *data, size_t size) {
	ATOM tmp, *end;
	for( end = data + size - 1; data < end; ++data, --end) {
		tmp = *data;
		*data = *end;
		*end = tmp;
	}
}

void FUNCTION(reverse_stride)(ATOM *data, size_t size, size_t stride) {
	ATOM tmp, *end;
	for( end = data + (size - 1) * stride; data < end; data += stride, end -= stride) {
		tmp = *data;
		*data = *end;
		*end = tmp;
	}
}
