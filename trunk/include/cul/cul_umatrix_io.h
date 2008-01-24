#ifndef __CUL_UMATRIX_IO_H__
#define __CUL_UMATRIX_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_umatrix.h>
#include <stdio.h>

cul_errno cul_umatrix_fprintf(FILE *stream, const CulUMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_umatrix_fscanf (FILE *stream, CulUMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

#endif /* __CUL_UMATRIX_IO_H__ */
