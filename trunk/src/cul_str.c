#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

#include <stdlib.h>
#include <string.h>

/* private functions */
/* used in other cul modules */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);

size_t _cul_strtrim_right_size(char *str, size_t size) {
	char *end = str + size - 1;
	for( ; str <= end && cul_isspace(*end); --end );
		*(++end) = CUL_STR_NULL;
	return end - str;
}

size_t _cul_strtrim_left_size(char *str, size_t size) {
	char *end = str + size - 1;
	for( ; str <= end && cul_isspace(*str); ++str );

	const size_t copy_size = end - str + 1;
	if( copy_size != size )
		memmove(str - (size-copy_size) , str, copy_size + 1);

	return copy_size;
}

char *cul_strdup(const char *str) {
	return cul_strdup_size(str, strlen(str));
}

char *cul_strdup_size(const char *str, size_t size) {
	char *dup;

	if( (dup = malloc(size+1 * sizeof(char))) == NULL )
		return NULL;

	memcpy(dup, str, size);
	dup[size] = CUL_STR_NULL;
	return dup;
}

char *cul_strndup(const char *str, size_t size);
char *cul_strndup(const char *str, size_t size) {
	const size_t len = strlen(str);
	return cul_strdup_size(str, len > size? size: len);
}

char *cul_strtrim(char *str) {
	const size_t size = _cul_strtrim_right_size(str, strlen(str));
	_cul_strtrim_left_size(str, size);
	return str;
}

char *cul_strtrim_right(char *str) {
	_cul_strtrim_right_size(str, strlen(str));
	return str;
}

char *cul_strtrim_left(char *str) {
	_cul_strtrim_left_size(str, strlen(str));
	return str;
}

char *cul_strtolower(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_tolower(*str);
	return begin;
}

char *cul_strtoupper(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_toupper(*str);
	return begin;
}

cul_bool cul_strisspace(const char *str) {
	for( ; *str; ++str) if( !cul_isspace(*str) )
		return CUL_FALSE;
	return CUL_TRUE;
}

char **cul_strsplit(const char *s, const char *delimiter) {
	const size_t delimiter_size = strlen(delimiter);
	const char *string = s;

	size_t size = 1;
	while( (string = strstr(string, delimiter)) != NULL ) {
		string += delimiter_size;
		++size;
	}

	char **strv;
	if( (strv = malloc( (size+1)*sizeof(char **) )) == NULL )
		return NULL;

	/* set last position */
	strv[size] = NULL;

	size_t i = 0;
	for(; (string = strstr(s, delimiter)) != NULL; ++i) {
		/* size of item */
		size = string - s;
		if( (strv[i] = malloc( (size+1)*sizeof(char) )) == NULL ) {
			cul_strv_free(strv);
			return NULL;
		}

		/* copy item */
		memcpy(strv[i], s, size);
		strv[i][size] = CUL_STR_NULL;

		/* update current position */
		s = string + delimiter_size;
	}

	/* size of last item */
	size = strlen(s);
	if( (strv[i] = malloc( (size+1)*sizeof(char) )) == NULL ) {
		cul_strv_free(strv);
		return NULL;
	}

	/* copy last item */
	memcpy(strv[i], s, size);
	strv[i][size] = CUL_STR_NULL;

	return strv;
}

size_t cul_strv_size(char **strv) {
	size_t size = 0;

	for(; *strv != NULL; ++strv)
		++size;
	return size;
}

size_t cul_strv_find(char **strv, const char *key, cul_cmp_f *cmp_f) {
	size_t find = 0;

	for(; *strv != NULL; ++strv){
		if( !cmp_f(*strv, key) ) break;
		++find;
	}
	return find;
}

char **cul_strv_dup(char **strv) {
	return cul_strv_dup_size(strv, cul_strv_size(strv));
}


char **cul_strv_dup_size(char **strv, size_t size) {
	char **dupv;

	if( (dupv = malloc( (size+1)*sizeof(char *) )) == NULL )
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
			free(*itemv);
		/* free vector */
		free(strv);
	}
}
