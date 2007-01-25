#include <cul/cul_string_raw.h>
#include <cul/cul_string_type.h>

/* private functions */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);
size_t _cul_strtrim_compress_size(char *str, size_t size);

size_t _cul_strtrim_right_size(char *str, size_t size) {
	char *end = str + size - 1;
	for( ; str <= end && cul_isspace_ascii(*end); --end );
	*(++end) = CUL_STR_NULL;
	return end - str;
}

size_t _cul_strtrim_left_size(char *str, size_t size) {
	char *end = str + size - 1;
	for( ; str <= end && cul_isspace_ascii(*str); ++str );

	const size_t copy_size = end - str + 1;
	if( copy_size != size )
		cul_memmove(str - (size-copy_size) , str, copy_size + 1);

	return copy_size;
}

size_t _cul_strtrim_compress_size(char *str, size_t size) {
	char *cur = str, *end = str + size - 1;

	/* omit start whitespaces */
	for( ; str <= end && cul_isspace_ascii(*str); ++str);
	/* omit end whitespaces */
	for( ; str <= end && cul_isspace_ascii(*end); --end);
	*(end+1) = CUL_STR_NULL;

	/* remember string beginning */
	const char *begin = str;

	/* copy internal parts */
	for( ; str <= end; ++str, ++cur) {
		/* check if character is space */
		if( cul_isspace_ascii(*str) ) {
			*cur = CUL_STR_SPACE;

			/* omit next spaces if present */
			/* NOTICE: we know that at the end of string is NON space character */
			for( ++str; str <= end && cul_isspace_ascii(*str); ++str );
			/* go back to non space character */
			--str;
		}
		else {
			/* copy character */
			*cur = *str;
		}
	}
	return end - begin;
}

char *cul_strdup(char *str) {
	const size_t size = cul_strlen(str) + 1;
	char *dup;

	if( (dup = cul_malloc(size * sizeof(char))) == NULL )
		return NULL;

	cul_memcpy(dup, str, size);
	return dup;
}

char *cul_strndup(char *str, size_t size) {
	const size_t len = cul_strlen(str);
	char *dup;

	if( (dup = cul_malloc((size+1) * sizeof(char))) == NULL )
		return NULL;

	if( len > size ) {
		/* input string is longer that desired dublicate */
		cul_memcpy(dup, str, size);
		cul_strnull(dup+size);
	}
	else
		/* whole input string would fit */
		cul_memcpy(dup, str, len);

	return dup;
}

char *cul_strtrim(char *str) {
	const size_t size = _cul_strtrim_right_size(str, cul_strlen(str));
	_cul_strtrim_left_size(str, size);
	return str;
}

char *cul_strtrim_right(char *str) {
	_cul_strtrim_right_size(str, cul_strlen(str));
	return str;
}

char *cul_strtrim_left(char *str) {
	_cul_strtrim_left_size(str, cul_strlen(str));
	return str;
}

char *cul_strtrim_compress(char *str) {
	_cul_strtrim_compress_size(str, cul_strlen(str));
	return str;
}

char *cul_strtolower(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_tolower_ascii(*str);
	return begin;
}

char *cul_strtoupper(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_toupper_ascii(*str);
	return begin;
}

char **cul_strsplit_delimiter(const char *s, const char *delimiter) {
	const size_t delimiter_size = cul_strlen(delimiter);
	const char *string = s;

	size_t size = 1;
	while( (string = cul_strstr(string, delimiter)) != NULL ) {
		string += delimiter_size;
		++size;
	}

	char **strv;
	if( (strv = cul_malloc( (size+1)*sizeof(char **) )) == NULL )
		return NULL;

	/* set last position */
	strv[size] = NULL;

	size_t i = 0;
	for(; (string = cul_strstr(s, delimiter)) != NULL; ++i) {
		/* size of item */
		size = string - s;
		if( (strv[i] = cul_malloc( (size+1)*sizeof(char) )) == NULL ) {
			cul_strv_free(strv);
			return NULL;
		}

		/* copy item */
		cul_memcpy(strv[i], s, size);
		cul_strnull(strv[i]+size);

		/* update current position */
		s = string + delimiter_size;
	}

	/* size of last item */
	size = cul_strlen(s);
	if( (strv[i] = cul_malloc( (size+1)*sizeof(char) )) == NULL ) {
		cul_strv_free(strv);
		return NULL;
	}

	/* copy last item */
	cul_memcpy(strv[i], s, size);
	cul_strnull(strv[i]+size);

	return strv;
}

size_t cul_strv_size(const char **strv) {
	size_t size = 0;
	for(; *strv != NULL; ++strv)
		++size;
	return size;
}

void cul_strv_free(char **strv) {
	if( strv != NULL ) {
		/* free items */
		for( char **itemv = strv; *itemv != NULL; ++itemv)
			cul_free(*itemv);
		/* free vector */
		cul_free(strv);
	}
}
