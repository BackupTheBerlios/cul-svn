/* private structure allocator */
TYPE(Matrix) *FUNCTION(matrix_new_struct)(void);

TYPE(Matrix) *FUNCTION(matrix_new)(size_t x, size_t y) {
	TYPE(Matrix) *m = FUNCTION(matrix_new_struct)();
	if( m != NULL && FUNCTION(matrix_init)(m, x, y) == NULL ){
		free(m);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_new_empty)(void) {
	return FUNCTION(matrix_new)(0, 0);
}

TYPE(Matrix) *FUNCTION(matrix_new_struct)(void) {
	TYPE(Matrix) *m;
	if( (m = (TYPE(Matrix) *)malloc(sizeof(TYPE(Matrix)))) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_init)(TYPE(Matrix) *m, size_t x, size_t y) {
	ATOM *d;

	if( x*y == 0 )
		FUNCTION(matrix_init_all)(m, 0, 0, NULL);
	else {
		if( (d = FUNCTION(new)(x*y)) == NULL  )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		FUNCTION(matrix_init_all)(m, x, y, d);
	}
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_init_empty)(TYPE(Matrix) *m) {
	return FUNCTION(matrix_init)(m, 0, 0);
}

/* private structure allocator */
VIEW(Matrix) *FUNCTION(matrixview_new_struct)(void);

VIEW(Matrix) *FUNCTION(matrixview_new)(void) {
	VIEW(Matrix) *mv = FUNCTION(matrixview_new_struct)();
	if( mv != NULL && FUNCTION(matrixview_init)(mv) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	return mv;
}

VIEW(Matrix) *FUNCTION(matrixview_new_struct)(void) {
	VIEW(Matrix) *mv;
	if(  (mv = (VIEW(Matrix) *)malloc(sizeof(VIEW(Matrix)))) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	return mv;
}

VIEW(Matrix) *FUNCTION(matrixview_init)(VIEW(Matrix) *mv) {
	return FUNCTION(matrixview_init_all)(mv, 0, 0, 0, NULL);
}

VIEW(Matrix) *FUNCTION(matrixview_init_matrix)(VIEW(Matrix) *mv, TYPE(Matrix) *base_m) {
	return FUNCTION(matrixview_init_all)(mv, base_m->size_x, base_m->size_y, base_m->size_x, base_m->data);
}

VIEW(Matrix) *FUNCTION(matrixview_init_submatrix)(VIEW(Matrix) *mv, TYPE(Matrix) *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y) {
	if( base_offset_x + base_size_x > base_m->size_x || base_offset_y + base_size_y > base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
	return FUNCTION(matrixview_init_all)(mv, base_size_x, base_size_y, base_m->size_x, base_m->data + base_offset_x + base_m->size_x * base_offset_y);
}

VIEW(Vector) *FUNCTION(matrix_row)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_row) {
#if defined(CUL_RANGE_CHECK)
	if( base_row >= base_m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return FUNCTION(vectorview_init_struct)(vv, base_m->size_x, 1, base_m->data + base_m->size_x * base_row);
}

VIEW(Vector) *FUNCTION(matrix_col)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_col) {
#if defined(CUL_RANGE_CHECK)
	if( base_col >= base_m->size_x ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return FUNCTION(vectorview_init_struct)(vv, base_m->size_y, base_m->size_x, base_m->data + base_col);
}

VIEW(Vector) *FUNCTION(matrix_diag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m) {
	return FUNCTION(vectorview_init_struct)(vv, cul_umin_pair(base_m->size_x, base_m->size_y), base_m->size_x + 1, base_m->data);
}

VIEW(Vector) *FUNCTION(matrix_subdiag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_k) {
#if defined(CUL_RANGE_CHECK)
	if( base_k >= base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return FUNCTION(vectorview_init_struct)(vv, cul_umin_pair(base_m->size_x - base_k, base_m->size_y), base_m->size_x + 1, base_m->data + base_m->size_x * base_k);
}

VIEW(Vector) *FUNCTION(matrix_superdiag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_k) {
#if defined(CUL_RANGE_CHECK)
	if( base_k >= base_m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);;
#endif
	return FUNCTION(vectorview_init_struct)(vv, cul_umin_pair(base_m->size_x, base_m->size_y - base_k), base_m->size_x + 1, base_m->data + base_k);
}

void FUNCTION(matrix_free)(TYPE(Matrix) *m) {
	FUNCTION(matrix_free_data)(m);
	free(m);
}

void FUNCTION(matrix_free_data)(TYPE(Matrix) *m) {
	if( m != NULL )
		free(m->data);
}

void FUNCTION(matrixview_free)(VIEW(Matrix) *mv) {
	free(mv);
}

cul_errno FUNCTION(matrix_copy)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m) {
	if( m->size_x != base_m->size_x || m->size_y != base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(m->data, base_m->data, base_m->size_x * base_m->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_offset)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t offset_x, size_t offset_y) {
	if( m->size_x - offset_x < base_m->size_x || m->size_y - offset_y < base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(m->data + offset_x + m->size_x * offset_y, base_m->data, base_m->size_x * base_m->size_y, base_m->size_x, m->size_x - offset_x, 0);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_submatrix)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t base_offset_x, size_t base_offset_y) {
	if( base_m->size_x - base_offset_x < m->size_x || base_m->size_y - base_offset_y < m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(m->data, base_m->data + base_offset_x + base_m->size_x * base_offset_y, m->size_x * m->size_y, m->size_x, 0, base_m->size_x - base_offset_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view)(TYPE(Matrix) *m, const VIEW(Matrix) *base_mv) {
	if( m->size_x != base_mv->size_x || m->size_y == base_mv->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	if( base_mv->tda == base_mv->size_x )
		FUNCTION(copy)(m->data, base_mv->data, base_mv->size_x * base_mv->size_y);
	else
		FUNCTION(copy_tda)(m->data, base_mv->data, base_mv->size_x * base_mv->size_y, base_mv->size_x, 0, base_mv->tda - base_mv->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy)(VIEW(Matrix) *mv, const VIEW(Matrix) *base_mv) {
	if( mv->size_x != base_mv->size_x || mv->size_y == base_mv->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_tda)(mv->data, base_mv->data, base_mv->size_x * base_mv->size_y, base_mv->size_x, mv->tda - mv->size_x, base_mv->tda - base_mv->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_row)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t row, size_t base_row) {
	if( row >= m->size_y || base_row >= base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( m->size_x != base_m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(m->data + m->size_x * row, base_m->data + base_m->size_x * base_row, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_col)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t col, size_t base_col) {
	if( col >= m->size_x || base_col >= base_m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( m->size_y != base_m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(m->data + col, base_m->data + base_col, base_m->size_y, m->size_x, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_get_row)(TYPE(Vector) *v, const TYPE(Matrix) *m, const size_t row) {
	if( row >= m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( v->size != m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(v->data, m->data + m->size_x * row, v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_get_col)(TYPE(Vector) *v, const TYPE(Matrix) *m, const size_t col) {
	if( col >= m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( v->size != m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(v->data, m->data + col, v->size, 1, m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_set_row)(TYPE(Matrix) *m, const TYPE(Vector) *v, const size_t row) {
	if( row >= m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( v->size != m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(m->data + m->size_x * row, v->data, m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_set_col)(TYPE(Matrix) *m, const TYPE(Vector) *v, const size_t col) {
	if( col >= m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( v->size != m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(m->data + col, v->data, m->size_y, m->size_x, 1);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap)(TYPE(Matrix) *ma, TYPE(Matrix) *mb) {
	if( ma->size_x != mb->size_x || ma->size_y != mb->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(ma->data, mb->data, ma->size_x * ma->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_row)(TYPE(Matrix) *ma, TYPE(Matrix) *mb, size_t row_a, size_t row_b) {
	if( row_a >= ma->size_y || row_b >= mb->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( ma->size_x != mb->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(ma->data + ma->size_x * row_a, mb->data + mb->size_x * row_b, ma->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_col)(TYPE(Matrix) *ma, TYPE(Matrix) *mb, size_t col_a, size_t col_b) {
	if( col_a >= ma->size_x || col_b >= mb->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( ma->size_y != mb->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_stride)(ma->data + col_a, mb->data + col_b, ma->size_y, ma->size_x, mb->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_transpose)(TYPE(Matrix) *m) {
	if( m->size_x != m->size_y )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	CUL_ERROR_ERRNO_RET_VAL(CUL_ESTUB, CUL_ESTUB);
}

cul_errno FUNCTION(matrix_transpose_copy)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m) {
	if( m->size_x != base_m->size_y || m->size_y != base_m->size_x )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	CUL_ERROR_ERRNO_RET_VAL(CUL_ESTUB, CUL_ESTUB);
}

TYPE(Matrix) *FUNCTION(matrix_resize)(TYPE(Matrix) *m, size_t x, size_t y) {
	/* copy structure to temporary container */
	TYPE(Matrix) m_tmp = *m;
	const size_t size_x = cul_umin_pair(m->size_x, x), size_y = cul_umin_pair(m->size_y, y);

	if( FUNCTION(matrix_init)(m, x, y) != NULL ) {
		*m = m_tmp;
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}
	FUNCTION(copy_tda)(m->data, m_tmp.data, m_tmp.size_x * size_y, size_x, m_tmp.size_x - size_x, x - size_x);
	FUNCTION(matrix_free_data)(&m_tmp);
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_resize_rows)(TYPE(Matrix) *m, size_t x) {
	/* copy structure to temporary container */
	TYPE(Matrix) m_tmp = *m;
	const size_t size_x = cul_umin_pair(m->size_x, x);

	if( FUNCTION(matrix_init)(m, x, m_tmp.size_y) == NULL ) {
		*m = m_tmp;
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}
	FUNCTION(copy_tda)(m->data, m_tmp.data, m_tmp.size_x * m_tmp.size_y, size_x, m_tmp.size_x - size_x, x - size_x);
	FUNCTION(matrix_free_data)(&m_tmp);
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_resize_cols)(TYPE(Matrix) *m, size_t y) {
	/* copy structure to temporary container */
	TYPE(Matrix) m_tmp = *m;

	if( FUNCTION(matrix_init)(m, m_tmp.size_x, y) == NULL ) {
		*m = m_tmp;
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}
	FUNCTION(copy)(m->data, m_tmp.data, m_tmp.size_x * cul_umin_pair(m_tmp.size_y, y));
	FUNCTION(matrix_free_data)(&m_tmp);
	return m;
}

ATOM FUNCTION(matrix_min)(const TYPE(Matrix) *m) {
	return FUNCTION(min)(m->data, m->size_x * m->size_y);
}

size_t FUNCTION(matrix_min_index)(const TYPE(Matrix) *m) {
	return FUNCTION(min_index)(m->data, m->size_x * m->size_y);
}

ATOM FUNCTION(matrix_max)(const TYPE(Matrix) *m) {
	return FUNCTION(max)(m->data, m->size_x * m->size_y);
}

size_t FUNCTION(matrix_max_index)(const TYPE(Matrix) *m) {
	return FUNCTION(max_index)(m->data, m->size_x * m->size_y);
}

void FUNCTION(matrix_minmax)(const TYPE(Matrix) *m, ATOM *min, ATOM *max) {
	return FUNCTION(minmax)(m->data, m->size_x * m->size_y, min, max);
}

void FUNCTION(matrix_minmax_index)(const TYPE(Matrix) *m, size_t *min_i, size_t *max_i) {
	return FUNCTION(minmax_index)(m->data, m->size_x * m->size_y, min_i, max_i);
}

cul_errno FUNCTION(matrix_print_stream)(const TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i< m->size_y; ++i) {
		if( FUNCTION(stream_printf)(format, separator, FUNCTION(matrix_const_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
		if( cul_stream_printf("\n") < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fprintf)(FILE *id, const TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i<m->size_y; ++i) {
		if( FUNCTION(fprintf)(id, format, separator, FUNCTION(matrix_const_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
		if( cul_fprintf(id, "\n") < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fscanf)(FILE *id, TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i<m->size_y; ++i)
		if( FUNCTION(fscanf)(id, format, separator, FUNCTION(matrix_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_ESCANF, CUL_ESCANF);
	return CUL_SUCCESS;
}
