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

	/* allocate and initialize to empty string */
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

char **cul_str_split(const char *str, const char *delimiter) {
	const size_t delimiter_size = strlen(delimiter);
	const char *string = str;
	char **strv;

	size_t size = 1;
	/* compute number of strings */
	for(; (string = strstr(string, delimiter)) != NULL; string += delimiter_size)
		++size;

	if( (strv = malloc((size+1)*sizeof(char **))) == NULL )
		return NULL;

	/* set last position */
	strv[size] = NULL;

	size_t i = 0;
	for(; (string = strstr(str, delimiter)) != NULL; ++i) {
		/* size of item */
		size = string - str;
		
		/* copy string */
		if( (strv[i] = cul_strdup_size(str, size)) == NULL ) {
			cul_strv_free(strv);
			return NULL;
		}

		/* update current position */
		str = string + delimiter_size;
	}

	/* copy last item */
	if( (strv[i] = cul_strdup(str)) == NULL ) {
		cul_strv_free(strv);
		return NULL;
	}

	return strv;
}

char **cul_str_splits(const char *str, const char *delimiters) {
	const char *string = str;
	char **strv;

	size_t size = 1;
	/* compute number of strings */
	for(; (string = strpbrk(string, delimiters)) != NULL; string += 1)
		++size;

	if( (strv = malloc((size+1)*sizeof(char **))) == NULL )
		return NULL;

	/* set last position */
	strv[size] = NULL;

	size_t i = 0;
	for(; (string = strpbrk(str, delimiters)) != NULL; ++i) {
		/* size of item */
		size = string - str;
		
		/* copy string */
		if( (strv[i] = cul_strdup_size(str, size)) == NULL ) {
			cul_strv_free(strv);
			return NULL;
		}

		/* update current position */
		str = string + 1;
	}

	/* copy last item */
	if( (strv[i] = cul_strdup(str)) == NULL ) {
		cul_strv_free(strv);
		return NULL;
	}

	return strv;
}

char *cul_str_join(const char *separator, const char *str, ...) {
	va_list args;
	const size_t separator_size = strlen(separator);
	const char *string;
	size_t size = 0;
	char *join;

	/* check initial conditions */
	if( separator == NULL )
		separator = "";
	if( str == NULL )
		return NULL;

	/* initialize size with first string */
	size = strlen(str);

	/* compute total size of string */
	va_start(args, str);
	while( (string = va_arg(args, const char *)) != NULL )
		size += separator_size + strlen(string);
	/* remove last separator */
	va_end(args);

	/* allocate space */
	if( (join = malloc((size + 1)*sizeof(char))) == NULL )
		return NULL;

	/* initialize join with first string */
	for(string = str; *string != '\0'; ++join, ++string)
		*join = *string;

	/* copy strings and separators */
	va_start(args, str);
	while( (string = va_arg(args, const char *)) != NULL ) {
		for(const char *sep = separator; *sep != '\0'; ++join, ++sep)
			*join = *sep;
		for(; *string != '\0'; ++join, ++string)
			*join = *string;
	}
	va_end(args);

	/* end the string */
	*join = '\0';

	/* return string */
	return join - size;
}

