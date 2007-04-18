#include <cul/cul_bbtree.h>

struct _CulBBTree {
	CulBBTreeNode *root;
	cul_cmp_f *cmp;
	size_t nodes;
	uint16_t depth;
	uint16_t is_unique : 1;
};

struct _CulBBTreeNode {
	cul_ptr data;
	CulBBTreeNode *left;
	CulBBTreeNode *right;
	uint16_t depth;
	uint16_t is_left : 1;
	uint16_t is_right : 1;
};

static inline CulBBTree *cul_bbtree_new_struct(void);
static inline void cul_bbtree_free_struct(CulBBTree *t);
static inline CulBBTree *cul_bbtree_init_struct(CulBBTree *t, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth, cul_bool is_unique);

static inline CulBBTreeNode *cul_bbtree_node_new_struct(void);
static inline void cul_bbtree_node_free_struct(CulBBTreeNode *tn);

static inline CulBBTree *cul_bbtree_new_struct(void) {
	return cul_slab_new(sizeof(CulBBTree));
}

static inline void cul_bbtree_free_struct(CulBBTree *t) {
	cul_slab_free(sizeof(CulBBTree), t);
}

static inline CulBBTree *cul_bbtree_init_struct(CulBBTree *t, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth, cul_bool is_unique) {
	t->root = root;
	t->cmp = cmp;
	t->nodes = nodes;
	t->depth = depth;
	t->is_unique = is_unique;
	return t;
}

static inline CulBBTreeNode *cul_bbtree_node_new_struct(void) {
	return cul_slab_new(sizeof(CulBBTreeNode));
}

static inline void cul_bbtree_node_free_struct(CulBBTreeNode *tn) {
	cul_slab_free(sizeof(CulBBTreeNode), tn);
}

CulBBTree *cul_bbtree_new(cul_cmp_f *cmp) {
	CulBBTree *t;
	if( (t = cul_bbtree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	return cul_bbtree_init_struct(t, NULL, cmp, 0, 0, CUL_TRUE);
}

void cul_bbtree_free(CulBBTree *t, cul_free_f *free_data) {
	CulBBTreeNode *tn, *tn_next;

	if( t != NULL ) {
		tn = cul_bbtree_node_first(t);

		for( ; tn != NULL; tn = tn_next) {
			tn_next = cul_bbtree_node_next(tn);
			if( free_data != NULL )
				free_data(tn->data);
			cul_bbtree_node_free_struct(tn);
		}

		cul_bbtree_free_struct(t);
	}
}

CulBBTreeNode *cul_bbtree_insert(CulBBTree *t, cul_ptr data) {
	CUL_UNUSED(t);
	CUL_UNUSED(data);
	return NULL;
}

cul_bool cul_bbtree_remove(CulBBTree *t, cul_ptr data) {
	CUL_UNUSED(t);
	CUL_UNUSED(data);
	return CUL_FALSE;
}

cul_bool cul_bbtree_remove_node(CulBBTree *t, CulBBTreeNode *tn) {
	CUL_UNUSED(t);
	CUL_UNUSED(tn);
	return CUL_FALSE;
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

size_t cul_bbtree_foreach(CulBBTree *t, cul_foreach_f *foreach) {
	CulBBTreeNode *tn;
	size_t i_foreach = 0;

	tn = cul_bbtree_node_first(t);
	for( ; tn != NULL; tn = cul_bbtree_node_next(tn), ++i_foreach )
		if( foreach(tn->data) )
			break;

	return i_foreach;
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
