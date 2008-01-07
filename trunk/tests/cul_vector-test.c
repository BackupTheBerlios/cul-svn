#include <cul/cul_global.h>
#include <cul/cul_vector.h>

#include <stdlib.h>
#include <time.h>

/* size has to be even */
const size_t size = 10000;

void     test_dvector_rand     (CulDVector *this);
cul_bool test_dvector_equal    (const CulDVector *this, const CulDVector *other);
cul_bool test_dvectorview_equal(const CulDVectorView *this, const CulDVectorView *other);

int main(int argc, char* argv[]) {
	/* initialize standard random number generator */
	srand(time(NULL));

	CulDVector *v, *base, *v1, *v2;
	CulDVectorView *vv, *vbase, *vv1, *vv2;

	/* create base vactors and views */
	v = cul_dvector_new(size);
	base = cul_dvector_new(size);
	vv = cul_dvectorview_new();
	vbase = cul_dvectorview_new();

	CUL_MESSAGE("Basic copy vector test...\n");
	test_dvector_rand(base);
	CUL_ASSERT( !cul_dvector_copy(v, base) );
	CUL_ASSERT( test_dvector_equal(base, v) );

	CUL_MESSAGE("Basic copy vector view test...\n");
	test_dvector_rand(base);
	cul_dvectorview_vector(vbase, base);
	cul_dvectorview_vector(vv, v);
	CUL_ASSERT( !cul_dvectorview_copy(vv, vbase) );
	CUL_ASSERT( test_dvectorview_equal(vbase, vv) );
	CUL_ASSERT( test_dvector_equal(base, v) );

	/* create additional vectors and views */
	v1 = cul_dvector_new(size / 2);
	v2 = cul_dvector_new(size / 2);

	CUL_MESSAGE("Advanced copy vector test...\n");
	test_dvector_rand(base);
	CUL_ASSERT( !cul_dvector_copy_subvector(v1, base, 0) );
	CUL_ASSERT( !cul_dvector_copy_subvector(v2, base, base->size / 2) );
	CUL_ASSERT( !cul_dvector_copy_offset(v, v1, 0) );
	CUL_ASSERT( !cul_dvector_copy_offset(v, v2, base->size / 2) );
	CUL_ASSERT( test_dvector_equal(base, v) );

	CUL_MESSAGE("Advanced copy vector view test...\n");
	test_dvector_rand(base);
	cul_dvectorview_subvector(vbase, base, 0, base->size / 2, 2);
	cul_dvectorview_subvector(vv, v, 0, v->size / 2, 2);
	CUL_ASSERT( !cul_dvectorview_copy(vv, vbase) );
	cul_dvectorview_subvector(vbase, base, 1, base->size / 2, 2);
	cul_dvectorview_subvector(vv, v, 1, v->size / 2, 2);
	CUL_ASSERT( !cul_dvectorview_copy(vv, vbase) );
	CUL_ASSERT( test_dvector_equal(base, v) );
	test_dvector_rand(base);
	cul_dvectorview_vector(vv, v);
	cul_dvectorview_copy_vector(vv, base);
	CUL_ASSERT( test_dvector_equal(base, v) );

	cul_dvector_free(v1);
	cul_dvector_free(v2);

	cul_dvectorview_free(vbase);
	cul_dvectorview_free(vv);

	cul_dvector_free(base);
	cul_dvector_free(v);
	return 0;
}

void test_dvector_rand(CulDVector *this) {
	const double max = 100.0;

	const size_t size = this->size;
	for(size_t i = 0; i < size; ++i) {
		size_t value = max * ((double)rand()/(double)RAND_MAX);
		cul_dvector_set(this, i, value);
	}
}

cul_bool test_dvector_equal(const CulDVector *this, const CulDVector *other) {
	if( this->size != other->size )
		return CUL_FALSE;

	const double *restrict data = this->data;
	const double *restrict other_data = other->data;

	const size_t size = this->size;
	for(size_t i = 0; i < size; ++i)
		if( data[i] != other_data[i] )
			return CUL_FALSE;

	return CUL_TRUE;
}

cul_bool test_dvectorview_equal(const CulDVectorView *this, const CulDVectorView *other) {
	if( this->size != other->size )
		return CUL_FALSE;

	const double *restrict data = this->data;
	const size_t stride = this->stride;
	const double *restrict other_data = other->data;
	const size_t other_stride = other->stride;

	const size_t size = stride * this->size;
	for(size_t i = 0, other_i = 0; i < size; i += stride, other_i += other_stride)
		if( data[i] != other_data[other_i] )
			return CUL_FALSE;

	return CUL_TRUE;
}

