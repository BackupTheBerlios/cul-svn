TYPE(Matrix) *FUNCTION(matrix_new)(size_t x, size_t y) {
	TYPE(Matrix) *this;
	ATOM *data;

	if( (this = FUNCTION(matrix_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	const size_t size = x*y;
	if( size == 0 )
		FUNCTION(matrix_init_struct)(this, NULL, 0, 0);
	else {
		if( (data = malloc(size * sizeof(ATOM))) == NULL  )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		FUNCTION(matrix_init_struct)(this, data, x, y);
	}
	return this;
}

TYPE(Matrix) *FUNCTION(matrix_new_empty)(void) {
	return FUNCTION(matrix_new)(0, 0);
}

#ifndef TEMPLATE_CUL_PTR
	TYPE(Matrix) *FUNCTION(matrix_clone)(TYPE(Matrix) *this) {
		TYPE(Matrix) *clone;
		
		if( (clone = FUNCTION(matrix_new)(this->size_x, this->size_y)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(matrix_copy)(clone, this) ) {
			FUNCTION(matrix_free)(clone);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
	
	TYPE(Matrix) *FUNCTION(matrix_clone_view)(VIEW(Matrix) *this) {
		TYPE(Matrix) *clone;
		
		if( (clone = FUNCTION(matrix_new)(this->size_x, this->size_y)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(matrix_copy_view)(clone, this) ) {
			FUNCTION(matrix_free)(clone);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(matrix_free)(TYPE(Matrix) *this) {
	if( this != NULL ) {
		free(this->data);
		free(this);
	}
}

VIEW(Matrix) *FUNCTION(matrixview_new)(void) {
	VIEW(Matrix) *this;
	if( (this = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(this, NULL, 0, 0, 0);
}

void FUNCTION(matrixview_free)(VIEW(Matrix) *this) {
	free(this);
}

VIEW(Matrix) *FUNCTION(matrixview_matrix)(VIEW(Matrix) *this, TYPE(Matrix) *base) {
	if( this == NULL && (this = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(this, base->data, base->size_x, base->size_y, base->size_x);
}

VIEW(Matrix) *FUNCTION(matrixview_submatrix)(VIEW(Matrix) *this, TYPE(Matrix) *base, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y) {
	if( base_offset_x + base_size_x > base->size_x || base_offset_y + base_size_y > base->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(matrixview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(matrixview_init_struct)(this, base->data + base_offset_x + base->size_x * base_offset_y, base_size_x, base_size_y, base->size_x);
}

VIEW(Vector) *FUNCTION(matrixview_row)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_row) {
	if( base_row >= base->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base->size_x * base_row, base->size_x, 1);
}

VIEW(Vector) *FUNCTION(matrixview_col)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_col) {
	if( base_col >= base->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base_col, base->size_y, base->size_x);
}

VIEW(Vector) *FUNCTION(matrixview_diag)(VIEW(Vector) *this, const TYPE(Matrix) *base) {
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data, cul_umin_2(base->size_x, base->size_y), base->size_x + 1);
}

VIEW(Vector) *FUNCTION(matrixview_subdiag)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_k) {
	if( base_k >= base->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base->size_x * base_k, cul_umin_2(base->size_x - base_k, base->size_y), base->size_x + 1);
}

VIEW(Vector) *FUNCTION(matrixview_superdiag)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_k) {
	if( base_k >= base->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base_k, cul_umin_2(base->size_x, base->size_y - base_k), base->size_x + 1);
}

cul_errno FUNCTION(matrix_copy)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(this->data, other->data, other->size_x * other->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_offset)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t offset_x, size_t offset_y) {
	if( this->size_x - offset_x < other->size_x || this->size_y - offset_y < other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(this->data + offset_x + this->size_x * offset_y, other->data, other->size_x * other->size_y, other->size_x, this->size_x, other->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_submatrix)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t other_offset_x, size_t other_offset_y) {
	if( other->size_x - other_offset_x < this->size_x || other->size_y - other_offset_y < this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy_tda)(this->data, other->data + other_offset_x + other->size_x * other_offset_y, other->size_x * (this->size_y - 1) + this->size_x, this->size_x, this->size_x, other->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_row)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t row, size_t other_row) {
	if( row >= this->size_y || other_row >= other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_x != other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(this->data + this->size_x * row, other->data + other->size_x * other_row, other->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_col)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t col, size_t other_col) {
	if( col >= this->size_x || other_col >= other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(this->data + col, other->data + other_col, other->size_y, this->size_x, other->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view)(TYPE(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y == other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	if( other->tda == other->size_x )
		FUNCTION(copy)(this->data, other->data, other->size_x * other->size_y);
	else
		FUNCTION(copy_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->size_x, other->tda);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y == other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap)(TYPE(Matrix) *this, TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(this->data, other->data, this->size_x * this->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_row)(TYPE(Matrix) *this, TYPE(Matrix) *other, size_t row, size_t other_row) {
	if( row >= this->size_y || other_row >= other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_x != other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(this->data + this->size_x * row, other->data + other->size_x * other_row, this->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_col)(TYPE(Matrix) *this, TYPE(Matrix) *other, size_t col, size_t other_col) {
	if( col >= this->size_x || other_col >= other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_stride)(this->data + col, other->data + other_col, this->size_y, this->size_x, other->size_x);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_swap)(VIEW(Matrix) *this, VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_transpose)(TYPE(Matrix) *this) {
	if( this->size_x != this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	CUL_ERROR_ERRNO_RET(CUL_ESTUB, CUL_ESTUB);
}

cul_errno FUNCTION(matrixview_transpose)(VIEW(Matrix) *this) {
	if( this->size_x != this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	CUL_ERROR_ERRNO_RET(CUL_ESTUB, CUL_ESTUB);
}

cul_errno FUNCTION(matrix_resize)(TYPE(Matrix) *this, size_t x, size_t y) {
	ATOM *data;

	if( x*y == 0 ) {
		free(this->data);
		FUNCTION(matrix_init_struct)(this, NULL, 0, 0);
		return CUL_SUCCESS;
	}	else if( (data = malloc((x*y)*sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	const size_t copy_x = x > this->size_x? this->size_x: x;
	const size_t copy_y = y > this->size_y? this->size_y: y;

	if( x == copy_x )
		FUNCTION(copy)(data, this->data, copy_x * copy_y);
	else
		FUNCTION(copy_tda)(data, this->data, this->size_x * copy_y, copy_x, x, this->size_x);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, x, y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_resize_empty)(TYPE(Matrix) *this, size_t x, size_t y) {
	ATOM *data;

	if( x*y == 0 ) {
		free(this->data);
		FUNCTION(matrix_init_struct)(this, NULL, 0, 0);
		return CUL_SUCCESS;
	}	else if( (data = malloc((x*y) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, x, y);
	return CUL_SUCCESS;
}

void FUNCTION(matrix_set_all)(TYPE(Matrix) *this, ATOM value) {
	FUNCTION(set)(this->data, this->size_x * this->size_y, value);
}

void FUNCTION(matrix_set_diag)(TYPE(Matrix) *this, ATOM value, ATOM diag) {
	FUNCTION(set)(this->data, this->size_x * this->size_y, value);
	FUNCTION(set_stride)(this->data, this->size_x * this->size_y, this->size_x + 1, diag);
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(matrix_add_constant)(TYPE(Matrix) *this, double value) {
		FUNCTION(add_constant)(this->data, this->size_x * this->size_y, value);
	}

	void FUNCTION(matrix_scale)(TYPE(Matrix) *this, double value) {
		FUNCTION(scale)(this->data, this->size_x * this->size_y, value);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(matrix_zero)(TYPE(Matrix) *this) {
	FUNCTION(zero)(this->data, this->size_x * this->size_y);
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(matrix_add)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add)(this->data, other->data, other->size_x * other->size_y);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrix_sub)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub)(this->data, other->data, other->size_x * other->size_y);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrix_mul)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul)(this->data, other->data, other->size_x * other->size_y);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrix_div)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div)(this->data, other->data, other->size_x * other->size_y);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(matrixview_set_all)(VIEW(Matrix) *this, ATOM value) {
	FUNCTION(set_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, value);
}

void FUNCTION(matrixview_set_diag)(VIEW(Matrix) *this, ATOM value, ATOM diag) {
	FUNCTION(set_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, value);
	FUNCTION(set_stride)(this->data, this->tda * this->size_y, this->tda + 1, diag);
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(matrixview_add_constant)(VIEW(Matrix) *this, double value) {
		FUNCTION(add_constant_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, value);
	}

	void FUNCTION(matrixview_scale)(VIEW(Matrix) *this, double value) {
		FUNCTION(scale_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, value);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(matrixview_add)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrixview_sub)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrixview_mul)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(matrixview_div)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
		if( this->size_x != other->size_x || this->size_y != other->size_y )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div_tda)(this->data, other->data, other->tda * other->size_y, other->size_x, this->tda, other->tda);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(matrix_min)(const TYPE(Matrix) *this) {
		return FUNCTION(min)(this->data, this->size_x * this->size_y);
	}
	
	size_t FUNCTION(matrix_min_index)(const TYPE(Matrix) *this) {
		return FUNCTION(min_index)(this->data, this->size_x * this->size_y);
	}
	
	ATOM FUNCTION(matrix_max)(const TYPE(Matrix) *this) {
		return FUNCTION(max)(this->data, this->size_x * this->size_y);
	}
	
	size_t FUNCTION(matrix_max_index)(const TYPE(Matrix) *this) {
		return FUNCTION(max_index)(this->data, this->size_x * this->size_y);
	}
	
	void FUNCTION(matrix_minmax)(const TYPE(Matrix) *this, ATOM *min, ATOM *max) {
		return FUNCTION(minmax)(this->data, this->size_x * this->size_y, min, max);
	}
	
	void FUNCTION(matrix_minmax_index)(const TYPE(Matrix) *this, size_t *min_i, size_t *max_i) {
		return FUNCTION(minmax_index)(this->data, this->size_x * this->size_y, min_i, max_i);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	double FUNCTION(matrix_sum)(const TYPE(Matrix) *this) {
		return FUNCTION(sum)(this->data, this->size_x * this->size_y);
	}

	double FUNCTION(matrix_mean)(const TYPE(Matrix) *this) {
		return FUNCTION(mean)(this->data, this->size_x * this->size_y);
	}

	double FUNCTION(matrix_variance)(const TYPE(Matrix) *this, double mean) {
		return FUNCTION(variance)(this->data, this->size_x * this->size_y, mean);
	}

	double FUNCTION(matrixview_sum)(const VIEW(Matrix) *this) {
		return FUNCTION(sum_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda);
	}
	
	double FUNCTION(matrixview_mean)(const VIEW(Matrix) *this) {
		return FUNCTION(mean_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda);
	}
	
	double FUNCTION(matrixview_variance)(const VIEW(Matrix) *this, double mean) {
		return FUNCTION(variance_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, mean);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

cul_errno FUNCTION(matrix_fprintf)(FILE *id, const TYPE(Matrix) *this, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	size_t i;

	/* prepare formatting */
	row = row == NULL? "\n": row;

	for( i=0; i<this->size_y; ++i) {
		if( !FUNCTION(fprintf)(id, FUNCTION(matrix_const_ptr)(this, 0, i), this->size_x, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		if( row != NULL && fprintf(id, row) < 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fscanf)(FILE *id, TYPE(Matrix) *this, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	size_t i;

	/* prepare formatting */
	row = row == NULL? "\n": row;

	for( i=0; i<this->size_y; ++i) {
		if( !FUNCTION(fscanf)(id, FUNCTION(matrix_ptr)(this, 0, i), this->size_x, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		if( row != NULL && fscanf(id, row) != 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}
