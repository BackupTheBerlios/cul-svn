#include <cul/cul_error.h>

cul_bool cul_error_fatal = CUL_TRUE;

const char *cul_error_string(CulErrno eid) {
	switch( eid ) {
		case CUL_SUCCESS:   return "success";
		case CUL_FAILURE:   return "failure";
		case CUL_EINVAL:    return "invalid argument";
		case CUL_EINIT:     return "initialization failed";
		case CUL_EFAILED:   return "operation failed";
		case CUL_ENOMEM:    return "memory allocation failed";
		case CUL_EBADLEN:   return "invalid size, sizes do not match";
		case CUL_EBADPOS:   return "position out of range";
		case CUL_EPRINTF:   return "print data error";
		case CUL_ESPRINTF:  return "print data to string error";
		case CUL_ESCANF:    return "read data error";
		case CUL_EARGMISS:  return "missing required argument";
		case CUL_EARGUNK:   return "unknown argument";
		case CUL_EARGCONV:  return "argument conversion failed";
		case CUL_EARGSHORT: return "bad format of short switch";
		case CUL_EARGLONG:  return "bad format of long switch";
	}
	return "unknown error code";
}

cul_bool cul_error_fatal_get(void) {
	return cul_error_fatal;
}

cul_bool cul_error_fatal_set(cul_bool val) {
	cul_bool old_val = cul_error_fatal;
	cul_error_fatal = val;
	return old_val;
}
