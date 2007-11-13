#include <cul/cul_error.h>

cul_bool cul_error_fatal = CUL_TRUE;

const char *cul_error_string(CulErrno eid) {
	switch( eid ) {
	case CUL_SUCCESS:    return "success";
	case CUL_FAILURE:    return "failure";
	case CUL_ESTUB:      return "missing implementation";
	case CUL_EINVAL:     return "invalid argument";
	case CUL_EFAILED:    return "operation failed";
	case CUL_ENOMEM:     return "memory allocation failed";
	case CUL_EBADLEN:    return "invalid size, sizes do not match";
	case CUL_EBADPOS:    return "position out of range";
	case CUL_EPRINTF:    return "write data error";
	case CUL_ESCANF:     return "read data error";
	case CUL_EARGNEED:   return "missing needed argument";
	case CUL_EARGUNK:    return "unknown argument";
	case CUL_EARGCONV:   return "argument conversion failed";
	case CUL_EFACCESS:   return "file access error";
	case CUL_EFIO:       return "input/output error";
	case CUL_ECONVINVAL: return "invalid converion";
	case CUL_ECONVRANGE: return "conversion range error";
	}
	return "unknown error code";
}

cul_bool cul_error_fatal_get(void) {
	return cul_error_fatal;
}

cul_bool cul_error_fatal_set(cul_bool is_fatal) {
	cul_bool value = cul_error_fatal;
	cul_error_fatal = is_fatal;
	return value;
}

