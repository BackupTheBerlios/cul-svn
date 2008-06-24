#ifndef __CUL_RNG_H__
#define __CUL_RNG_H__

#include <cul/cul_global.h>

/* rng structures */
typedef struct _CulRng     CulRng;
typedef enum   _CulRngType CulRngType;
typedef union  _CulRngSeed CulRngSeed;

/* typedefs for generic callback functions */
typedef void   cul_rng_seed_f    (void *state, CulRngSeed seed);
typedef double cul_rng_get_real_f(void *state);
typedef size_t cul_rng_get_f     (void *state);

/** Type of random number generator
 * Type of random number generator that is used to create generator in generic
 * way and check type of generator that is stored in opaque CulRng structure.
 */
enum _CulRngType {
	CUL_RNG_DEFAULT,    /* default generator, could be set through environment variable */
	CUL_RNG_RAND,       /* standard generator present in libc, structure is only wrapper */
	CUL_RNG_MT19937,    /* mersenne twister */
	CUL_RNG_MT19937_64  /* mersenne twister, 64 bit version */
};

/** Simple seed structure to seed rng
 * Generic union that could be used to seed any supported rng. Use specific
 * initialization routines rather that manually initialize its fields.
 */
union _CulRngSeed {
	uint32_t _32;       /* unsigned 32 bit seed */
	uint64_t _64;       /* unsigned 64 bit seed */
};

/* simple seed functions */
static inline CulRngSeed cul_rng_seed_32(uint32_t seed); /* initialize seed with 32 bit unsigned value */
static inline CulRngSeed cul_rng_seed_64(uint64_t seed); /* initialize seed with 64 bit unsigned value */

/* generic rng functions */
CulRng    *cul_rng_new     (CulRngType type);               /* allocate and initialize specific rng */
void       cul_rng_free    (CulRng *rng);                   /* free memory associated with rng */
void       cul_rng_seed    (CulRng *rng, CulRngSeed seed);  /* seed rng in generic way */
CulRngType cul_rng_type    (const CulRng *rng);             /* get rung type */
size_t     cul_rng_max     (const CulRng *rng);             /* return maximum possible value of rng */
size_t     cul_rng_get     (const CulRng *rng);             /* get unsigned random number generated by a rng [0; max] */
double     cul_rng_get_real(const CulRng *rng);             /* get real random number generated by a rng [0; 1.0) */
size_t     cul_rng_get_flat(const CulRng *rng, size_t max); /* get subsampled unsigned random number generated by a rng [0; max] */
void      *cul_rng_state   (const CulRng *rng);             /* return internal state structure */
size_t     cul_rng_size    (const CulRng *rng);             /* return size (in bytes) of internal state structure */

/* specific rng functions */

/* rand rng, wrapper for standard library rand() */
#define  CUL_RNG_RAND_MAX     RAND_MAX
CulRng  *cul_rng_rand_new();
void     cul_rng_rand_seed    (void *state, CulRngSeed seed);
uint32_t cul_rng_rand_sample  (void *state);
size_t   cul_rng_rand_get     (void *state);
double   cul_rng_rand_get_real(void *state);

/* Mersenne Twister rng */
#define  CUL_RNG_MT19937_MAX     UINT32_C(0xffffffff)
CulRng  *cul_rng_mt19937_new     ();
void     cul_rng_mt19937_seed    (void *state, CulRngSeed seed);
uint32_t cul_rng_mt19937_sample  (void *state);
size_t   cul_rng_mt19937_get     (void *state);
double   cul_rng_mt19937_get_real(void *state);

/* Mersenne Twister 64 bit rng */
#define  CUL_RNG_MT19937_64_MAX     UINT64_C(0xffffffffffffffff)
CulRng  *cul_rng_mt19937_64_new     ();
void     cul_rng_mt19937_64_seed    (void *state, CulRngSeed seed);
uint64_t cul_rng_mt19937_64_sample  (void *state);
size_t   cul_rng_mt19937_64_get     (void *state);
double   cul_rng_mt19937_64_get_real(void *state);

/* implementations */
static inline CulRngSeed cul_rng_seed_32(uint32_t seed) {
	CulRngSeed seed_32 = {._32 = seed};
	return seed_32;
}

static inline CulRngSeed cul_rng_seed_64(uint64_t seed) {
	CulRngSeed seed_64 = {._64 = seed};
	return seed_64;
}

#endif /* __CUL_RNG_H__ */

