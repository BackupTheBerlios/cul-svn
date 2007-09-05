#include <cul/cul_bbtree.h>

struct _CulBBTree {
	CulBBTreeNode *root;
	cul_cmp_f *cmp;
	size_t nodes;
	uint16_t depth;
};

struct _CulBBTreeNode {
	cul_ptr data;
	CulBBTreeNode *left;
	CulBBTreeNode *right;
	uint16_t depth;
	uint16_t is_left : 1;
	uint16_t is_right : 1;
};

static inline CulBBTree     *_cul_bbtree_new_struct(void);
static inline void           _cul_bbtree_free_struct(CulBBTree *t);
static inline CulBBTree     *_cul_bbtree_init_struct(CulBBTree *t, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth);

static inline CulBBTreeNode *_cul_bbtree_node_new_struct(void);
static inline void           _cul_bbtree_node_free_struct(CulBBTreeNode *tn);
static inline CulBBTreeNode *_cul_bbtree_node_init_struct(CulBBTreeNode *tn, cul_ptr data, CulBBTreeNode *left, CulBBTreeNode *right, uint16_t depth, cul_bool is_left, cul_bool is_right);

static inline CulBBTree *_cul_bbtree_new_struct(void) {
	return cul_slab_new(sizeof(CulBBTree));
}

static inline void _cul_bbtree_free_struct(CulBBTree *t) {
	cul_slab_free(sizeof(CulBBTree), t);
}

static inline CulBBTree *_cul_bbtree_init_struct(CulBBTree *t, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth) {
	t->root = root;
	t->cmp = cmp;
	t->nodes = nodes;
	t->depth = depth;
	return t;
}

static inline CulBBTreeNode *_cul_bbtree_node_new_struct(void) {
	return cul_slab_new(sizeof(CulBBTreeNode));
}

static inline void _cul_bbtree_node_free_struct(CulBBTreeNode *tn) {
	cul_slab_free(sizeof(CulBBTreeNode), tn);
}

static inline CulBBTreeNode *_cul_bbtree_node_init_struct(CulBBTreeNode *tn, cul_ptr data, CulBBTreeNode *left, CulBBTreeNode *right, uint16_t depth, cul_bool is_left, cul_bool is_right) {
	tn->data = data;
	tn->left = left;
	tn->right = right;
	tn->depth = depth;
	tn->is_left = is_left;
	tn->is_right = is_right;
	return tn;
}

CulBBTree *cul_bbtree_new(cul_cmp_f *cmp) {
	CulBBTree *t;
	if( (t = _cul_bbtree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return _cul_bbtree_init_struct(t, NULL, cmp, 0, 0);
}

void cul_bbtree_free(CulBBTree *t, cul_free_f *free_f) {
	CulBBTreeNode *tn, *tn_next;

	if( t != NULL ) {
		tn = cul_bbtree_node_first(t);

		for( ; tn != NULL; tn = tn_next) {
			tn_next = cul_bbtree_node_next(tn);
			if( free_f != NULL )
				free_f(tn->data);
			_cul_bbtree_node_free_struct(tn);
		}

		_cul_bbtree_free_struct(t);
	}
}

CulBBTreeNode *cul_bbtree_insert(CulBBTree *t, cul_ptr data) {
	CUL_UNUSED(t);
	CUL_UNUSED(data);
	/* TODO cul_bbtree_insert stub */
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

cul_bool cul_bbtree_remove(CulBBTree *t, cul_ptr data) {
	CUL_UNUSED(t);
	CUL_UNUSED(data);
	/* TODO cul_bbtree_remove stub */
	CUL_ERROR_ERRNO_RET(CUL_FALSE, CUL_ESTUB);
}

cul_bool cul_bbtree_remove_node(CulBBTree *t, CulBBTreeNode *tn) {
	CUL_UNUSED(t);
	CUL_UNUSED(tn);
	/* TODO cul_bbtree_remove_node stub */
	CUL_ERROR_ERRNO_RET(CUL_FALSE, CUL_ESTUB);
}

CulBBTreeNode *cul_bbtree_find(const CulBBTree *t, cul_ptr data) {
	CulBBTreeNode *tn = t->root;
	cul_cmp_f *cmp = t->cmp;
	int cmp_result;

	while( CUL_TRUE ) {
		if( (cmp_result = cmp(tn->data, data)) == 0 )
			return tn;
		else if( cmp_result < 0 ) {
			if( !tn->is_right )
				return NULL;
			tn = tn->right;
		}
		else {
			if( !tn->is_left )
				return NULL;
			tn = tn->left;
		}
	}
	return NULL;
}

void cul_bbtree_foreach(CulBBTree *t, cul_foreach_f *foreach_f, cul_ptr user_data) {
	CulBBTreeNode *tn = cul_bbtree_node_first(t);
	for(; tn != NULL; tn = cul_bbtree_node_next(tn))
		foreach_f(tn->data, user_data);
}

CulBBTreeNode *cul_bbtree_node_first(CulBBTree *t) {
	CulBBTreeNode *tn = t->root;

	if( tn == NULL )
		return NULL;

	while( tn->is_left )
		tn = tn->left;

	return tn;
}

CulBBTreeNode *cul_bbtree_node_last(CulBBTree *t) {
	CulBBTreeNode *tn = t->root;

	if( tn == NULL )
		return NULL;

	while( tn->is_right )
		tn = tn->right;

	return tn;
}

CulBBTreeNode *cul_bbtree_node_next(CulBBTreeNode *tn) {
	if( tn->is_right ) {
		tn = tn->right;
		while( tn->is_left )
			tn = tn->left;
	}
	else
		tn = tn->right;

	return tn;
}

CulBBTreeNode *cul_bbtree_node_prev(CulBBTreeNode *tn) {
	if( tn->is_left ) {
		tn = tn->left;
		while( tn->is_right )
			tn = tn->right;
	}
	else
		tn = tn->left;

	return tn;
}

cul_ptr *cul_bbtree_node_data(CulBBTreeNode *tn) {
	return tn->data;
}
