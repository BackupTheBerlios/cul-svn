#ifndef CUL_RANDOM_H
#define CUL_RANDOM_H

#include <cul/cul_global.h>
#include <cul/cul_rng.h>
#include <stdlib.h>

/* basic wrappers for standard functions */

static inline int cul_rand();
static inline double cul_rand_real();
static inline void cul_srand(unsigned int seed);

/* various distributions */

double cul_random_uniform(const CulRng *rng, double min, double max);

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

#endif /* CUL_RANDOM_H */
