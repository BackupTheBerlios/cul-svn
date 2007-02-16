#if !defined(CUL_MATH_H)
#define CUL_MATH_H

#include <math.h>

#define CUL_POW_2(val) ((val)*(val))

static inline double cul_sqrt(double val);
static inline double cul_pow_2(double val);

/* implementations */

static inline double cul_sqrt(double val) {
	return sqrt(val);
}

static inline double cul_pow_2(double val) {
	return val*val;
}

#endif
