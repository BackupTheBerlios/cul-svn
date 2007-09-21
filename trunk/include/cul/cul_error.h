#ifndef __CUL_ERROR_H__
#define __CUL_ERROR_H__

#include <cul/cul_base_global.h>

typedef enum _CulErrno CulErrno;

/**
 * Error flag describing type of error.
 * In cul library possible errors are passed *only* as a return result. No
 * global errno flag is used.
 */
enum _CulErrno {
	CUL_FAILURE  = -1,
	CUL_SUCCESS  =  0,

	CUL_ESTUB,
	CUL_EINVAL,
	CUL_EFAILED,
	CUL_ENOMEM,
	CUL_EBADLEN,
	CUL_EBADPOS,
	CUL_EPRINTF,
	CUL_ESCANF,
	CUL_EARGNEED,
	CUL_EARGUNK,
	CUL_EARGCONV,
	CUL_EFACCESS,
	CUL_EFIO
};

const char *cul_error_string         (CulErrno error);

cul_bool    cul_error_fatal_get      ();
cul_bool    cul_error_fatal_set      (cul_bool value);

#endif /* __CUL_ERROR_H__ */
