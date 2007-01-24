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

void FUNCTION(matrix_free_null)(TYPE(Matrix) **m) {
	FUNCTION(matrix_free_data)(*m);
	free(*m);
	*m = NULL;
}

void FUNCTION(matrixview_free)(VIEW(Matrix) *mv) {
	free(mv);
}
