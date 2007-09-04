#include <cul/cul_global.h>
#include <cul/cul_rng.h>
#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

const size_t length = 101;
const size_t alphabet = 26;

int main(int argc, char* argv[]) {
	/* initialize rng */
	CulRng *rng = cul_rng_new(CUL_RNG_MT19937);
	cul_rng_seed(rng, cul_rng_seed_32(1));

	{ /* test tolower, toupper and islower, isupper functions */
		char lower[length], upper[length],
			lower_lower[length], upper_upper[length],
			lower_upper[length], upper_lower[length];

		for(size_t i = 0, random; i < length - 1; ++i) {
			random = (size_t)(cul_rng_get_real(rng) * alphabet);
			lower[i] = 'a' + random;
			upper[i] = 'A' + random;
		}

		lower[length - 1] = CUL_STR_NULL;
		upper[length - 1] = CUL_STR_NULL;

		strcpy(lower_lower, lower);
		strcpy(lower_upper, lower);
		CUL_ASSERT( strcmp(cul_strtolower(lower_lower), lower) == 0 );
		CUL_ASSERT( strcmp(cul_strtoupper(lower_upper), upper) == 0 );

		strcpy(upper_upper, upper);
		strcpy(upper_lower, upper);
		CUL_ASSERT( strcmp(cul_strtoupper(upper_upper), upper) == 0 );
		CUL_ASSERT( strcmp(cul_strtolower(upper_lower), lower) == 0 );
	}

	{ /* test cul_strdup and cul_strndup */
		char base[length], *dup;
		for(size_t i = 0, random; i < length - 1; ++i) {
			char character;
			while( !cul_isprint(character = (char)(cul_rng_get_real(rng) * CHAR_MAX + 1)) );
			base[i] = character;
		}

		base[length - 1] = CUL_STR_NULL;

		dup = cul_strdup(base);
		CUL_ASSERT( strcmp(base, dup) == 0 );
		free(dup);

		for(size_t i = 0; i < length; ++i) {
			size_t size = (size_t)(cul_rng_get_real(rng) * length);
			dup = cul_strndup(base, size);
			CUL_ASSERT( strncmp(base, dup, size) == 0 );
			free(dup);
		}
	}

	cul_rng_free(rng);
	return 0;
}
