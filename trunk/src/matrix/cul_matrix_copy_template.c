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
