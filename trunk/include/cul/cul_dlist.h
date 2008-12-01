#ifndef __CUL_DLIST_H__
#define __CUL_DLIST_H__

#include <cul/cul_global.h>
#include <cul/cul_dnode.h>

#define CUL_DLIST(ptr) ((CulDList *)(ptr))

typedef struct _CulDList CulDList;

CulDList               *cul_dlist_new                 (CulDNode *first);
CulDList               *cul_dlist_new_empty           ();
void                    cul_dlist_free                (CulDList *list,
                                                       cul_free_f *free_f);
void                    cul_dlist_init                (CulDList *list,
                                                       CulDNode *first);
void                    cul_dlist_init_empty          ();

CulDNode               *cul_dlist_first               (CulDList *list);
CulDNode               *cul_dlist_last                (CulDList *list);
CulDNode               *cul_dlist_nth                 (CulDList *list,
                                                       size_t n);
size_t                  cul_dlist_size                (CulDList *list);
cul_bool                cul_dlist_valid               (CulDList *list);

CulDNode               *cul_dlist_insert              (CulDList *list,
                                                       CulDNode *node,
                                                       cul_ptr data);
void                    cul_dlist_remove              (CulDList *list,
                                                       CulDNode *node,
                                                       cul_free_f *free_f);
CulDNode               *cul_dlist_push_front          (CulDList *list,
                                                       cul_ptr data);
void                    cul_dlist_pop_front           (CulDList *list,
                                                       cul_free_f *free_f);
CulDNode               *cul_dlist_push_back           (CulDList *list,
                                                       cul_ptr data);
void                    cul_dlist_pop_back            (CulDList *list,
                                                       cul_free_f *free_f);

CulDList               *cul_dlist_copy                (CulDList *list);
cul_bool                cul_dlist_detach              (CulDList *list,
                                                       cul_clone_f *clone_f);
void                    cul_dlist_reverse             (CulDList *list);

void                    cul_dlist_sort                (CulDList *list,
                                                       cul_cmp_f *cmp_f);
void                    cul_dlist_unique              (CulDList *list,
                                                       cul_cmp_f *cmp_f,
                                                       cul_free_f *free_f);
CulDNode               *cul_dlist_find                (CulDList *list,
                                                       cul_cmp_f *cmp_f,
                                                       cul_ptr data);

void                    cul_dlist_each                (CulDList *list,
                                                       cul_each_f *each_f);
void                    cul_dlist_each_data           (CulDList *list,
                                                       cul_each_data_f *each_f,
                                                       cul_ptr data);

/* implementations */

#endif /* __CUL_DLIST_H__ */

