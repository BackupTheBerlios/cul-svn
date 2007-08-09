TYPE(Vector) *FUNCTION(vector_new)(size_t size) {
	TYPE(Vector) *v;
	ATOM *data;

	if( (v = FUNCTION(vector_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( size == 0 )
		FUNCTION(vector_init_struct)(v, NULL, 0, 0);
	else {
		if( (data = malloc(size * sizeof(ATOM))) == NULL ) {
			FUNCTION(vector_free_struct)(v);
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
		FUNCTION(vector_init_struct)(v, data, size, size);
	}

	return v;
}

TYPE(Vector) *FUNCTION(vector_new_empty)(void) {
	return FUNCTION(vector_new)(0);
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_free)(TYPE(Vector) *v) {
		if( v != NULL ) {
			free(v->data);
			FUNCTION(vector_free_struct)(v);
		}
	}
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(vector_free)(TYPE(Vector) *v, cul_free_f *free_f) {
		if( v != NULL ) {
			if( free_f != NULL) FUNCTION(free)(v->data, v->size, free_f);
			free(v->data);
			FUNCTION(vector_free_struct)(v);
		}
	}
#endif /* TEMPLATE_CUL_PTR */

VIEW(Vector) *FUNCTION(vectorview_new)(void) {
	VIEW(Vector) *vv;
	if( (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, NULL, 0, 0);
}

void FUNCTION(vectorview_free)(VIEW(Vector) *vv) {
	FUNCTION(vectorview_free_struct)(vv);
}

VIEW(Vector) *FUNCTION(vectorview_vector)(VIEW(Vector) *vv, const TYPE(Vector) *base_v) {
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_v->data, base_v->size, 1);
}

VIEW(Vector) *FUNCTION(vectorview_subvector)(VIEW(Vector) *vv, const TYPE(Vector) *base_v, size_t base_offset, size_t base_size, size_t base_stride) {
	if( base_offset + base_size > base_v->size )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_v->data + base_offset, base_size, base_stride);
}

void FUNCTION(vector_set_all)(TYPE(Vector) *v, ATOM val) {
	FUNCTION(set)(v->data, v->size, val);
}

void FUNCTION(vectorview_set_all)(VIEW(Vector) *vv, ATOM val) {
	if( vv->stride == 1 )
		FUNCTION(set)(vv->data, vv->size, val);
	else
		FUNCTION(set_stride)(vv->data, vv->size, vv->stride, val);
}

void FUNCTION(vector_set_basis)(TYPE(Vector) *v, size_t i, ATOM val, ATOM basis) {
	FUNCTION(set)(v->data, v->size, val);
	FUNCTION(vector_set)(v, i, basis);
}

void FUNCTION(vectorview_set_basis)(VIEW(Vector) *vv, size_t i, ATOM val, ATOM basis) {
	if( vv->stride == 1 )
		FUNCTION(set)(vv->data, vv->size, val);
	else
		FUNCTION(set_stride)(vv->data, vv->size, vv->stride, val);
	FUNCTION(vectorview_set)(vv, i, basis);
}

cul_errno FUNCTION(vector_copy)(TYPE(Vector) *v, const TYPE(Vector) *base_v) {
	if( v->size != base_v->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(v->data, base_v->data, base_v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_offset)(TYPE(Vector) *v, const TYPE(Vector) *base_v, size_t offset) {
	if( v->size - offset < base_v->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy)(v->data + offset, base_v->data, base_v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_subvector)(TYPE(Vector) *v, const TYPE(Vector) *base_v, size_t base_offset) {
	if( base_v->size - base_offset < v->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy)(v->data, base_v->data + base_offset, v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_view)(TYPE(Vector) *v, const VIEW(Vector) *base_vv) {
	if( v->size != base_vv->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(v->data, base_vv->data, base_vv->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_copy)(VIEW(Vector) *vv, const VIEW(Vector) *base_vv) {
	if( vv->size != base_vv->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(vv->data, base_vv->data, base_vv->size, vv->stride, base_vv->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_copy_vector)(VIEW(Vector) *vv, const TYPE(Vector) *base_v) {
	if( vv->size != base_v->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(vv->data, base_v->data, base_v->size, vv->stride, 1);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_swap)(TYPE(Vector) *a, TYPE(Vector) *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_swap)(VIEW(Vector) *va, VIEW(Vector) *vb) {
	if( va->size != vb->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_stride)(va->data, vb->data, va->size, va->stride, vb->stride);
	return CUL_SUCCESS;
}

void FUNCTION(vector_reverse)(TYPE(Vector) *v) {
	FUNCTION(reverse)(v->data, v->size);
}

void FUNCTION(vectorview_reverse)(VIEW(Vector) *vv) {
	FUNCTION(reverse_stride)(vv->data, vv->size, vv->stride);
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_resize)(TYPE(Vector) *v, size_t size) {
		ATOM *d;
	
		if( size == 0 ) {
			free(v->data);
			FUNCTION(vector_init_struct)(v, NULL, 0, 0);
		} else if( size >= v->size && size <= v->reserved )
			v->size = size;
		else {
			if( (d = (ATOM *)realloc(v->data, size * sizeof(ATOM))) == NULL )
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
			FUNCTION(vector_init_struct)(v, d, size, size);
		}
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
	cul_errno FUNCTION(vector_resize)(TYPE(Vector) *v, size_t size, cul_free_f *free_f) {
		ATOM *d;
	
		if( size == 0 ) {
			if( free_f != NULL) FUNCTION(free)(v->data, v->size, free_f);
			free(v->data);
			FUNCTION(vector_init_struct)(v, NULL, 0, 0);
		} else if( size >= v->size && size <= v->reserved )
			v->size = size;
		else {
			size_t copy = size < v->size? size: v->size;

			/* allocate and copy data */
			if( (d = (ATOM *)malloc(size * sizeof(ATOM))) == NULL )
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
			memcpy(d, v->data, copy * sizeof(ATOM));

			/* free old data */
			if( free_f != NULL )
				FUNCTION(free)(v->data + size, v->size - copy, free_f);
			free(v->data);

			FUNCTION(vector_init_struct)(v, d, size, size);
		}
		return CUL_SUCCESS;
	}
#endif /* TEMPLATE_CUL_PTR */

cul_errno FUNCTION(vector_resize_empty)(TYPE(Vector) *v, size_t size) {
	ATOM *d;

	if( size == 0 ) {
		free(v->data);
		FUNCTION(vector_init_struct)(v, NULL, 0, 0);
		return CUL_SUCCESS;
	} else if( size >= v->size && size <= v->reserved ) {
		v->size = size;
		return CUL_SUCCESS;
	} else if( (d = (ATOM *)malloc(size * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	free(v->data);
	FUNCTION(vector_init_struct)(v, d, size, size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_reserve)(TYPE(Vector) *v, size_t size) {
	ATOM *d;

	if( size == 0 ) {
		free(v->data);
		FUNCTION(vector_init_struct)(v, NULL,  0, 0);
		return CUL_SUCCESS;
	}
	else if( (d = (ATOM *)realloc(v->data, size * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	if( size < v->size )
		FUNCTION(vector_init_struct)(v, d, size, size);
	else
		FUNCTION(vector_init_struct)(v, d, size, v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_push_back)(TYPE(Vector) *v, ATOM val) {
	if( v->size >= v->reserved )
		if( FUNCTION(vector_reserve)(v, (v->size + 1)*CUL_EFACTOR_MUL + CUL_EFACTOR_SUM) )
			CUL_ERROR_ERRNO_RET(CUL_EFAILED, CUL_EFAILED);

	v->size += 1;
	FUNCTION(vector_set)(v, v->size - 1, val);
	return CUL_SUCCESS;
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_pop_back)(TYPE(Vector) *v) {
		if( v->size > 0 )
			v->size -= 1;
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
	cul_errno FUNCTION(vector_pop_back)(TYPE(Vector) *v, cul_free_f *free_f) {
		if( v->size > 0 ) {
			v->size -= 1;
			if( free_f != NULL ) free_f(v->data[v->size]);
		}
		return CUL_SUCCESS;
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(vector_min)(const TYPE(Vector) *v) {
		return FUNCTION(min)(v->data, v->size);
	}

	size_t FUNCTION(vector_min_index)(const TYPE(Vector) *v) {
		return FUNCTION(min_index)(v->data, v->size);
	}

	ATOM FUNCTION(vector_max)(const TYPE(Vector) *v) {
		return FUNCTION(max)(v->data, v->size);
	}

	size_t FUNCTION(vector_max_index)(const TYPE(Vector) *v) {
		return FUNCTION(max_index)(v->data, v->size);
	}

	void FUNCTION(vector_minmax)(const TYPE(Vector) *v, ATOM *min, ATOM *max) {
		FUNCTION(minmax)(v->data, v->size, min, max);
	}

	void FUNCTION(vector_minmax_index)(const TYPE(Vector) *v, size_t *min_i, size_t *max_i) {
		FUNCTION(minmax_index)(v->data, v->size, min_i, max_i);
	}

	ATOM FUNCTION(vectorview_min)(const VIEW(Vector) *vv) {
		return FUNCTION(min_stride)(vv->data, vv->size, vv->stride);
	}

	size_t FUNCTION(vectorview_min_index)(const VIEW(Vector) *vv) {
		return FUNCTION(min_index_stride)(vv->data, vv->size, vv->stride);
	}

	ATOM FUNCTION(vectorview_max)(const VIEW(Vector) *vv) {
		return FUNCTION(max_stride)(vv->data, vv->size, vv->stride);
	}

	size_t FUNCTION(vectorview_max_index)(const VIEW(Vector) *vv) {
		return FUNCTION(max_index_stride)(vv->data, vv->size, vv->stride);
	}

	void FUNCTION(vectorview_minmax)(const VIEW(Vector) *vv, ATOM *min, ATOM *max) {
		FUNCTION(minmax_stride)(vv->data, vv->size, vv->stride, min, max);
	}

	void FUNCTION(vectorview_minmax_index)(const VIEW(Vector) *vv, size_t *min_i, size_t *max_i) {
		FUNCTION(minmax_index_stride)(vv->data, vv->size, vv->stride, min_i, max_i);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	double FUNCTION(vector_sum)(const TYPE(Vector)  *v) {
		return FUNCTION(sum)(v->data, v->size);
	}

	double FUNCTION(vector_mean)(const TYPE(Vector)  *v) {
		return FUNCTION(mean)(v->data, v->size);
	}

	double FUNCTION(vector_variance)(const TYPE(Vector)  *v, double mean) {
		return FUNCTION(variance)(v->data, v->size, mean);
	}

	double FUNCTION(vectorview_sum)(const VIEW(Vector)  *vv) {
		return FUNCTION(sum_stride)(vv->data, vv->size, vv->stride);
	}
	
	double FUNCTION(vectorview_mean)(const VIEW(Vector)  *vv) {
		return FUNCTION(mean_stride)(vv->data, vv->size, vv->stride);
	}
	
	double FUNCTION(vectorview_variance)(const VIEW(Vector)  *vv, double mean) {
		return FUNCTION(variance_stride)(vv->data, vv->size, vv->stride, mean);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_sort_asc)(TYPE(Vector) *v) {
		FUNCTION(sort_asc)(v->data, v->size);
	}

	void FUNCTION(vector_sort_desc)(TYPE(Vector) *v) {
		FUNCTION(sort_desc)(v->data, v->size);
	}

	size_t FUNCTION(vector_unique)(TYPE(Vector)  *v) {
		return (size_t)(FUNCTION(unique)(v->data, v->size) - v->data);
	}

	size_t FUNCTION(vector_find)(const TYPE(Vector) *v, size_t offset, ATOM key) {
		ATOM *find;

		if( offset >= v->size )
			CUL_ERROR_ERRNO_RET(v->size, CUL_EBADPOS);
		if( (find = FUNCTION(find)(v->data + offset, v->size - offset, key)) == NULL )
			return v->size;
		return (size_t)(find - v->data);
	}

	size_t FUNCTION(vector_bfind)(const TYPE(Vector) *v, ATOM key) {
		ATOM *find;

		if( (find = FUNCTION(bfind)(v->data, v->size, key)) == NULL )
			return v->size;
		return (size_t)(find - v->data);
	}

	void FUNCTION(vectorview_sort_asc)(VIEW(Vector) *vv) {
		FUNCTION(sort_asc_stride)(vv->data, vv->size, vv->stride);
	}

	void FUNCTION(vectorview_sort_desc)(VIEW(Vector) *vv) {
		FUNCTION(sort_desc_stride)(vv->data, vv->size, vv->stride);
	}

	size_t FUNCTION(vectorview_unique)(VIEW(Vector)  *vv) {
		return (size_t)(FUNCTION(unique_stride)(vv->data, vv->size, vv->stride) - vv->data)/vv->stride;
	}

	size_t FUNCTION(vectorview_find)(const VIEW(Vector) *vv, size_t offset, ATOM key) {
		ATOM *find;

		if( offset >= vv->size )
			CUL_ERROR_ERRNO_RET(vv->size, CUL_EBADPOS);
		if( (find = FUNCTION(find_stride)(vv->data + offset * vv->stride, vv->size - offset, vv->stride, key)) == NULL )
			return vv->size;
		return (size_t)(find - vv->data)/vv->stride;
	}

	size_t FUNCTION(vectorview_bfind)(const VIEW(Vector) *vv, ATOM key) {
		ATOM *find;

		if( (find = FUNCTION(bfind_stride)(vv->data, vv->size, vv->stride, key)) == NULL )
			return vv->size;
		return (size_t)(find - vv->data)/vv->stride;
	}
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(vector_sort)(TYPE(Vector) *v, cul_cmp_f *cmp_f) {
		FUNCTION(sort)(v->data, v->size, cmp_f);
	}

	size_t FUNCTION(vector_unique)(TYPE(Vector)  *v, cul_cmp_f *cmp_f) {
		return (size_t)(FUNCTION(unique)(v->data, v->size, cmp_f) - v->data);
	}

	size_t FUNCTION(vector_find)(const TYPE(Vector) *v, size_t offset, ATOM key, cul_cmp_f *cmp_f) {
		if( offset >= v->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
		return (size_t)(FUNCTION(find)(v->data + offset, v->size - offset, key, cmp_f) - v->data);
	}

	size_t FUNCTION(vector_bfind)(const TYPE(Vector) *v, ATOM key, cul_cmp_f *cmp_f) {
		return (size_t)(FUNCTION(bfind)(v->data, v->size, key, cmp_f) - v->data);
	}

	void FUNCTION(vector_foreach)(TYPE(Vector) *v, cul_foreach_f *foreach_f, cul_ptr user_data) {
		FUNCTION(foreach)(v->data, v->size, foreach_f, user_data);
	}

	void FUNCTION(vectorview_sort)(VIEW(Vector) *vv, cul_cmp_f *cmp_f) {
		FUNCTION(sort_stride)(vv->data, vv->size, vv->stride, cmp_f);
	}

	size_t FUNCTION(vectorview_unique)(VIEW(Vector)  *vv, cul_cmp_f *cmp_f) {
		return (size_t)(FUNCTION(unique_stride)(vv->data, vv->size, vv->stride, cmp_f) - vv->data)/vv->stride;
	}

	size_t FUNCTION(vectorview_find)(const VIEW(Vector) *vv, size_t offset, ATOM key, cul_cmp_f *cmp_f) {
		if( offset >= vv->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
		return (size_t)(FUNCTION(find_stride)(vv->data + offset * vv->stride, vv->size - offset, vv->stride, key, cmp_f) - vv->data)/vv->stride;
	}

	size_t FUNCTION(vectorview_bfind)(const VIEW(Vector) *vv, ATOM key, cul_cmp_f *cmp_f) {
		return (size_t)(FUNCTION(bfind_stride)(vv->data, vv->size, vv->stride, key, cmp_f) - vv->data)/vv->stride;
	}

	void FUNCTION(vectorview_foreach)(VIEW(Vector) *vv, cul_foreach_f *foreach_f, cul_ptr user_data) {
		FUNCTION(foreach_stride)(vv->data, vv->size, vv->stride, foreach_f, user_data);
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_add_scalar)(TYPE(Vector)  *v, ATOM val) {
		FUNCTION(add_scalar)(v->data, v->size, val);
	}

	void FUNCTION(vector_mul_scalar)(TYPE(Vector)  *v, ATOM val) {
		FUNCTION(mul_scalar)(v->data, v->size, val);
	}

	cul_errno FUNCTION(vector_add)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
		if( a->size != b->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add)(a->data, b->data, a->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_sub)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
		if( a->size != b->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub)(a->data, b->data, a->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_mul)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
		if( a->size != b->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul)(a->data, b->data, a->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_div)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
		if( a->size != b->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div)(a->data, b->data, a->size);
		return CUL_SUCCESS;
	}

	void FUNCTION(vectorview_add_scalar)(VIEW(Vector)  *vv, ATOM val) {
		FUNCTION(add_scalar_stride)(vv->data, vv->size, vv->stride, val);
	}

	void FUNCTION(vectorview_mul_scalar)(VIEW(Vector)  *vv, ATOM val) {
		FUNCTION(mul_scalar_stride)(vv->data, vv->size, vv->stride, val);
	}

	cul_errno FUNCTION(vectorview_add)(VIEW(Vector)  *va, const VIEW(Vector)  *vb) {
		if( va->size != vb->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add_stride)(va->data, vb->data, va->size, va->stride, vb->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_sub)(VIEW(Vector)  *va, const VIEW(Vector)  *vb) {
		if( va->size != vb->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub_stride)(va->data, vb->data, va->size, va->stride, vb->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_mul)(VIEW(Vector)  *va, const VIEW(Vector)  *vb) {
		if( va->size != vb->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul_stride)(va->data, vb->data, va->size, va->stride, vb->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_div)(VIEW(Vector)  *va, const VIEW(Vector)  *vb) {
		if( va->size != vb->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div_stride)(va->data, vb->data, va->size, va->stride, vb->stride);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_fprintf)(FILE *stream, const TYPE(Vector) *v, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fprintf)(stream, v->data, v->size, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_fscanf)(FILE *stream, TYPE(Vector) *v, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fscanf)(stream, v->data, v->size, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_fprintf)(FILE *stream, const VIEW(Vector) *vv, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fprintf_stride)(stream, vv->data, vv->size, vv->stride, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_fscanf)(FILE *stream, VIEW(Vector) *vv, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fscanf_stride)(stream, vv->data, vv->size, vv->stride, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */
