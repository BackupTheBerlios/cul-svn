#ifndef __CUL_STREAM__
#define __CUL_STREAM__

#include <cul/cul_global.h>
#include <stdio.h>

/* global cul library io stream for printing */

FILE *cul_stream_get        ();
FILE *cul_stream_get_default();
FILE *cul_stream_set        (FILE *stream);

#endif /* __CUL_STREAM__ */
