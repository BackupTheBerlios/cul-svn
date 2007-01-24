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
