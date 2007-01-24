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
CulTree *cul_tree_init(CulTree *t);
void cul_tree_free(CulTree *t, cul_free_f *free_item);
void cul_tree_free_all(CulTree *t, cul_free_f *free_item);

/* implementations */

static inline CulTree *cul_tree_new_struct(void) {
	return cul_slab_new(sizeof(CulTree));
}

static inline void cul_tree_free_struct(CulTree *const t) {
	cul_slab_free(sizeof(CulTree), t);
}

static inline CulTree *cul_tree_init_struct(CulTree *const t, CulTree *parent, CulTree *next, CulTree *prev, CulTree *child, cul_ptr data) {
	t->data = data;
	t->parent = parent;
	t->next = next;
	t->prev = prev;
	t->child = child;
	return t;
}

#endif
