cul_errno FUNCTION(vector_print_stream)(const TYPE(Vector) *v, const char *format, const char *separator) {

	if( !FUNCTION(stream_printf)(format, separator, v->data, v->size) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	if( cul_stream_printf("\n") < 0 )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_fprintf)(FILE *id, const TYPE(Vector) *v, const char *format, const char *separator) {

	if( !FUNCTION(fprintf)(id, format, separator, v->data, v->size) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	if( cul_fprintf(id, "\n") < 0 )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vector_fscanf)(FILE *id, TYPE(Vector) *v, const char *format, const char *separator) {

	if( !FUNCTION(fscanf)(id, format, separator, v->data, v->size) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_ESCANF, CUL_ESCANF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_print_stream)(const VIEW(Vector) *vv, const char *format, const char *separator) {

	if( !FUNCTION(stream_printf_stride)(format, separator, vv->data, vv->size, vv->stride) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	if( cul_stream_printf("\n") < 0 )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_fprintf)(FILE *id, const VIEW(Vector) *vv, const char *format, const char *separator) {

	if( !FUNCTION(fprintf_stride)(id, format, separator, vv->data, vv->size, vv->stride) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	if( cul_fprintf(id, "\n") < 0 )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);

	return CUL_SUCCESS;
}

cul_errno FUNCTION(vectorview_fscanf)(FILE *id, VIEW(Vector) *vv, const char *format, const char *separator) {

	if( !FUNCTION(fscanf_stride)(id, format, separator, vv->data, vv->size, vv->stride) )
		CUL_ERROR_ERRNO_RET_VAL(CUL_ESCANF, CUL_ESCANF);

	return CUL_SUCCESS;
}
