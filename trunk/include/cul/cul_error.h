#if !defined(CUL_ERROR_H)
#define CUL_ERROR_H

#include <cul/cul_global_base.h>

typedef enum _CulErrno CulErrno;
typedef enum _CulErrnoMsg CulErrnoMsg;

enum _CulErrno {
	CUL_FAILURE  = -1,
	CUL_SUCCESS  =  0,

	CUL_EINVAL,
	CUL_EINIT,
	CUL_EFAILED,
	CUL_ENOMEM,
	CUL_EBADLEN,
	CUL_EBADPOS,
	CUL_EPRINTF,
	CUL_ESPRINTF,
	CUL_ESCANF,
	CUL_EARGMISS,
	CUL_EARGUNK,
	CUL_EARGCONV,
	CUL_EARGSHORT,
	CUL_EARGLONG
};

const char *cul_error_string(CulErrno eid);

cul_bool cul_error_fatal_get(void);
cul_bool cul_error_fatal_set(cul_bool val);

#endif
