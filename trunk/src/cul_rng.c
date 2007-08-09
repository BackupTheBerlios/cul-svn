#include <cul/cul_random.h>    /* rand rng functions */
#include <cul/cul_rng.h>

CulRngType cul_rng_default = CUL_RNG_DEFAULT;

/* private get default function */
CulRngType _cul_rng_get_default(void);
CulRngType _cul_rng_set_default(CulRngType type);

CulRngType _cul_rng_get_default(void) {
	/* TODO possible environment variable read in future */
	if( cul_rng_default == CUL_RNG_DEFAULT )
		_cul_rng_set_default(CUL_RNG_MT19937);
	return cul_rng_default;
}

CulRngType _cul_rng_set_default(CulRngType type) {
	CulRngType old_type = cul_rng_default;
	cul_rng_default = type;
	return old_type;
}

/* private rng structure */
struct _CulRng {
	CulRngType type;                 /* type of rng */
	cul_rng_seed_f *seed;            /* generic seed routine */
	cul_rng_get_f *get;              /* generic size_t sampling routine */
	cul_rng_get_real_f *get_real;    /* generic double sampling routine */
	void *state;                     /* rng state used for sampling */
};

static inline CulRng *cul_rng_new_struct(void) {
	return cul_slab_new(sizeof(CulRng));
}

static inline void cul_rng_free_struct(CulRng *rng) {
	cul_slab_free(sizeof(CulRng), rng);
}

static inline CulRng *cul_rng_init_struct(CulRng *rng, CulRngType type, cul_rng_seed_f *seed, cul_rng_get_f *get, cul_rng_get_real_f *get_real, void *state) {
	rng->type = type;
	rng->seed = seed;
	rng->get = get;
	rng->get_real = get_real;
	rng->state = state;
	return rng;
}

/* basic rng functions */

CulRng *cul_rng_new(CulRngType type) {
	CulRng *rng;

	/* check if we have to use default rng */
	if( type == CUL_RNG_DEFAULT )
		type = _cul_rng_get_default();

	switch( type ) {
		case CUL_RNG_DEFAULT:    rng = NULL; break;
		case CUL_RNG_RAND:       rng = cul_rng_rand_new(); break;
		case CUL_RNG_MT19937:    rng = cul_rng_mt19937_new(); break;
		case CUL_RNG_MT19937_64: rng = cul_rng_mt19937_64_new(); break;
	}
	if( rng == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_EFAILED);
	return rng;
}

void cul_rng_free(CulRng *rng) {
	if( rng != NULL ) {
		free(rng->state);
		free(rng);
	}
}

/* private helper functions */
static inline size_t _cul_rng_max(const CulRng *rng);
static inline size_t _cul_rng_size(const CulRng *rng);

void cul_rng_seed(CulRng *rng, CulRngSeed seed) {
	rng->seed(rng->state, seed);
}

size_t cul_rng_max(const CulRng *rng) {
	return _cul_rng_max(rng);
}

double cul_rng_get_real(const CulRng *rng) {
	return rng->get_real(rng->state);
}

size_t cul_rng_get(const CulRng *rng) {
	return rng->get(rng->state);
}

void *cul_rng_state(const CulRng *rng) {
	return rng->state;
}

size_t cul_rng_size(const CulRng *rng) {
	return _cul_rng_size(rng);
}

/* default rand rng */

