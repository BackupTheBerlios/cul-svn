void FUNCTION(vector_add_scalar)(TYPE(Vector)  *v, ATOM val) {
	FUNCTION(add_scalar)(v->data, v->size, val);
}

void FUNCTION(vector_mul_scalar)(TYPE(Vector)  *v, ATOM val) {
	FUNCTION(mul_scalar)(v->data, v->size, val);
}

cul_errno FUNCTION(vector_add)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(add)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_sub)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(sub)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_mul)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(mul)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_div)(TYPE(Vector)  *a, const TYPE(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(div)(a->data, b->data, a->size);
	return CUL_SUCCESS;
}

void FUNCTION(vectorview_add_scalar)(VIEW(Vector)  *vv, ATOM val) {
	FUNCTION(add_scalar_stride)(vv->data, vv->size, vv->stride, val);
}

void FUNCTION(vectorview_mul_scalar)(VIEW(Vector)  *vv, ATOM val) {
	FUNCTION(mul_scalar_stride)(vv->data, vv->size, vv->stride, val);
}

cul_errno FUNCTION(vectorview_add)(VIEW(Vector)  *a, const VIEW(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(add_stride)(a->data, b->data, a->size, a->stride, b->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_sub)(VIEW(Vector)  *a, const VIEW(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(sub_stride)(a->data, b->data, a->size, a->stride, b->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_mul)(VIEW(Vector)  *a, const VIEW(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(mul_stride)(a->data, b->data, a->size, a->stride, b->stride);
	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_div)(VIEW(Vector)  *a, const VIEW(Vector)  *b) {
	if( a->size != b->size )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EBADLEN, CUL_EBADLEN);
	FUNCTION(div_stride)(a->data, b->data, a->size, a->stride, b->stride);
	return CUL_SUCCESS;
}
