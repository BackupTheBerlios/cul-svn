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

static inline CulBBTree     *_cul_bbtree_new_struct      ();
static inline void           _cul_bbtree_free_struct     (CulBBTree *this);
static inline CulBBTree     *_cul_bbtree_init_struct     (CulBBTree *this, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth);

static inline CulBBTreeNode *_cul_bbtree_node_new_struct ();
static inline void           _cul_bbtree_node_free_struct(CulBBTreeNode *node);
static inline CulBBTreeNode *_cul_bbtree_node_init_struct(CulBBTreeNode *node, cul_ptr data, CulBBTreeNode *left, CulBBTreeNode *right, uint16_t depth, cul_bool is_left, cul_bool is_right);

static inline CulBBTree *_cul_bbtree_new_struct() {
	return cul_slab_new(sizeof(CulBBTree));
}

static inline void _cul_bbtree_free_struct(CulBBTree *this) {
	cul_slab_free(sizeof(CulBBTree), this);
}

static inline CulBBTree *_cul_bbtree_init_struct(CulBBTree *this, CulBBTreeNode *root, cul_cmp_f *cmp, size_t nodes, uint16_t depth) {
	this->root = root;
	this->cmp = cmp;
	this->nodes = nodes;
	this->depth = depth;
	return this;
}

static inline CulBBTreeNode *_cul_bbtree_node_new_struct() {
	return cul_slab_new(sizeof(CulBBTreeNode));
}

static inline void _cul_bbtree_node_free_struct(CulBBTreeNode *node) {
	cul_slab_free(sizeof(CulBBTreeNode), node);
}

static inline CulBBTreeNode *_cul_bbtree_node_init_struct(CulBBTreeNode *node, cul_ptr data, CulBBTreeNode *left, CulBBTreeNode *right, uint16_t depth, cul_bool is_left, cul_bool is_right) {
	node->data = data;
	node->left = left;
	node->right = right;
	node->depth = depth;
	node->is_left = is_left;
	node->is_right = is_right;
	return node;
}

CulBBTree *cul_bbtree_new(cul_cmp_f *cmp_f) {
	CulBBTree *this;
	if( (this = _cul_bbtree_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return _cul_bbtree_init_struct(this, NULL, cmp_f, 0, 0);
}

void cul_bbtree_free(CulBBTree *this, cul_free_f *free_f) {
	CulBBTreeNode *node, *next;

	if( this != NULL ) {
		node = cul_bbtree_first(this);

		for( ; node != NULL; node = next) {
			next = cul_bbtree_node_next(node);
			if( free_f != NULL )
				free_f(node->data);
			_cul_bbtree_node_free_struct(node);
		}

		_cul_bbtree_free_struct(this);
	}
}

CulBBTreeNode *cul_bbtree_insert(CulBBTree *this, cul_ptr data) {
	CUL_UNUSED(this);
	CUL_UNUSED(data);
	/* TODO cul_bbtree_insert stub */
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

cul_bool cul_bbtree_remove(CulBBTree *this, cul_ptr data, cul_free_f *free_f) {
	CUL_UNUSED(this);
	CUL_UNUSED(data);
	CUL_UNUSED(free_f);
	/* TODO cul_bbtree_remove stub */
	CUL_ERROR_ERRNO_RET(CUL_FALSE, CUL_ESTUB);
}

cul_bool cul_bbtree_remove_node(CulBBTree *this, CulBBTreeNode *node, cul_free_f *free_f) {
	CUL_UNUSED(this);
	CUL_UNUSED(node);
	CUL_UNUSED(free_f);
	/* TODO cul_bbtree_remove_node stub */
	CUL_ERROR_ERRNO_RET(CUL_FALSE, CUL_ESTUB);
}

CulBBTreeNode *cul_bbtree_find(const CulBBTree *this, cul_ptr data) {
	CulBBTreeNode *node = this->root;
	cul_cmp_f *cmp_f = this->cmp;
	int cmp;

	while( CUL_TRUE ) {
		if( (cmp = cmp_f(node->data, data)) == 0 )
			return node;
		else if( cmp < 0 ) {
			if( !node->is_right )
				return NULL;
			node = node->right;
		} else {
			if( !node->is_left )
				return NULL;
			node = node->left;
		}
	}
	return NULL;
}

void cul_bbtree_each(CulBBTree *this, cul_each_f *each_f, cul_ptr user_data) {
	CulBBTreeNode *node = cul_bbtree_first(this);
	for(; node != NULL; node = cul_bbtree_node_next(node))
		each_f(node->data, user_data);
}

CulBBTreeNode *cul_bbtree_node_first(CulBBTree *this) {
	CulBBTreeNode *node = this->root;

	if( node == NULL )
		return NULL;

	while( node->is_left )
		node = node->left;

	return node;
}

CulBBTreeNode *cul_bbtree_node_last(CulBBTree *this) {
	CulBBTreeNode *node = this->root;

	if( node == NULL )
		return NULL;

	while( node->is_right )
		node = node->right;

	return node;
}

CulBBTreeNode *cul_bbtree_node_next(CulBBTreeNode *node) {
	if( node->is_right ) {
		node = node->right;
		while( node->is_left )
			node = node->left;
	} else
		node = node->right;

	return node;
}

CulBBTreeNode *cul_bbtree_node_prev(CulBBTreeNode *node) {
	if( node->is_left ) {
		node = node->left;
		while( node->is_right )
			node = node->right;
	} else
		node = node->left;

	return node;
}

cul_ptr *cul_bbtree_node_data(CulBBTreeNode *node) {
	return node->data;
}
