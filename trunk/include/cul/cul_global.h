#ifndef CUL_GLOBAL_H
#define CUL_GLOBAL_H

/* basic include for config and base typedefs and defines */
#include <cul/cul_base_global.h>

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

#endif /* CUL_GLOBAL_H */
