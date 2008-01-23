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

VIEW(Vector) *FUNCTION(vectorview_matrix_row)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_row) {
	if( base_row >= base->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base->size_x * base_row, base->size_x, 1);
}

VIEW(Vector) *FUNCTION(vectorview_matrix_col)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t base_col) {
	if( base_col >= base->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base_col, base->size_y, base->size_x);
}

VIEW(Vector) *FUNCTION(vectorview_matrix_diag)(VIEW(Vector) *this, const TYPE(Matrix) *base, size_t offset, int sub_or_sup) {
	size_t size;

	if( sub_or_sup == 0 ) {
		size = base->size_x < base->size_y? base->size_x: base->size_y;
		offset = 0;
	} else if( sub_or_sup > 0 ) {
		if( offset >= base->size_x )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
		size = base->size_x - offset < base->size_y? base->size_x - offset: base->size_y;
	} else {
		if( offset >= base->size_y )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
		size = base->size_x < base->size_y - offset? base->size_x: base->size_y - offset;
		offset = base->size_x * offset;
	}

	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + offset, size, base->size_x + 1);
}

VIEW(Vector) *FUNCTION(vectorview_matrixview_row)(VIEW(Vector) *this, const VIEW(Matrix) *base, size_t base_row) {
	if( base_row >= base->size_y )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base->tda * base_row, base->size_x, 1);
}

VIEW(Vector) *FUNCTION(vectorview_matrixview_col)(VIEW(Vector) *this, const VIEW(Matrix) *base, size_t base_col) {
	if( base_col >= base->size_x )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base_col, base->size_y, base->tda);
}

VIEW(Vector) *FUNCTION(vectorview_matrixview_diag)(VIEW(Vector) *this, const VIEW(Matrix) *base, size_t offset, int sub_or_sup) {
	size_t size;

	if( sub_or_sup == 0 ) {
		size = base->size_x < base->size_y? base->size_x: base->size_y;
		offset = 0;
	} else if( sub_or_sup > 0 ) {
		if( offset >= base->size_x )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
		size = base->size_x - offset < base->size_y? base->size_x - offset: base->size_y;
	} else {
		if( offset >= base->size_y )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
		size = base->size_x < base->size_y - offset? base->size_x: base->size_y - offset;
		offset = base->tda * offset;
	}

	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + offset, size, base->tda + 1);
}

