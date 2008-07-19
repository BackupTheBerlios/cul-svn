#ifndef __CUL_SLIST_H__
#define __CUL_SLIST_H__

#include <cul/cul_global.h>

#define CUL_SLIST(ptr) ((CulSList *)(ptr))

typedef struct _CulSList CulSList;

struct _CulSList {
	cul_ptr data;     /* data associated with list element */
	CulSList *next;   /* next element in the list */
};

static inline CulSList *cul_slist_new_struct ();
static inline void      cul_slist_free_struct(CulSList *slist);
static inline CulSList *cul_slist_init_struct(CulSList *slist, cul_ptr data, CulSList *next);

CulSList *cul_slist_new        (cul_ptr data);
CulSList *cul_slist_new_empty  ();
void      cul_slist_free       (CulSList *slist, cul_free_f *free_f);
void      cul_slist_free_all   (CulSList *slist, cul_free_f *free_f);

CulSList *cul_slist_last       (CulSList *slist);
CulSList *cul_slist_half       (CulSList *slist);
CulSList *cul_slist_nth        (CulSList *slist, size_t n);
size_t    cul_slist_size       (CulSList *slist);

CulSList *cul_slist_insert_next(CulSList *slist, cul_ptr data);
CulSList *cul_slist_insert_prev(CulSList *slist, cul_ptr data);
CulSList *cul_slist_remove     (CulSList *slist, cul_free_f *free_f);
CulSList *cul_slist_remove_next(CulSList *slist, cul_free_f *free_f);

CulSList *cul_slist_copy       (CulSList *slist);
CulSList *cul_slist_detach     (CulSList *slist, cul_clone_f *clone_f);
CulSList *cul_slist_reverse    (CulSList *slist);

CulSList *cul_slist_sort       (CulSList *slist, cul_cmp_f *cmp_f);
size_t    cul_slist_unique     (CulSList *slist, cul_cmp_f *cmp_f, cul_free_f *free_f);
CulSList *cul_slist_find       (CulSList *slist, cul_ptr data, cul_cmp_f *cmp_f);
void      cul_slist_each       (CulSList *slist, cul_each_f *each_f);
void      cul_slist_each_prv   (CulSList *slist, cul_each_prv_f *each_prv_f, cul_ptr prv);

/* implementations */

static inline CulSList *cul_slist_new_struct() {
	return cul_slab_new(sizeof(CulSList));
}

static inline void cul_slist_free_struct(CulSList *slist) {
	cul_slab_free(sizeof(CulSList), slist);
}

static inline CulSList *cul_slist_init_struct(CulSList *slist, cul_ptr data, CulSList *next) {
	slist->data = data;
	slist->next = next;
	return slist;
}

#endif

