#include <cul/cul_tree.h>

CulTree *cul_tree_new(void) {
	CulTree *t;
	if( (t = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( cul_tree_init(t) == NULL ) {
		cul_tree_free_struct(t);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return t;
}

CulTree *cul_tree_init(CulTree *t) {
	return cul_tree_init_struct(t, NULL, NULL, NULL, NULL, NULL);
}

void cul_tree_free(CulTree *t, cul_free_f *free_item) {
	if( t != NULL && free_item != NULL )
		free_item(t->data);
	cul_tree_free_struct(t);
}

void cul_tree_free_all(CulTree *t, cul_free_f *free_item) {
	CUL_UNUSED(t);
	CUL_UNUSED(free_item);
}
