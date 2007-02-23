#if !defined(CUL_STR_H)
#define CUL_STR_H

#include <cul/cul_global.h>
#include <stdlib.h>
#include <string.h>

/* some basic characters */

#define CUL_STR_NULL    '\0'
#define CUL_STR_SPACE   ' '
#define CUL_STR_TAB     '\t'
#define CUL_STR_NEWLINE '\n'

/* simple functions */

static inline void cul_strnull(char *str);
static inline cul_bool cul_strisnull(const char *str);

/* base wrappers */

static inline char *cul_strcat(char *dest, const char *src);
static inline char *cul_strncat(char *dest, const char *src, size_t size);

static inline char *cul_strcpy(char *dest, const char *src);
static inline char *cul_strncpy(char *dest, const char *src, size_t size);

static inline int cul_strcmp(const char *str, const char *cmp);
static inline int cul_strncmp(const char *str, const char *cmp, size_t size);

static inline size_t cul_strlen(const char *str);

static inline long int cul_strtol(const char *str, char **end, int base);
static inline double cul_strtod(const char *str, char **end);

static inline char *cul_strchr(const char *str, int find);
static inline char *cul_strrchr(const char *str, int find);
static inline char *cul_strstr(const char *str, const char *find);

/* printf string writing */

int cul_sprintf(char *str, const char *format, ...);
int cul_sprintf(char *str, const char *format, ...);
int cul_snprintf(char *str, size_t size, const char *format, ...);
int cul_asprintf(char **str, const char *format, ...);

/* additional functions */

char *cul_strdup(const char *str);
char *cul_strdup_size(const char *str, size_t size);
char *cul_strndup(const char *str, size_t size);

char *cul_strtrim(char *str);
char *cul_strtrim_right(char *str);
char *cul_strtrim_left(char *str);
char *cul_strtrim_compress(char *str);

char *cul_strtolower(char *str);
char *cul_strtoupper(char *str);

char *cul_strchr_space(const char *str);
char *cul_strchr_nonspace(const char *str);

char **cul_strsplit_delimiter(const char *s, const char *delimiter);

/* strv functions */

size_t cul_strv_size(char **strv);

char **cul_strv_dup(char **strv);
char **cul_strv_dup_size(char **strv, size_t size);

void cul_strv_free(char **strv);

/* implementations */

static inline void cul_strnull(char *str) {
	*str = CUL_STR_NULL;
}

static inline cul_bool cul_strisnull(const char *str) {
	return (*str == CUL_STR_NULL);
}

static inline char *cul_strcat(char *dest, const char *src) {
	return strcat(dest, src);
}

static inline char *cul_strncat(char *dest, const char *src, size_t size) {
	return strncat(dest, src, size);
}

static inline char *cul_strcpy(char *dest, const char *src) {
	return strcpy(dest, src);
}

static inline char *cul_strncpy(char *dest, const char *src, size_t size) {
	return strncpy(dest, src, size);
}

static inline int cul_strcmp(const char *str, const char *cmp) {
	return strcmp(str, cmp);
}

static inline int cul_strncmp(const char *str, const char *cmp, size_t size) {
	return strncmp(str, cmp, size);
}

static inline size_t cul_strlen(const char *str) {
	return strlen(str);
}

static inline long int cul_strtol(const char *str, char **end, int base) {
	return strtol(str, end, base);
}

static inline double cul_strtod(const char *str, char **end) {
	return strtod(str, end);
}

static inline char *cul_strchr(const char *str, int find) {
	return strchr(str, find);
}

static inline char *cul_strrchr(const char *str, int find) {
	return strrchr(str, find);
}

static inline char *cul_strstr(const char *str, const char *find) {
	return strstr(str, find);
}

#endif