#ifndef TEMPLATE_CUL_PTR
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(free)(ATOM *data, size_t size, cul_free_f *free_f) {
		ATOM *const last = data + size;
		for(; data < last; ++data)
			free_f(*data);
	}
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(copy)(ATOM *data, const ATOM *other, size_t size) {
	memcpy(data, other, size*sizeof(ATOM));
}

void FUNCTION(copy_overlap)(ATOM *data, const ATOM *other, size_t size) {
	memmove(data, other, size*sizeof(ATOM));
}

void FUNCTION(copy_stride)(ATOM *data, const ATOM *other, size_t size, size_t stride, size_t other_stride) {
	const ATOM *const last = other + size * other_stride;
	for(; other < last; data += stride, other += other_stride)
		*data = *other;
}

void FUNCTION(copy_tda)(ATOM *data, const ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
	const ATOM *const last = other + size;

	/* move through all rows */
	for(; other < last; data += tda, other += other_tda)
		memcpy(data, other, tda_size*sizeof(ATOM));
}

void FUNCTION(swap)(ATOM *data, ATOM *other, size_t size) {
	ATOM tmp, *const last = other + size;
	for(; other < last; ++data, ++other)
		CUL_SWAP(*data, *other, tmp);
}

void FUNCTION(swap_stride)(ATOM *data, ATOM *other, size_t size, size_t stride, size_t other_stride) {
	ATOM tmp, *const last = other + size * other_stride;
	for(; other < last; data += stride, other += other_stride)
		CUL_SWAP(*data, *other, tmp);
}

void FUNCTION(swap_tda)(ATOM *data, ATOM *other, size_t size, size_t tda_size, size_t tda, size_t other_tda) {
	const ATOM *const last = other + size, *tda_last = other + tda_size;
	ATOM tmp;

	/* adjust tda jumps */
	tda -= tda_size;
	other_tda -= tda_size;
	tda_size += other_tda;

	/* move through all rows */
	for(; other < last; tda_last += tda_size) {
		/* move through single row */
		for(; other < tda_last; ++data, ++other)
			CUL_SWAP(*data, *other, tmp);
		/* move through empty space */
		data += tda;
		other += other_tda;
	}
}

#ifndef TEMPLATE_CUL_PTR
#else /* TEMPLATE_CUL_PTR */
	ATOM FUNCTION(detach)(ATOM *data, size_t size, cul_clone_f *clone_f) {
		ATOM *const first = data, *const last = data + size;
		for(; data < last; ++data)
			if( (*data = clone_f(*data)) == NULL ) {
				/* erase rest of undetached pointers */
				for(++data; data < last; ++data)
					*data = NULL;
				return NULL;
			}
		return first;
	}

	ATOM FUNCTION(detach_stride)(ATOM *data, size_t size, size_t stride, cul_clone_f *clone_f) {
		ATOM *const first = data, *const last = data + size * stride;
		for(; data < last; data += stride)
			if( (*data = clone_f(*data)) == NULL ) {
				/* erase rest of undetached pointers */
				for(++data; data < last; data += stride)
					*data = NULL;
				return NULL;
			}
		return first;
	}

	ATOM FUNCTION(detach_tda)(ATOM *data, size_t size, size_t tda_size, size_t tda, cul_clone_f *clone_f) {
		ATOM *const first = data, *const last = data + size, *tda_last = data + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size) {
			/* move through single row */
			for(; data < tda_last; ++data)
				if( (*data = clone_f(*data)) == NULL ) {
					/* erase rest of undetached pointers */

					/* end of line */
					for(; data < tda_last; ++data)
						*data = NULL;
					data += tda;

					/* rest lines */
					for(tda_last += tda_size; data < last; tda_last += tda_size) {
						for(; data < tda_last; ++data)
							*data = NULL;
						data += tda;
					}

					return NULL;
				}
			/* move through empty space */
			data += tda;
		}
		return first;
	}
#endif /* TEMPLATE_CUL_PTR */

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

void FUNCTION(set)(ATOM *data, size_t size, ATOM value) {
	const ATOM *last = data + size;
	for(; data < last; ++data)
		*data = value;
	return;
}

void FUNCTION(set_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
	const ATOM *last = data + size * stride;
	for(; data < last; data += stride)
		*data = value;
	return;
}

void FUNCTION(set_tda)(ATOM *data, size_t size, size_t tda_size, size_t tda, ATOM value) {
	const ATOM *const last = data + size, *tda_last = data + tda_size;

	/* adjust tda jumps */
	tda -= tda_size;
	tda_size += tda;

	/* move through all rows */
	for(; data < last; tda_last += tda_size) {
		/* move through single row */
		for(; data < tda_last; ++data)
			*data = value;
		/* move through empty space */
		data += tda;
	}
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(add_constant)(ATOM *data, size_t size, double value) {
		const ATOM *last = data + size;
		for(; data < last; ++data)
			*data += value;
		return;
	}

	void FUNCTION(add_constant_stride)(ATOM *data, size_t size, size_t stride, double value) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride)
			*data += value;
		return;
	}

	void FUNCTION(add_constant_tda)(ATOM *data, size_t size, size_t tda_size, size_t tda, double value) {
		const ATOM *const last = data + size, *tda_last = data + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size) {
			/* move through single row */
			for(; data < tda_last; ++data)
				*data += value;
			/* move through empty space */
			data += tda;
		}
	}

	void FUNCTION(scale)(ATOM *data, size_t size, double value) {
		const ATOM *last = data + size;
		for(; data < last; ++data)
			*data *= value;
		return;
	}

	void FUNCTION(scale_stride)(ATOM *data, size_t size, size_t stride, double value) {
		const ATOM *last = data + size * stride;
		for(; data < last; data += stride)
			*data *= value;
		return;
	}

	void FUNCTION(scale_tda)(ATOM *data, size_t size, size_t tda_size, size_t tda, double value) {
		const ATOM *const last = data + size, *tda_last = data + tda_size;

		/* adjust tda jumps */
		tda -= tda_size;
		tda_size += tda;

		/* move through all rows */
		for(; data < last; tda_last += tda_size) {
			/* move through single row */
			for(; data < tda_last; ++data)
				*data *= value;
			/* move through empty space */
			data += tda;
		}
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(zero)(ATOM *data, size_t size) {
	memset(data, 0, size*sizeof(ATOM));
}

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

#ifndef TEMPLATE_CUL_PTR
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(each)(const ATOM *data, size_t size, cul_each_f *each_f, cul_ptr user_data){
		const ATOM *const last = data + size;
		for(; data < last; ++data)
			each_f(*data, user_data);
	}

	void FUNCTION(each_stride)(const ATOM *data, size_t size, size_t stride, cul_each_f *each_f, cul_ptr user_data) {
		const ATOM *const last = data + size * stride;
		for(; data < last; data += stride)
			each_f(*data, user_data);
	}
#endif /* TEMPLATE_CUL_PTR */