cul_errno FUNCTION(matrix_copy)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	FUNCTION(copy)(this->data, other->data, this->size_x*this->size_y);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_offset)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t offset_x, size_t offset_y) {
	if( this->size_x - offset_x < other->size_x || this->size_y - offset_y < other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	const size_t offset = this->size_x * offset_y + offset_x;
	FUNCTION(copy_tda)(this->data + offset, other->data, other->size_x, other->size_y, this->size_x, other->size_x);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_submatrix)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t other_offset_x, size_t other_offset_y) {
	if( other->size_x - other_offset_x < this->size_x || other->size_y - other_offset_y < this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	const size_t other_offset = other->size_x * other_offset_y + other_offset_x;
	FUNCTION(copy_tda)(this->data, other->data + other_offset, this->size_x, this->size_y, this->size_x, other->size_x);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_row)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t row, size_t other_row) {
	if( row >= this->size_y || other_row >= other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_x != other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	const size_t offset = this->size_x * row;
	const size_t other_offset = other->size_x * other_row;
	FUNCTION(copy)(this->data + offset, other->data + other_offset, this->size_x);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_col)(TYPE(Matrix) *this, const TYPE(Matrix) *other, size_t col, size_t other_col) {
	if( col >= this->size_x || other_col >= other->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);
	if( this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	const size_t offset = col;
	const size_t other_offset = other_col;
	FUNCTION(copy_stride)(this->data + offset, other->data + other_offset, this->size_y, this->size_x, other->size_x);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view)(TYPE(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y == other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	if( other->tda == other->size_x )
		FUNCTION(copy)(this->data, other->data, this->size_x * this->size_y);
	else
		FUNCTION(copy_tda)(this->data, other->data, this->size_x, this->size_y, this->size_x, other->tda);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_copy_view_offset)(TYPE(Matrix) *this, const VIEW(Matrix) *other, size_t offset_x, size_t offset_y) {
	if( this->size_x - offset_x < other->size_x || this->size_y - offset_y < other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	const size_t offset = this->size_x * offset_y + offset_x;
	FUNCTION(copy_tda)(this->data + offset, other->data, other->size_x, other->size_y, this->size_x, other->tda);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	FUNCTION(copy_tda)(this->data, other->data, this->size_x, this->size_y, this->tda, other->tda);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_copy_matrix)(VIEW(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	FUNCTION(copy_tda)(this->data, other->data, this->size_x, this->size_y, this->tda, other->size_x);

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

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			CUL_SWAP(data[x], other_data[x], tmp);

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_transpose)(TYPE(Matrix) *this) {
	if( this->size_x != this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	ATOM tmp;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y - 1;
	for(size_t y = 0; y < size_y; ++y) {

		/* transpose row */
		const size_t size = size_x - y;
		for(size_t x = 1, other_x = size_x; x < size; ++x, other_x += size_x)
			CUL_SWAP(data[x], data[other_x], tmp);

		/* adjust positions */
		data += size_x + 1;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_transpose)(VIEW(Matrix) *this) {
	if( this->size_x != this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM tmp;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y - 1;
	for(size_t y = 0; y < size_y; ++y) {

		/* transpose row */
		const size_t size = size_x - y;
		for(size_t x = 1, other_x = tda; x < size; ++x, other_x += tda)
			CUL_SWAP(data[x], data[other_x], tmp);

		/* adjust positions */
		data += tda + 1;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_resize)(TYPE(Matrix) *this, size_t x, size_t y) {
	ATOM *restrict data;

	if( x == 0 || y == 0 ) {
		free(this->data);
		FUNCTION(matrix_init_struct)(this, NULL, x, y);
		return CUL_SUCCESS;
	}	else if( (data = malloc((x*y)*sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	const size_t copy_x = x > this->size_x? this->size_x: x;
	const size_t copy_y = y > this->size_y? this->size_y: y;

	/* copy data */
	if( x == copy_x )
		FUNCTION(copy)(data, this->data, copy_x * copy_y);
	else
		FUNCTION(copy_tda)(data, this->data, copy_x, copy_y, x, this->size_x);
	free(this->data);

	FUNCTION(matrix_init_struct)(this, data, x, y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_resize_empty)(TYPE(Matrix) *this, size_t x, size_t y) {
	ATOM *restrict data;

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

cul_errno FUNCTION(matrix_insert_row)(TYPE(Matrix) *this, size_t row) {
	if( row > this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	ATOM *restrict data;
	const size_t size = this->size_x * this->size_y;
	const size_t offset = this->size_x * row;

	if( (data = malloc((size + this->size_x) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	/* copy data */
	FUNCTION(copy)(data, this->data, offset);
	FUNCTION(copy)(data + offset + this->size_x, this->data + offset, size - offset);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, this->size_x, this->size_y + 1);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_insert_col)(TYPE(Matrix) *this, size_t col) {
	if( col > this->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	ATOM *restrict data;
	const size_t size = this->size_x * this->size_y;

	if( (data = malloc((size + this->size_y) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	/* copy data */
	FUNCTION(copy_tda)(data, this->data, col, this->size_y, this->size_x + 1, this->size_x);
	FUNCTION(copy_tda)(data + col + 1, this->data + col, this->size_x - col, this->size_y, this->size_x + 1, this->size_x);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, this->size_x + 1, this->size_y);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_remove_row)(TYPE(Matrix) *this, size_t row) {
	if( row >= this->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( this->size_y <= 1 ) {
		free(this->data);
		FUNCTION(matrix_init_struct)(this, NULL, this->size_x, 0);
		return CUL_SUCCESS;
	}

	ATOM *restrict data;
	const size_t size = this->size_x * this->size_y;
	const size_t offset = this->size_x * row;

	if( (data = malloc((size - this->size_x) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	/* copy data */
	FUNCTION(copy)(data, this->data, offset);
	FUNCTION(copy)(data + offset, this->data + offset + this->size_x, size - offset - this->size_x);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, this->size_x, this->size_y - 1);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_remove_col)(TYPE(Matrix) *this, size_t col) {
	if( col >= this->size_x )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( this->size_x <= 1 ) {
		free(this->data);
		FUNCTION(matrix_init_struct)(this, NULL, 0, this->size_y);
		return CUL_SUCCESS;
	}

	ATOM *restrict data;
	const size_t size = this->size_x * this->size_y;

	if( (data = malloc((size - this->size_y) * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);

	/* copy data */
	FUNCTION(copy_tda)(data, this->data, col, this->size_y, this->size_x - 1, this->size_x);
	FUNCTION(copy_tda)(data + col, this->data + col + 1, this->size_x - col - 1, this->size_y, this->size_x - 1, this->size_x);

	free(this->data);
	FUNCTION(matrix_init_struct)(this, data, this->size_x - 1, this->size_y);
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

void FUNCTION(matrix_zero)(TYPE(Matrix) *this) {
	memset(this->data, 0, this->size_x * this->size_y * sizeof(ATOM));
}

cul_errno FUNCTION(matrix_add)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const ATOM *restrict other_data = other->data;

	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] += other_data[i];

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_sub)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const ATOM *restrict other_data = other->data;

	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] -= other_data[i];

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_mul)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const ATOM *restrict other_data = other->data;

	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] *= other_data[i];

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_div)(TYPE(Matrix) *this, const TYPE(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const ATOM *restrict other_data = other->data;

	const size_t size = this->size_x * this->size_y;
	for(size_t i = 0; i < size; ++i)
		data[i] /= other_data[i];

	return CUL_SUCCESS;
}

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

void FUNCTION(matrixview_add_constant)(VIEW(Matrix) *this, double value) {
	ATOM *restrict data = this->data;

	if( this->tda == this->size_x ) {
		const size_t size = this->tda * this->size_y;
		for(size_t i = 0; i < size; ++i)
			data[i] += value;
	} else {
		const size_t size_x = this->size_x;
		const size_t size_y = this->size_y;
		const size_t tda = this->tda;
		for(size_t x, y = 0; y < size_y; ++y, data += tda)
			for(x = 0; x < size_x; ++x)
				data[x] += value;
	}
}

void FUNCTION(matrixview_scale)(VIEW(Matrix) *this, double value) {
	ATOM *restrict data = this->data;

	if( this->tda == this->size_x ) {
		const size_t size = this->tda * this->size_y;
		for(size_t i = 0; i < size; ++i)
			data[i] *= value;
	} else {
		const size_t size_x = this->size_x;
		const size_t size_y = this->size_y;
		const size_t tda = this->tda;
		for(size_t x, y = 0; y < size_y; ++y, data += tda)
			for(x = 0; x < size_x; ++x)
				data[x] *= value;
	}
}

cul_errno FUNCTION(matrixview_add)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			data[x] += other_data[x];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_sub)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			data[x] -= other_data[x];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_mul)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			data[x] *= other_data[x];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrixview_div)(VIEW(Matrix) *this, const VIEW(Matrix) *other) {
	if( this->size_x != other->size_x || this->size_y != other->size_y )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM *restrict other_data = other->data;
	const size_t other_tda = other->tda;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y) {
		for(x = 0; x < size_x; ++x)
			data[x] /= other_data[x];

		/* adjust current row */
		data += tda;
		other_data += other_tda;
	}

	return CUL_SUCCESS;
}

ATOM FUNCTION(matrix_min)(const TYPE(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(EMPTY, CUL_EBADLEN);

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM min = data[0];

	for(size_t i = 1; i < size; ++i)
		if( data[i] < min )
			min = data[i];

	return min;
}

size_t FUNCTION(matrix_min_index)(const TYPE(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(0, CUL_EBADLEN);

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM min = data[0];
	size_t index = 0;

	for(size_t i = 1; i < size; ++i)
		if( data[i] < min ) {
			min = data[i];
			index = i;
		}

	return index;
}

ATOM FUNCTION(matrix_max)(const TYPE(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(EMPTY, CUL_EBADLEN);

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM max = data[0];

	for(size_t i = 1; i < size; ++i)
		if( data[i] > max )
			max = data[i];

	return max;
}

size_t FUNCTION(matrix_max_index)(const TYPE(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(0, CUL_EBADLEN);

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM max = data[0];
	size_t index = 0;

	for(size_t i = 1; i < size; ++i)
		if( data[i] > max ) {
			max = data[i];
			index = i;
		}

	return index;
}

void FUNCTION(matrix_minmax)(const TYPE(Matrix) *this, ATOM *min_v, ATOM *max_v) {
	if( this->size_x == 0 || this->size_y == 0 ) {
		if( min_v != NULL ) *min_v = EMPTY;
		if( max_v != NULL ) *max_v = EMPTY;
		CUL_ERROR_ERRNO_RET_VOID(CUL_EBADLEN);
	}

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM min = data[0], max = min;

	for(size_t i = 1; i < size; ++i) {
		if( data[i] < min )
			min = data[i];
		if( data[i] > max )
			max = data[i];
	}

	if( min_v != NULL ) *min_v = min;
	if( max_v != NULL ) *max_v = max;
}

void FUNCTION(matrix_minmax_index)(const TYPE(Matrix) *this, size_t *min_i, size_t *max_i) {
	if( this->size_x == 0 || this->size_y == 0 ) {
		if( min_i != NULL ) *min_i = 0;
		if( max_i != NULL ) *max_i = 0;
		CUL_ERROR_ERRNO_RET_VOID(CUL_EBADLEN);
	}

	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	ATOM min = data[0], max = min;
	size_t min_index = 0, max_index = 0;

	for(size_t i = 1; i < size; ++i) {
		if( data[i] < min ) {
			min = data[i];
			min_index = i;
		}
		if( data[i] > max ) {
			max = data[i];
			max_index = i;
		}
	}

	if( min_i != NULL ) *min_i = min_index;
	if( max_i != NULL ) *max_i = max_index;
}

ATOM FUNCTION(matrixview_min)(const VIEW(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(EMPTY, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM min = data[0];

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x)
			if( data[x] < min )
				min = data[x];

	return min;
}

size_t FUNCTION(matrixview_min_index)(const VIEW(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(0, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM min = data[0];
	size_t index = 0;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x)
			if( data[x] < min ) {
				min = data[x];
				index = x;
			}

	return (data - this->data) + index;
}

ATOM FUNCTION(matrixview_max)(const VIEW(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(EMPTY, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM max = data[0];

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x)
			if( data[x] > max )
				max = data[x];

	return max;
}

size_t FUNCTION(matrixview_max_index)(const VIEW(Matrix) *this) {
	if( this->size_x == 0 || this->size_y == 0 )
		CUL_ERROR_ERRNO_RET(0, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM max = data[0];
	size_t index = 0;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x)
			if( data[x] > max ) {
				max = data[x];
				index = x;
			}

	return (data - this->data) + index;
}

void FUNCTION(matrixview_minmax)(const VIEW(Matrix) *this, ATOM *min_v, ATOM *max_v) {
	if( this->size_x == 0 || this->size_y == 0 ) {
		if( min_v != NULL ) *min_v = EMPTY;
		if( max_v != NULL ) *max_v = EMPTY;
		CUL_ERROR_ERRNO_RET_VOID(CUL_EBADLEN);
	}

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM min = data[0], max = data[0];

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x) {
			if( data[x] < min )
				min = data[x];
			if( data[x] > max )
				max = data[x];
		}

	if( min_v != NULL ) *min_v = min;
	if( max_v != NULL ) *max_v = max;
}

void FUNCTION(matrixview_minmax_index)(const VIEW(Matrix) *this, size_t *min_i, size_t *max_i) {
	if( this->size_x == 0 || this->size_y == 0 ) {
		if( min_i != NULL ) *min_i = 0;
		if( max_i != NULL ) *max_i = 0;
		CUL_ERROR_ERRNO_RET_VOID(CUL_EBADLEN);
	}

	ATOM *restrict data = this->data;
	const size_t tda = this->tda;
	ATOM min = data[0], max = data[0];
	size_t min_index = 0, max_index = 0;

	const size_t size_x = this->size_x;
	const size_t size_y = this->size_y;
	for(size_t x, y = 0; y < size_y; ++y, data += tda)
		for(x = 0; x < size_x; ++x) {
			if( data[x] < min ) {
				min = data[x];
				min_index = y * size_x + x;
			}
			if( data[x] > max ) {
				max = data[x];
				max_index = y * size_x + x;
			}
		}

	if( min_i != NULL ) *min_i = min_index;
	if( max_i != NULL ) *max_i = max_index;
}

double FUNCTION(matrix_mean)(const TYPE(Matrix) *this) {
	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	long double mean = 0.0;

	for(size_t i = 0, value_i = 1; i < size; ++i, ++value_i)
		mean += (data[i] - mean)/value_i;

	return mean;
}

double FUNCTION(matrix_variance)(const TYPE(Matrix) *this) {
	double mean = FUNCTION(matrix_mean)(this);
	return FUNCTION(matrix_variance_mean)(this, mean);
}

double FUNCTION(matrix_variance_mean)(const TYPE(Matrix) *this, double mean) {
	const size_t size = this->size_x * this->size_y;
	ATOM *restrict data = this->data;
	double variance = 0.0;

	for(size_t i = 0; i < size; ++i)
		variance += (data[i] - mean)*(data[i] - mean);
	return variance / size;
}

double FUNCTION(matrixview_mean)(const VIEW(Matrix) *this) {
	ATOM *restrict data = this->data;
	long double mean = 0.0;

	if( this->tda == this->size_x ) {
		const size_t size = this->tda * this->size_y;
		for(size_t i = 0, value_i = 1; i < size; ++i, ++value_i)
			mean += (data[i] - mean)/value_i;
	} else {
		const size_t tda = this->tda;
		const size_t size_x = this->size_x;
		const size_t size_y = this->size_y;
		for(size_t x, y = 0, value_i = 1; y < size_y; ++y, data += tda)
			for(x = 0; x < size_x; ++x, ++value_i)
				mean += (data[x] - mean)/value_i;
	}

	return mean;
}

double FUNCTION(matrixview_variance)(const VIEW(Matrix) *this) {
	double mean = FUNCTION(matrixview_mean)(this);
	return FUNCTION(matrixview_variance_mean)(this, mean);
}

double FUNCTION(matrixview_variance_mean)(const VIEW(Matrix) *this, double mean) {
	ATOM *restrict data = this->data;
	double variance = 0.0;

	if( this->tda == this->size_x ) {
		const size_t size = this->tda * this->size_y;
		for(size_t i = 0; i < size; ++i)
			variance += (data[i] - mean)*(data[i] - mean);
	} else {
		const size_t tda = this->tda;
		const size_t size_x = this->size_x;
		const size_t size_y = this->size_y;
		for(size_t x, y = 0, i = 1; y < size_y; ++y, data += tda)
			for(x = 0; x < size_x; ++x, ++i)
				variance += (data[x] - mean)*(data[x] - mean);
	}

	return variance / (this->size_x * this->size_y);
}

cul_errno FUNCTION(matrix_fprintf)(FILE *stream, const TYPE(Matrix) *this, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	const ATOM *restrict data = this->data;
	const size_t row_size = this->size_x;
	const size_t size = row_size * this->size_y;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;
	row = row == NULL? "\n": row;

	/* print begin */
	if( begin != NULL && fprintf(stream, "%s", begin) < 0 )
		CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);

	/* print data */
	for(size_t i = 0; i < size; ) {
		/* print single row */
		for(const size_t end = i + row_size; i < end; ++i)
			if( fprintf(stream, separator) < 0 || fprintf(stream, format, data[i]) < 0 )
				CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		/* print row separator */
		if( row != NULL && fprintf(stream, row) < 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}

	/* print end */
	if( end != NULL && fprintf(stream, "%s", end) < 0 )
		CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fscanf)(FILE *stream, TYPE(Matrix) *this, const char *format, const char *separator, const char *begin, const char *end, const char *row) {
	const ATOM *restrict data = this->data;
	const size_t row_size = this->size_x;
	const size_t size = row_size * this->size_y;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;
	row = row == NULL? "\n": row;

	/* print begin */
	if( begin != NULL && fscanf(stream, begin) != 0 )
		CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);

	/* print data */
	for(size_t i = 0; i < size; ) {
		/* print single row */
		for(const size_t end = i + row_size; i < end; ++i)
			if( fscanf(stream, separator) != 0 || fscanf(stream, format, data[i]) != 1 )
				CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		/* print row separator */
		if( row != NULL && fprintf(stream, row) < 0 )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
	}

	/* print end */
	if( end != NULL && fscanf(stream, end) != 0 )
		CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);

	return CUL_SUCCESS;
}

