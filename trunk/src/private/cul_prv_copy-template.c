void FUNCTION(copy_stride)(ATOM *restrict data, const ATOM *restrict other, size_t size, size_t stride, size_t other_stride) {
	/* adjust size */
	size *= stride;

	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		data[i] = other[other_i];
}

void FUNCTION(copy_stride_data)(ATOM *restrict data, const ATOM *restrict other, size_t size, size_t stride) {
	for(size_t i = 0, other_i = 0; other_i < size; i += stride, ++other_i)
		data[i] = other[other_i];
}

void FUNCTION(copy_stride_other)(ATOM *restrict data, const ATOM *restrict other, size_t size, size_t other_stride) {
	for(size_t i = 0, other_i = 0; i < size; ++i, other_i += other_stride)
		data[i] = other[other_i];
}

void FUNCTION(copy_tda)(ATOM *restrict data, const ATOM *restrict other, size_t size_x, size_t size_y, size_t tda, size_t other_tda) {
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			data[x] = other[x];

		/* adjust current row */
		data += tda;
		other += other_tda;
	}
}

