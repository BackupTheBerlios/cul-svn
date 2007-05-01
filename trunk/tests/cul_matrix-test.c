#include <cul/cul_global.h>
#include <cul/cul_matrix.h>

const size_t size_x = 10;
const size_t size_y = 10;

int main(int argc, char* argv[]) {
	CulDMatrix *m1, *m2, *merge;

	m1 = cul_dmatrix_new(size_x, size_y);
	m2 = cul_dmatrix_new(size_x, size_y);

	merge = cul_dmatrix_new_empty();
	cul_dmatrix_resize_empty(merge, 2*size_x, size_y);

	cul_dmatrix_copy_offset(merge, m1, 0, 0);
	cul_dmatrix_copy_offset(merge, m2, size_x, 0);

	cul_dmatrix_free(merge);

	merge = cul_dmatrix_new_empty();
	cul_dmatrix_resize_empty(merge, size_x, 2*size_y);

	cul_dmatrix_copy_offset(merge, m1, 0, 0);
	cul_dmatrix_copy_offset(merge, m2, 0, size_y);

	cul_dmatrix_free(merge);

	cul_dmatrix_free(m1);
	cul_dmatrix_free(m2);

	return 0;
}
