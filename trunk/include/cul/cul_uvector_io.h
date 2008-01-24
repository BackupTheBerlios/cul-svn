#ifndef __CUL_UVECTOR_IO_H__
#define __CUL_UVECTOR_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>
#include <stdio.h>

cul_errno cul_uvector_fprintf    (FILE *stream, const CulUVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvector_fscanf     (FILE *stream, CulUVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fprintf(FILE *stream, const CulUVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fscanf (FILE *stream, CulUVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

#endif /* __CUL_UVECTOR_IO_H__ */
