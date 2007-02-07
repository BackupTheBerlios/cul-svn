cul_bool FUNCTION(printf_stream)(const char *format, const char *separator, const ATOM *data, size_t size) {
	const ATOM *end;

	end = data + size;
	separator = separator ? separator: " ";
	if( cul_printf_stream(format, *data) < 0 )
		return CUL_FALSE;

	for( ++data; data < end; ++data)
		if( cul_printf_stream(separator) < 0 || cul_printf_stream(format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(printf_stream_stride)(const char *format, const char *separator, const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;

	end = data + size * stride;
	separator = separator ? separator: " ";
	if( cul_printf_stream(format, *data) < 0 )
		return CUL_FALSE;

	for( data += stride; data < end; data += stride)
		if( cul_printf_stream(separator) < 0 || cul_printf_stream(format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fprintf)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size) {
	const ATOM *end;

	end = data + size;
	separator = separator ? separator: " ";
	if( cul_fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;

	for( ++data; data < end; ++data)
		if( cul_fprintf(stream, separator) < 0 || cul_fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fprintf_stride)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;

	end = data + size * stride;
	separator = separator ? separator: " ";
	if( cul_fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;

	for( data += stride; data < end; data += stride)
		if( cul_fprintf(stream, separator) < 0 || cul_fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size) {
	const ATOM *end;

	end = data + size;
	separator = separator ? separator: " ";
	if( cul_fscanf(stream, format, data) != 1 )
		return CUL_FALSE;

	for( ++data; data < end; ++data)
		if( cul_fscanf(stream, separator) != 0 || cul_fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf_stride)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;

	end = data + size * stride;
	separator = separator ? separator: " ";
	if( cul_fscanf(stream, format, data) != 1 )
		return CUL_FALSE;

	for( data += stride; data < end; data += stride)
		if( cul_fscanf(stream, separator) != 0 || cul_fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	return CUL_TRUE;
}
