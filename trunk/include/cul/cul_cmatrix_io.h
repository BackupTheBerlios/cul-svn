#ifndef __CUL_CMATRIX_IO_H__
#define __CUL_CMATRIX_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_cmatrix.h>
#include <stdio.h>

cul_errno cul_cmatrix_fprintf(FILE *stream, const CulCMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_cmatrix_fscanf (FILE *stream, CulCMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

#endif /* __CUL_CMATRIX_IO_H__ */
