#ifndef __CUL_ERROR_H__
#define __CUL_ERROR_H__

#include <cul/cul_base_global.h>

typedef enum _CulErrno CulErrno;

/** Error flag describing type of error.
 * Error flag describes error situation in cul library. Possible errors are
 * passed _only_ as a return result. No global flag like errno is used. All
 * non base functions additionally would call cul_log function to log error
 * situation. By default it would cause application abort, but this behaviour
 * could be customized.
 *
 * NOTE: Exception to errno non-usage are functions, wrappers that make use
 * of standard library calls (i.e. cul_strtol). In these cases errno value is
 * used, but its previous value is restored.
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
	CUL_EARGUNK,
	CUL_EARGCONV,
	CUL_EARGEX,
	CUL_EARGNEED,
	CUL_EFACCESS,
	CUL_EFIO,
	CUL_ECONVINVAL,
	CUL_ECONVRANGE,
	CUL_ECONVPART
};

const char *cul_error_string         (CulErrno error);

cul_bool    cul_error_fatal_get      ();
cul_bool    cul_error_fatal_set      (cul_bool is_fatal);

#endif /* __CUL_ERROR_H__ */
