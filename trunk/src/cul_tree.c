#include <cul/cul_tree.h>

CulTree *cul_tree_new(void) {
	CulTree *t;
	if( (t = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	return cul_tree_init_struct(t, NULL, NULL, NULL, NULL, NULL);
}

void cul_tree_free(CulTree *t, cul_free_f *free_f) {
	if( t != NULL && free_f != NULL )
		free_f(t->data);
	cul_tree_free_struct(t);
}

void cul_tree_free_all(CulTree *t, cul_free_f *free_f) {
	for( CulTree *n; t != NULL; t = n) {
		n = cul_tree_next(t);

		/* free childs */
		cul_tree_free_all(cul_tree_child(t), free_f);

		/* free itself */
		if( free_f != NULL )
			free_f(t->data);
		cul_tree_free_struct(t);
	}
}

CulTree *cul_tree_first(CulTree *t) {
	if( t != NULL )
		while( cul_tree_prev(t) != NULL )
			t = cul_tree_prev(t);
	return t;
}

CulTree *cul_tree_last(CulTree *t) {
	if( t != NULL )
		while( cul_tree_next(t) != NULL )
			t = cul_tree_next(t);
	return t;
}

CulTree *cul_tree_root(CulTree *t) {
	if( t != NULL )
		while( cul_tree_parent(t) != NULL )
			t = cul_tree_parent(t);
	return t;
}

CulTree *cul_tree_insert_next(CulTree *t, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( t != NULL ) {
		CulTree *next = cul_tree_next(t);

		cul_tree_init_struct(n, t->parent, next, t, NULL, data);
		/* adjust tree pointers */
		if( next != NULL )
			next->prev = n;
		t->next = n;
	}
	else
		cul_tree_init_struct(n, NULL, NULL, NULL, NULL, data);
	return n;
}

CulTree *cul_tree_insert_prev(CulTree *t, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( t != NULL ) {
		CulTree *prev = cul_tree_prev(t);

		cul_tree_init_struct(n, t->parent, t, prev, NULL, data);
		/* adjust tree pointers */
		if( prev != NULL )
			prev->next = n;
		else
			cul_tree_parent(t)->child = n;
		t->prev = n;
	}
	else
		cul_tree_init_struct(n, NULL, NULL, NULL, NULL, data);
	return n;
}

CulTree *cul_tree_insert_child_first(CulTree *t, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( t != NULL ) {
		CulTree *child = cul_tree_child(t);

		cul_tree_init_struct(n, t, child, NULL, NULL, data);
		/* adjust tree pointers */
		if( child != NULL )
			child->prev = n;
		t->child = n;
	}
	else
		cul_tree_init_struct(n, NULL, NULL, NULL, NULL, data);
	return n;
}

CulTree *cul_tree_insert_child_last(CulTree *t, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( t != NULL ) {
		CulTree *child = cul_tree_last(cul_tree_child(t));

		cul_tree_init_struct(n, t, NULL, child, NULL, data);
		/* adjust tree pointers */
		if( child != NULL )
			child->next = n;
	}
	else
		cul_tree_init_struct(n, NULL, NULL, NULL, NULL, data);
	return n;
}
