#ifndef __CUL_RANDOM_H__
#define __CUL_RANDOM_H__

#include <cul/cul_global.h>
#include <cul/cul_rng.h>
#include <stdlib.h>

/* basic wrappers for standard functions */

static inline int cul_rand();
static inline double cul_rand_real();
static inline void cul_srand(unsigned int seed);

/* implementations */

static inline int cul_rand() {
	return rand();
}

static inline void cul_srand(unsigned int seed) {
	srand(seed);
}

static inline double cul_rand_real() {
	return (double)cul_rand()/(double)((unsigned int)RAND_MAX+1);
}

#endif /* __CUL_RANDOM_H__ */
