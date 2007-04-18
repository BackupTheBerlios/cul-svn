#ifndef CUL_BBTREE_H
#define CUL_BBTREE_H

#include <cul/cul_global.h>

#define CUL_BBTREE(ptr)     ((CulBBTree *)(ptr))
#define CUL_BBTREENODE(ptr) ((CulBBTreeNode *)(ptr))

typedef struct _CulBBTree     CulBBTree;
typedef struct _CulBBTreeNode CulBBTreeNode;

CulBBTree *cul_bbtree_new(cul_cmp_f *cmp);
void cul_bbtree_free(CulBBTree *t, cul_free_f *free_node);

size_t cul_bbtree_nodes(const CulBBTree *t);

CulBBTreeNode *cul_bbtree_insert(CulBBTree *t, cul_ptr data);

cul_bool cul_bbtree_remove(CulBBTree *t, cul_ptr data);
cul_bool cul_bbtree_remove_node(CulBBTree *t, CulBBTreeNode *tn);

CulBBTreeNode *cul_bbtree_find(const CulBBTree *t, cul_ptr data);
size_t cul_bbtree_foreach(CulBBTree *t, cul_foreach_f *foreach);

CulBBTreeNode *cul_bbtree_node_first(CulBBTree *t);
CulBBTreeNode *cul_bbtree_node_last(CulBBTree *t);
CulBBTreeNode *cul_bbtree_node_next(CulBBTreeNode *tn);
CulBBTreeNode *cul_bbtree_node_prev(CulBBTreeNode *tn);
cul_ptr *cul_bbtree_node_data(CulBBTreeNode *tn);

#endif /* CUL_BBTREE_H */
