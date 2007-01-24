#if !defined(CUL_RANDOM_H)
#define CUL_RANDOM_H

#include <stdlib.h>
#include <time.h>

static inline void cul_random_init();
static inline double cul_drandom();
static inline int cul_irandom();

/* FIXME temporary implementations */
/* implementations */

static inline void cul_random_init() {
	srand( (size_t)time(NULL) );
}

static inline double cul_drandom() {
	return (double)rand()/RAND_MAX;
}

static inline int cul_irandom() {
	return rand();
}

#endif