CulRng *cul_rng_rand_new() {
	const CulRngSeed default_seed = cul_rng_seed_32( UINT32_C(0) );
	CulRng *rng;

	if( (rng = cul_rng_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	cul_rng_init_struct(rng, CUL_RNG_RAND, cul_rng_rand_seed, cul_rng_rand_get, cul_rng_rand_get_real, NULL);
	cul_rng_rand_seed(rng->state, default_seed);
	return rng;
}

void cul_rng_rand_seed(void *state, CulRngSeed seed) {
	CUL_UNUSED(state);
	cul_srand(seed._32);
}

uint32_t cul_rng_rand_sample(void *state) {
	CUL_UNUSED(state);
	return cul_rand();
}

size_t cul_rng_rand_get(void *state) {
	if( SIZE_MAX < CUL_RNG_RAND_MAX )
		return cul_rng_rand_sample(state) * ((double)SIZE_MAX/(double)CUL_RNG_RAND_MAX );
	return cul_rng_rand_sample(state);
}

double cul_rng_rand_get_real(void *state) {
	CUL_UNUSED(state);
	return cul_rand_real();
}

/* Mersenne Twister rng */

#define N          624
#define M          397
#define UPPER_MASK UINT32_C(0x80000000)
#define LOWER_MASK UINT32_C(0x7fffffff)

typedef struct _CulRngState_mt19937 _CulRngState_mt19937;
struct _CulRngState_mt19937 {
	uint32_t mt[N];
	size_t mti;
};

CulRng *cul_rng_mt19937_new() {
	const CulRngSeed default_seed = cul_rng_seed_32( UINT32_C(0) );
	CulRng *rng;
	void *state;

	if( (rng = cul_rng_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( (state = malloc(sizeof(_CulRngState_mt19937))) == NULL ) {
		cul_rng_free_struct(rng);
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	}

	cul_rng_init_struct(rng, CUL_RNG_MT19937, cul_rng_mt19937_seed, cul_rng_mt19937_get, cul_rng_mt19937_get_real, state);
	cul_rng_mt19937_seed(rng->state, default_seed);
	return rng;
}

void cul_rng_mt19937_seed(void *state, CulRngSeed seed) {
	_CulRngState_mt19937 *const _state = state;
	uint32_t *const mt = _state->mt;

	mt[0] = seed._32;
	for(size_t i=1; i<N; ++i)
		mt[i] = (UINT32_C(1812433253)*(mt[i-1] ^ (mt[i-1] >> 30)) + i);
	_state->mti = N;
}

uint32_t cul_rng_mt19937_sample(void *state) {
	static uint32_t magic[2] = {0, UINT32_C(0x9908b0df)};

	_CulRngState_mt19937 *_state = state;
	uint32_t *mt = _state->mt;

	/* regenerate state if needed */
	if( _state->mti >= N ) {
		uint32_t val;
		size_t i;

		for(i=0; i<N-M; ++i) {
			val = (mt[i]&UPPER_MASK) | (mt[i+1]&LOWER_MASK);
			mt[i] = mt[i+M] ^ (val>>1) ^ magic[val & UINT32_C(1)];
		}
		for(; i<N-1; ++i) {
			val = (mt[i]&UPPER_MASK) | (mt[i+1]&LOWER_MASK);
			mt[i] = mt[i+(M-N)] ^ (val>>1) ^ magic[val & UINT32_C(1)];
		}
		val = (mt[N-1]&UPPER_MASK) | (mt[0]&LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (val>>1) ^ magic[val & UINT32_C(1)];
		_state->mti = 0;
	}

	/* generate result */
	uint32_t result = mt[_state->mti++];
	result ^= (result>>11);
	result ^= (result<<7) & UINT32_C(0x9d2c5680);
	result ^= (result<<15) & UINT32_C(0xefc60000);
	result ^= (result>>18);
	return result;
}

size_t cul_rng_mt19937_get(void *state) {
	if( SIZE_MAX < CUL_RNG_MT19937_MAX )
		return cul_rng_mt19937_sample(state) * ((double)SIZE_MAX/(double)CUL_RNG_MT19937_MAX );
	return cul_rng_mt19937_sample(state);
}

double cul_rng_mt19937_get_real(void *state) {
	return cul_rng_mt19937_get(state) / (CUL_RNG_MT19937_MAX + 1.0);
}

/* clear macros */

#undef N
#undef M
#undef UPPER_MASK
#undef LOWER_MASK

/* Mersenne Twister 64 bit rng */

#define NN         312
#define MM         156
#define UPPER_MASK UINT64_C(0xFFFFFFFF80000000)
#define LOWER_MASK UINT64_C(0x7FFFFFFF)

typedef struct _CulRngState_mt19937_64 _CulRngState_mt19937_64;
struct _CulRngState_mt19937_64 {
	uint64_t mt[NN];
	size_t mti;
};

CulRng *cul_rng_mt19937_64_new() {
	const CulRngSeed default_seed = cul_rng_seed_64( UINT64_C(0) );
	CulRng *rng;
	void *state;

	if( (rng = cul_rng_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( (state = malloc(sizeof(_CulRngState_mt19937_64))) == NULL ) {
		cul_rng_free_struct(rng);
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	}

	cul_rng_init_struct(rng, CUL_RNG_MT19937_64, cul_rng_mt19937_64_seed, cul_rng_mt19937_64_get, cul_rng_mt19937_64_get_real, state);
	cul_rng_mt19937_64_seed(rng->state, default_seed);
	return rng;
}

void cul_rng_mt19937_64_seed(void *state, CulRngSeed seed) {
	_CulRngState_mt19937_64 *_state = state;
	uint64_t *mt = _state->mt;

	mt[0] = seed._64;
	for(size_t i=1; i<NN; ++i)
		mt[i] = (UINT64_C(6364136223846793005)*(mt[i-1] ^ (mt[i-1] >> 62)) + i);
	_state->mti = NN;
}

uint64_t cul_rng_mt19937_64_sample(void *state) {
	static uint64_t magic[2] = {0, UINT64_C(0xB5026F5AA96619E9)};

	_CulRngState_mt19937_64 *_state = state;
	uint64_t *mt = _state->mt;

	/* regenerate state if needed */
	if( _state->mti >= NN ) {
		uint64_t val;
		size_t i;

		for(i=0; i<NN-MM; ++i) {
			val = (mt[i]&UPPER_MASK) | (mt[i+1]&LOWER_MASK);
			mt[i] = mt[i+MM] ^ (val>>1) ^ magic[val & UINT64_C(1)];
		}
		for(; i<NN-1; ++i) {
			val = (mt[i]&UPPER_MASK) | (mt[i+1]&LOWER_MASK);
			mt[i] = mt[i+(MM-NN)] ^ (val>>1) ^ magic[val & UINT64_C(1)];
		}
		val = (mt[NN-1]&UPPER_MASK) | (mt[0]&LOWER_MASK);
		mt[NN-1] = mt[MM-1] ^ (val>>1) ^ magic[val & UINT64_C(1)];
		_state->mti = 0;
	}

	/* generate result */
	uint64_t result = mt[_state->mti++];
	result ^= (result>>29) & UINT64_C(0x5555555555555555);
	result ^= (result<<17) & UINT64_C(0x71D67FFFEDA60000);
	result ^= (result<<37) & UINT64_C(0xFFF7EEE000000000);
	result ^= (result>>43);
	return result;
}

size_t cul_rng_mt19937_64_get(void *state) {
	if( SIZE_MAX < CUL_RNG_MT19937_64_MAX )
		return cul_rng_mt19937_64_sample(state) * ((double)SIZE_MAX/(double)CUL_RNG_MT19937_64_MAX );
	return cul_rng_mt19937_64_sample(state);
}

double cul_rng_mt19937_64_get_real(void *state) {
	/* use maximum possible double precision */
	return (cul_rng_mt19937_64_get(state)>>11) / (9007199254740992.0);
}

/* clear macros */

#undef NN
#undef MM
#undef UPPER_MASK
#undef LOWER_MASK

/* internal helper function */
static inline size_t _cul_rng_max(const CulRng *rng) {
	switch( rng->type ) {
		case CUL_RNG_RAND:       return (SIZE_MAX < CUL_RNG_RAND_MAX)? SIZE_MAX: CUL_RNG_RAND_MAX;
		case CUL_RNG_MT19937:    return (SIZE_MAX < CUL_RNG_MT19937_MAX)? SIZE_MAX: CUL_RNG_MT19937_MAX;
		case CUL_RNG_MT19937_64: return (SIZE_MAX < CUL_RNG_MT19937_64_MAX)? SIZE_MAX: CUL_RNG_MT19937_64_MAX;
		default:                 return 0;
	}
}

/* internal helper function, have to be at the end for sizeof operator */
static inline size_t _cul_rng_size(const CulRng *rng) {
	switch( rng->type ) {
		case CUL_RNG_RAND:       return 0;
		case CUL_RNG_MT19937:    return sizeof(_CulRngState_mt19937);
		case CUL_RNG_MT19937_64: return sizeof(_CulRngState_mt19937_64);
		default:                 return 0;
	}
}
