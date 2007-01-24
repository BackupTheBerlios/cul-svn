cul_errno FUNCTION(vector_copy)(TYPE(Vector) *v, const TYPE(Vector) *base_v) {
	if( v->size != base_v->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(v->data, base_v->data, base_v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_offset)(TYPE(Vector) *v, const TYPE(Vector) *base_v, size_t offset) {
	if( v->size - offset < base_v->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	FUNCTION(copy)(v->data + offset, base_v->data, base_v->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_view)(TYPE(Vector) *v, const VIEW(Vector) *base_vv) {
	if( v->size != base_vv->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy)(v->data, base_vv->data, base_vv->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_copy_view_offset)(TYPE(Vector) *v, const VIEW(Vector) *base_vv, size_t offset) {
	if( v->size - offset < base_vv->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADPOS, CUL_EBADPOS);
	if( base_vv->stride == 1 )
		FUNCTION(copy)(v->data + offset, base_vv->data, base_vv->size);
	else
		FUNCTION(copy_stride)(v->data + offset, base_vv->data, base_vv->size, 1, base_vv->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_copy)(VIEW(Vector) *vv, const VIEW(Vector) *base_vv) {
	if( vv->size != base_vv->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(copy_stride)(vv->data, base_vv->data, base_vv->size, vv->stride, base_vv->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_swap)(TYPE(Vector) *a, TYPE(Vector) *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_swap)(VIEW(Vector) *a, VIEW(Vector) *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(swap_stride)(a->data, b->data, a->size, a->stride, b->stride);
	return CUL_SUCCESS;
}

void FUNCTION(vector_reverse)(TYPE(Vector) *a) {
	FUNCTION(reverse)(a->data, a->size);
}

void FUNCTION(vectorview_reverse)(VIEW(Vector) *a) {
	FUNCTION(reverse_stride)(a->data, a->size, a->stride);
}
