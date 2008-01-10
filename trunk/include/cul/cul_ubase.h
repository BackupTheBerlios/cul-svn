#ifndef __CUL_UBASE_H__
#define __CUL_UBASE_H__

#include <cul/cul_base_global.h>
#include <stdio.h>

void     cul_usort_asc            (size_t *data, size_t size);
void     cul_usort_asc_stride     (size_t *data, size_t size, size_t stride);
void     cul_usort_desc           (size_t *data, size_t size);
void     cul_usort_desc_stride    (size_t *data, size_t size, size_t stride);
size_t  *cul_uunique              (size_t *data, size_t size);
size_t  *cul_ufind                (const size_t *data, size_t size, size_t key);
size_t  *cul_ubfind               (const size_t *data, size_t size, size_t key);

cul_bool cul_ufprintf             (FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufprintf_stride      (FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf              (FILE *stream, const size_t *data, size_t size, const char *format, const char *separator, const char *begin, const char *end);
cul_bool cul_ufscanf_stride       (FILE *stream, const size_t *data, size_t size, size_t stride, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

#endif /* __CUL_UBASE_H__ */
