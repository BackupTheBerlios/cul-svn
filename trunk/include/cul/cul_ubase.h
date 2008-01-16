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

/* implementations */

#endif /* __CUL_UBASE_H__ */
