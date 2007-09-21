#ifndef __CUL_STR_H__
#define __CUL_STR_H__

#include <cul/cul_global.h>

#define CUL_STR_NULL    '\0'
#define CUL_STR_SPACE   ' '
#define CUL_STR_TAB     '\t'
#define CUL_STR_NEWLINE '\n'

char    *cul_strdup       (const char *str);
char    *cul_strdup_size  (const char *str, size_t size);
char    *cul_strndup      (const char *str, size_t size);

char    *cul_strtrim      (char *str);
char    *cul_strtrim_right(char *str);
char    *cul_strtrim_left (char *str);

char    *cul_strtolower   (char *str);
char    *cul_strtoupper   (char *str);

cul_bool cul_strisspace   (const char *str);
char   **cul_strsplit     (const char *s, const char *delimiter);

size_t   cul_strv_size    (char **strv);
size_t   cul_strv_find    (char **strv, const char *key, cul_cmp_f *cmp_f);

char   **cul_strv_dup     (char **strv);
char   **cul_strv_dup_size(char **strv, size_t size);
void     cul_strv_free    (char **strv);

#endif /* __CUL_STR_H__ */
