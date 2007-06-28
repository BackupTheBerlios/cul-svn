#ifndef CUL_RNG_H
#define CUL_RNG_H

#include <cul/cul_global.h>

/* rng structures */
typedef struct _CulRng     CulRng;
typedef enum   _CulRngType CulRngType;
typedef union  _CulRngSeed CulRngSeed;

/* typedefs for generic access to different rngs */
typedef void cul_rng_seed_f(void *state, CulRngSeed seed);
typedef double cul_rng_get_real_f(void *state);
typedef size_t cul_rng_get_f(void *state);

enum _CulRngType {
	CUL_RNG_DEFAULT,
	CUL_RNG_RAND,
	CUL_RNG_MT19937,
	CUL_RNG_MT19937_64
};

union _CulRngSeed {
	uint32_t _32;
	uint64_t _64;
};

/* generic rng allocation */
CulRng *cul_rng_new(CulRngType type);
void cul_rng_free(CulRng *rng);

/* generic rng acces */
void   cul_rng_seed(CulRng *rng, CulRngSeed seed);
size_t cul_rng_max(const CulRng *rng);
size_t cul_rng_get(const CulRng *rng);
double cul_rng_get_real(const CulRng *rng);

/* access internal structure data */
void *cul_rng_state(const CulRng *rng);
size_t cul_rng_size(const CulRng *rng);

/* simple seed functions */
static inline CulRngSeed cul_rng_seed_32(uint32_t seed);
static inline CulRngSeed cul_rng_seed_64(uint64_t seed);

/* rand rng, wrapper for standard library rand() */

#define CUL_RNG_RAND_MAX RAND_MAX

CulRng *cul_rng_rand_new();
void cul_rng_rand_seed(void *state, CulRngSeed seed);
uint32_t cul_rng_rand_sample(void *state);
size_t cul_rng_rand_get(void *state);
double cul_rng_rand_get_real(void *state);

/* Mersenne Twister rng */

#define CUL_RNG_MT19937_MAX UINT32_C(0xffffffff)

CulRng *cul_rng_mt19937_new();
void cul_rng_mt19937_seed(void *state, CulRngSeed seed);
uint32_t cul_rng_mt19937_sample(void *state);
size_t cul_rng_mt19937_get(void *state);
double cul_rng_mt19937_get_real(void *state);

/* Mersenne Twister 64 bit rng */

#define CUL_RNG_MT19937_64_MAX UINT64_C(0xffffffffffffffff)

CulRng *cul_rng_mt19937_64_new();
void cul_rng_mt19937_64_seed(void *state, CulRngSeed seed);
uint64_t cul_rng_mt19937_64_sample(void *state);
size_t cul_rng_mt19937_64_get(void *state);
double cul_rng_mt19937_64_get_real(void *state);

/* implementations */
static inline CulRngSeed cul_rng_seed_32(uint32_t seed) {
	CulRngSeed seed_32 = {._32 = seed};
	return seed_32;
}

static inline CulRngSeed cul_rng_seed_64(uint64_t seed) {
	CulRngSeed seed_64 = {._64 = seed};
	return seed_64;
}

#endif /*CUL_RNG_H*/
