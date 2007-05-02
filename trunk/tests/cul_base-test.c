#include <cul/cul_global.h>
#include <cul/cul_base.h>

#include <stdlib.h>
#include <time.h>

const size_t size = 10000;

cul_bool test_permute(size_t *data, const size_t *permutation, size_t size);

int main(int argc, char* argv[]) {
	/* initialize standard random number generator */
	srand(time(NULL));
	/* get more verbose error messages */
	cul_error_fatal_set(CUL_FALSE);

	/* test permute */
	size_t *permutation = malloc(size*sizeof(size_t));

	/* identitity permutation */
	for( size_t i=0; i<size; ++i)
		permutation[i] = i;

	/* test data */
	size_t *data_rand = malloc(size*sizeof(size_t));
	size_t *data_identity = malloc(size*sizeof(size_t));

	/* initialize data */
	for( size_t i=0; i<size; ++i) {
		data_identity[i] = i;
		data_rand[i] = (size_t)(((double)rand()/(double)RAND_MAX)*size);
	}

	CUL_MESSAGE("Identity permutation test...\n");
	CUL_ASSERT( test_permute(data_identity, permutation, size) );
	CUL_ASSERT( test_permute(data_rand, permutation, size) );

	/* shuffle identitity permutation */
	for( size_t i=size-1; i>0; i--)
		cul_uswap_pos(permutation, i, (rand()/RAND_MAX) * (i+1));

	CUL_MESSAGE("Shuffled permutation test...\n");
	CUL_ASSERT( test_permute(data_identity, permutation, size) );
	CUL_ASSERT( test_permute(data_rand, permutation, size) );

	/* free all data */
	free(data_identity);
	free(data_rand);

	free(permutation);

	return 0;
}

cul_bool test_permute(size_t *data, const size_t *permutation, size_t size) {
	cul_bool is_error = CUL_FALSE;
	size_t *permute;

	/* allocate space for standard permutation */
	permute = malloc(size*sizeof(double));

	/* standard permutation */
	for( size_t i=0; i<size; ++i)
		permute[i] = data[ permutation[i] ];

	/* get permute */
	cul_upermute(data, permutation, size);

	/* check results */
	for( size_t i=0; i<size; ++i) if( permute[i] != data[i] ) {
		is_error = CUL_TRUE;
		break;
	}

	free(permute);
	return !is_error;
}
