#ifndef CUL_STREAM
#define CUL_STREAM

#include <cul/cul_global.h>
#include <stdio.h>

/* global cul library io stream for printing */

FILE *cul_stream_get(void);
FILE *cul_stream_set(FILE *stream);
FILE *cul_stream_default(void);

#endif /* CUL_STREAM */