char *cul_str_cat(const char *str, ...) {
	va_list args;
	const char *string;
	size_t size;
	char *cat;

	if( str == NULL )
	 return NULL;

	/* initialize size with first string */
	size = strlen(str);

	/* compute total size of string */
	va_start(args, str);
	while( (string = va_arg(args, const char *)) != NULL )
		size += strlen(string);
	va_end(args);

	/* allocate cat storage */
	if( (cat = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	/* initialize cat with first string */
	for(string = str; *string != '\0'; ++cat, ++string)
		*cat = *string;

	/* copy strings */
	va_start(args, str);
	while( (string = va_arg(args, const char *)) != NULL )
		for(; *string != '\0'; ++cat, ++string)
			*cat = *string;
	va_end(args);

	/* end the string */
	*cat = '\0';

	/* return string */
	return cat - size;
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
		errno = old_errno;
		*value = 0;
		return CUL_ECONVINVAL;
	case ERANGE:
		errno = old_errno;
		*value = SIZE_MAX;
		return CUL_ECONVRANGE;
	default:
		errno = old_errno;
		break;
	}

	if( !(*end == '\0' ) ) {
		*value = tmp;
		return CUL_ECONVPART;
	} else if( tmp != (unsigned long)(size_t)tmp ) {
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
		errno = old_errno;
		*value = 0;
		return CUL_ECONVINVAL;
	case ERANGE: 
		errno = old_errno;
		if( tmp > 0 ) *value = INT_MAX;
		else          *value = INT_MIN;
		return CUL_ECONVRANGE;
	default:
		errno = old_errno;
		break;
	}

	if( !(*end == '\0' ) ) {
		*value = tmp;
		return CUL_ECONVPART;
	} else if( tmp != (long)(int)tmp ) {
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
		errno = old_errno;
		*value = NAN;
		return CUL_ECONVINVAL;
	case ERANGE:
		errno = old_errno;
		*value = tmp;
		return CUL_ECONVRANGE;
	default:
		errno = old_errno;
		break;
	}

	if( !(*end == '\0' ) ) {
		*value = tmp;
		return CUL_ECONVPART;
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

void cul_strv_push_back(char **strv, char *str) {
	const size_t size = cul_strv_size(strv);
	strv[size] = str;
	strv[size + 1] = NULL;
}

void cul_strv_pop_back(char **strv) {
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

	char *string, *str, *other;
	/* allocate string and initialize temporary strings for copying */
	if( (string = malloc((size + 1)*sizeof(char))) == NULL )
		return NULL;
	str = string;

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

size_t cul_strv_find(char **strv, const char *key, cul_eq_f *eq_f) {
	size_t find = 0;

	for(; *strv != NULL; ++strv){
		if( eq_f(*strv, key) ) break;
		++find;
	}
	return find;
}

char **cul_strv_head(char **strv, size_t size) {
	const size_t strv_size = cul_strv_size(strv);
	char **head;

	/* allocate head storage */
	if( (head = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	/* compute size to copy */
	size = size > strv_size? strv_size: size;
	/* shallow copy of strv head */
	for(size_t i = 0; i < size; ++i)
		head[i] = strv[i];
	head[size] = NULL;

	return head;
}

char **cul_strv_tail(char **strv, size_t size) {
	const size_t strv_size = cul_strv_size(strv);
	char **tail;

	/* allocate tail storage */
	if( (tail = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	/* compute size to copy, size if offset */
	size = size > strv_size? 0: strv_size - size;
	/* shallow copy of strv tail */
	for(size_t i = size; i < strv_size; ++i)
		tail[i] = strv[i];
	tail[strv_size] = NULL;

	return tail;
}

char **cul_strv_grep(char **strv, cul_const_ptr data, cul_eq_f *eq_f) {
	const size_t size = cul_strv_size(strv);
	char **grep, **grepv;

	/* allocate grep storage */
	if( (grep = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	/* make shallow grep copy */
	for(grepv = grep; *strv != NULL; ++strv)
		if( eq_f(*strv, data) )
			*(grepv++) = *strv;
	*grepv = NULL;

	return grep;
}

char **cul_strv_cat(char **strv, ...) {
	va_list args;
	char **stringv, **cat;
	size_t size = 0;

	/* compute total size of string */
	va_start(args, strv);
	while( (stringv = va_arg(args, char **)) != NULL )
		size += cul_strv_size(stringv);
	va_end(args);

	/* allocate cat storage */
	if( (cat = malloc((size + 1)*sizeof(char *))) == NULL )
		return NULL;

	/* shallow copy strv vectors */
	va_start(args, strv);
	while( (stringv = va_arg(args, char **)) != NULL )
		for(; *stringv != NULL; ++stringv, ++cat)
			*cat = *stringv;
	*cat = NULL;
	va_end(args);

	return cat - size;
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

