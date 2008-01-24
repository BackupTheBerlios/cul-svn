#ifndef __CUL_DMATRIX_IO_H__
#define __CUL_DMATRIX_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_dmatrix.h>
#include <stdio.h>

cul_errno cul_dmatrix_fprintf(FILE *stream, const CulDMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_dmatrix_fscanf (FILE *stream, CulDMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

#endif /* __CUL_DMATRIX_IO_H__ */
