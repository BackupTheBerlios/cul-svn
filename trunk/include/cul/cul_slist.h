#ifndef __CUL_SLIST_H__
#define __CUL_SLIST_H__

#include <cul/cul_global.h>
#include <cul/cul_snode.h>

#define CUL_SLIST(ptr) ((CulSList *)(ptr))

typedef struct _CulSList CulSList;

CulSList               *cul_slist_new                 (CulSNode *first);
CulSList               *cul_slist_new_empty           ();
void                    cul_slist_free                (CulSList *list,
                                                       cul_free_f *free_f);
void                    cul_slist_init                (CulSList *list,
                                                       CulSNode *first);
void                    cul_slist_init_empty          ();

CulSNode               *cul_slist_first               (CulSList *list);
CulSNode               *cul_slist_last                (CulSList *list);
CulSNode               *cul_slist_nth                 (CulSList *list,
                                                       size_t n);
size_t                  cul_slist_size                (CulSList *list);
cul_bool                cul_slist_valid               (CulSList *list);

CulSNode               *cul_slist_insert              (CulSList *list,
                                                       CulSNode *node,
                                                       cul_ptr data);
CulSNode               *cul_slist_insert_next         (CulSList *list,
                                                       CulSNode *node,
                                                       cul_ptr data);
void                    cul_slist_remove              (CulSList *list,
                                                       CulSNode *node,
                                                       cul_free_f *free_f);
void                    cul_slist_remove_next         (CulSList *list,
                                                       CulSNode *node,
                                                       cul_free_f *free_f);
CulSNode               *cul_slist_push_front          (CulSList *list,
                                                       cul_ptr data);
void                    cul_slist_pop_front           (CulSList *list,
                                                       cul_free_f *free_f);
CulSNode               *cul_slist_push_back           (CulSList *list,
                                                       cul_ptr data);
void                    cul_slist_pop_back            (CulSList *list,
                                                       cul_free_f *free_f);

CulSList               *cul_slist_copy                (CulSList *list);
cul_bool                cul_slist_detach              (CulSList *list,
                                                       cul_clone_f *clone_f);
void                    cul_slist_reverse             (CulSList *list);

void                    cul_slist_sort                (CulSList *list,
                                                       cul_cmp_f *cmp_f);
void                    cul_slist_unique              (CulSList *list,
                                                       cul_cmp_f *cmp_f,
                                                       cul_free_f *free_f);
CulSNode               *cul_slist_find                (CulSList *list,
                                                       cul_cmp_f *cmp_f,
                                                       cul_ptr data);

#endif /* __CUL_SLIST_H__ */

