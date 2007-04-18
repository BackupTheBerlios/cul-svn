#ifndef CUL_RNG_H
#define CUL_RNG_H

#include <cul/cul_global.h>

/* typedefs for generic access to different rng-s */
typedef double cul_rng_get_real_f(void *state);
typedef size_t cul_rng_get_f(void *state);

typedef struct _CulRng CulRng;

void cul_rng_free(CulRng *rng);

/* generic acces to rng */
size_t cul_rng_max(const CulRng *rng);
size_t cul_rng_get(const CulRng *rng);
double cul_rng_get_real(const CulRng *rng);

/* access internal structure data */
void *cul_rng_state(const CulRng *rng);
size_t cul_rng_size(const CulRng *rng);

/* rand rng, wrapper for standard library rand() */

#define CUL_RNG_RAND_MAX RAND_MAX

CulRng *cul_rng_rand_new();
void cul_rng_rand_seed(void *state, uint32_t seed);
uint32_t cul_rng_rand_sample(void *state);
size_t cul_rng_rand_get(void *state);
double cul_rng_rand_get_real(void *state);

/* Mersenne Twister rng */

#define CUL_RNG_MT19937_MAX UINT32_C(0xffffffff)

CulRng *cul_rng_mt_19937_new();
void cul_rng_mt19937_seed(void *state, uint32_t seed);
uint32_t cul_rng_mt19937_sample(void *state);
size_t cul_rng_mt19937_get(void *state);
double cul_rng_mt19937_get_real(void *state);

/* Mersenne Twister 64 bit rng */

#define CUL_RNG_MT19937_64_MAX UINT64_C(0xffffffffffffffff)

CulRng *cul_rng_mt_19937_64_new();
void cul_rng_mt19937_64_seed(void *state, uint64_t seed);
uint64_t cul_rng_mt19937_64_sample(void *state);
size_t cul_rng_mt19937_64_get(void *state);
double cul_rng_mt19937_64_get_real(void *state);

#endif /*CUL_RNG_H*/