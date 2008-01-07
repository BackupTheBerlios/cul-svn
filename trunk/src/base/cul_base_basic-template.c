#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(add)(ATOM *data, const ATOM *other, size_t size) {
		const ATOM *last = other + size;
		for(; other < last; ++other, ++data)
			*data += *other;
		return;
	}

	void FUNCTION(add_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
		const ATOM *last = other + size * stride;
		for(; other < last; other += other_stride, data += stride)
			*data += *other;
		return;
	}

	void FUNCTION(add_tda)(ATOM *data, const ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
		const ATOM *const last = other + size, *tda_last = other + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		other_tda -= tda_size;
		tda_size += other_tda;

		/* move through all rows */
		for(; other < last; tda_last += tda_size) {
			/* move through single row */
			for(; other < tda_last; ++data, ++other)
				*data += *other;
			/* move through empty space */
			data += tda;
			other += other_tda;
		}
	}

	void FUNCTION(sub)(ATOM *data, const ATOM *other, size_t size) {
		const ATOM *last = other + size;
		for(; other < last; ++other, ++data)
			*data -= *other;
		return;
	}

	void FUNCTION(sub_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
		const ATOM *last = other + size * stride;
		for(; other < last; other += other_stride, data += stride)
			*data -= *other;
		return;
	}

	void FUNCTION(sub_tda)(ATOM *data, const ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
		const ATOM *const last = other + size, *tda_last = other + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		other_tda -= tda_size;
		tda_size += other_tda;

		/* move through all rows */
		for(; other < last; tda_last += tda_size) {
			/* move through single row */
			for(; other < tda_last; ++data, ++other)
				*data -= *other;
			/* move through empty space */
			data += tda;
			other += other_tda;
		}
	}

	void FUNCTION(mul)(ATOM *data, const ATOM *other, size_t size) {
		const ATOM *last = other + size;
		for(; other < last; ++other, ++data)
			*data *= *other;
		return;
	}

	void FUNCTION(mul_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
		const ATOM *last = other + size * stride;
		for(; other < last; other += other_stride, data += stride)
			*data *= *other;
		return;
	}

	void FUNCTION(mul_tda)(ATOM *data, const ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
		const ATOM *const last = other + size, *tda_last = other + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		other_tda -= tda_size;
		tda_size += other_tda;

		/* move through all rows */
		for(; other < last; tda_last += tda_size) {
			/* move through single row */
			for(; other < tda_last; ++data, ++other)
				*data *= *other;
			/* move through empty space */
			data += tda;
			other += other_tda;
		}
	}

	void FUNCTION(div)(ATOM *data, const ATOM *other, size_t size) {
		const ATOM *last = other + size;
		for(; other < last; ++other, ++data)
			*data /= *other;
		return;
	}

	void FUNCTION(div_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
		const ATOM *last = other + size * stride;
		for(; other < last; other += other_stride, data += stride)
			*data /= *other;
		return;
	}

	void FUNCTION(div_tda)(ATOM *data, const ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
		const ATOM *const last = other + size, *tda_last = other + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		other_tda -= tda_size;
		tda_size += other_tda;

		/* move through all rows */
		for(; other < last; tda_last += tda_size) {
			/* move through single row */
			for(; other < tda_last; ++data, ++other)
				*data /= *other;
			/* move through empty space */
			data += tda;
			other += other_tda;
		}
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(dot)(ATOM *data, const ATOM *other, size_t size) {
		const ATOM *last = other + size;
		ATOM dot_product = 0;

		for(; other < last; ++other, ++data)
			dot_product += (*data * *other);
		return dot_product;
	}

	ATOM FUNCTION(dot_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
		const ATOM *last = other + size * stride;
		ATOM dot_product = 0;

		for(; other < last; other += other_stride, data += stride)
			dot_product += (*data * *other);
		return dot_product;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(min)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return EMPTY;

		for( ++data; data < last; ++data) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	ATOM FUNCTION(min_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return EMPTY;

		for( data += stride; data < last; data += stride) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	size_t FUNCTION(min_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return 0;

		for( ++data; data < last; ++data) {
			if( *data < min ) {
				min = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(min_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin = data, *last = data + size * stride, *index = data;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return 0;

		for( data += stride; data < last; data += stride) {
			if( *data < min ) {
				min = *data;
				index = data;
			}
		}
		return (size_t)(index - begin)/stride;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(max)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return EMPTY;

		for( ++data; data < last; ++data) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	ATOM FUNCTION(max_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return EMPTY;

		for( data += stride; data < last; data += stride) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	size_t FUNCTION(max_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return 0;

		for( ++data; data < last; ++data) {
			if( *data > max ) {
				max = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(max_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin = data, *last = data + size * stride, *index = data;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return 0;

		for( data += stride; data < last; data += stride) {
			if( *data > max ) {
				max = *data;
				index = data;
			}
		}
		return (size_t)(index - begin)/stride;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(minmax)(const ATOM *data, size_t size, ATOM *min_out, ATOM *max_out) {
		const ATOM *last = data + size;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_out = EMPTY;
			*max_out = EMPTY;
			return;
		}

		for( ++data; data < last; ++data) {
			if( *data < min )
				min = *data;
			if( *data > max )
				max = *data;
		}
		*min_out = min;
		*max_out = max;
		return;
	}

	void FUNCTION(minmax_stride)(const ATOM *data, size_t size, size_t stride, ATOM *min_out, ATOM *max_out) {
		const ATOM *last = data + size * stride;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_out = EMPTY;
			*max_out = EMPTY;
			return;
		}

		for( data += stride; data < last; data += stride) {
			if( *data < min )
				min = *data;
			if( *data > max )
				max = *data;
		}
		*min_out = min;
		*max_out = max;
		return;
	}

	void FUNCTION(minmax_index)(const ATOM *data, size_t size, size_t *min_index_out, size_t *max_index_out) {
		const ATOM *begin = data, *last = data + size, *min_index = data, *max_index = data;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_index_out = 0;
			*max_index_out = 0;
			return;
		}

		for( ++data; data < last; ++data) {
			if( *data < min ) {
				min = *data;
				min_index = data;
			}
			if( *data > max ) {
				max = *data;
				max_index = data;
			}
		}
		*min_index_out = (size_t)(min_index - begin);
		*max_index_out = (size_t)(max_index - begin);
		return;
	}

	void FUNCTION(minmax_index_stride)(const ATOM *data, size_t size, size_t stride, size_t *min_index_out, size_t *max_index_out) {
		const ATOM *begin = data, *last = data + size * stride, *min_index = data, *max_index = data;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_index_out = 0;
			*max_index_out = 0;
			return;
		}

		for( data += stride; data < last; data += stride) {
			if( *data < min ) {
				min = *data;
				min_index = data;
			}
			if( *data > max ) {
				max = *data;
				max_index = data;
			}
		}
		*min_index_out = (size_t)(min_index - begin)/stride;
		*max_index_out = (size_t)(max_index - begin)/stride;
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

	double FUNCTION(sum_tda)(const ATOM *data, size_t size, size_t tda_size, size_t tda) {
		const ATOM *const last = data + size, *tda_last = data + tda_size;
		double sum = 0.0;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size) {
			/* move through single row */
			for(; data < tda_last; ++data)
				sum += *data;
			/* move through empty space */
			data += tda;
		}
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

	double FUNCTION(mean_tda)(const ATOM *data, size_t size, size_t tda_size, size_t tda) {
		const ATOM *const last = data + size, *tda_last = data + tda_size;
		double mean = 0.0;
		size_t rows = 0;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size, rows += 1) {
			/* move through single row */
			for(; data < tda_last; ++data)
				mean += *data;
			/* move through empty space */
			data += tda;
		}
		return mean / (double)(rows * (tda_size - tda) );
	}

	double FUNCTION(variance)(const ATOM *data, size_t size) {
		double mean = FUNCTION(mean)(data, size);
		return FUNCTION(variance_mean)(data, size, mean);
	}

	double FUNCTION(variance_stride)(const ATOM *data, size_t size, size_t stride) {
		double mean = FUNCTION(mean_stride)(data, size, stride);
		return FUNCTION(variance_mean_stride)(data, size, stride, mean);
	}

	double FUNCTION(variance_tda)(const ATOM *data, size_t size, size_t tda_size, size_t tda) {
		double mean = FUNCTION(mean_tda)(data, size, tda_size, tda);
		return FUNCTION(variance_mean_tda)(data, size, tda_size, tda, mean);
	}

	double FUNCTION(variance_mean)(const ATOM *data, size_t size, double mean) {
		const ATOM *last = data + size;
		double variance = 0.0;
		for(; data < last; ++data)
			variance += (*data - mean)*(*data - mean);
		return variance /= size;
	}

	double FUNCTION(variance_mean_stride)(const ATOM *data, size_t size, size_t stride, double mean) {
		const ATOM *last = data + size * stride;
		double variance = 0.0;
		for(; data < last; data += stride)
			variance += (*data - mean) * (*data - mean);
		return variance /= size;
	}

	double FUNCTION(variance_mean_tda)(const ATOM *data, size_t size, size_t tda_size, size_t tda, double mean) {
		const ATOM *const last = data + size, *tda_last = data + tda_size;
		double variance = 0.0;
		size_t rows = 0;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size, rows += 1) {
			/* move through single row */
			for(; data < tda_last; ++data)
				variance += (*data - mean) * (*data - mean);
			/* move through empty space */
			data += tda;
		}
		return variance / (double)(rows * (tda_size - tda) );
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

