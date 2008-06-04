#include <cul/cul_error.h>

cul_bool cul_error_fatal = CUL_TRUE;

const char *cul_error_string(CulErrno eid) {
	switch( eid ) {
	case CUL_UNKNOWN:    return "unknown, success or error";
	case CUL_SUCCESS:    return "success";
	case CUL_EFAILED:    return "generic failure";
	case CUL_ESTUB:      return "missing implementation";
	case CUL_EINVAL:     return "invalid argument";
	case CUL_ENOMEM:     return "memory allocation failed";
	case CUL_EBADLEN:    return "invalid size, sizes do not match";
	case CUL_EBADPOS:    return "position out of range";
	case CUL_EARGUNK:    return "unknown argument";
	case CUL_EARGCONV:   return "argument conversion failed";
	case CUL_EARGNEED:   return "missing needed argument";
	case CUL_EARGEX:     return "ambiguous exclusive argument";
	case CUL_ECONVINVAL: return "invalid conversion";
	case CUL_ECONVRANGE: return "conversion range error";
	case CUL_ECONVPART:  return "partial conversion error";
	case CUL_EFACCESS:   return "file/stream access error";
	case CUL_EFIO:       return "stream input/output error";
	case CUL_E_MASK:     break;
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

