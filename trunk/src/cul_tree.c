#include <cul/cul_tree.h>

/* private functions */

static cul_bool _cul_tree_subcopy(CulTree *tree, CulTree *copy);

CulTree *cul_tree_new(void) {
	CulTree *tree;
	if( (tree = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_tree_init_struct(tree, NULL, NULL, NULL, NULL, NULL);
}

void cul_tree_free(CulTree *tree, cul_free_f *free_f) {
	if( tree != NULL && free_f != NULL )
		free_f(tree->data);
	cul_tree_free_struct(tree);
}

void cul_tree_free_all(CulTree *tree, cul_free_f *free_f) {
	for( CulTree *n; tree != NULL; tree = n) {
		n = tree->next;

		/* free childs */
		cul_tree_free_all(tree->child, free_f);

		/* free itself */
		if( free_f != NULL )
			free_f(tree->data);
		cul_tree_free_struct(tree);
	}
}

CulTree *cul_tree_first(CulTree *tree) {
	if( tree != NULL )
		while( tree->prev != NULL )
			tree = tree->prev;
	return tree;
}

CulTree *cul_tree_last(CulTree *tree) {
	if( tree != NULL )
		while( tree->next != NULL )
			tree = tree->next;
	return tree;
}

CulTree *cul_tree_nth(CulTree *tree, size_t n) {
	while( tree != NULL && n-- )
		tree = tree->next;
	return tree;
}

CulTree *cul_tree_root(CulTree *tree) {
	if( tree != NULL )
		while( tree->parent != NULL )
			tree = tree->parent;
	return tree;
}

CulTree *cul_tree_insert_next(CulTree *tree, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( tree != NULL ) {
		CulTree *next = tree->next;

		cul_tree_init_struct(n, data, tree->parent, next, tree, NULL);
		/* adjust tree pointers */
		if( next != NULL )
			next->prev = n;
		tree->next = n;
	}
	else
		cul_tree_init_struct(n, data, NULL, NULL, NULL, NULL);
	return n;
}

CulTree *cul_tree_insert_prev(CulTree *tree, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( tree != NULL ) {
		CulTree *prev = tree->prev;

		cul_tree_init_struct(n, data, tree->parent, tree, prev, NULL);
		/* adjust tree pointers */
		if( prev != NULL )
			prev->next = n;
		else if( tree->parent != NULL )
			tree->parent->child = n;
		tree->prev = n;
	}
	else
		cul_tree_init_struct(n, data, NULL, NULL, NULL, NULL);
	return n;
}

CulTree *cul_tree_insert_child_first(CulTree *tree, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( tree != NULL ) {
		CulTree *child = tree->child;

		cul_tree_init_struct(n, data, tree, child, NULL, NULL);
		/* adjust tree pointers */
		if( child != NULL )
			child->prev = n;
		tree->child = n;
	}
	else
		cul_tree_init_struct(n, data, NULL, NULL, NULL, NULL);
	return n;
}

CulTree *cul_tree_insert_child_last(CulTree *tree, cul_ptr data) {
	CulTree *n;
	if( (n = cul_tree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( tree != NULL ) {
		CulTree *child = cul_tree_last(tree->child);

		cul_tree_init_struct(n, data, tree, NULL, child, NULL);
		/* adjust tree pointers */
		if( child != NULL )
			child->next = n;
	}
	else
		cul_tree_init_struct(n, data, NULL, NULL, NULL, NULL);
	return n;
}

CulTree *cul_tree_remove(CulTree *tree, cul_free_f *free_f) {
	CUL_UNUSED(tree);
	CUL_UNUSED(free_f);
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

CulTree *cul_tree_remove_child_first(CulTree *tree, cul_free_f *free_f) {
	CUL_UNUSED(tree);
	CUL_UNUSED(free_f);
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

CulTree *cul_tree_remove_child_last(CulTree *tree, cul_free_f *free_f) {
	CUL_UNUSED(tree);
	CUL_UNUSED(free_f);
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

/*
 * copy all tree node childs to corresponding copy node
 * NOTE: on memory error no cleaning is done
 * CAUTION: tree and copy are assumend to be *NOT* NULL
 */
static cul_bool _cul_tree_subcopy(CulTree *tree, CulTree *copy) {
	CulTree *n;

	if( (tree = tree->child) == NULL )
		return CUL_TRUE;

	/* create first child */
	if( (n = cul_tree_insert_next(NULL, tree->data)) == NULL )
		return CUL_FALSE;

	/* adjust vertical links in tree for first child */
	copy->child = n;
	n->parent = copy;

	/* now we can safelu copy first child childs */
	if( !_cul_tree_subcopy(tree, n) )
		return CUL_FALSE;

	/* create and copy other childs */
	for(tree = tree->next; tree != NULL; tree = tree->next) {
		/* create next child */
		if( (n = cul_tree_insert_next(n, tree->data)) == NULL )
			return CUL_FALSE;

		/* adjust parent of child */
		n->parent = copy;

		/* copy all child childs */
		if( !_cul_tree_subcopy(tree, n) )
			return CUL_FALSE;
	}

	return CUL_TRUE;
}

CulTree *cul_tree_copy(CulTree *tree) {
	CulTree *root = NULL, *n, *t;
	if( tree != NULL ) {
		/* copy root node with all childs */
		if( (root = cul_tree_insert_next(NULL, tree->data)) == NULL ||
				!_cul_tree_subcopy(tree, root) ) {
			cul_tree_free_all(root, NULL);
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}

		/* copy other nodes at root level with all childs */
		for( n = root, t = tree->next; t != NULL; t = t->next)
			if( (n = cul_tree_insert_next(n, t->data)) == NULL ||
					!_cul_tree_subcopy(t, n) ) {
				cul_tree_free_all(root, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return root;
}

CulTree *cul_tree_copy_child(CulTree *tree) {
	CulTree *root = NULL;
	if( tree != NULL ) {
		/* copy root node with all childs */
		if( (root = cul_tree_insert_next(NULL, tree->data)) == NULL ||
				!_cul_tree_subcopy(tree, root) ) {
			cul_tree_free_all(root, NULL);
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return root;
}

CulTree *cul_tree_detach(CulTree *tree, cul_clone_f *clone_f) {
	CUL_UNUSED(tree);
	CUL_UNUSED(clone_f);
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

CulTree *cul_tree_reverse(CulTree *tree) {
	CulTree *last = NULL;
	while( tree != NULL ) {
		last = tree;

		/* process child nodes and adjust node child */
		tree->child = cul_tree_reverse(tree->child);

		/* swap nodes */
		tree = last->next;
		last->next = last->prev;
		last->prev = tree;
	}
	return last;
}

