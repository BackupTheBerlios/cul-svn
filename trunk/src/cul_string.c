#define _GNU_SOURCE         /* for asprintf if present */

#include <cul/cul_string.h>
#include <cul/cul_str.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* private functions */
CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg);

/* private raw functions */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);

CulString *cul_string_new(const CulString *string) {
	return cul_string_new_block(string->str, string->size);
}

CulString *cul_string_new_empty() {
	return cul_string_new_block(NULL, 0);
}

CulString *cul_string_new_printf(const char *format, ...) {
	CulString *s;
	va_list arg;

	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	cul_string_init_struct(s, 0, 0, NULL);

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, 0, format, arg) == NULL ) {
		va_end(arg);
		cul_string_free_struct(s);
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_new_str(const char *str) {
	return (str == NULL)? cul_string_new_block(NULL, 0): cul_string_new_block(str, strlen(str));
}

CulString *cul_string_new_block(const char *block, size_t size) {
	CulString *s;
	char *str;

	if( (s = cul_string_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	/* initialize */
	cul_string_init_struct(s, 0, 0, NULL);

	/* copy block */
	if( cul_string_copy_block(s, block, size) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);

	if( size > 0 ) {
		/* allocate string */
		if( (str = malloc((size+1)*sizeof(char))) == NULL ) {
			cul_string_free_struct(s);
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}

		/* copy string */
		memcpy(str, block, size*sizeof(char));
		str[size] = CUL_STR_NULL;
		cul_string_init_struct(s, size, size+1, str);
	}
	else
		cul_string_init_struct(s, 0, 0, NULL);

	return s;
}

void cul_string_free(CulString *s) {
	if( s != NULL ) {
		free(s->str);
		cul_string_free_struct(s);
	}
}

CulString *cul_string_clean(CulString *s) {
	s->size = 0;
	s->str[0] = CUL_STR_NULL;
	return s;
}

CulString *cul_string_clear(CulString *s) {
	free(s->str);
	cul_string_init_struct(s, 0, 0, NULL);
	return s;
}

CulString *cul_string_resize(CulString *s, size_t size) {
	const size_t copy_size = s->size > size? size: s->size;
	char *str;

	if( size > 0 ) {
		if( (str = malloc((size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	}
	else
		return cul_string_clear(s);

	/* copy old string */
	memcpy(str, s->str, copy_size*sizeof(char));
	str[copy_size] = CUL_STR_NULL;
	free(s->str);

	return cul_string_init_struct(s, copy_size, size+1, str);
}

/**
 * Function reserves additional storage space for a string.
 * This function never trims the string content.
 */
CulString *cul_string_reserve(CulString *s, size_t size) {
	char *str;

	/* if size is smaller than current size then shirink maximaly */
	if( size <= s->size )
		size = s->size+1;

	if( (str = malloc((size)*sizeof(char))) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	/* we can safly copy null terminator */
	memcpy(str, s->str, (s->size+1)*sizeof(char));
	free(s->str);

	/* set new string contents */
	s->reserved = size;
	s->str = str;

	return s;
}

CulString *cul_string_shrink(CulString *s) {
	return cul_string_reserve(s, s->size+1);
}

CulString *cul_string_copy(CulString *s, const CulString *copy) {
	return cul_string_copy_block(s, copy->str, copy->size);
}

CulString *cul_string_copy_str(CulString *s, const char *copy) {
	return (copy == NULL)? cul_string_clean(s): cul_string_copy_block(s, copy, strlen(copy));
}

CulString *cul_string_copy_block(CulString *s, const char *copy, size_t size) {
	char *str;

	/* reserve new space if needed */
	if( s->reserved < size + 1 ) {
		if( (str = malloc( (size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		free(s->str);

		/* init string */
		s->reserved = size+1;
		s->str = str;
	}

	/* set new string size */
	s->size = size;

	/* copy block */
	memcpy(s->str, copy, size*sizeof(char));
	s->str[size] = CUL_STR_NULL;

	return s;
}

CulString *cul_string_append(CulString *s, const CulString *append) {
	return cul_string_insert_block(s, s->size, append->str, append->size);
}

CulString *cul_string_append_printf(CulString *s, const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, s->size, format, arg) == NULL ) {
		va_end(arg);
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_append_str(CulString *s, const char *append) {
	return ( append == NULL )? s: cul_string_insert_block(s, s->size, append, strlen(append));
}

CulString *cul_string_prepend(CulString *s, const CulString *prepend) {
	return cul_string_insert_block(s, 0, prepend->str, prepend->size);
}

CulString *cul_string_prepend_printf(CulString *s, const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	if( _cul_string_insert_vprintf(s, 0, format, arg) == NULL ) {
		va_end(arg);
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
	}
	va_end(arg);
	return s;
}

CulString *cul_string_prepend_str(CulString *s, const char *prepend) {
	return ( prepend == NULL )? s: cul_string_insert_block(s, 0, prepend, strlen(prepend));
}

CulString *cul_string_insert(CulString *s, size_t pos, const CulString *insert) {
	return cul_string_insert_block(s, pos, insert->str, insert->size);
}

CulString *_cul_string_insert_vprintf(CulString *s, size_t pos, const char *format, va_list arg) {
	char *str = NULL;
	int strsize;

	/* copy data to buffer */
#ifdef HAVE_ASPRINTF
	if( (strsize = vasprintf(&str, format, arg)) < 0 )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EPRINTF);
#else
	char character;
	if( (strsize = vsnprintf(&character, 1, format, arg)) < 0 )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EPRINTF);
	if( (str = malloc((strsize+1) * sizeof(char))) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	if( vsprintf(str, format, arg) < 0 )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EPRINTF);
#endif

	/* insert buffer to string */
	if( cul_string_isnull(s) )
		/* we don't know exactly size of reserved space, use minial possible value */
		cul_string_init_struct(s, strsize, strsize+1, str);
	else {
		if( cul_string_insert_block(s, pos, str, strsize ) == NULL ) {
			free(str);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}
		free(str);
	}

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

CulString *cul_string_insert_str(CulString *s, size_t pos, const char *insert) {
	return (insert == NULL)? s: cul_string_insert_block(s, pos, insert, strlen(insert));
}

CulString *cul_string_insert_block(CulString *s, size_t pos, const char *insert, size_t size) {
	const size_t s_size = s->size, s_pos = s->size > pos? pos: s->size;
	char *str;

	/* check if append is empty */
	if( size == 0 )
		return s;

	if( s->reserved < s_size + size + 1 ) {
		if( (str = malloc( (s_size+size+1)*sizeof(char))) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);

		if( s->str != NULL ) {
			/* copy previous data, create gap for insert */
			memcpy(str, s->str, s_pos*sizeof(char));
			memcpy(str + s_pos + size, s->str + s_pos, (s_size - s_pos)*sizeof(char));
		}
		free(s->str);

		/* init string */
		s->reserved = s_size+size+1;
		s->str = str;
	}	else {
		/* create gap for insert */
		memmove(s->str + s_pos + size, s->str + s_pos, (s_size - s_pos)*sizeof(char));
	}

	/* update string size */
	s->size += size;

	/* insert string and update length */
	memcpy(s->str + s_pos, insert, size*sizeof(char));
	s->str[s->size] = CUL_STR_NULL;
	return s;
}

CulString *cul_string_cut(CulString *s, size_t pos, size_t size) {
	if( pos > s->size )
		return s;

	const size_t size_cut = s->size < pos+size? s->size-pos: size;

	s->size -= size_cut;
	memmove(s->str + pos, s->str + pos + size, size_cut*sizeof(char));
	return s;
}

CulString *cul_string_cut_begin(CulString *s, size_t size) {
	if( size > s->size )
		return cul_string_clean(s);

	s->size -= size;
	memmove(s->str, s->str + size, s->size*sizeof(char));
	return s;
}

CulString *cul_string_cut_end(CulString *s, size_t size) {
	if( size > s->size )
		return cul_string_clean(s);

	s->size -= size;
	s->str[s->size] = CUL_STR_NULL;
	return s;
}

int cul_string_compare(const CulString *s, const CulString *compare) {
	return memcmp(s->str, compare->str, s->size > compare->size? (compare->size+1)*sizeof(char): (s->size+1)*sizeof(char));
}

int cul_string_compare_str(const CulString *s, const char *compare) {
	if( compare == NULL )
		return 0;

	const size_t size = strlen(compare);
	return memcmp(s->str, compare, s->size > size? (size+1)*sizeof(char): (s->size+1)*sizeof(char));
}

int cul_string_subcompare(const CulString *s, size_t pos, const CulString *compare) {
	return cul_string_subcompare_block(s, pos, compare->str, compare->size);
}

int cul_string_subcompare_str(const CulString *s, size_t pos, const char *compare) {
	return (compare == NULL)? 0: 	cul_string_subcompare_block(s, pos, compare, strlen(compare));
}

int cul_string_subcompare_block(const CulString *s, size_t pos, const char *compare, size_t size) {
	/* we have to include string nul terminator to return correct result
		 possible similarity on all characters, but s is shorter that block */
	pos = pos > s->size? s->size: pos;
	size = s->size - pos > size? size: s->size - pos + 1;
	return memcmp(s->str + pos, compare, size*sizeof(char));
}

cul_bool cul_string_equal(const CulString *s, const CulString *compare) {
	if( cul_string_compare(s, compare) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
}

cul_bool cul_string_equal_str(const CulString *s, const char *compare) {
	if( cul_string_compare_str(s, compare) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
}

cul_bool cul_string_start_with(const CulString *s, const CulString *prefix) {
	if( cul_string_subcompare_block(s, 0, prefix->str, prefix->size) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
}

cul_bool cul_string_start_with_str(const CulString *s, const char *prefix) {
	if( prefix == NULL )
		return CUL_TRUE;
	if( cul_string_subcompare_block(s, 0, prefix, strlen(prefix)) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
}

cul_bool cul_string_end_with(const CulString *s, const CulString *postfix) {
	/* we have to check size -> possible unsigned variables substraction error */
	if( postfix->size > s->size )
		return CUL_FALSE;

	if( cul_string_subcompare_block(s, s->size - postfix->size, postfix->str, postfix->size) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
}

cul_bool cul_string_end_with_str(const CulString *s, const char *postfix) {
	if( postfix == NULL )
		return CUL_TRUE;

	const size_t size = strlen(postfix);
	/* we have to check size -> possible unsigned variables substraction error */
	if( size > s->size )
		return CUL_FALSE;

	if( cul_string_subcompare_block(s, s->size - size, postfix, size) == 0 )
		return CUL_TRUE;
	return CUL_FALSE;
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
	const size_t delimiter_size = strlen(delimiter);
	const char *str = s->str;
	CulList *split = NULL;

	CulString *item;
	for(char *item_str; (item_str = strstr(str, delimiter)) != NULL; split = cul_list_next(split)) {
		/* allocate string and insert to list */
		item = cul_string_new_block(item_str, item_str - str);
		if( cul_list_insert_next(split, item) == NULL || item == NULL) {
			cul_list_free_all(cul_list_first(split), CUL_FREE_F(cul_string_free));
			cul_string_free(item);
			CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
		}

		/* update current position */
		str = item_str + delimiter_size;
	}

	/* add last item */
	item = cul_string_new_str(str);
	if( cul_list_insert_next(split, item) == NULL || item == NULL) {
		cul_list_free_all(cul_list_first(split), CUL_FREE_F(cul_string_free));
		cul_string_free(item);
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
	}

	return cul_list_first(split);
}
