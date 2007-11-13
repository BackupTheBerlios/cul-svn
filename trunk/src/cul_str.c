#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/* private functions */
/* used in other cul modules */
size_t _cul_strtrim_right_size(char *str, size_t size);
size_t _cul_strtrim_left_size(char *str, size_t size);

size_t _cul_strtrim_right_size(char *str, size_t size) {
	char *end = str + size - 1;
	for( ; str <= end && cul_isspace(*end); --end );
		*(++end) = '\0';
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

char *cul_str_new(size_t size) {
	char *str;

	if( (str = malloc((size + 1)*sizeof(char))) == NULL )
		return NULL;

	str[0] = '\0';
	return str;
}

void cul_str_free(char *str) {
	free(str);
}

cul_bool cul_str_isspace(const char *str) {
	for( ; *str; ++str) if( !cul_isspace(*str) )
		return CUL_FALSE;
	return CUL_TRUE;
}

char *cul_str_tolower(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_tolower(*str);
	return begin;
}

char *cul_str_toupper(char *str) {
	char *begin = str;
	for( ; *str; ++str)
		*str = cul_toupper(*str);
	return begin;
}

char *cul_str_trim(char *str) {
	const size_t size = _cul_strtrim_right_size(str, strlen(str));
	_cul_strtrim_left_size(str, size);
	return str;
}

char *cul_str_trim_right(char *str) {
	_cul_strtrim_right_size(str, strlen(str));
	return str;
}

char *cul_str_trim_left(char *str) {
	_cul_strtrim_left_size(str, strlen(str));
	return str;
}

char **cul_str_split(const char *s, const char *delimiter) {
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
		strv[i][size] = '\0';

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
	strv[i][size] = '\0';

	return strv;
}

int cul_strcmp(const char *str, const char *other) {
	size_t i = 0;

	for(; str[i] == other[i]; ++i)
		if( str[i] == '\0' )
			return 0;
	return str[i] - other[i];
}

int cul_strcmp_size(const char *str, const char *other, size_t size) {
	size_t i = 0;

	for(; i < size; ++i)
		if( str[i] != other[i] )
			return str[i] - other[i];
	return 0;
}

int cul_strncmp(const char *str, const char *other, size_t size) {
	size_t i = 0;

	for(; i < size; ++i)
		if( str[i] != other[i] )
			return str[i] - other[i];
		else if( str[i] == '\0' )
			return 0;
	return 0;
}

int cul_stricmp(const char *str, const char *other) {
	size_t i = 0;

	for(; cul_tolower(str[i]) == cul_tolower(other[i]); ++i)
		if( str[i] == '\0' )
			return 0;
	return cul_tolower(str[i]) - cul_tolower(other[i]);
}

int cul_stricmp_size(const char *str, const char *other, size_t size) {
	size_t i = 0;

	for(; i < size; ++i)
		if( cul_tolower(str[i]) != cul_tolower(other[i]) )
			return cul_tolower(str[i]) - cul_tolower(other[i]);
	return 0;
}

int cul_strincmp(const char *str, const char *other, size_t size) {
	size_t i = 0;

	for(; i < size; ++i)
		if( cul_tolower(str[i]) != cul_tolower(other[i]) )
			return cul_tolower(str[i]) - cul_tolower(other[i]);
		else if( str[i] == '\0' )
			return 0;
	return 0;
}

char *cul_strdup(const char *str) {
	return cul_strdup_size(str, strlen(str));
}

char *cul_strdup_size(const char *str, size_t size) {
	char *dup;

	if( (dup = malloc((size + 1)*sizeof(char))) == NULL )
		return NULL;

	memcpy(dup, str, size);
	dup[size] = '\0';
	return dup;
}

char *cul_strndup(const char *str, size_t size) {
	const size_t len = strlen(str);
	return cul_strdup_size(str, len > size? size: len);
}

cul_errno cul_strtou(const char *str, size_t base, size_t *value) {
	unsigned long tmp;
	char *end;

	/* init errno */
	int old_errno = errno;
	errno = 0;

	/* convert and check for errors */
	tmp = strtoul(str, &end, base);

	switch( errno ) {
	case EINVAL:
		*value = 0;
		errno = old_errno;
		return CUL_ECONVINVAL;
	case ERANGE:
		*value = SIZE_MAX;
		errno = old_errno;
		return CUL_ECONVRANGE;
	default:
		/* restore old errno */
		errno = old_errno;
	}

	if( !(*end == '\0' ) ) {
		*value = 0;
		return CUL_ECONVINVAL;
	} else if( tmp != (size_t)tmp ) {
		*value = SIZE_MAX;
		return CUL_ECONVRANGE;
	}

	*value = tmp;
	return CUL_SUCCESS;
}

cul_errno cul_strtoi(const char *str, size_t base, int *value) {
	long tmp;
	char *end;

	/* init errno */
	int old_errno = errno;
	errno = 0;

	/* convert and check for errors */
	tmp = strtol(str, &end, base);

	switch( errno ) {
	case EINVAL:
		*value = 0;
		errno = old_errno;
		return CUL_ECONVINVAL;
	case ERANGE:
		if( tmp > 0 ) *value = INT_MAX;
		else          *value = INT_MIN;
		errno = old_errno;
		return CUL_ECONVRANGE;
	default:
		/* restore old errno */
		errno = old_errno;
	}

	if( !(*end == '\0' ) ) {
		*value = 0;
		return CUL_ECONVINVAL;
	} else if( tmp != (int)tmp ) {
		if( tmp > 0 ) *value = INT_MAX;
		else          *value = INT_MIN;
		return CUL_ECONVRANGE;
	}

	*value = tmp;
	return CUL_SUCCESS;
}

cul_errno cul_strtod(const char *str, double *value) {
	double tmp;
	char *end;

	/* init errno */
	int old_errno = errno;
	errno = 0;

	/* convert and check for errors */
	tmp = strtod(str, &end);

	switch( errno ) {
	case EINVAL:
		*value = 0.0;
		errno = old_errno;
		return CUL_ECONVINVAL;
	case ERANGE:
		*value = tmp;
		errno = old_errno;
		return CUL_ECONVRANGE;
	default:
		/* restore old errno */
		errno = old_errno;
	}

	if( !(*end == '\0' ) ) {
		*value = NAN;
		return CUL_ECONVINVAL;
	} else if( tmp != (double)tmp ) {
		*value = NAN;
		return CUL_ECONVRANGE;
	}

	*value = tmp;
	return CUL_SUCCESS;
}

char **cul_strv_new(size_t size) {
	char **strv;

	if( (strv = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	strv[0] = NULL;
	return strv;
}

void cul_strv_free(char **strv) {
	if( strv != NULL ) {
		for(char **itemv = strv; *itemv != NULL; ++itemv)
			free(*itemv);
		free(strv);
	}
}

void cul_strv_free_size(char **strv, size_t size) {
	if( strv != NULL ) {
		for(size_t i = 0; i < size; ++i)
			free(strv[i]);
		free(strv);
	}
}

int cul_strv_cmp(char **strv, char **otherv) {
	int result;

	for(; *strv != NULL; ++strv, ++otherv)
		if( (result = cul_strcmp(*strv, *otherv)) != 0 )
			return result;
	return result;
}

int cul_strv_cmp_size (char **strv, char **otherv, size_t size) {
	int result;

	for(size_t i = 0; i < size; ++i)
		if( (result = cul_strcmp(strv[i], otherv[i])) != 0 )
			return result;
	return result;
}

int cul_strv_icmp(char **strv, char **otherv) {
	int result;

	for(; *strv != NULL; ++strv, ++otherv)
		if( (result = cul_stricmp(*strv, *otherv)) != 0 )
			return result;
	return result;
}

int cul_strv_icmp_size(char **strv, char **otherv, size_t size) {
	int result;

	for(size_t i = 0; i < size; ++i)
		if( (result = cul_stricmp(strv[i], otherv[i])) != 0 )
			return result;
	return result;
}

char **cul_strv_dup(char **strv) {
	return cul_strv_dup_size(strv, cul_strv_size(strv));
}

char **cul_strv_dup_size(char **strv, size_t size) {
	char **dupv;

	if( (dupv = malloc( (size+1)*sizeof(char *) )) == NULL )
	 return NULL;

	/* copy strings */
	for(size_t i = 0; i < size; ++i)
		if( (dupv[i] = cul_strdup(strv[i])) == NULL ) {
			cul_strv_free(dupv);
			return NULL;
		}

	/* set dupv end */
	dupv[size] = NULL;

	return dupv;
}

size_t cul_strv_size(char **strv) {
	size_t size = 0;

	for(; *strv != NULL; ++strv)
		++size;
	return size;
}

void cul_strv_push(char **strv, char *str) {
	const size_t size = cul_strv_size(strv);
	strv[size] = str;
	strv[size + 1] = NULL;
}

void cul_strv_pop(char **strv) {
	const size_t size = cul_strv_size(strv);
	free(strv[size - 1]);
	strv[size - 1] = NULL;
}

char *cul_strv_join(char *separator, char **strv) {
	if( strv[0] == NULL )
		return cul_strdup("");

	if( separator == NULL )
		separator = "";

	size_t i, size = 0;
	size_t separator_size = strlen(separator);

	/* how much space we have to allocate */
	for(i = 0; strv[i] != NULL; ++i)
		size += strlen(strv[i]);
	size += separator_size * (i - 2);

	/* allocate string and provide temporary strings for copying */
	char *string = cul_str_new(size);
	char *str = string, *other;

	/* set size to strv size */
	size = i - 1;

	/* copy items and add separators */
	for(i = 0; i < size; ++i) {
		for(other = strv[i]; *other != '\0'; ++other, ++str) *str = *other;
		for(other = separator; *other != '\0'; ++other, ++str) *str = *other;
	}
	for(other = strv[i]; *other != '\0'; ++other, ++str) *str = *other;

	/* terminate string */
	*str = '\0';

	return string;
}

size_t cul_strv_find(char **strv, const char *key, cul_cmp_f *cmp_f) {
	size_t find = 0;

	for(; *strv != NULL; ++strv){
		if( !cmp_f(*strv, key) ) break;
		++find;
	}
	return find;
}

cul_errno cul_strv_tou(char **strv, size_t base, size_t *value) {
	const size_t size = cul_strv_size(strv);
	for(size_t i = 0; i < size; ++i) if( cul_strtou(strv[i], base, &value[i]) ) {
		while( i < size ) value[i++] = 0;
		return CUL_FAILURE;
	}
	return CUL_SUCCESS;
}

cul_errno cul_strv_toi(char **strv, size_t base, int *value) {
	const size_t size = cul_strv_size(strv);
	for(size_t i = 0; i < size; ++i) if( cul_strtoi(strv[i], base, &value[i]) ) {
		while( i < size ) value[i++] = 0;
		return CUL_FAILURE;
	}
	return CUL_SUCCESS;
}

cul_errno cul_strv_tod(char **strv, double *value) {
	const size_t size = cul_strv_size(strv);
	for(size_t i = 0; i < size; ++i) if( cul_strtod(strv[i], &value[i]) ) {
		while( i < size ) value[i++] = 0.0;
		return CUL_FAILURE;
	}
	return CUL_SUCCESS;
}

