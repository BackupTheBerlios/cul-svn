TYPE(Matrix) *FUNCTION(matrix_new)(size_t x, size_t y) {
	TYPE(Matrix) *this;
	ATOM *data;

	if( (this = FUNCTION(matrix_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( x == 0 || y == 0 )
		FUNCTION(matrix_init_struct)(this, NULL, x, y);
	else {
		if( (data = malloc((x*y) * sizeof(ATOM))) == NULL  )
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

	memcpy(this->data, other->data, this->size_x*this->size_y*sizeof(ATOM));

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_offset)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t offset_x, size_t offset_y) {
	if( this->size_x - offset_x < other->size_x || this->size_y - offset_y < other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	ATOM *restrict data = this->data + this->size_x * offset_y + offset_x;
	const size_t tda = this->size_x;
	const ATOM *restrict other_data = other->data;
	const size_t other_tda = other->size_x;

	const size_t size = other->size_x;
	const size_t rows = other->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			data[i] = other_data[i];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_submatrix)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t other_offset_x, size_t other_offset_y) {
	if( other->size_x - other_offset_x < this->size_x || other->size_y - other_offset_y < this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	ATOM *restrict data = this->data;
	const size_t tda = this->size_x;
	const ATOM *restrict other_data = other->data + other->size_x * other_offset_y + other_offset_x;
	const size_t other_tda = other->size_x;

	const size_t size = this->size_x;
	const size_t rows = this->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			data[i] = other_data[i];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_row)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t row, size_t other_row) {
	if( row >= this->size_y || other_row >= other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_x != other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	memcpy(this->data + this->size_x * row, other->data + other->size_x * other_row, this->size_x*sizeof(ATOM));

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_col)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t col, size_t other_col) {
	if( col >= this->size_x || other_col >= other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data + col;
	const size_t stride = this->size_x;
	const ATOM *restrict other_data = other->data + other_col;
	const size_t other_stride = other->size_x;

	const size_t size = stride * this->size_y;
	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		data[i] = other_data[other_i];

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view)(TYPE(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y == other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	if( other->tda == other->size_x )
		memcpy(this->data, other->data, this->size_x*this->size_y*sizeof(ATOM));
	else {
		ATOM *restrict data = this->data;
		const size_t tda = this->size_x;
		const ATOM *restrict other_data = other->data;
		const size_t other_tda = other->tda;

		const size_t size = this->size_x;
		const size_t rows = this->size_y;
		for(size_t row = 0; row < rows; ++row) {
			for(size_t i = 0; i < size; ++i)
				data[i] = other_data[i];

			/* adjust current row */
			data += tda;
			other_data += other_tda;
		}
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view_offset)(TYPE(Matrix) *this, const VIEW(Matrix) *other, size_t offset_x, size_t offset_y) {
	if( this->size_x - offset_x < other->size_x || this->size_y - offset_y < other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	ATOM *restrict data = this->data + this->size_x * offset_y + offset_x;
	const size_t tda = this->size_x;
	const ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size = other->size_x;
	const size_t rows = other->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			data[i] = other_data[i];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	const ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size = this->size_x;
	const size_t rows = this->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			data[i] = other_data[i];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy_matrix)(VIEW(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	const ATOM *restrict other_data = other->data;
	const size_t other_tda = other->size_x;

	const size_t size = this->size_x;
	const size_t rows = this->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			data[i] = other_data[i];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap)(TYPE(Matrix) *this, TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	ATOM *restrict other_data = other->data;
	ATOM tmp;

	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		CUL_SWAP(data[i], other_data[i], tmp);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_row)(TYPE(Matrix) *this, TYPE(Matrix) *other, size_t row, size_t other_row) {
	if( row >= this->size_y || other_row >= other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_x != other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data + this->size_x * row;
	ATOM *restrict other_data = other->data + other->size_x * other_row;
	ATOM tmp;

	const size_t size = this->size_x;
	for(size_t i = 0; i < size; ++i)
		CUL_SWAP(data[i], other_data[i], tmp);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_swap_col)(TYPE(Matrix) *this, TYPE(Matrix) *other, size_t col, size_t other_col) {
	if( col >= this->size_x || other_col >= other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data + col;
	const size_t stride = this->size_x;
	ATOM *restrict other_data = other->data + other_col;
	const size_t other_stride = other->size_x;
	ATOM tmp;

	const size_t size = stride * this->size_y;
	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		CUL_SWAP(data[i], other_data[other_i], tmp);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_swap)(VIEW(Matrix) *this, VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;
	ATOM tmp;

	const size_t size = this->size_x;
	const size_t rows = this->size_y;
	for(size_t row = 0; row < rows; ++row) {
		for(size_t i = 0; i < size; ++i)
			CUL_SWAP(data[i], other_data[i], tmp);

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

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
		memcpy(data, this->data, copy_x*copy_y*sizeof(ATOM));
	else {
		ATOM *restrict this_data = data;
		const size_t this_tda = x;
		const ATOM *restrict other_data = this->data;
		const size_t other_tda = this->size_x;

		const size_t size = copy_x;
		const size_t rows = copy_y;
		for(size_t row = 0; row < rows; ++row) {
			for(size_t i = 0; i < size; ++i)
				this_data[i] = other_data[i];

			/* adjust current row */
			this_data += this_tda;
			other_data += other_tda;
		}
	}

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
	ATOM *restrict data = this->data;

	/* set all */
	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] = value;
}

void FUNCTION(matrix_set_diag)(TYPE(Matrix) *this, ATOM value, ATOM diag) {
	ATOM *restrict data = this->data;

	/* set all */
	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] = value;

	/* set diag */
	const size_t stride = this->size_x + 1;
	for(size_t i = 0; i < size; i += stride)
		data[i] = diag;
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(matrix_add_constant)(TYPE(Matrix) *this, double value) {
		ATOM *restrict data = this->data;

		const size_t size = this->size_x * this->size_y;
		for(size_t i = 0; i < size; ++i)
			data[i] += value;
	}

	void FUNCTION(matrix_scale)(TYPE(Matrix) *this, double value) {
		ATOM *restrict data = this->data;

		const size_t size = this->size_x * this->size_y;
		for(size_t i = 0; i < size; ++i)
			data[i] *= value;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(matrix_zero)(TYPE(Matrix) *this) {
	memset(this->data, 0, this->size_x * this->size_y * sizeof(ATOM));
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
	ATOM *restrict data = this->data;
	const size_t row = this->size_x, tda = this->tda - row;

	/* set all */
	const size_t size = this->tda * this->size_y;
	for(size_t i = 0; i < size; i += tda)
		for(const size_t end = i + row; i < end; ++i)
			data[i] = value;
}

void FUNCTION(matrixview_set_diag)(VIEW(Matrix) *this, ATOM value, ATOM diag) {
	ATOM *restrict data = this->data;
	const size_t row = this->size_x, tda = this->tda - row;

	/* set all */
	const size_t size = this->tda * this->size_y;
	for(size_t i = 0; i < size; i += tda)
		for(const size_t end = i + row; i < end; ++i)
			data[i] = value;

	/* set diag */
	for(size_t i = 0; i < size; i += (tda + 1))
		data[i] = diag;
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(matrixview_add_constant)(VIEW(Matrix) *this, double value) {
		ATOM *restrict data = this->data;
		const size_t row = this->size_x, tda = this->tda - row;

		const size_t size = this->tda * this->size_y;
		for(size_t i = 0; i < size; i += tda)
			for(const size_t end = i + row; i < end; ++i)
				data[i] += value;
	}

	void FUNCTION(matrixview_scale)(VIEW(Matrix) *this, double value) {
		ATOM *restrict data = this->data;
		const size_t row = this->size_x, tda = this->tda - row;

		const size_t size = this->tda * this->size_y;
		for(size_t i = 0; i < size; i += tda)
			for(const size_t end = i + row; i < end; ++i)
				data[i] *= value;
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

	double FUNCTION(matrix_variance)(const TYPE(Matrix) *this) {
		return FUNCTION(variance)(this->data, this->size_x * this->size_y);
	}

	double FUNCTION(matrix_variance_mean)(const TYPE(Matrix) *this, double mean) {
		return FUNCTION(variance_mean)(this->data, this->size_x * this->size_y, mean);
	}

	double FUNCTION(matrixview_sum)(const VIEW(Matrix) *this) {
		return FUNCTION(sum_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda);
	}
	
	double FUNCTION(matrixview_mean)(const VIEW(Matrix) *this) {
		return FUNCTION(mean_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda);
	}
	
	double FUNCTION(matrixview_variance)(const VIEW(Matrix) *this) {
		return FUNCTION(variance_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda);
	}

	double FUNCTION(matrixview_variance_mean)(const VIEW(Matrix) *this, double mean) {
		return FUNCTION(variance_mean_tda)(this->data, this->tda * this->size_y, this->size_x, this->tda, mean);
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
