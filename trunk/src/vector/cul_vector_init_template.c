TYPE(Vector) *FUNCTION(vector_new)(size_t size) {
	TYPE(Vector) *v;
	if( (v = FUNCTION(vector_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( FUNCTION(vector_init)(v, size) == NULL ) {
		FUNCTION(vector_free_struct)(v);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return v;
}

TYPE(Vector) *FUNCTION(vector_new_empty)(void) {
	return FUNCTION(vector_new)(0);
}

TYPE(Vector) *FUNCTION(vector_init)(TYPE(Vector) *v, size_t size) {
	ATOM *d;

	if( size == 0 )
		FUNCTION(vector_init_struct)(v, 0, 0, NULL);
	else {
		if( (d = FUNCTION(new)(size)) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
		FUNCTION(vector_init_struct)(v, size, size, d);
	}
	return v;
}

TYPE(Vector) *FUNCTION(vector_init_empty)(TYPE(Vector) *v) {
	return FUNCTION(vector_init)(v, 0);
}

VIEW(Vector) *FUNCTION(vectorview_new)(void) {
	VIEW(Vector) *vv;
	if( (vv = FUNCTION(vectorview_new_struct)()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( FUNCTION(vectorview_init)(vv) == NULL ) {
		FUNCTION(vectorview_free_struct)(vv);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return vv;
}

VIEW(Vector) *FUNCTION(vectorview_init)(VIEW(Vector) *vv) {
	return FUNCTION(vectorview_init_struct)(vv, 0, 0, NULL);
}

VIEW(Vector) *FUNCTION(vectorview_init_vector)(VIEW(Vector) *vv, const TYPE(Vector) *base_v) {
	return FUNCTION(vectorview_init_struct)(vv, base_v->size, 1, base_v->data);
}

VIEW(Vector) *FUNCTION(vectorview_init_subvector)(VIEW(Vector) *vv, const TYPE(Vector) *base_v, size_t base_offset, size_t base_size) {
	if( base_offset + base_size > base_v->size )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
	return FUNCTION(vectorview_init_struct)(vv, base_size, 1, base_v->data + base_offset);
}

VIEW(Vector) *FUNCTION(vectorview_init_subvector_stride)(VIEW(Vector) *vv, const TYPE(Vector) *base_v, size_t base_offset, size_t base_size, size_t base_stride) {
	if( base_offset + base_size > base_v->size )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
	return FUNCTION(vectorview_init_struct)(vv, base_size, base_stride, base_v->data + base_offset);
}

void FUNCTION(vector_free)(TYPE(Vector) *v) {
	FUNCTION(vector_free_data)(v);
	FUNCTION(vector_free_struct)(v);
}

void FUNCTION(vector_free_data)(TYPE(Vector) *v) {
	if( v != NULL ) cul_free(v->data);
}

void FUNCTION(vectorview_free)(VIEW(Vector) *vv) {
	FUNCTION(vectorview_free_struct)(vv);
}

void FUNCTION(vector_set_all)(TYPE(Vector) *v, ATOM val) {
	FUNCTION(set_all)(v->data, v->size, val);
}

void FUNCTION(vectorview_set_all)(VIEW(Vector) *vv, ATOM val) {
	if( vv->stride == 1 )
		FUNCTION(set_all)(vv->data, vv->size, val);
	else
		FUNCTION(set_all_stride)(vv->data, vv->size, vv->stride, val);
}

void FUNCTION(vector_set_zero)(TYPE(Vector) *v) {
	FUNCTION(set_all)(v->data, v->size, ZERO);
}

void FUNCTION(vectorview_set_zero)(VIEW(Vector) *vv) {
	if( vv->stride == 1 )
		FUNCTION(set_all)(vv->data, vv->size, ZERO);
	else
		FUNCTION(set_all_stride)(vv->data, vv->size, vv->stride, ZERO);
}

void FUNCTION(vector_set_basis)(TYPE(Vector) *v, size_t i) {
	FUNCTION(set_all)(v->data, v->size, ZERO);
	FUNCTION(vector_set)(v, i, ONE);
}

void FUNCTION(vectorview_set_basis)(VIEW(Vector) *vv, size_t i) {
	if( vv->stride == 1 )
		FUNCTION(set_all)(vv->data, vv->size, ZERO);
	else
		FUNCTION(set_all_stride)(vv->data, vv->size, vv->stride, ZERO);
	FUNCTION(vectorview_set)(vv, i, ONE);
}
