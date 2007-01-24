cul_errno FUNCTION(matrix_print_stream)(const TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i< m->size_y; ++i) {
		if( FUNCTION(stream_printf)(format, separator, FUNCTION(matrix_const_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
		if( cul_stream_printf("\n") < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fprintf)(FILE *id, const TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i<m->size_y; ++i) {
		if( FUNCTION(fprintf)(id, format, separator, FUNCTION(matrix_const_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
		if( cul_fprintf(id, "\n") < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_EPRINTF, CUL_EPRINTF);
	}
	return CUL_SUCCESS;
}

cul_errno FUNCTION(matrix_fscanf)(FILE *id, TYPE(Matrix) *m, const char *format, const char *separator) {
	size_t i;

	for( i=0; i<m->size_y; ++i)
		if( FUNCTION(fscanf)(id, format, separator, FUNCTION(matrix_ptr)(m, 0, i), m->size_x) < 0 )
			CUL_ERROR_ERRNO_RET_VAL(CUL_ESCANF, CUL_ESCANF);
	return CUL_SUCCESS;
}
