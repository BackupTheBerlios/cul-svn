#ifndef CUL_ERROR_H
#define CUL_ERROR_H

#include <cul/cul_base_global.h>

typedef enum _CulErrno CulErrno;
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
	CUL_EARGMISS,
	CUL_EARGUNK,
	CUL_EARGCONV,
	CUL_EARGSHORT,
	CUL_EARGLONG,
	CUL_EFACCESS,
	CUL_EFIO
};

const char *cul_error_string(CulErrno eid);

cul_bool cul_error_fatal_get(void);
cul_bool cul_error_fatal_set(cul_bool val);

#endif /* CUL_ERROR_H */
