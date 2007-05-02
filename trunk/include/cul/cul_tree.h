#if !defined(CUL_TREE_H)
#define CUL_TREE_H

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

/* Allocation */

static inline CulTree *cul_tree_new_struct(void);
static inline void cul_tree_free_struct(CulTree *t);
static inline CulTree *cul_tree_init_struct(CulTree *t, CulTree *parent, CulTree *next, CulTree *prev, CulTree *child, cul_ptr data);

CulTree *cul_tree_new(void);
void cul_tree_free(CulTree *t, cul_free_f *free_f);
void cul_tree_free_all(CulTree *t, cul_free_f *free_f);

/* Basic Tree Operators */

static inline CulTree *cul_tree_parent(CulTree *t);
static inline CulTree *cul_tree_child(CulTree *t);
static inline CulTree *cul_tree_next(CulTree *t);
static inline CulTree *cul_tree_prev(CulTree *t);
CulTree *cul_tree_first(CulTree *t);
CulTree *cul_tree_last(CulTree *t);
CulTree *cul_tree_root(CulTree *t);

/* Resize */

CulTree *cul_tree_insert_next(CulTree *t, cul_ptr data);
CulTree *cul_tree_insert_prev(CulTree *t, cul_ptr data);
CulTree *cul_tree_insert_child_first(CulTree *t, cul_ptr data);
CulTree *cul_tree_insert_child_last(CulTree *t, cul_ptr data);

/* implementations */

static inline CulTree *cul_tree_new_struct(void) {
	return cul_slab_new(sizeof(CulTree));
}

static inline void cul_tree_free_struct(CulTree *t) {
	cul_slab_free(sizeof(CulTree), t);
}

static inline CulTree *cul_tree_init_struct(CulTree *t, CulTree *parent, CulTree *next, CulTree *prev, CulTree *child, cul_ptr data) {
	t->data = data;
	t->parent = parent;
	t->next = next;
	t->prev = prev;
	t->child = child;
	return t;
}

static inline CulTree *cul_tree_parent(CulTree *t) {
	return t->parent;
}

static inline CulTree *cul_tree_child(CulTree *t) {
	return t->child;
}

static inline CulTree *cul_tree_next(CulTree *t) {
	return t->next;
}

static inline CulTree *cul_tree_prev(CulTree *t) {
	return t->prev;
}

#endif
