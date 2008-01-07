TYPE(Vector) *FUNCTION(vector_new)(size_t size) {
	TYPE(Vector) *this;
	ATOM *data;

	if( (this = FUNCTION(vector_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( size == 0 )
		FUNCTION(vector_init_struct)(this, NULL, 0, 0);
	else {
		if( (data = malloc(size * sizeof(ATOM))) == NULL ) {
			FUNCTION(vector_free_struct)(this);
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
		FUNCTION(vector_init_struct)(this, data, size, size);
	}

	return this;
}

TYPE(Vector) *FUNCTION(vector_new_empty)() {
	return FUNCTION(vector_new)(0);
}

#ifndef TEMPLATE_CUL_PTR
	TYPE(Vector) *FUNCTION(vector_clone)(TYPE(Vector) *this) {
		TYPE(Vector) *clone;
		
		if( (clone = FUNCTION(vector_new)(this->size)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(vector_copy)(clone, this) ) {
			FUNCTION(vector_free)(clone);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
	
	TYPE(Vector) *FUNCTION(vector_clone_view)(VIEW(Vector) *this) {
		TYPE(Vector) *clone;
		
		if( (clone = FUNCTION(vector_new)(this->size)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(vector_copy_view)(clone, this) ) {
			FUNCTION(vector_free)(clone);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
#else /* TEMPLATE_CUL_PTR */
	TYPE(Vector) *FUNCTION(vector_clone)(TYPE(Vector) *this) {
		TYPE(Vector) *clone;
		
		if( (clone = FUNCTION(vector_new)(this->size)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(vector_copy)(clone, this) ) {
			FUNCTION(vector_free)(clone, NULL);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
	
	TYPE(Vector) *FUNCTION(vector_clone_view)(VIEW(Vector) *this) {
		TYPE(Vector) *clone;
		
		if( (clone = FUNCTION(vector_new)(this->size)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		if( FUNCTION(vector_copy_view)(clone, this) ) {
			FUNCTION(vector_free)(clone, NULL);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		
		return clone;
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_free)(TYPE(Vector) *this) {
		if( this != NULL ) {
			free(this->data);
			FUNCTION(vector_free_struct)(this);
		}
	}
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(vector_free)(TYPE(Vector) *this, cul_free_f *free_f) {
		if( this != NULL ) {

			/* free data if needed */
			if( free_f != NULL) {
				ATOM *restrict data = this->data;
				const size_t size = this->size;

				for(size_t i = 0; i < size; ++i)
					free_f(data[i]);
			}

			free(this->data);
			FUNCTION(vector_free_struct)(this);
		}
	}
#endif /* TEMPLATE_CUL_PTR */

VIEW(Vector) *FUNCTION(vectorview_new)() {
	VIEW(Vector) *this;
	if( (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, NULL, 0, 0);
}

void FUNCTION(vectorview_free)(VIEW(Vector) *this) {
	FUNCTION(vectorview_free_struct)(this);
}

VIEW(Vector) *FUNCTION(vectorview_vector)(VIEW(Vector) *this, const TYPE(Vector) *base) {
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data, base->size, 1);
}

VIEW(Vector) *FUNCTION(vectorview_subvector)(VIEW(Vector) *this, const TYPE(Vector) *base, size_t base_offset, size_t base_size, size_t base_stride) {
	if( base_offset + base_size > base->size )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
	if( this == NULL && (this = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return FUNCTION(vectorview_init_struct)(this, base->data + base_offset, base_size, base_stride);
}

cul_errno FUNCTION(vector_copy)(TYPE(Vector) *this, const TYPE(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	memcpy(this->data, other->data, this->size*sizeof(ATOM));

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_offset)(TYPE(Vector) *this, const TYPE(Vector) *other, size_t offset) {
	if( this->size - offset < other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	memcpy(this->data + offset, other->data, other->size*sizeof(ATOM));

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_subvector)(TYPE(Vector) *this, const TYPE(Vector) *other, size_t other_offset) {
	if( other->size - other_offset < this->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	memcpy(this->data, other->data + other_offset, this->size*sizeof(ATOM));

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_view)(TYPE(Vector) *this, const VIEW(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	if( other->stride == 1 )
		memcpy(this->data, other->data, this->size*sizeof(ATOM));
	else {
		ATOM *restrict data = this->data;
		const ATOM *restrict other_data = other->data;
		const size_t other_stride = other->stride;

		const size_t size = this->size;
		for(size_t i = 0, other_i = 0; i < size; ++i, other_i += other_stride)
			data[i] = other_data[other_i];
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_view_offset)(TYPE(Vector) *this, const VIEW(Vector) *other, size_t offset) {
	if( this->size - offset < other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( other->stride == 1 )
		memcpy(this->data + offset, other->data, other->size*sizeof(ATOM));
	else {
		ATOM *restrict data = this->data;
		const ATOM *restrict other_data = other->data;
		const size_t other_stride = other->stride;

		const size_t size = other->size;
		for(size_t i = 0, other_i = 0; i < size; ++i, other_i += other_stride)
			data[i] = other_data[other_i];
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_copy)(VIEW(Vector) *this, const VIEW(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	const size_t stride = this->stride;
	const ATOM *restrict other_data = other->data;
	const size_t other_stride = other->stride;

	const size_t size = stride * this->size;
	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		data[i] = other_data[other_i];

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_copy_vector)(VIEW(Vector) *this, const TYPE(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	if( this->stride == 1 )
		memcpy(this->data, other->data, this->size*sizeof(ATOM));
	else {
		ATOM *restrict data = this->data;
		const size_t stride = this->stride;
		const ATOM *restrict other_data = other->data;

		const size_t size = stride * this->size;
		for(size_t i = 0, other_i = 0; i < size; i += stride, ++other_i)
			data[i] = other_data[other_i];
	}

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_swap)(TYPE(Vector) *this, TYPE(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);

	ATOM *restrict data = this->data;
	ATOM *restrict other_data = other->data;
	ATOM tmp;

	const size_t size = this->size;
	for(size_t i = 0; i < size; ++i)
		CUL_SWAP(data[i], other_data[i], tmp);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_swap)(VIEW(Vector) *this, VIEW(Vector) *other) {
	if( this->size != other->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
	
	ATOM *restrict data = this->data;
	const size_t stride = this->stride;
	ATOM *restrict other_data = other->data;
	const size_t other_stride = other->stride;
	ATOM tmp;

	const size_t size = stride * this->size;
	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		CUL_SWAP(data[i], other_data[other_i], tmp);

	return CUL_SUCCESS;
}

void FUNCTION(vector_reverse)(TYPE(Vector) *this) {
	/* validate minimum size */
	if( this->size < 2 )
		return;

	ATOM *restrict data = this->data;
	ATOM tmp;

	for(size_t i = 0, last = this->size - 1; i < last; ++i, --last)
		CUL_SWAP(data[i], data[last], tmp);
}

void FUNCTION(vectorview_reverse)(VIEW(Vector) *this) {
	/* validate minimum size */
	if( this->size < 2 )
		return;

	ATOM *restrict data = this->data;
	const size_t stride = this->stride;
	ATOM tmp;

	for(size_t i = 0, last = (this->size - 1) * stride; i < last; i += stride, last -= stride)
		CUL_SWAP(data[i], data[last], tmp);
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_resize)(TYPE(Vector) *this, size_t size) {
		ATOM *data;

		if( size == 0 ) {
			free(this->data);
			FUNCTION(vector_init_struct)(this, NULL, 0, 0);
			return CUL_SUCCESS;
		} else if( size >= this->size && size <= this->reserved ) {
			this->size = size;
			return CUL_SUCCESS;
		}

		size_t copy = size < this->size? size: this->size;
		if( (data = malloc(size*sizeof(ATOM))) == NULL )
			CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
		memcpy(data, this->data, copy*sizeof(ATOM));

		free(this->data);

		FUNCTION(vector_init_struct)(this, data, size, size);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
	cul_errno FUNCTION(vector_resize)(TYPE(Vector) *this, size_t size, cul_free_f *free_f) {
		ATOM *data;

		if( size == 0 ) {

			/* free data if needed */
			if( free_f != NULL)  {
				ATOM *restrict data = this->data;

				const size_t size = this->size;
				for(size_t i = 0; i < size; ++i)
					free_f(data[i]);
			}
			free(this->data);

			FUNCTION(vector_init_struct)(this, NULL, 0, 0);
			return CUL_SUCCESS;
		} else if( size >= this->size && size <= this->reserved ) {
			this->size = size;
			return CUL_SUCCESS;
		}

		size_t copy = size < this->size? size: this->size;
		if( (data = malloc(size*sizeof(ATOM))) == NULL )
			CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
		memcpy(data, this->data, copy*sizeof(ATOM));

		/* free data if needed */
		if( free_f != NULL)  {
			ATOM *restrict data = this->data;

			const size_t size = this->size;
			for(size_t i = 0; i < size; ++i)
				free_f(data[i]);
		}
		free(this->data);

		FUNCTION(vector_init_struct)(this, data, size, size);
		return CUL_SUCCESS;
	}
#endif /* TEMPLATE_CUL_PTR */

cul_errno FUNCTION(vector_resize_empty)(TYPE(Vector) *this, size_t size) {
	ATOM *data;

	if( size == 0 ) {
		free(this->data);
		FUNCTION(vector_init_struct)(this, NULL, 0, 0);
		return CUL_SUCCESS;
	} else if( size >= this->size && size <= this->reserved ) {
		this->size = size;
		return CUL_SUCCESS;
	}

	if( (data = (ATOM *)malloc(size * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
	free(this->data);

	FUNCTION(vector_init_struct)(this, data, size, size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_reserve)(TYPE(Vector) *this, size_t size) {
	ATOM *data;

	if( size < this->size )
		size = this->size;

	if( (data = malloc(size*sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
	memcpy(data, this->data, this->size*sizeof(ATOM));
	free(this->data);

	FUNCTION(vector_init_struct)(this, data, this->size, size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_shrink)(TYPE(Vector) *this) {
	return FUNCTION(vector_reserve)(this, this->size);
}

cul_errno FUNCTION(vector_insert)(TYPE(Vector) *this, size_t offset, ATOM value) {
	if( offset > this->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( this->size + 1 > this->reserved )
		if( FUNCTION(vector_reserve)(this, this->size + 1) )
			CUL_ERROR_ERRNO_RET(CUL_EFAILED, CUL_EFAILED);

	/* make space for item */
	memmove(this->data + offset + 1, this->data + offset, this->size - offset);
	/* copy insert item */
	this->data[offset] = value;
	this->size += 1;
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_insert_vector)(TYPE(Vector) *this, size_t offset, const TYPE(Vector) *other) {
	if( offset + other->size > this->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( this->size + other->size > this->reserved )
		if( FUNCTION(vector_reserve)(this, this->size + other->size) )
			CUL_ERROR_ERRNO_RET(CUL_EFAILED, CUL_EFAILED);

	/* make space for item */
	memmove(this->data + offset + other->size, this->data + offset, (this->size - offset)*sizeof(ATOM));
	/* copy insert item */
	memcpy(this->data + offset, other->data, other->size*sizeof(ATOM));
	this->size += other->size;
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_insert_view)(TYPE(Vector) *this, size_t offset, const VIEW(Vector) *other) {
	if( offset + other->size > this->size )
		CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

	if( this->size + other->size > this->reserved )
		if( FUNCTION(vector_reserve)(this, this->size + other->size) )
			CUL_ERROR_ERRNO_RET(CUL_EFAILED, CUL_EFAILED);

	/* make space for item */
	memmove(this->data + offset + other->size, this->data + offset, (this->size - offset)*sizeof(ATOM));
	/* copy insert item */
	if( other->stride == 1 )
		memcpy(this->data + offset, other->data, other->size*sizeof(ATOM));
	else {
		ATOM *restrict this_data = this->data + offset;
		const ATOM *restrict other_data = other->data;
		const size_t other_stride = other->stride;

		const size_t size = other->size;
		for(size_t i = 0; i < size; ++i)
			this_data[i] = other_data[i * other_stride];
	}
	this->size += other->size;
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_push_back)(TYPE(Vector) *this, ATOM value) {
	if( this->size >= this->reserved )
		if( FUNCTION(vector_reserve)(this, (this->size + 1)*CUL_EFACTOR_MUL + CUL_EFACTOR_SUM) )
			CUL_ERROR_ERRNO_RET(CUL_EFAILED, CUL_EFAILED);

	this->data[this->size] = value;
	this->size += 1;
	return CUL_SUCCESS;
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_remove)(TYPE(Vector) *this, size_t offset) {
		return FUNCTION(vector_remove_range)(this, offset, 1);
	}

	cul_errno FUNCTION(vector_remove_range)(TYPE(Vector) *this, size_t offset, size_t size) {
		if( offset + size > this->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

		this->size -= size;
		memmove(this->data + offset, this->data + offset + size, (this->size - offset)*sizeof(ATOM));
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_pop_back)(TYPE(Vector) *this) {
		if( this->size == 0 )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

		this->size -= 1;
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
	cul_errno FUNCTION(vector_remove)(TYPE(Vector) *this, size_t offset, cul_free_f *free_f) {
		return FUNCTION(vector_remove_range)(this, offset, 1, free_f);
	}

	cul_errno FUNCTION(vector_remove_range)(TYPE(Vector) *this, size_t offset, size_t size, cul_free_f *free_f) {
		if( offset + size > this->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

		/* free data if needed */
		if( free_f != NULL) for(size_t i = offset; i < offset + size; ++i)
			free_f(this->data[i]);

		this->size -= size;
		memmove(this->data + offset, this->data + offset + size, (this->size - offset)*sizeof(ATOM));
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_pop_back)(TYPE(Vector) *this, cul_free_f *free_f) {
		if( this->size == 0 )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

		this->size -= 1;
		if( free_f != NULL ) free_f(this->data[this->size]);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_detach)(TYPE(Vector) *this, cul_clone_f *clone_f) {
		return FUNCTION(vector_detach_range)(this, 0, this->size, clone_f);
	}

	cul_errno FUNCTION(vector_detach_range)(TYPE(Vector) *this, size_t offset, size_t size, cul_clone_f *clone_f) {
		if( offset + size > this->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADPOS, CUL_EBADPOS);

		ATOM *restrict data = this->data;

		/* adjust size */
		size += offset;

		for(size_t i = offset; i < size; ++i)
			if( (data[i] = clone_f(data[i])) == NULL ) {
				/* erase rest of undetached pointers */
				for(++i; i < size; ++i)
					data[i] = NULL;
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
			}
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_detach)(VIEW(Vector) *this, cul_clone_f *clone_f) {
		const size_t stride = this->stride, size = this->size * stride;
		ATOM *restrict data = this->data;

		for(size_t i = 0; i < size; i += stride)
			if( (data[i] = clone_f(data[i])) == NULL ) {
				/* erase rest of undetached pointers */
				for(i += stride; i < size; i += stride)
					data[i] = NULL;
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
			}
		return CUL_SUCCESS;
	}
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(vector_set_all)(TYPE(Vector) *this, ATOM value) {
	ATOM *restrict data = this->data;

	/* set all */
	const size_t size = this->size;
	for(size_t i = 0; i < size; ++i)
		data[i] = value;
}

void FUNCTION(vector_set_basis)(TYPE(Vector) *this, size_t index, ATOM value, ATOM basis) {
	ATOM *restrict data = this->data;

	/* set all */
	const size_t size = this->size;
	for(size_t i = 0; i < size; ++i)
		data[i] = value;

	/* set basis */
	data[index] = basis;
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_add_constant)(TYPE(Vector) *this, double value) {
		ATOM *restrict data = this->data;

		const size_t size = this->size;
		for(size_t i = 0; i < size; ++i)
			data[i] += value;
	}

	void FUNCTION(vector_scale)(TYPE(Vector) *this, double value) {
		ATOM *restrict data = this->data;

		const size_t size = this->size;
		for(size_t i = 0; i < size; ++i)
			data[i] *= value;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(vector_zero)(TYPE(Vector) *this) {
	memset(this->data, 0, this->size * sizeof(ATOM));
}

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_add)(TYPE(Vector) *this, const TYPE(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add)(this->data, other->data, this->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_sub)(TYPE(Vector) *this, const TYPE(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub)(this->data, other->data, this->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_mul)(TYPE(Vector) *this, const TYPE(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul)(this->data, other->data, this->size);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_div)(TYPE(Vector) *this, const TYPE(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div)(this->data, other->data, this->size);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

void FUNCTION(vectorview_set_all)(VIEW(Vector) *this, ATOM value) {
	const size_t stride = this->stride, size = stride * this->size;
	ATOM *restrict data = this->data;

	/* set all */
	if( stride == 1 ) for(size_t i = 0; i < size; ++i)
		data[i] = value;
	else for(size_t i = 0; i < size; i += stride)
		data[i] = value;
}

void FUNCTION(vectorview_set_basis)(VIEW(Vector) *this, size_t index, ATOM value, ATOM basis) {
	const size_t stride = this->stride, size = stride * this->size;
	ATOM *restrict data = this->data;

	/* set all */
	if( stride == 1 ) for(size_t i = 0; i < size; ++i)
		data[i] = value;
	else for(size_t i = 0; i < size; i += stride)
		data[i] = value;

	/* set basis */
	data[index * stride] = basis;
}

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vectorview_add_constant)(VIEW(Vector) *this, double value) {
		const size_t stride = this->stride, size = stride * this->size;
		ATOM *restrict data = this->data;

		/* set all */
		if( stride == 1 ) for(size_t i = 0; i < size; ++i)
			data[i] += value;
		else for(size_t i = 0; i < size; i += stride)
			data[i] += value;
	}

	void FUNCTION(vectorview_scale)(VIEW(Vector) *this, double value) {
		const size_t stride = this->stride, size = stride * this->size;
		ATOM *restrict data = this->data;

		/* set all */
		if( stride == 1 ) for(size_t i = 0; i < size; ++i)
			data[i] *= value;
		else for(size_t i = 0; i < size; i += stride)
			data[i] *= value;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vectorview_add)(VIEW(Vector) *this, const VIEW(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(add_stride)(this->data, other->data, this->size, this->stride, other->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_sub)(VIEW(Vector) *this, const VIEW(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(sub_stride)(this->data, other->data, this->size, this->stride, other->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_mul)(VIEW(Vector) *this, const VIEW(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(mul_stride)(this->data, other->data, this->size, this->stride, other->stride);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_div)(VIEW(Vector) *this, const VIEW(Vector)  *other) {
		if( this->size != other->size )
			CUL_ERROR_ERRNO_RET(CUL_EBADLEN, CUL_EBADLEN);
		FUNCTION(div_stride)(this->data, other->data, this->size, this->stride, other->stride);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(vector_min)(const TYPE(Vector) *this) {
		return FUNCTION(min)(this->data, this->size);
	}

	size_t FUNCTION(vector_min_index)(const TYPE(Vector) *this) {
		return FUNCTION(min_index)(this->data, this->size);
	}

	ATOM FUNCTION(vector_max)(const TYPE(Vector) *this) {
		return FUNCTION(max)(this->data, this->size);
	}

	size_t FUNCTION(vector_max_index)(const TYPE(Vector) *this) {
		return FUNCTION(max_index)(this->data, this->size);
	}

	void FUNCTION(vector_minmax)(const TYPE(Vector) *this, ATOM *min, ATOM *max) {
		FUNCTION(minmax)(this->data, this->size, min, max);
	}

	void FUNCTION(vector_minmax_index)(const TYPE(Vector) *this, size_t *min_i, size_t *max_i) {
		FUNCTION(minmax_index)(this->data, this->size, min_i, max_i);
	}

	ATOM FUNCTION(vectorview_min)(const VIEW(Vector) *this) {
		return FUNCTION(min_stride)(this->data, this->size, this->stride);
	}

	size_t FUNCTION(vectorview_min_index)(const VIEW(Vector) *this) {
		return FUNCTION(min_index_stride)(this->data, this->size, this->stride);
	}

	ATOM FUNCTION(vectorview_max)(const VIEW(Vector) *this) {
		return FUNCTION(max_stride)(this->data, this->size, this->stride);
	}

	size_t FUNCTION(vectorview_max_index)(const VIEW(Vector) *this) {
		return FUNCTION(max_index_stride)(this->data, this->size, this->stride);
	}

	void FUNCTION(vectorview_minmax)(const VIEW(Vector) *this, ATOM *min, ATOM *max) {
		FUNCTION(minmax_stride)(this->data, this->size, this->stride, min, max);
	}

	void FUNCTION(vectorview_minmax_index)(const VIEW(Vector) *this, size_t *min_i, size_t *max_i) {
		FUNCTION(minmax_index_stride)(this->data, this->size, this->stride, min_i, max_i);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	double FUNCTION(vector_sum)(const TYPE(Vector) *this) {
		return FUNCTION(sum)(this->data, this->size);
	}

	double FUNCTION(vector_mean)(const TYPE(Vector) *this) {
		return FUNCTION(mean)(this->data, this->size);
	}

	double FUNCTION(vector_variance)(const TYPE(Vector) *this) {
		return FUNCTION(variance)(this->data, this->size);
	}

	double FUNCTION(vector_variance_mean)(const TYPE(Vector) *this, double mean) {
		return FUNCTION(variance_mean)(this->data, this->size, mean);
	}

	double FUNCTION(vectorview_sum)(const VIEW(Vector) *this) {
		return FUNCTION(sum_stride)(this->data, this->size, this->stride);
	}
	
	double FUNCTION(vectorview_mean)(const VIEW(Vector) *this) {
		return FUNCTION(mean_stride)(this->data, this->size, this->stride);
	}
	
	double FUNCTION(vectorview_variance)(const VIEW(Vector) *this) {
		return FUNCTION(variance_stride)(this->data, this->size, this->stride);
	}

	double FUNCTION(vectorview_variance_mean)(const VIEW(Vector) *this, double mean) {
		return FUNCTION(variance_mean_stride)(this->data, this->size, this->stride, mean);
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(vector_sort_asc)(TYPE(Vector) *this) {
		FUNCTION(sort_asc)(this->data, this->size);
	}

	void FUNCTION(vector_sort_desc)(TYPE(Vector) *this) {
		FUNCTION(sort_desc)(this->data, this->size);
	}

	size_t FUNCTION(vector_unique)(TYPE(Vector) *this) {
		const size_t size = this->size;
		ATOM *restrict data = this->data;

		/* check for non-empty vector */
		if( size == 0 )
			return 0;

		/* number of unique items */
		size_t u = 1;

		for(size_t i = 1; i < size; ++i) {
			if( data[i - 1] == data[i] )
				continue;
			data[u] = data[i];
			++u;
		}
		return u; 
	}

	size_t FUNCTION(vector_find)(const TYPE(Vector) *this, size_t offset, ATOM key) {
		const size_t size = this->size;
		const ATOM *restrict data = this->data;

		for(size_t i = offset; i < size; ++i)
			if( data[i] == key )
				return i;
		return this->size;
	}

	size_t FUNCTION(vector_bfind)(const TYPE(Vector) *this, ATOM key) {
		size_t low = 0, high = this->size;
		const ATOM *restrict data = this->data;

		for(size_t mid; low < high;) {
			mid = low + (high - low)/2;
			if( data[mid] < key )
				low = mid + 1;
			else
				high = mid;
		}

		if( low < this->size && data[low] == key )
			return low;
		return this->size;
	}

	void FUNCTION(vectorview_sort_asc)(VIEW(Vector) *this) {
		if( this->stride == 1 )
			FUNCTION(sort_asc)(this->data, this->size);
		else
			FUNCTION(sort_asc_stride)(this->data, this->size, this->stride);
	}

	void FUNCTION(vectorview_sort_desc)(VIEW(Vector) *this) {
		if( this->stride == 1 )
			FUNCTION(sort_desc)(this->data, this->size);
		else
			FUNCTION(sort_desc_stride)(this->data, this->size, this->stride);
	}

	size_t FUNCTION(vectorview_unique)(VIEW(Vector)  *this) {
		const size_t stride = this->stride, size = this->size * stride;
		ATOM *restrict data = this->data;

		/* check for non-empty vector */
		if( size == 0 )
			return 0;

		/* number of unique items */
		size_t u = stride;

		for(size_t i = stride; i < size; i += stride) {
			if( data[i - stride] == data[i] )
				continue;
			data[u] = data[i];
			u += stride;
		}
		return u / stride; 
	}

	size_t FUNCTION(vectorview_find)(const VIEW(Vector) *this, size_t offset, ATOM key) {
		const size_t stride = this->stride, size = this->size * stride;
		const ATOM *restrict data = this->data;

		for(size_t i = offset * stride; i < size; i += stride)
			if( data[i] == key )
				return i / stride;
		return this->size;
	}

	size_t FUNCTION(vectorview_bfind)(const VIEW(Vector) *this, ATOM key) {
		const size_t stride = this->stride;
		size_t low = 0, high = this->size;
		const ATOM *restrict data = this->data;

		for(size_t mid; low < high;) {
			mid = low + (high - low)/2;
			if( data[mid * stride] < key )
				low = mid + 1;
			else
				high = mid;
		}

		if( low < this->size && data[low * stride] == key )
			return low;
		return this->size;
	}
#else /* TEMPLATE_CUL_PTR */
	void FUNCTION(vector_sort)(TYPE(Vector) *this, cul_cmp_f *cmp_f) {
		FUNCTION(sort)(this->data, this->size, cmp_f);
	}

	size_t FUNCTION(vector_unique)(TYPE(Vector)  *this, cul_eq_f *eq_f) {
		const size_t size = this->size;
		ATOM *restrict data = this->data;

		/* check for non-empty vector */
		if( size == 0 )
			return 0;

		/* number of unique items */
		size_t u = 1;

		for(size_t i = 1; i < size; ++i) {
			if( eq_f(data[i - 1], data[i]) )
				continue;
			data[u] = data[i];
			++u;
		}
		return u; 
	}

	size_t FUNCTION(vector_find)(const TYPE(Vector) *this, size_t offset, ATOM key, cul_eq_f *eq_f) {
		const size_t size = this->size;
		const ATOM *restrict data = this->data;

		for(size_t i = offset; i < size; ++i)
			if( eq_f(data[i], &key) )
				return i;
		return this->size;
	}

	size_t FUNCTION(vector_bfind)(const TYPE(Vector) *this, ATOM key, cul_cmp_f *cmp_f) {
		size_t low = 0, high = this->size;
		const ATOM *restrict data = this->data;

		for(size_t mid; low < high;) {
			mid = low + (high - low)/2;
			if( cmp_f(data[mid], &key) < 0 )
				low = mid + 1;
			else
				high = mid;
		}

		if( low < this->size && cmp_f(data[low], &key) == 0 )
			return low;
		return this->size;
	}

	void FUNCTION(vector_each)(TYPE(Vector) *this, cul_each_f *each_f, cul_ptr user_data) {
		const size_t size = this->size;
		const ATOM *restrict data = this->data;

		for(size_t i = 0; i < size; ++i)
			each_f(data[i], user_data);
	}

	void FUNCTION(vectorview_sort)(VIEW(Vector) *this, cul_cmp_f *cmp_f) {
		if( this->stride == 1 )
			FUNCTION(sort)(this->data, this->size, cmp_f);
		else
			FUNCTION(sort_stride)(this->data, this->size, this->stride, cmp_f);
	}

	size_t FUNCTION(vectorview_unique)(VIEW(Vector)  *this, cul_eq_f *eq_f) {
		const size_t stride = this->stride, size = this->size * stride;
		ATOM *restrict data = this->data;

		/* check for non-empty vector */
		if( size == 0 )
			return 0;

		/* number of unique items */
		size_t u = stride;

		for(size_t i = stride; i < size; i += stride) {
			if( eq_f(data[i - stride], data[i]) )
				continue;
			data[u] = data[i];
			u += stride;
		}
		return u / stride; 
	}

	size_t FUNCTION(vectorview_find)(const VIEW(Vector) *this, size_t offset, ATOM key, cul_eq_f *eq_f) {
		const size_t stride = this->stride, size = this->size * stride;
		const ATOM *restrict data = this->data;

		for(size_t i = offset * stride; i < size; i += stride)
			if( eq_f(data[i], &key) )
				return i / stride;
		return this->size;
	}

	size_t FUNCTION(vectorview_bfind)(const VIEW(Vector) *this, ATOM key, cul_cmp_f *cmp_f) {
		const size_t stride = this->stride;
		size_t low = 0, high = this->size;
		const ATOM *restrict data = this->data;

		for(size_t mid; low < high;) {
			mid = low + (high - low)/2;
			if( cmp_f(data[mid * stride], &key) < 0 )
				low = mid + 1;
			else
				high = mid;
		}

		if( low < this->size && cmp_f(data[low * stride], &key) == 0 )
			return low;
		return this->size;
	}

	void FUNCTION(vectorview_each)(VIEW(Vector) *this, cul_each_f *each_f, cul_ptr user_data) {
		const size_t stride = this->stride, size = this->size * stride;
		const ATOM *restrict data = this->data;

		for(size_t i = 0; i < size; i += stride)
			each_f(data[i], user_data);
	}
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	cul_errno FUNCTION(vector_fprintf)(FILE *stream, const TYPE(Vector) *this, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fprintf)(stream, this->data, this->size, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vector_fscanf)(FILE *stream, TYPE(Vector) *this, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fscanf)(stream, this->data, this->size, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_fprintf)(FILE *stream, const VIEW(Vector) *this, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fprintf_stride)(stream, this->data, this->size, this->stride, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_EPRINTF, CUL_EPRINTF);
		return CUL_SUCCESS;
	}

	cul_errno FUNCTION(vectorview_fscanf)(FILE *stream, VIEW(Vector) *this, const char *format, const char *separator, const char *begin, const char *end) {
		if( !FUNCTION(fscanf_stride)(stream, this->data, this->size, this->stride, format, separator, begin, end) )
			CUL_ERROR_ERRNO_RET(CUL_ESCANF, CUL_ESCANF);
		return CUL_SUCCESS;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */
