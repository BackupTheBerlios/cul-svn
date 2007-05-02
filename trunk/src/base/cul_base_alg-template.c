#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(min)(const ATOM *data, size_t size) {
		const ATOM *end;
		ATOM min;

		end = data + size;
		min = *data;
		for( ++data; data < end; ++data) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	ATOM FUNCTION(min_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *end;
		ATOM min;

		end = data + size * stride;
		min = *data;
		for( data += stride; data < end; data += stride) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	size_t FUNCTION(min_index)(const ATOM *data, size_t size) {
		const ATOM *begin, *end, *index;
		ATOM min;

		begin = data;
		end = data + size;
		min = *data; index = data;
		for( ++data; data < end; ++data) {
			if( *data < min ) {
				min = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(min_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin, *end, *index;
		ATOM min;

		begin = data;
		end = data + size * stride;
		min = *data; index = data;
		for( data += stride; data < end; data += stride) {
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
		const ATOM *end;
		ATOM max;

		end = data + size;
		max = *data;
		for( ++data; data < end; ++data) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	ATOM FUNCTION(max_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *end;
		ATOM max;

		end = data + size * stride;
		max = *data;
		for( data += stride; data < end; data += stride) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	size_t FUNCTION(max_index)(const ATOM *data, size_t size) {
		const ATOM *begin, *end, *index;
		ATOM max;

		begin = data;
		end = data + size;
		max = *data; index = data;
		for( ++data; data < end; ++data) {
			if( *data > max ) {
				max = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(max_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin, *end, *index;
		ATOM max;

		begin = data;
		end = data + size * stride;
		max = *data; index = data;
		for( data += stride; data < end; data += stride) {
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
		const ATOM *end;
		ATOM min, max;

		end = data + size;
		min = *data;
		max = *data;
		for( ++data; data < end; ++data) {
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
		const ATOM *end;
		ATOM min, max;

		end = data + size * stride;
		min = *data;
		max = *data;
		for( data += stride; data < end; data += stride) {
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
		const ATOM *begin, *end, *min_index, *max_index;
		ATOM min, max;

		begin = data;
		end = data + size;
		min = *data; min_index = data;
		max = *data; max_index = data;
		for( ++data; data < end; ++data) {
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
		const ATOM *begin, *end, *min_index, *max_index;
		ATOM min, max;

		begin = data;
		end = data + size * stride;
		min = *data; min_index = data;
		max = *data; max_index = data;
		for( data += stride; data < end; data += stride) {
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
		ATOM *const begin = l, *const end = r;
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
			PFUNCTION(qsort_asc)(l, end);
		}
	}

	void PFUNCTION(qsort_asc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *const end = r;
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
			PFUNCTION(qsort_asc_stride)(l, end, stride);
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
		ATOM *const begin = l, *const end = r;
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
			PFUNCTION(qsort_desc)(l, end);
		}
	}

	void PFUNCTION(qsort_desc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *const end = r;
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
			PFUNCTION(qsort_asc_stride)(l, end, stride);
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
	void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp);
	void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp);
	void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp);
	void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp);

	void FUNCTION(sort)(ATOM *data, size_t size, cul_cmp_f *cmp) {
		PFUNCTION(qsort)(data, data + size - 1, cmp);
	}

	void FUNCTION(sort_stride)(ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp) {
		PFUNCTION(qsort_stride)(data, data + (size - 1) * stride, stride, cmp);
	}

	void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && cmp(l_val, *i) < 0; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
		}
	}

	void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && cmp(l_val, *i) < 0; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
		}
	}

	void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp) {
		ATOM *const begin = l, *const end = r;
		ATOM *pivot = l, val;
		if( r < l + 8 )
			PFUNCTION(isort)(l, r, cmp);
		else {
			pivot += (r - l) >> 1;
			if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			if( cmp(*r, *pivot) < 0 ) {
				CUL_SWAP(*pivot, *r, val);
				if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			}
			++l; --r;
			do {
				while( cmp(*l, *pivot) < 0 ) ++l;
				while( cmp(*pivot, *r) < 0 ) --r;
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
			PFUNCTION(qsort)(begin, r, cmp);
			PFUNCTION(qsort)(l, end, cmp);
		}
	}

	void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp) {
		ATOM *const begin = l, *const end = r;
		ATOM *pivot = l, val;
		if( r < l + (stride << 3) )
			PFUNCTION(isort_stride)(l, r, stride, cmp);
		else {
			pivot += (r - l)/stride >> 1;
			if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			if( cmp(*r, *pivot) < 0 ) {
				CUL_SWAP(*pivot, *r, val);
				if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
			};
			l += stride; r -= stride;
			do {
				while( cmp(*l, *pivot) < 0 ) l += stride;
				while( cmp(*pivot, *r) < 0 ) r -= stride;
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
			PFUNCTION(qsort_stride)(begin, r, stride, cmp);
			PFUNCTION(qsort_stride)(l, end, stride, cmp);
		}
	}
#endif /* TEMPLATE_CUL_PTR */

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
