#if !defined(CUL_GLOBAL_H)
#define CUL_GLOBAL_H

#include <cul/cul_global_base.h>
#include <cul/cul_error.h>
#include <cul/cul_log.h>
#include <cul/cul_macro.h>
#include <cul/cul_mem.h>

/* advanced type mapping */

typedef CulErrno cul_errno;

#define CUL_NAN (0.0/0.0)

static inline double cul_nan() {
	return CUL_NAN;
}

static inline cul_bool cul_isnan(double val) {
	return !(val == val);
}

#endif
