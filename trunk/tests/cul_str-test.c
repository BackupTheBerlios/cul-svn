#include <cul/cul_global.h>
#include <cul/cul_rng.h>
#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

#include <stdio.h>
#include <string.h>

const size_t length = 101;
const size_t alphabet = 26;

int main(int argc, char* argv[]) {
	/* initialize rng */
	CulRng *rng = cul_rng_new(CUL_RNG_MT19937);
	cul_rng_seed(rng, cul_rng_seed_32(1));

	/* check islower */
	for(size_t i = 0x60; i <= 0x80; ++i) {
		printf("%c(%d)",i, cul_islower(i));
	}
	printf("\n");

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

	cul_rng_free(rng);
	return 0;
}
