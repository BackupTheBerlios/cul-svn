#ifndef __CUL_CVECTOR_IO_H__
#define __CUL_CVECTOR_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_cvector.h>
#include <stdio.h>

cul_errno cul_cvector_fprintf    (FILE *stream, const CulCVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_cvector_fscanf     (FILE *stream, CulCVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_cvectorview_fprintf(FILE *stream, const CulCVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_cvectorview_fscanf (FILE *stream, CulCVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

#endif /* __CUL_CVECTOR_IO_H__ */
