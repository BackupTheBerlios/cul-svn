#ifndef __CUL_DNODE_H__
#define __CUL_DNODE_H__

#include <cul/cul_global.h>

typedef struct _CulDNode CulDNode;
struct _CulDNode {
    cul_ptr data;     /* data associated with element */
    CulDNode *next;   /* next element */
    CulDNode *prev;   /* previous element */
};

CulDNode               *cul_dnode_new                 (cul_ptr data);
CulDNode               *cul_dnode_new_empty           ();
void                    cul_dnode_free                (CulDNode *node,
                                                       cul_free_f *free_f);
void                    cul_dnode_init                (CulDNode *node,
                                                       cul_ptr data);
void                    cul_dnode_init_empty          (CulDNode *node);

CulDNode               *cul_dnode_first               (CulDNode *node);
CulDNode               *cul_dnode_last                (CulDNode *node);
CulDNode               *cul_dnode_nth                 (CulDNode *node,
                                                       size_t n);
size_t                  cul_dnode_size                (CulDNode *node,
                                                       CulDNode *end);

CulDNode               *cul_dnode_insert_next         (CulDNode *node,
                                                       cul_ptr data);
CulDNode               *cul_dnode_insert_prev         (CulDNode *node,
                                                       cul_ptr data);
CulDNode               *cul_dnode_remove              (CulDNode *node,
                                                       cul_free_f *free_f);

CulDNode               *cul_dnode_copy                (CulDNode *node,
                                                       CulDNode *end);
CulDNode               *cul_dnode_detach              (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_clone_f *clone_f);
CulDNode               *cul_dnode_reverse             (CulDNode *node,
                                                       CulDNode *end);

CulDNode               *cul_dnode_sort                (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_cmp_f *cmp_f);
CulDNode               *cul_dnode_unique              (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_cmp_f *cmp_f,
                                                       cul_free_f *free_f);
CulDNode               *cul_dnode_find                (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_cmp_f *cmp_f,
                                                       cul_ptr data);

void                    cul_dnode_each                (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_each_f *each_f);
void                    cul_dnode_each_data           (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_each_data_f *each_f,
                                                       cul_ptr data);
void                    cul_dnode_each_free           (CulDNode *node,
                                                       CulDNode *end,
                                                       cul_free_f *free_f);

/* implementations */

#endif /* __CUL_DNODE_H__ */

