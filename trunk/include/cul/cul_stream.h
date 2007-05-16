#ifndef CUL_STREAM
#define CUL_STREAM

#include <cul/cul_global.h>
#include <stdio.h>

/* global cul library io stream for printing */

FILE *cul_stream_get(void);
FILE *cul_stream_get_default(void);
FILE *cul_stream_set(FILE *stream);

#endif /* CUL_STREAM */
