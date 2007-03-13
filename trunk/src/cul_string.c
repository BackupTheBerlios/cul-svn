#include <cul/cul_global.h>
#include <cul/cul_iof.h>
#include <cul/cul_string.h>
#include <cul/cul_base_size.h>

/* private functions */
CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg);

/* privete raw functions */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);
size_t _cul_strtrim_compress_size(char *strm, size_t size);

CulString *cul_string_new(const CulString *string) {
	CulString *s;
	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( cul_string_init(s, string) == NULL ) {
		cul_string_free_struct(s);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return s;
}

CulString *cul_string_new_printf(const char *format, ...) {
	CulString *s;
	va_list arg;

	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	cul_string_init_all(s, 0, 0, NULL);

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, 0, format, arg) == NULL ) {
		cul_string_free_struct(s);
		va_end(arg);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_new_raw(const char *string) {
	CulString *s;
	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( cul_string_init_raw(s, string) == NULL ) {
		cul_string_free_struct(s);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return s;
}

CulString *cul_string_new_size(size_t size) {
	CulString *s;
	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( cul_string_init_size(s, size) == NULL ) {
		cul_string_free_struct(s);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return s;
}

CulString *cul_string_init(CulString *s, const CulString *string) {
	if( string != NULL && string->str != NULL ) {
		if( cul_string_init_size(s, string->size) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
		/* copy string with terminator */
		cul_memcpy(s->str, string->str, string->size + 1);
		s->size = string->size;
	}
	else
		cul_string_init_all(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_init_raw(CulString *s, const char *string) {
	if( string != NULL ) {
		const size_t size = cul_strlen(string);
		if( cul_string_init_size(s, size) == NULL)
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
		/* copy string with terminator */
		cul_memcpy(s->str, string, size + 1);
		s->size = size;
	}
	else
		cul_string_init_all(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_init_size(CulString *s, size_t size) {
	char *d;

	if( size > 0 ) {
		if( (d = (char *)cul_malloc((size + 1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		cul_strnull(d);
		cul_string_init_all(s, 0, size + 1, d);
	}
	else
		cul_string_init_all(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_init_attach_raw(CulString *s, char *string, size_t reserved) {
	if( string != NULL ) {
		size_t size = cul_strlen(string);

		/* check reserved */
		if( reserved == 0 )
			reserved = size + 1;
		else if( size >= reserved )
			return NULL;

		cul_string_init_all(s, size, reserved, string);
	}
 else
		cul_string_init_all(s, 0, 0, NULL);
	return s;
}

void cul_string_free(CulString *s) {
	cul_string_free_data(s);
	cul_string_free_struct(s);
}

void cul_string_free_data(CulString *s) {
	if( s != NULL )
		cul_free(s->str);
}

CulString *cul_string_clean(CulString *s) {
	s->size = 0;
	cul_strnull(s->str);
	return s;
}

CulString *cul_string_clear(CulString *s) {
	cul_string_free_data(s);
	cul_string_init_all(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_resize(CulString *s, size_t size) {
	const size_t size_min = cul_umin_pair(s->size, size);
	char *d = s->str;

	if( size > 0 ) {
		if( (d = (char *)cul_malloc((size + 1) * sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	}
	else
		return cul_string_clear(s);

	/* check if we should copy something (non-empty old string) */
	if( size_min > 0 )
		cul_memcpy(d, s->str, size_min*sizeof(char));
	/* set tertmination character at size position */
	cul_strnull(d + size);

	/* free old string */
	cul_string_free_data(s);

	/* set all structure variables */
	cul_string_init_all(s, size, size + 1, d);
	return s;
}

CulString *cul_string_resize_char(CulString *s, size_t size, char character) {
	const size_t size_string = s->size;

	if( cul_string_resize(s, size) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);

	/* set memory if needed */
	if( size > size_string )
		cul_memset(s->str + size_string, character, (size - size_string)*sizeof(char));

	return s;
}

CulString *cul_string_reserve(CulString *s, size_t size) {
	const size_t size_min = cul_umin_pair(s->size, size);
	char *d = s->str;

	if( size > 0 ) {
		if( (d = (char *)cul_malloc((size + 1) * sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	}
	else
		return cul_string_clear(s);

	/* check if we should copy something (non-empty old string) */
	if( size_min > 0 )
		cul_memcpy(d, s->str, size_min*sizeof(char));

	/* set tertmination character at size_min position */
	cul_strnull(d + size_min);

	/* free old string */
	cul_string_free_data(s);

	/* set all structure variables */
	cul_string_init_all(s, size_min, size + 1, d);
	return s;
}

CulString *cul_string_shrink(CulString *s) {
	/* check if we need to shrink */
	if( s->reserved > s->size + 1 && cul_string_resize(s, s->size) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	return s;
}

CulString *cul_string_copy(CulString *s, const CulString *copy) {
	return cul_string_copy_raw_size(s, copy->str, copy->size);
}

CulString *cul_string_copy_raw(CulString *s, const char *copy) {
	if( copy == NULL )
		return cul_string_clean(s);
	return cul_string_copy_raw_size(s, copy, cul_strlen(copy));
}

CulString *cul_string_copy_raw_size(CulString *s, const char *copy, size_t size) {
	char *const d = s->str;

	if( copy == NULL )
		return cul_string_clean(s);

	/* reserve new space if needed */
	if( s->reserved < size + 1 ) {
		if( cul_string_init_size(s, size) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);

		/* free old string if necesery */
		if( d != NULL )
			free(d);
	}

	/* change string size */
	s->size = size;

	/* copy string */
	cul_memcpy(s->str, copy, size*sizeof(char));
	cul_strnull(s->str + size);
	return s;
}

CulString *cul_string_append(CulString *s, const CulString *append) {
	return cul_string_insert_raw_size(s, s->size, append->str, append->size);
}

CulString *cul_string_append_printf(CulString *s, const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, s->size, format, arg) == NULL ) {
		va_end(arg);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_append_raw(CulString *s, const char *append) {
	if( append == NULL )
		return s;
	return cul_string_insert_raw_size(s, s->size, append, cul_strlen(append));
}

CulString *cul_string_prepend(CulString *s, const CulString *prepend) {
	return cul_string_insert_raw_size(s, 0, prepend->str, prepend->size);
}

CulString *cul_string_prepend_printf(CulString *s, const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, 0, format, arg) == NULL ) {
		va_end(arg);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_prepend_raw(CulString *s, const char *prepend) {
	if( prepend == NULL )
		return s;
	return cul_string_insert_raw_size(s, 0, prepend, cul_strlen(prepend));
}

CulString *cul_string_insert(CulString *s, size_t pos, const CulString *insert) {
	return cul_string_insert_raw_size(s, cul_umin_pair(s->size, pos), insert->str, insert->size);
}

CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg) {
	char *str = NULL;
	int strsize;

	/* copy data to buffer */
	if( (strsize = cul_vasprintf(&str, format, arg)) < 0 )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ESPRINTF);

	/* insert buffer to string */
	if( cul_string_insert_raw_size(s, cul_umin_pair(s->size, pos), str, strsize ) == NULL ) {
		cul_free(str);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}

	cul_free(str);
	return s;
}

CulString *cul_string_insert_printf(CulString *s, size_t pos, const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, pos, format, arg) == NULL ) {
		va_end(arg);
		return NULL;
	}
	va_end(arg);
	return s;
}

CulString *cul_string_insert_raw(CulString *s, size_t pos, const char *insert) {
	if( insert == NULL )
		return s;
	return cul_string_insert_raw_size(s, pos, insert, cul_strlen(insert));
}

CulString *cul_string_insert_raw_size(CulString *s, size_t pos, const char *insert, size_t size) {
	const size_t size_d = s->size, pos_s = cul_umin_pair(s->size, pos);
	char *d = s->str;

	/* check if append is empty */
	if( !insert )
		return s;

	if( s->reserved < size_d + size + 1 ) {
		if( cul_string_init_size(s, size_d + size) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
		/* ensure we don't have nul base string */
		if( d != NULL ) {
			/* set original size */
			s->size = size_d;

			/* copy previous data, create gap for insert */
			cul_memcpy(s->str, d, pos_s*sizeof(char));
			cul_memcpy(s->str + pos_s + size, d + pos_s, (size_d - pos_s)*sizeof(char));

			/* free previous string */
			free(d);
		}
	}
	else
		/* create gap for insert */
		cul_memmove(s->str + pos_s + size, d + pos_s, (size_d - pos_s)*sizeof(char));

	/* update string size */
	s->size += size;

	/* insert string and update length */
	cul_memcpy(s->str + pos_s, insert, size*sizeof(char));
	cul_strnull(s->str + s->size);
	return s;
}

CulString *cul_string_cut(CulString *s, size_t x, size_t size) {
	if( x > s->size )
		return s;

	const size_t size_cut = s->size < x+size? s->size-x: size;

	s->size -= size_cut;
	cul_memmove(s->str + x, s->str + x + size, size_cut*sizeof(char));
	return s;
}

CulString *cul_string_cut_begin(CulString *s, size_t size) {
	if( size > s->size )
		return cul_string_clean(s);

	s->size -= size;
	cul_memmove(s->str, s->str + size, s->size*sizeof(char));
	return s;
}

CulString *cul_string_cut_end(CulString *s, size_t size) {
	if( size > s->size )
		return cul_string_clean(s);

	s->size -= size;
	cul_strnull(s->str + s->size);
	return s;
}

cul_bool cul_string_start_with(const CulString *s, const CulString *prefix) {
	if( s->size >= prefix->size ) {
		if( cul_string_isempty(prefix) )
			return CUL_TRUE;

		const char *str = s->str;
		const char *str_prefix = prefix->str;
		const size_t size_prefix = prefix->size;
		for( size_t i=0; i<size_prefix; ++i, ++str_prefix, ++str)
			if( *str_prefix != *str )
				return CUL_FALSE;
		return CUL_TRUE;
	}
	return CUL_FALSE;
}

cul_bool cul_string_start_with_raw(const CulString *s, const char *prefix) {
	if( prefix == NULL )
		return CUL_TRUE;

	if( cul_string_isempty(s) && !(*prefix) )
		return CUL_FALSE;

	const char *str = s->str;
	while( *prefix )
		if( *prefix++ != *str++)
			return CUL_FALSE;
	return CUL_TRUE;
}

cul_bool cul_string_end_with(const CulString *s, const CulString *postfix) {
	if( s->size >= postfix->size ) {
		if( cul_string_isempty(postfix) )
			return CUL_TRUE;

		const char *str = s->str + s->size - 1;
		const char *str_postfix = postfix->str + postfix->size - 1;
		const size_t size_postfix = postfix->size;
		for( size_t i=0; i<size_postfix; ++i, --str_postfix, --str)
			if( *str_postfix != *str )
				return CUL_FALSE;
		return CUL_TRUE;

	}
	return CUL_FALSE;
}

cul_bool cul_string_end_with_raw(const CulString *s, const char *postfix) {
	if( postfix == NULL )
		return CUL_TRUE;

	if( cul_string_isempty(s) && !(*postfix) )
		return CUL_FALSE;

	/* go to the end of string */
	size_t size_postfix;
	for( size_postfix=0; *postfix; ++postfix)
		++size_postfix;
	--postfix;

	const char *str = s->str + s->size - 1;
	for( size_t i=0; i<size_postfix; ++i, --postfix, --str)
		if( *postfix != *str )
			return CUL_FALSE;
	return CUL_TRUE;
}

cul_bool cul_string_equal(const CulString *s, const CulString *compare) {
	if( s->size == compare->size ) {

		const char *str = s->str;
		const char *str_compare = compare->str;
		const size_t size_compare = compare->size;
		for( size_t i=0; i<size_compare; ++i, ++str_compare, ++str)
			if( *str_compare != *str )
				return CUL_FALSE;
		return CUL_TRUE;
	}
	return CUL_FALSE;
}

cul_bool cul_string_equal_raw(const CulString *s, const char *compare) {
	if( compare == NULL )
		return cul_string_isnull(s)? CUL_TRUE: CUL_FALSE;
	return (cul_strcmp(s->str, compare) == 0);
}

CulString *cul_string_trim(CulString *s) {
	if( cul_string_isnull(s) )
		return s;

	s->size = _cul_strtrim_left_size(s->str, s->size);
	s->size = _cul_strtrim_right_size(s->str, s->size);
	return s;
}

CulString *cul_string_trim_left(CulString *s) {
	if( cul_string_isnull(s) )
		return s;

	s->size = _cul_strtrim_left_size(s->str, s->size);
	return s;
}

CulString *cul_string_trim_right(CulString *s) {
	if( cul_string_isnull(s) )
		return s;

	s->size = _cul_strtrim_right_size(s->str, s->size);
	return s;
}

CulString *cul_string_trim_compress(CulString *s) {
	if( cul_string_isnull(s) )
		return s;

	s->size = _cul_strtrim_compress_size(s->str, s->size);
	return s;
}
