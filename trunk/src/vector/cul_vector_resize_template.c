TYPE(Vector) *FUNCTION(vector_resize)(TYPE(Vector) *v, size_t size) {
	ATOM *d;

	if( size == 0 ) {
		FUNCTION(vector_free_data)(v);
		FUNCTION(vector_init_struct)(v, 0, 0, NULL);
		return v;
	}
	else if( size >= v->size && size <= v->reserved ) {
		v->size = size;
		return v;
	}
	else if( (d = (ATOM *)realloc(v->data, size * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	FUNCTION(vector_init_struct)(v, size, size, d);
	return v;
}

TYPE(Vector) *FUNCTION(vector_reserve)(TYPE(Vector) *v, size_t size) {
	ATOM *d;

	if( size == 0 ) {
		FUNCTION(vector_free_data)(v);
		FUNCTION(vector_init)(v, size);
		return v;
	}
	else if( (d = (ATOM *)realloc(v->data, size * sizeof(ATOM))) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( size < v->size )
		FUNCTION(vector_init_struct)(v, size, size, d);
	else
		FUNCTION(vector_init_struct)(v, size, v->size, d);
	return v;
}

TYPE(Vector) *FUNCTION(vector_push_back)(TYPE(Vector) *v, ATOM val) {
	if( v->size >= v->reserved )
		if( FUNCTION(vector_reserve)(v, (v->size + 1)*CUL_EFACTOR_MUL + CUL_EFACTOR_SUM) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);

	v->size += 1;
	FUNCTION(vector_set)(v, v->size - 1, val);
	return v;
}

TYPE(Vector) *FUNCTION(vector_pop_back)(TYPE(Vector) *v) {
	v->size -= 1;
	return v;
}
