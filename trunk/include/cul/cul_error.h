#ifndef __CUL_ERROR_H__
#define __CUL_ERROR_H__

#include <cul/cul_core.h>

/* basic error type */
typedef enum _CulErrno CulErrno;

/* type mapping */
typedef CulErrno cul_errno;

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
	/* generic results */
	CUL_UNKNOWN = -1,  /* unknown status */
	CUL_SUCCESS =  0,  /* operation is successful */
	CUL_EFAILED,       /* generic fail */

	/* generic error codes */
	CUL_ESTUB,         /* stub implementation */
	CUL_EINVAL,        /* invalid arguments */
	CUL_ENOMEM,        /* not enough memory */
	CUL_EBADLEN,       /* invalid length of objects */
	CUL_EBADPOS,       /* invalid position */

	/* conversion errors */
	CUL_ECONVINVAL,    /* invalid conversion */
	CUL_ECONVRANGE,    /* number out of range */
	CUL_ECONVPART,     /* partial conversion occurred */

	/* command line arguments */
	CUL_EARGUNK,       /* unknown argument */
	CUL_EARGCONV,      /* conversion error */
	CUL_EARGEX,        /* two exclusive arguments present */
	CUL_EARGNEED,      /* missing needed argument */

	/* file/stream access */
	CUL_EFACCESS,      /* file access error */
	CUL_EFIO,          /* input/output error */

	CUL_E_MASK,        /* maximum error mask */
};

const char *cul_error_string         (CulErrno error);

cul_bool    cul_error_fatal_get      ();
cul_bool    cul_error_fatal_set      (cul_bool is_fatal);

#endif /* __CUL_ERROR_H__ */
