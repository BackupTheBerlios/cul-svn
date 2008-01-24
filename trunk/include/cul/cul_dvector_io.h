#ifndef __CUL_DVECTOR_IO_H__
#define __CUL_DVECTOR_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_dvector.h>
#include <stdio.h>

cul_errno cul_dvector_fprintf    (FILE *stream, const CulDVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_dvector_fscanf     (FILE *stream, CulDVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_dvectorview_fprintf(FILE *stream, const CulDVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_dvectorview_fscanf (FILE *stream, CulDVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

#endif /* __CUL_DVECTOR_IO_H__ */
