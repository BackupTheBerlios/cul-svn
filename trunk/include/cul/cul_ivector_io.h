#ifndef __CUL_IVECTOR_IO_H__
#define __CUL_IVECTOR_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_ivector.h>
#include <stdio.h>

cul_errno cul_ivector_fprintf    (FILE *stream, const CulIVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivector_fscanf     (FILE *stream, CulIVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fprintf(FILE *stream, const CulIVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fscanf (FILE *stream, CulIVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

#endif /* __CUL_IVECTOR_IO_H__ */
