#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

/* private functions */
/* used in other cul modules */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);

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

char *cul_strdup(const char *str) {
	return cul_strdup_size(str, cul_strlen(str));
}

char *cul_strdup_size(const char *str, size_t size) {
	char *dup;

	if( (dup = cul_malloc(size+1 * sizeof(char))) == NULL )
		return NULL;

	cul_memcpy(dup, str, size);
	cul_strnull(dup + size);
	return dup;
}

char *cul_strndup(const char *str, size_t size) {
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
		cul_memcpy(dup, str, len+1);

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

char *cul_strchr_space(const char *str) {
	for( ; *str && !cul_isspace_ascii(*str); ++str) ;
	return (char *)str;
}

char *cul_strchr_nonspace(const char *str) {
	for( ; *str && cul_isspace_ascii(*str); ++str) ;
	return (char *)str;
}

char **cul_strsplit(const char *s, const char *delimiter) {
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

size_t cul_strv_size(char **strv) {
	size_t size = 0;
	for(; *strv != NULL; ++strv)
		++size;
	return size;
}

char **cul_strv_dup(char **strv) {
	return cul_strv_dup_size(strv, cul_strv_size(strv));
}


char **cul_strv_dup_size(char **strv, size_t size) {
	char **dupv;

	if( (dupv = cul_malloc( (size+1)*sizeof(char *) )) == NULL )
	 return NULL;

	/* copy strings */
	for( size_t i=0; i<size; ++i)
		if( (dupv[i] = cul_strdup(strv[i])) == NULL ) {
			cul_strv_free(dupv);
			return NULL;
		}

	/* set dupv end */
	dupv[size] = NULL;

	return dupv;
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
