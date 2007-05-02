#include <cul/cul_global.h>
#include <cul/cul_matrix.h>

#include <stdlib.h>
#include <time.h>

const size_t size_x = 10;
const size_t size_y = 10;

cul_bool test_matrixview_equal(const CulDMatrixView *va, const CulDMatrixView *vb);

int main(int argc, char* argv[]) {
	CulDMatrix *m1, *m2, *merge;
	CulDMatrixView *mv1 = NULL, *mv2 = NULL, *mergev = NULL;

	/* initialize standard random number generator */
	srand(time(NULL));
	/* get more verbose error messages */
	cul_error_fatal_set(CUL_FALSE);

	/* allocate matrices and views */
	m1 = cul_dmatrix_new(size_x, size_y);
	m2 = cul_dmatrix_new(size_x, size_y);

	mv1 = cul_dmatrixview_matrix(mv1, m1);
	mv2 = cul_dmatrixview_matrix(mv2, m2);
	mergev = cul_dmatrixview_new();

	/* initilize random numer generator */

	/* initialize matrices */
	for( size_t x=0; x<size_x; ++x) for( size_t y=0; y<size_y; ++y) {
		cul_dmatrix_set(m1, x, y, (double)rand()/(double)RAND_MAX);
		cul_dmatrix_set(m2, x, y, (double)rand()/(double)RAND_MAX);
	}

	/* test vertical copy */
	merge = cul_dmatrix_new_empty();
	cul_dmatrix_resize_empty(merge, 2*size_x, size_y);

	cul_dmatrix_copy_offset(merge, m1, 0, 0);
	cul_dmatrix_copy_offset(merge, m2, size_x, 0);

	CUL_MESSAGE("Vertical matrix copy test...\n");
	CUL_ASSERT( cul_dmatrixview_submatrix(mergev, merge, 0, 0, size_x, size_y) != NULL );
	CUL_ASSERT( test_matrixview_equal(mv1, mergev) );
	CUL_ASSERT( cul_dmatrixview_submatrix(mergev, merge, size_x, 0, size_x, size_y) != NULL );
	CUL_ASSERT( test_matrixview_equal(mv2, mergev) );

	cul_dmatrix_free(merge);

	/* test horizontal copy */
	merge = cul_dmatrix_new_empty();
	cul_dmatrix_resize_empty(merge, size_x, 2*size_y);

	cul_dmatrix_copy_offset(merge, m1, 0, 0);
	cul_dmatrix_copy_offset(merge, m2, 0, size_y);

	CUL_MESSAGE("Horizontal matrix copy test...\n");
	CUL_ASSERT( cul_dmatrixview_submatrix(mergev, merge, 0, 0, size_x, size_y) != NULL );
	CUL_ASSERT( test_matrixview_equal(mv1, mergev) );
	CUL_ASSERT( cul_dmatrixview_submatrix(mergev, merge, 0, size_y, size_x, size_y) != NULL );
	CUL_ASSERT( test_matrixview_equal(mv2, mergev) );

	cul_dmatrix_free(merge);

	/* free all views and matrices */
	cul_dmatrixview_free(mv1);
	cul_dmatrixview_free(mv2);
	cul_dmatrixview_free(mergev);

	cul_dmatrix_free(m1);
	cul_dmatrix_free(m2);

	return 0;
}

cul_bool test_matrixview_equal(const CulDMatrixView *va, const CulDMatrixView *vb) {
	if( va->size_x != vb->size_y || va->size_x != vb->size_y )
		return CUL_FALSE;

	const size_t size_x = va->size_x;
	const size_t size_y = va->size_y;
	for( size_t x=0; x<size_x; ++x) for( size_t y=0; y<size_y; ++y)
		if( cul_dmatrixview_get(va, x, y) != cul_dmatrixview_get(vb, x, y) )
			return CUL_FALSE;
	return CUL_TRUE;
}
