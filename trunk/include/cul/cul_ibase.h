#ifndef __CUL_IBASE_H__
#define __CUL_IBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void     cul_isort_asc            (int *data, size_t size);
void     cul_isort_asc_stride     (int *data, size_t size, size_t stride);
void     cul_isort_desc           (int *data, size_t size);
void     cul_isort_desc_stride    (int *data, size_t size, size_t stride);
int     *cul_iunique              (int *data, size_t size);
int     *cul_ifind                (const int *data, size_t size, int key);
int     *cul_ibfind               (const int *data, size_t size, int key);

cul_bool cul_ifprintf             (FILE *stream, const int *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifprintf_stride      (FILE *stream, const int *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifscanf              (FILE *stream, const int *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ifscanf_stride       (FILE *stream, const int *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

#endif /* __CUL_IBASE_H__ */
