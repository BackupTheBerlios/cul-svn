cul_bool FUNCTION(fprintf)(FILE *stream, const ATOM *data, size_t size, const char *format, const char *separator, const char *begin, const char *end) {
	const ATOM *last = data + size;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;

	/* print begin */
	if( begin != NULL && fprintf(stream, "%s", begin) < 0 )
		return CUL_FALSE;

	/* print data and separators */
	if( fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;
	for(++data; data < last; ++data)
		if( fprintf(stream, separator) < 0 || fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	/* print end */
	if( end != NULL && fprintf(stream, "%s", end) < 0 )
		return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fprintf_stride)(FILE *stream, const ATOM *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end) {
	const ATOM *last = data + size * stride;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;

	/* print begin */
	if( begin != NULL && fprintf(stream, "%s", begin) < 0 )
		return CUL_FALSE;

	/* print data and separators */
	if( fprintf(stream, format, *data) < 0 )
		return CUL_FALSE;
	for(data += stride; data < last; data += stride)
		if( fprintf(stream, separator) < 0 || fprintf(stream, format, *data) < 0 )
			return CUL_FALSE;

	/* print end */
	if( end != NULL && fprintf(stream, "%s", end) < 0 )
		return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf)(FILE *stream, const ATOM *data, size_t size, const char *format, const char *separator, const char *begin, const char *end) {
	const ATOM *last = data + size;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;

	/* read begin */
	if( begin != NULL && fscanf(stream, begin) != 0 )
		return CUL_FALSE;

	/* read data and separators */
	if( fscanf(stream, format, data) != 1 )
		return CUL_FALSE;
	for(++data; data < last; ++data)
		if( fscanf(stream, separator) != 0 || fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	/* read end */
	if( end != NULL && fscanf(stream, end) != 0 )
		return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool FUNCTION(fscanf_stride)(FILE *stream, const ATOM *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end) {
	const ATOM *last = data + size * stride;

	/* prepare formatting */
	separator = separator == NULL? " ": separator;

	/* read begin */
	if( begin != NULL && fscanf(stream, begin) != 0 )
		return CUL_FALSE;

	/* read data and separators */
	if( fscanf(stream, format, data) != 1 )
		return CUL_FALSE;
	for(data += stride; data < last; data += stride)
		if( fscanf(stream, separator) != 0 || fscanf(stream, format, data) != 1 )
			return CUL_FALSE;

	/* read end */
	if( end != NULL && fscanf(stream, end) != 0 )
		return CUL_FALSE;

	return CUL_TRUE;
}
