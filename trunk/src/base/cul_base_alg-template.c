#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(min)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		ATOM min = *data;

		for( ++data; data < last; ++data) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	ATOM FUNCTION(min_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM min = *data;

		for( data += stride; data < last; data += stride) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	size_t FUNCTION(min_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM min = *data;

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
		ATOM min = *data;

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
		ATOM max = *data;

		for( ++data; data < last; ++data) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	ATOM FUNCTION(max_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM max = *data;

		for( data += stride; data < last; data += stride) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	size_t FUNCTION(max_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM max = *data;

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
		ATOM max = *data;

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
		ATOM min = *data, max = *data;

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
		ATOM min = *data, max = *data;

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
		ATOM min = *data, max = *data;

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
		ATOM min = *data, max = *data;

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
	ATOM *FUNCTION(lfind)(ATOM key, ATOM *data, size_t size) {
		ATOM *const last = data + size;
		for( ; data < last; ++data)
			if( *data == key )
				return data;
		return NULL;
	}

	ATOM *FUNCTION(lfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride) {
		ATOM *const last = data + size * stride;
		for( ; data < last; data += stride)
			if( *data == key )
				return data;
		return NULL;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM *FUNCTION(lfind)(ATOM key, ATOM *data, size_t size, cul_cmp_f *cmp_f) {
		ATOM *const last = data + size;
		for( ; data < last; ++data)
			if( !cmp_f(data, &key) )
				return data;
		return NULL;
	}

	ATOM *FUNCTION(lfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp_f) {
		ATOM *const last = data + size * stride;
		for( ; data < last; data += stride)
			if( !cmp_f(data, &key) )
				return data;
		return NULL;
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM *FUNCTION(bfind)(ATOM key, ATOM *data, size_t size) {
		ATOM *last = data + size;
		for( size >>= 1; size > 0; size >>= 1) {
			const ATOM val = *(data + size);
			if( val < key ) {
				data += size + 1;
				size = last - data;
			}	else if( val > key )
				last = data + size;
			else
				return data + size;
		}
		if( *data == key )
			return data;
		return NULL;
	}

	ATOM *FUNCTION(bfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride) {
		ATOM *last = data + size * stride;
		for( size >>= 1; size > 0 ; size >>= 1) {
			const ATOM val = *(data + size * stride);
			if( val < key ) {
				data += (size + 1) * stride;
				size = (last - data) / stride;
			}	else if( val > key )
				last = data + size * stride;
			else
				return data + size * stride;
		}
		if( *data == key )
			return data;
		return NULL;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM *FUNCTION(bfind)(ATOM key, ATOM *data, size_t size, cul_cmp_f *cmp_f) {
		ATOM *last = data + size;
		for( size >>= 1; size > 0; size >>= 1) {
			int cmp_res = cmp_f(*(data + size), &key);
			if( cmp_res < 0 ) {
				data += size + 1;
				size = last - data;
			}
			else if( cmp_res > 0 )
				last = data + size;
			else
				return data + size;
		}
		if( cmp_f(*data, key) == 0 )
			return data;
		return NULL;
	}

	ATOM *FUNCTION(bfind_stride)(ATOM key, ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp_f) {
		ATOM *last = data + size * stride;
		for( size >>= 1; size > 0 ; size >>= 1) {
			int cmp_res = cmp_f(*(data + size * stride), &key);
			if( cmp_res < 0 ) {
				data += (size + 1) * stride;
				size = (last - data) / stride;
			}
			else if( cmp_res > 0 )
				last = data + size * stride;
			else
				return data + size * stride;
		}
		if( cmp_f(*data, key) == 0 )
			return data;
		return NULL;
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void PFUNCTION(isort_asc)(ATOM *l, ATOM *r);
	void PFUNCTION(isort_asc_stride)(ATOM *l, ATOM *r, size_t stride);
	void PFUNCTION(qsort_asc)(ATOM *l, ATOM *r);
	void PFUNCTION(qsort_asc_stride)(ATOM *l, ATOM *r, size_t stride);

	void PFUNCTION(isort_asc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && *i > l_val; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
		}
	}

	void PFUNCTION(isort_asc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && *i > l_val; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
		}
	}

	void PFUNCTION(qsort_asc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + 8 )
			PFUNCTION(isort_asc)(l, r);
		else {
			pivot += (r - l) >> 1;
			if( *pivot < *l ) CUL_SWAP(*pivot, *l, val);
			if( *r < *pivot ) {
				CUL_SWAP(*pivot, *r, val);
				if( *pivot < *l ) CUL_SWAP(*pivot, *l, val);
			}
			++l; --r;
			do {
				while( *l < *pivot ) ++l;
				while( *pivot < *r ) --r;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					++l; --r;
				}
				else if( l == r ) {
					++l; --r;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort_asc)(begin, r);
			PFUNCTION(qsort_asc)(l, last);
		}
	}

	void PFUNCTION(qsort_asc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + (stride << 3) )
			PFUNCTION(isort_asc_stride)(l, r, stride);
		else {
			pivot += (r - l)/stride >> 1;
			if( *pivot < *l ) CUL_SWAP(*pivot, *l, val);
			if( *r < *pivot ) {
				CUL_SWAP(*pivot, *r, val);
				if( *pivot < *l ) CUL_SWAP(*pivot, *l, val);
			};
			l += stride; r -= stride;
			do {
				while( *l < *pivot ) l += stride;
				while( *pivot < *r ) r -= stride;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					l += stride; r -= stride;
				}
				else if( l == r ) {
					l += stride; r -= stride;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort_asc_stride)(begin, r, stride);
			PFUNCTION(qsort_asc_stride)(l, last, stride);
		}
	}

	void PFUNCTION(isort_desc)(ATOM *l, ATOM *r);
	void PFUNCTION(isort_desc_stride)(ATOM *l, ATOM *r, size_t stride);
	void PFUNCTION(qsort_desc)(ATOM *l, ATOM *r);
	void PFUNCTION(qsort_desc_stride)(ATOM *l, ATOM *r, size_t stride);

	void PFUNCTION(isort_desc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && *i < l_val; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
		}
	}

	void PFUNCTION(isort_desc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && *i < l_val; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
		}
	}

	void PFUNCTION(qsort_desc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + 8 )
			PFUNCTION(isort_desc)(l, r);
		else {
			pivot += (r - l) >> 1;
			if( *pivot > *l ) CUL_SWAP(*pivot, *l, val);
			if( *r > *pivot ) {
				CUL_SWAP(*pivot, *r, val);
				if( *pivot > *l ) CUL_SWAP(*pivot, *l, val);
			}
			++l; --r;
			do {
				while( *l > *pivot ) ++l;
				while( *pivot > *r ) --r;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					++l; --r;
				}
				else if( l == r ) {
					++l; --r;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort_desc)(begin, r);
			PFUNCTION(qsort_desc)(l, last);
		}
	}

	void PFUNCTION(qsort_desc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + (stride << 3) )
			PFUNCTION(isort_asc_stride)(l, r, stride);
		else {
			pivot += (r - l)/stride >> 1;
			if( *pivot > *l ) CUL_SWAP(*pivot, *l, val);
			if( *r > *pivot ) {
				CUL_SWAP(*pivot, *r, val);
				if( *pivot > *l ) CUL_SWAP(*pivot, *l, val);
			};
			l += stride; r -= stride;
			do {
				while( *l > *pivot ) l += stride;
				while( *pivot > *r ) r -= stride;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					l += stride; r -= stride;
				}
				else if( l == r ) {
					l += stride; r -= stride;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort_asc_stride)(begin, r, stride);
			PFUNCTION(qsort_asc_stride)(l, last, stride);
		}
	}

	void FUNCTION(sort_asc)(ATOM *data, size_t size) {
		PFUNCTION(qsort_asc)(data, data + size - 1);
	}

	void FUNCTION(sort_asc_stride)(ATOM *data, size_t size, size_t stride) {
		PFUNCTION(qsort_asc_stride)(data, data + (size - 1) * stride, stride);
	}

	void FUNCTION(sort_desc)(ATOM *data, size_t size) {
		PFUNCTION(qsort_desc)(data, data + size - 1);
	}

	void FUNCTION(sort_desc_stride)(ATOM *data, size_t size, size_t stride) {
		PFUNCTION(qsort_desc_stride)(data, data + (size - 1) * stride, stride);
	}
