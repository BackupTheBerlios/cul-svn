#include <cul/cul_global.h>
#include <cul/cul_vector.h>

#include <stdlib.h>
#include <time.h>

const size_t size = 10000;
const double max = 100;
const double value = 3.0;

cul_bool test_dvector_equal(const CulDVector *v1, const CulDVector *v2);
cul_bool test_dvectorview_equal(const CulDVectorView *v1, const CulDVectorView *v2);

int main(int argc, char* argv[]) {
	/* initialize standard random number generator */
	srand(time(NULL));

	CulDVector *v, *base, *v1, *v2;
	CulDVectorView *vv, *vbase, *vv1, *vv2;

	/* create base vactors and views */
	v = cul_dvector_new(size);
	base = cul_dvector_new(size);
	vv = cul_dvectorview_vector(NULL, v);
	vbase = cul_dvectorview_vector(NULL, base);

	/* we work on integer floating point variables */
	for(size_t x = 0; x < size; ++x)
		cul_dvector_set(base, x, (size_t)(max * ((double)rand()/(double)RAND_MAX)));

	CUL_MESSAGE("Basic copy vector operations test...\n");
	CUL_ASSERT( !cul_dvector_copy(v, base) );
	CUL_ASSERT( test_dvector_equal(base, v) );
	cul_dvector_zero(v);
	CUL_ASSERT( !cul_dvectorview_copy(vv, vbase) );
	CUL_ASSERT( test_dvectorview_equal(vbase, vv) );
	CUL_ASSERT( test_dvector_equal(base, v) );

	/* create additional vectors and views */
	v1 = cul_dvector_new(size >> 1);
	v2 = cul_dvector_new(size >> 1);

	CUL_MESSAGE("Advanced copy vector operations test...\n");
	CUL_ASSERT( !cul_dvector_copy_subvector(v1, base, 0) );
	CUL_ASSERT( !cul_dvector_copy_subvector(v2, base, size >> 1) );
	CUL_ASSERT( !cul_dvector_copy_offset(v, v1, 0) );
	CUL_ASSERT( !cul_dvector_copy_offset(v, v2, size >> 1) );
	CUL_ASSERT( test_dvector_equal(base, v) );

	/* resize vectors, don't copy contents */
	cul_dvector_resize_empty(v1, size);
	cul_dvector_resize_empty(v2, size);
	vv1 = cul_dvectorview_vector(NULL, v1);
	vv2 = cul_dvectorview_vector(NULL, v2);

	/* check arithmetic operations */
	CulDVector *arithmetic = cul_dvector_new(size);
	CulDVectorView *varithmetic = cul_dvectorview_vector(NULL, arithmetic);
	cul_dvector_set_all(arithmetic, value);

	/* initialize vectors */
	cul_dvector_copy(v1, base);
	cul_dvector_copy(v2, base);

	CUL_MESSAGE("Basic vector arithmetic test...\n");
	cul_dvector_add(v1, arithmetic);
	cul_dvector_add_constant(v2, value);
	CUL_ASSERT( test_dvector_equal(v1, v2) );

	cul_dvector_copy(v1, base);
	cul_dvector_copy(v2, base);
	cul_dvectorview_add(vv1, varithmetic);
	cul_dvectorview_add_constant(vv2, value);
	CUL_ASSERT( test_dvectorview_equal(vv1, vv2) );


	cul_dvectorview_free(varithmetic);
	cul_dvector_free(arithmetic);

	cul_dvectorview_free(vv1);
	cul_dvectorview_free(vv2);

	cul_dvector_free(v1);
	cul_dvector_free(v2);

	cul_dvectorview_free(vbase);
	cul_dvectorview_free(vv);

	cul_dvector_free(base);
	cul_dvector_free(v);
	return 0;
}

cul_bool test_dvector_equal(const CulDVector *v1, const CulDVector *v2) {
	if( v1->size != v2->size )
		return CUL_FALSE;

	for(size_t x = 0; x < v1->size; ++x)
		if( cul_dvector_get(v1, x) != cul_dvector_get(v2, x) )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool test_dvectorview_equal(const CulDVectorView *v1, const CulDVectorView *v2) {
	if( v1->size != v2->size )
		return CUL_FALSE;

	for(size_t x = 0; x < v1->size; ++x)
		if( cul_dvectorview_get(v1, x) != cul_dvectorview_get(v2, x) )
			return CUL_FALSE;

	return CUL_TRUE;
}

