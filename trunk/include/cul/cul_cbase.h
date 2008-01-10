#ifndef __CUL_CBASE_H__
#define __CUL_CBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void     cul_csort_asc            (char *data, size_t size);
void     cul_csort_asc_stride     (char *data, size_t size, size_t stride);
void     cul_csort_desc           (char *data, size_t size);
void     cul_csort_desc_stride    (char *data, size_t size, size_t stride);
char    *cul_cunique              (char *data, size_t size);
char    *cul_cfind                (const char *data, size_t size, char key);
char    *cul_cbfind               (const char *data, size_t size, char key);

cul_bool cul_cfprintf             (FILE *stream, const char *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfprintf_stride      (FILE *stream, const char *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfscanf              (FILE *stream, const char *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_cfscanf_stride       (FILE *stream, const char *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implemenations */

#endif /* __CUL_CBASE_H__ */