#else /* TEMPLATE_CUL_PTR */
	void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp_f);
	void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp_f);
	void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp_f);
	void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp_f);

	void FUNCTION(sort)(ATOM *data, size_t size, cul_cmp_f *cmp_f) {
		PFUNCTION(qsort)(data, data + size - 1, cmp_f);
	}

	void FUNCTION(sort_stride)(ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp_f) {
		PFUNCTION(qsort_stride)(data, data + (size - 1) * stride, stride, cmp_f);
	}

	void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp_f) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && cmp_f(l_val, *i) < 0; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
		}
	}

	void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp_f) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && cmp_f(l_val, *i) < 0; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
		}
	}

	void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp_f) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + 8 )
			PFUNCTION(isort)(l, r, cmp_f);
		else {
			pivot += (r - l) >> 1;
			if( cmp_f(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			if( cmp_f(*r, *pivot) < 0 ) {
				CUL_SWAP(*pivot, *r, val);
				if( cmp_f(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			}
			++l; --r;
			do {
				while( cmp_f(*l, *pivot) < 0 ) ++l;
				while( cmp_f(*pivot, *r) < 0 ) --r;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					++l; --r;
				}
				else if( l == r ) {
					++l; --r;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort)(begin, r, cmp_f);
			PFUNCTION(qsort)(l, last, cmp_f);
		}
	}

	void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp_f) {
		ATOM *const begin = l, *const last = r;
		ATOM *pivot = l, val;
		if( r < l + (stride << 3) )
			PFUNCTION(isort_stride)(l, r, stride, cmp_f);
		else {
			pivot += (r - l)/stride >> 1;
			if( cmp_f(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			if( cmp_f(*r, *pivot) < 0 ) {
				CUL_SWAP(*pivot, *r, val);
				if( cmp_f(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			};
			l += stride; r -= stride;
			do {
				while( cmp_f(*l, *pivot) < 0 ) l += stride;
				while( cmp_f(*pivot, *r) < 0 ) r -= stride;
				if( l < r ) {
					CUL_SWAP(*l, *r, val);
					if( pivot == l )      pivot = r;
					else if( pivot == r ) pivot = l;
					l += stride; r -= stride;
				}
				else if( l == r ) {
					l += stride; r -= stride;
					break;
				}
			} while( l <= r );
			PFUNCTION(qsort_stride)(begin, r, stride, cmp_f);
			PFUNCTION(qsort_stride)(l, last, stride, cmp_f);
		}
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM * FUNCTION(unique)(ATOM *data, size_t size) {
		ATOM *cur = data + 1, *const last = data + size;
		for(++data; data < last; ++data) {
			if( *(data - 1) == *data )
				continue;
			*cur = *data;
			++cur;
		}
		return cur;
	}

	ATOM * FUNCTION(unique_stride)(ATOM *data, size_t size, size_t stride) {
		ATOM *cur = data + stride, * const last = data + size * stride;
		for( data += stride; data < last; data += stride) {
			if( *(data - stride) == *data )
				continue;
			*cur = *data;
			cur += stride;
		}
		return cur;
	}
#else /* TEMPLATE_CUL_PTR */
	ATOM * FUNCTION(unique)(ATOM *data, size_t size, cul_cmp_f *cmp_f) {
		ATOM *cur = data + 1, *const last = data + size;
		for(++data; data < last; ++data) {
			if( !cmp_f(data - 1, data) )
				continue;
			*cur = *data;
			++cur;
		}
		return cur;
	}

	ATOM * FUNCTION(unique_stride)(ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp_f) {
		ATOM *cur = data + stride, *const last = data + size * stride;
		for( data += stride; data < last; data += stride) {
			if( !cmp_f(data - stride, data) )
				continue;
			*cur = *data;
			cur += stride;
		}
		return cur;
	}
#endif /* TEMPLATE_CUL_PTR */
