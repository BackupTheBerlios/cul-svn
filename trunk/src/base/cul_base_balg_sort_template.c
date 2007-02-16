void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp);
void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp);
void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp);
void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp);

void PFUNCTION(isort)(ATOM *l, ATOM *r, cul_cmp_f *cmp) {
	ATOM *const begin = l, *i, l_val;
	for( ++l; l <= r; ++l) {
		l_val = *l;
#if !defined(TEMPLATE_CUL_PTR)
		for( i = l - 1; i >= begin && cmp(&l_val, i) < 0; --i)
#else
		for( i = l - 1; i >= begin && cmp(l_val, *i) < 0; --i)
#endif
			*(i + 1) = *i;
		*(i + 1) = l_val;
	}
}

void PFUNCTION(qsort)(ATOM *l, ATOM *r, cul_cmp_f *cmp) {
	ATOM *const begin = l, *const end = r;
	ATOM *pivot = l, val;
	if( r < l + 8 )
		PFUNCTION(isort)(l, r, cmp);
	else {
		pivot += (r - l) >> 1;
#if !defined(TEMPLATE_CUL_PTR)
		if( cmp(pivot, l) < 0 ) CUL_SWAP(*pivot, *l, val);
		if( cmp(r, pivot) < 0 ) {
			CUL_SWAP(*pivot, *r, val);
			if( cmp(pivot, l) < 0 ) CUL_SWAP(*pivot, *l, val);
		}
#else
		if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
		if( cmp(*r, *pivot) < 0 ) {
			CUL_SWAP(*pivot, *r, val);
			if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
		}
#endif
		++l; --r;
		do {
#if !defined(TEMPLATE_CUL_PTR)
			while( cmp(l, pivot) < 0 ) ++l;
			while( cmp(pivot, r) < 0 ) --r;
#else
			while( cmp(*l, *pivot) < 0 ) ++l;
			while( cmp(*pivot, *r) < 0 ) --r;
#endif
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

void PFUNCTION(isort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp) {
	ATOM *const begin = l, *i, l_val;
	for( l += stride; l <= r; l += stride) {
		l_val = *l;
#if !defined(TEMPLATE_CUL_PTR)
		for( i = l - stride; i >= begin && cmp(&l_val, i) < 0; i -= stride)
#else
		for( i = l - stride; i >= begin && cmp(l_val, *i) < 0; i -= stride)
#endif
			*(i + stride) = *i;
		*(i + stride) = l_val;
	}
}

void PFUNCTION(qsort_stride)(ATOM *l, ATOM *r, size_t stride, cul_cmp_f *cmp) {
	ATOM *const begin = l, *const end = r;
	ATOM *pivot = l, val;
	if( r < l + (stride << 3) )
		PFUNCTION(isort_stride)(l, r, stride, cmp);
	else {
		pivot += (r - l)/stride >> 1;
#if !defined(TEMPLATE_CUL_PTR)
		if( cmp(pivot, l) < 0 ) CUL_SWAP(*pivot, *l, val);
		if( cmp(r, pivot) < 0 ) {
			CUL_SWAP(*pivot, *r, val);
			if( cmp(pivot, l) < 0 ) CUL_SWAP(*pivot, *l, val);
		};
#else
		if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
		if( cmp(*r, *pivot) < 0 ) {
			CUL_SWAP(*pivot, *r, val);
			if( cmp(*pivot, *l) < 0 ) CUL_SWAP(*pivot, *l, val);
		};
#endif
		l += stride; r -= stride;
		do {
#if !defined(TEMPLATE_CUL_PTR)
			while( cmp(l, pivot) < 0 ) l += stride;
			while( cmp(pivot, r) < 0 ) r -= stride;
#else
			while( cmp(*l, *pivot) < 0 ) l += stride;
			while( cmp(*pivot, *r) < 0 ) r -= stride;
#endif
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

void FUNCTION(sort)(ATOM *data, size_t size, cul_cmp_f *cmp) {
	PFUNCTION(qsort)(data, data + size - 1, cmp);
}

void FUNCTION(sort_stride)(ATOM *data, size_t size, size_t stride, cul_cmp_f *cmp) {
	PFUNCTION(qsort_stride)(data, data + (size - 1) * stride, stride, cmp);
}

#if !defined(TEMPLATE_CUL_PTR)
	void PFUNCTION(isort_asc)(ATOM *l, ATOM *r);
	void PFUNCTION(qsort_asc)(ATOM *l, ATOM *r);
	void PFUNCTION(isort_desc)(ATOM *l, ATOM *r);
	void PFUNCTION(qsort_desc)(ATOM *l, ATOM *r);
	void PFUNCTION(isort_asc_stride)(ATOM *l, ATOM *r, size_t stride);
	void PFUNCTION(qsort_asc_stride)(ATOM *l, ATOM *r, size_t stride);
	void PFUNCTION(isort_desc_stride)(ATOM *l, ATOM *r, size_t stride);
	void PFUNCTION(qsort_desc_stride)(ATOM *l, ATOM *r, size_t stride);

	void PFUNCTION(isort_asc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && *i > l_val; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
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

	void PFUNCTION(isort_desc)(ATOM *l, ATOM *r) {
		ATOM *const begin = l, *i, l_val;
		for( ++l; l <= r; ++l) {
			l_val = *l;
			for( i = l - 1; i >= begin && *i < l_val; --i)
				*(i + 1) = *i;
			*(i + 1) = l_val;
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

	void PFUNCTION(isort_asc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && *i > l_val; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
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

	void PFUNCTION(isort_desc_stride)(ATOM *l, ATOM *r, size_t stride) {
		ATOM *const begin = l, *i, l_val;
		for( l += stride; l <= r; l += stride) {
			l_val = *l;
			for( i = l - stride; i >= begin && *i < l_val; i -= stride)
				*(i + stride) = *i;
			*(i + stride) = l_val;
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

	void FUNCTION(sort_desc)(ATOM *data, size_t size) {
		PFUNCTION(qsort_desc)(data, data + size - 1);
	}

	void FUNCTION(sort_asc_stride)(ATOM *data, size_t size, size_t stride) {
		PFUNCTION(qsort_asc_stride)(data, data + (size - 1) * stride, stride);
	}

	void FUNCTION(sort_desc_stride)(ATOM *data, size_t size, size_t stride) {
		PFUNCTION(qsort_desc_stride)(data, data + (size - 1) * stride, stride);
	}

#endif /* !defined(TEMPLATE_CUL_PTR) */
