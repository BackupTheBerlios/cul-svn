#include <cul/cul_global.h>
#include <cul/cul_iof.h>
#include <cul/cul_string.h>

/* private functions */
CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg);

/* private raw functions */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);

CulString *cul_string_new(const CulString *string) {
	return cul_string_new_raw_size(string->str, string->size);
}

CulString *cul_string_new_empty() {
	return cul_string_new_raw_size(NULL, 0);
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
	return cul_string_new_raw_size(string, cul_strlen(string));
}

CulString *cul_string_new_raw_size(const char *string, size_t size) {
	CulString *s;
	char *str;

	if( (s = cul_string_new_size(size)) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( size > 0 ) {
		/* allocate string */
		if( (str = (char *)cul_malloc((size+1)*sizeof(char))) == NULL ) {
			cul_string_free_struct(s);
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		}

		/* copy string if needed */
		if( string == NULL ) {
			cul_strnull(str);
			cul_string_init_all(s, 0, size+1, str);
		} else {
			cul_memcpy(str, string, size*sizeof(char));
			cul_strnull(str+size);
			cul_string_init_all(s, size, size+1, str);
		}
	}
	else
		cul_string_init_all(s, 0, 0, NULL);

	return s;
}

CulString *cul_string_new_size(size_t size) {
	return cul_string_new_raw_size(NULL, size);
}

void cul_string_free(CulString *s) {
	if( s != NULL ) {
		cul_free(s->str);
		cul_string_free_struct(s);
	}
}

CulString *cul_string_clean(CulString *s) {
	s->size = 0;
	cul_strnull(s->str);
	return s;
}

CulString *cul_string_clear(CulString *s) {
	cul_free(s->str);
	cul_string_init_all(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_resize(CulString *s, size_t size) {
	const size_t copy_size = s->size > size? size: s->size;
	char *str;

	if( size > 0 ) {
		if( (str = (char *)cul_malloc((size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	}
	else
		return cul_string_clear(s);

	/* copy old string */
	cul_memcpy(str, s->str, copy_size*sizeof(char));
	cul_strnull(str + copy_size);
	cul_free(s->str);

	return cul_string_init_all(s, copy_size, size+1, str);
}

/**
 * Function reserves ir shrink additional storage space for a string.
 * This function never trims the string content.
 */
CulString *cul_string_reserve(CulString *s, size_t size) {
	char *str;

	/* if size is smaller than current size then shirink maximaly */
	if( size <= s->size )
		size = s->size+1;

	if( (str = (char *)cul_malloc((size)*sizeof(char))) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	/* we can safly copy null terminator */
	cul_memcpy(str, s->str, (s->size+1)*sizeof(char));
	cul_free(s->str);

	/* set new string contents */
	s->reserved = size;
	s->str = str;

	return s;
}

CulString *cul_string_shrink(CulString *s) {
	return cul_string_reserve(s, s->size+1);
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
	char *str;

	if( copy == NULL )
		return cul_string_clean(s);

	/* reserve new space if needed */
	if( s->reserved < size + 1 ) {
		if( (str = (char *)cul_malloc( (size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
		cul_free(s->str);

		/* init string */
		s->reserved = size+1;
		s->str = str;
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
	return cul_string_insert_raw_size(s, s->size > pos? pos: s->size, insert->str, insert->size);
}

CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg) {
	char *str = NULL;
	int strsize;

	/* copy data to buffer */
	if( (strsize = cul_vasprintf(&str, format, arg)) < 0 )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ESPRINTF);

	/* insert buffer to string */
	if( cul_string_insert_raw_size(s, s->size > pos? pos: s->size, str, strsize ) == NULL ) {
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
	const size_t s_size = s->size, s_pos = s->size > pos? pos: s->size;
	char *str;

	/* check if append is empty */
	if( !insert )
		return s;

	if( s->reserved < s_size + size + 1 ) {
		if( (str = (char *)cul_malloc( (s_size+size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);

		if( s->str != NULL ) {
			/* copy previous data, create gap for insert */
			cul_memcpy(str, s->str, s_pos*sizeof(char));
			cul_memcpy(str + s_pos + size, s->str + s_pos, (s_size - s_pos)*sizeof(char));
		}
		cul_free(s->str);

		/* init string */
		s->reserved = s_size+size+1;
		s->str = str;
	}	else {
		/* create gap for insert */
		cul_memmove(s->str + s_pos + size, s->str + s_pos, (s_size - s_pos)*sizeof(char));
	}

	/* update string size */
	s->size += size;

	/* insert string and update length */
	cul_memcpy(s->str + s_pos, insert, size*sizeof(char));
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

CulList *cul_string_split(const CulString *s, const char *delimiter) {
	const size_t delimiter_size = cul_strlen(delimiter);
	const char *str = cul_string_const_c_str(s);
	CulList *split = NULL;

	CulString *item;
	for(char *item_str; (item_str = cul_strstr(str, delimiter)) != NULL; split = cul_list_next(split)) {
		/* allocate string and insert to list */
		item = cul_string_new_raw_size(item_str, item_str - str);
		if( cul_list_insert_next(split, item) == NULL || item == NULL) {
			cul_list_free_all(cul_list_first(split), CUL_FREE_F(cul_string_free));
			cul_string_free(item);
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
		}

		/* update current position */
		str = item_str + delimiter_size;
	}

	/* add last item */
	item = cul_string_new_raw(str);
	if( cul_list_insert_next(split, item) == NULL || item == NULL) {
		cul_list_free_all(cul_list_first(split), CUL_FREE_F(cul_string_free));
		cul_string_free(item);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EFAILED);
	}

	return cul_list_first(split);
}
