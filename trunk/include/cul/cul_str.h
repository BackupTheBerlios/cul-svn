#ifndef __CUL_STR_H__
#define __CUL_STR_H__

#include <cul/cul_global.h>

char     *cul_str_new      (size_t size);
void      cul_str_free     (char *strv);

cul_bool  cul_str_isspace   (const char *str);
char     *cul_str_tolower   (char *str);
char     *cul_str_toupper   (char *str);

char     *cul_str_trim      (char *str);
char     *cul_str_trim_right(char *str);
char     *cul_str_trim_left (char *str);

char    **cul_str_split     (const char *str, const char *delimiter);
char    **cul_str_splits    (const char *str, const char *delimiters);
char     *cul_str_cat       (const char *str, ...);
char     *cul_str_join      (const char *separator, const char *str, ...);

int       cul_strcmp        (const char *str, const char *other);
int       cul_strcmp_size   (const char *str, const char *other, size_t size);
int       cul_strncmp       (const char *str, const char *other, size_t size);
int       cul_stricmp       (const char *str, const char *other);
int       cul_stricmp_size  (const char *str, const char *other, size_t size);
int       cul_strincmp      (const char *str, const char *other, size_t size);
char     *cul_strdup        (const char *str);
char     *cul_strdup_size   (const char *str, size_t size);
char     *cul_strndup       (const char *str, size_t size);

cul_errno cul_strtou        (const char *str, size_t base, size_t *value);
cul_errno cul_strtoi        (const char *str, size_t base, int *value);
cul_errno cul_strtod        (const char *str, double *value);

char    **cul_strv_new      (size_t size);
void      cul_strv_free     (char **strv);
void      cul_strv_free_size(char **strv, size_t size);

int       cul_strv_cmp      (char **strv, char **otherv);
int       cul_strv_cmp_size (char **strv, char **otherv, size_t size);
int       cul_strv_icmp     (char **strv, char **otherv);
int       cul_strv_icmp_size(char **strv, char **otherv, size_t size);
char    **cul_strv_dup      (char **strv);
char    **cul_strv_dup_size (char **strv, size_t size);

size_t    cul_strv_size     (char **strv);
void      cul_strv_push_back(char **strv, char *str);
void      cul_strv_pop_back (char **strv);

char     *cul_strv_join     (char *separator, char **strv);
size_t    cul_strv_find     (char **strv, const char *key, cul_eq_f *eq_f);

char    **cul_strv_head     (char **strv, size_t size);
char    **cul_strv_tail     (char **strv, size_t size);
char    **cul_strv_grep     (char **strv, cul_const_ptr data, cul_eq_f *eq);
char    **cul_strv_cat      (char **strv, ...);

cul_errno cul_strv_tou      (char **strv, size_t base, size_t *value);
cul_errno cul_strv_toi      (char **strv, size_t base, int *value);
cul_errno cul_strv_tod      (char **strv, double *value);

#endif /* __CUL_STR_H__ */
