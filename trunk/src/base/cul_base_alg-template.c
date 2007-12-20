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

