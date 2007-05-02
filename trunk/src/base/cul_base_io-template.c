cul_bool FUNCTION(fprintf)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size) {
	const ATOM *end;

	end = data + size;
	separator = separator ? separator: " ";
	if( fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;

	for( ++data; data < end; ++data)
		if( fprintf(stream, separator) < 0 || fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fprintf_stride)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;

	end = data + size * stride;
	separator = separator ? separator: " ";
	if( fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;

	for( data += stride; data < end; data += stride)
		if( fprintf(stream, separator) < 0 || fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size) {
	const ATOM *end;

	end = data + size;
	separator = separator ? separator: " ";
	if( fscanf(stream, format, data) != 1 )
		return CUL_FALSE;

	for( ++data; data < end; ++data)
		if( fscanf(stream, separator) != 0 || fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf_stride)(FILE *stream, const char *format, const char *separator, const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;

	end = data + size * stride;
	separator = separator ? separator: " ";
	if( fscanf(stream, format, data) != 1 )
		return CUL_FALSE;

	for( data += stride; data < end; data += stride)
		if( fscanf(stream, separator) != 0 || fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	return CUL_TRUE;
}
