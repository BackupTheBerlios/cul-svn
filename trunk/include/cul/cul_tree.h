#ifndef __CUL_TREE_H__
#define __CUL_TREE_H__

#include <cul/cul_global.h>

#define CUL_TREE(ptr) ((CulTree *)(ptr)

typedef struct _CulTree CulTree;

struct _CulTree {
	cul_ptr data;       /* data associated with tree node */
	CulTree *next;      /* next sibling */
	CulTree *prev;      /* previous sibling */
	CulTree *parent;    /* parent node */
	CulTree *child;     /* child node */
};

static inline CulTree *cul_tree_new_struct ();
static inline void     cul_tree_free_struct(CulTree *tree);
static inline CulTree *cul_tree_init_struct(CulTree *tree, cul_ptr data, CulTree *parent, CulTree *next, CulTree *prev, CulTree *child);

CulTree *cul_tree_new               ();
void     cul_tree_free              (CulTree *tree, cul_free_f *free_f);
void     cul_tree_free_all          (CulTree *tree, cul_free_f *free_f);

CulTree *cul_tree_first             (CulTree *tree);
CulTree *cul_tree_last              (CulTree *tree);
CulTree *cul_tree_nth               (CulTree *tree, size_t n);
CulTree *cul_tree_nth_last          (CulTree *tree, size_t n);
size_t   cul_tree_size              (CulTree *tree);
CulTree *cul_tree_root              (CulTree *tree);
size_t   cul_tree_level             (CulTree *tree);

CulTree *cul_tree_insert_next       (CulTree *tree, cul_ptr data);
CulTree *cul_tree_insert_prev       (CulTree *tree, cul_ptr data);
CulTree *cul_tree_insert_child_first(CulTree *tree, cul_ptr data);
CulTree *cul_tree_insert_child_last (CulTree *tree, cul_ptr data);
CulTree *cul_tree_remove            (CulTree *tree, cul_free_f *free_f);

CulTree *cul_tree_copy              (CulTree *tree);
CulTree *cul_tree_detach            (CulTree *tree, cul_clone_f *clone_f);
CulTree *cul_tree_reverse           (CulTree *tree);
CulTree *cul_tree_reverse_level     (CulTree *tree);

/* implementations */

static inline CulTree *cul_tree_new_struct() {
	return cul_slab_new(sizeof(CulTree));
}

static inline void cul_tree_free_struct(CulTree *tree) {
	cul_slab_free(sizeof(CulTree), tree);
}

static inline CulTree *cul_tree_init_struct(CulTree *tree, cul_ptr data, CulTree *parent, CulTree *next, CulTree *prev, CulTree *child) {
	tree->data = data;
	tree->parent = parent;
	tree->next = next;
	tree->prev = prev;
	tree->child = child;
	return tree;
}

#endif /* __CUL_TREE_H__ */
