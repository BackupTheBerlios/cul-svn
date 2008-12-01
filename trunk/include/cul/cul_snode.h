#ifndef __CUL_SNODE_H__
#define __CUL_SNODE_H__

#include <cul/cul_global.h>

typedef struct _CulSNode CulSNode;
struct _CulSNode {
    cul_ptr data;     /* data associated with element */
    CulSNode *next;   /* next element */
};

CulSNode               *cul_snode_new                 (cul_ptr data);
CulSNode               *cul_snode_new_empty           ();
void                    cul_snode_free                (CulSNode *node,
                                                       cul_free_f *free_f);
void                    cul_snode_init                (CulSNode *node,
                                                       cul_ptr data);
void                    cul_snode_init_empty          (CulSNode *node);

CulSNode               *cul_snode_last                (CulSNode *node);
CulSNode               *cul_snode_nth                 (CulSNode *node,
                                                       size_t n);
size_t                  cul_snode_size                (CulSNode *node,
                                                       CulSNode *end);

CulSNode               *cul_snode_insert_next         (CulSNode *node,
                                                       cul_ptr data);
CulSNode               *cul_snode_insert_prev         (CulSNode *node,
                                                       cul_ptr data);
CulSNode               *cul_snode_remove              (CulSNode *node,
                                                       cul_free_f *free_f);
static inline void      cul_snode_remove_next         (CulSNode *node,
                                                       cul_free_f *free_f);

CulSNode               *cul_snode_copy                (CulSNode *node,
                                                       CulSNode *end);
CulSNode               *cul_snode_detach              (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_clone_f *clone_f);
CulSNode               *cul_snode_reverse             (CulSNode *node,
                                                       CulSNode *end);

CulSNode               *cul_snode_sort                (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_cmp_f *cmp_f);
CulSNode               *cul_snode_unique              (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_cmp_f *cmp_f,
                                                       cul_free_f *free_f);
CulSNode               *cul_snode_find                (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_cmp_f *cmp_f,
                                                       cul_ptr data);

void                    cul_snode_each                (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_each_f *each_f);
void                    cul_snode_each_data           (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_each_data_f *each_f,
                                                       cul_ptr data);
void                    cul_snode_each_free           (CulSNode *node,
                                                       CulSNode *end,
                                                       cul_free_f *free_f);

/* implementations */

static inline void cul_snode_remove_next(CulSNode *node,
                                         cul_free_f *free_f)
{
    node->next = cul_snode_remove(node->next, free_f);
}

#endif /* __CUL_SNODE_H__ */

