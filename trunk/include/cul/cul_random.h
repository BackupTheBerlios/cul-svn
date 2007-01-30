#if !defined(CUL_RANDOM_H)
#define CUL_RANDOM_H

#include <stdlib.h>
#include <time.h>

static inline void cul_random_init();
static inline double cul_drandom();
static inline size_t cul_urandom();

/* FIXME temporary implementations */

static inline void cul_random_init() {
	srand( (size_t)time(NULL) );
}

static inline double cul_drandom() {
	return (double)rand()/RAND_MAX;
}

static inline size_t cul_urandom() {
	return rand();
}

#endif
