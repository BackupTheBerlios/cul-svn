#ifndef __CUL_IMATRIX_IO_H__
#define __CUL_IMATRIX_IO_H__

#include <cul/cul_global.h>
#include <cul/cul_imatrix.h>
#include <stdio.h>

cul_errno cul_imatrix_fprintf(FILE *stream, const CulIMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_imatrix_fscanf (FILE *stream, CulIMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

#endif /* __CUL_IMATRIX_IO_H__ */
