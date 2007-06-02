TYPE(Matrix) *FUNCTION(matrix_new)(size_t x, size_t y) {
	TYPE(Matrix) *m;
	ATOM *data;

	if( (m = FUNCTION(matrix_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	size_t size = x*y;
	if( size == 0 )
		FUNCTION(matrix_init_struct)(m, NULL, 0, 0);
	else {
		if( (data = malloc(size * sizeof(ATOM))) == NULL  )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		FUNCTION(matrix_init_struct)(m, data, x, y);
	}
	return m;
}

TYPE(Matrix) *FUNCTION(matrix_new_empty)(void) {
	return FUNCTION(matrix_new)(0, 0);
}

VIEW(Matrix) *FUNCTION(matrixview_new)(void) {
	VIEW(Matrix) *mv;
	if( (mv = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(mv, NULL, 0, 0, 0);
}

VIEW(Matrix) *FUNCTION(matrixview_matrix)(VIEW(Matrix) *mv, TYPE(Matrix) *base_m) {
	if( mv == NULL && (mv = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(mv, base_m->data, base_m->size_x, base_m->size_y, base_m->size_x);
}

VIEW(Matrix) *FUNCTION(matrixview_submatrix)(VIEW(Matrix) *mv, TYPE(Matrix) *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y) {
	if( base_offset_x + base_size_x > base_m->size_x || base_offset_y + base_size_y > base_m->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( mv == NULL && (mv = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(mv, base_m->data + base_offset_x + base_m->size_x * base_offset_y, base_size_x, base_size_y, base_m->size_x);
}

VIEW(Vector) *FUNCTION(matrixview_row)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_row) {
	if( base_row >= base_m->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_m->data + base_m->size_x * base_row, base_m->size_x, 1);
}

VIEW(Vector) *FUNCTION(matrixview_col)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_col) {
	if( base_col >= base_m->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_m->data + base_col, base_m->size_y, base_m->size_x);
}

VIEW(Vector) *FUNCTION(matrixview_diag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m) {
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_m->data, cul_umin_pair(base_m->size_x, base_m->size_y), base_m->size_x + 1);
}

VIEW(Vector) *FUNCTION(matrixview_subdiag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_k) {
	if( base_k >= base_m->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_m->data + base_m->size_x * base_k, cul_umin_pair(base_m->size_x - base_k, base_m->size_y), base_m->size_x + 1);
}

VIEW(Vector) *FUNCTION(matrixview_superdiag)(VIEW(Vector) *vv, const TYPE(Matrix) *base_m, size_t base_k) {
	if( base_k >= base_m->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( vv == NULL && (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(vv, base_m->data + base_k, cul_umin_pair(base_m->size_x, base_m->size_y - base_k), base_m->size_x + 1);
}

void FUNCTION(matrix_free)(TYPE(Matrix) *m) {
	if( m != NULL ) {
		free(m->data);
		free(m);
	}
}

void FUNCTION(matrixview_free)(VIEW(Matrix) *mv) {
	free(mv);
}

cul_errno FUNCTION(matrix_copy)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m) {
	if( m->size_x != base_m->size_x || m->size_y != base_m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(m->data, base_m->data, base_m->size_x * base_m->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_offset)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t offset_x, size_t offset_y) {
	if( m->size_x - offset_x < base_m->size_x || m->size_y - offset_y < base_m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(m->data + offset_x + m->size_x * offset_y, base_m->data, base_m->size_x * base_m->size_y, base_m->size_x, m->size_x, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_submatrix)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t base_offset_x, size_t base_offset_y) {
	if( base_m->size_x - base_offset_x < m->size_x || base_m->size_y - base_offset_y < m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(m->data, base_m->data + base_offset_x + base_m->size_x * base_offset_y, base_m->size_x * (m->size_y-1) + m->size_x, m->size_x, m->size_x, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view)(TYPE(Matrix) *m, const VIEW(Matrix) *base_mv) {
	if( m->size_x != base_mv->size_x || m->size_y == base_mv->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	if( base_mv->tda == base_mv->size_x )
		FUNCTION(copy)(m->data, base_mv->data, base_mv->size_x * base_mv->size_y);
	else
		FUNCTION(copy_tda)(m->data, base_mv->data, base_mv->tda * base_mv->size_y, base_mv->size_x, m->size_x, base_mv->tda);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy)(VIEW(Matrix) *mv, const VIEW(Matrix) *base_mv) {
	if( mv->size_x != base_mv->size_x || mv->size_y == base_mv->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_tda)(mv->data, base_mv->data, base_mv->tda * base_mv->size_y, base_mv->size_x, mv->tda, base_mv->tda);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_row)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t row, size_t base_row) {
	if( row >= m->size_y || base_row >= base_m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( m->size_x != base_m->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(m->data + m->size_x * row, base_m->data + base_m->size_x * base_row, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_col)(TYPE(Matrix) *m, const TYPE(Matrix) *base_m, size_t col, size_t base_col) {
	if( col >= m->size_x || base_col >= base_m->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( m->size_y != base_m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(m->data + col, base_m->data + base_col, base_m->size_y, m->size_x, base_m->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap)(TYPE(Matrix) *ma, TYPE(Matrix) *mb) {
	if( ma->size_x != mb->size_x || ma->size_y != mb->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(ma->data, mb->data, ma->size_x * ma->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_row)(TYPE(Matrix) *ma, TYPE(Matrix) *mb, size_t row_a, size_t row_b) {
	if( row_a >= ma->size_y || row_b >= mb->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( ma->size_x != mb->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(ma->data + ma->size_x * row_a, mb->data + mb->size_x * row_b, ma->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_col)(TYPE(Matrix) *ma, TYPE(Matrix) *mb, size_t col_a, size_t col_b) {
	if( col_a >= ma->size_x || col_b >= mb->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( ma->size_y != mb->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_stride)(ma->data + col_a, mb->data + col_b, ma->size_y, ma->size_x, mb->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_resize)(TYPE(Matrix) *m, size_t x, size_t y) {
	ATOM *d;

	if( x*y == 0 ) {
		free(m->data);
		FUNCTION(matrix_init_struct)(m, NULL, 0, 0);
		return CUL_SUCCESS;
	}	else if( (d = (ATOM *)malloc((x*y) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	const size_t copy_x = x > m->size_x? m->size_x: x;
	const size_t copy_y = y > m->size_y? m->size_y: y;

	if( x == copy_x )
		FUNCTION(copy)(d, m->data, copy_x * copy_y);
	else
		FUNCTION(copy_tda)(d, m->data, m->size_x * copy_y, copy_x, x, m->size_x);

	free(m->data);
	FUNCTION(matrix_init_struct)(m, d, x, y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_resize_empty)(TYPE(Matrix) *m, size_t x, size_t y) {
	ATOM *d;

	if( x*y == 0 ) {
		free(m->data);
		FUNCTION(matrix_init_struct)(m, NULL, 0, 0);
		return CUL_SUCCESS;
	}	else if( (d = (ATOM *)malloc((x*y) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	free(m->data);
	FUNCTION(matrix_init_struct)(m, d, x, y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_transpose)(TYPE(Matrix) *m) {
	if( m->size_x != m->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	CUL_ERROR_ERRNO_RET(CUL_ESTUB, CUL_ESTUB);
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

cul_errno FUNCTION(matrix_fprintf)(FILE *id, const TYPE(Matrix) *m, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	size_t i;

	/* prepare formatting */
	row = row == NULL? "\n": row;

	for( i=0; i<m->size_y; ++i) {
		if( !FUNCTION(fprintf)(id, FUNCTION(matrix_const_ptr)(m, 0, i), m->size_x, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		if( row != NULL && fprintf(id, row) < 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fscanf)(FILE *id, TYPE(Matrix) *m, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	size_t i;

	/* prepare formatting */
	row = row == NULL? "\n": row;

	for( i=0; i<m->size_y; ++i) {
		if( !FUNCTION(fscanf)(id, FUNCTION(matrix_ptr)(m, 0, i), m->size_x, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		if( row != NULL && fscanf(id, row) != 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}
