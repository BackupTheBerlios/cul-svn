#ifndef __CUL_BBTREE_H__
#define __CUL_BBTREE_H__

#include <cul/cul_global.h>

#define CUL_BBTREE(ptr)     ((CulBBTree *)(ptr))
#define CUL_BBTREENODE(ptr) ((CulBBTreeNode *)(ptr))

typedef struct _CulBBTree     CulBBTree;
typedef struct _CulBBTreeNode CulBBTreeNode;

CulBBTree     *cul_bbtree_new         (cul_cmp_f *cmp_f);
void           cul_bbtree_free        (CulBBTree *t, cul_free_f *free_f);

size_t         cul_bbtree_nodes       (const CulBBTree *this);

CulBBTreeNode *cul_bbtree_insert      (CulBBTree *this, cul_ptr key, cul_ptr data);
cul_bool       cul_bbtree_remove      (CulBBTree *this, cul_ptr key, cul_free_f *free_f);
cul_bool       cul_bbtree_remove_node (CulBBTree *this, CulBBTreeNode *node, cul_free_f *free_f);

CulBBTreeNode *cul_bbtree_find        (const CulBBTree *this, cul_ptr key);
void           cul_bbtree_each_key    (CulBBTree *this, cul_each_key_f *each_f);
void           cul_bbtree_each_key_prv(CulBBTree *this, cul_each_key_prv_f *each_prv_f, cul_ptr prv);

CulBBTreeNode *cul_bbtree_first       (CulBBTree *this);
CulBBTreeNode *cul_bbtree_last        (CulBBTree *this);
CulBBTreeNode *cul_bbtree_node_next   (CulBBTreeNode *node);
CulBBTreeNode *cul_bbtree_node_prev   (CulBBTreeNode *node);
cul_ptr       *cul_bbtree_node_data   (CulBBTreeNode *node);

#endif /* __CUL_BBTREE_H__ */
