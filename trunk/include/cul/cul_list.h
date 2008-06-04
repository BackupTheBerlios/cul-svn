#ifndef __CUL_LIST_H__
#define __CUL_LIST_H__

#include <cul/cul_global.h>

#define CUL_LIST(ptr) ((CulList *)(ptr))

typedef struct _CulList CulList;

struct _CulList {
	cul_ptr data;     /* data associated with list element */
	CulList *next;    /* next element in the list */
	CulList *prev;    /* previous element in the list */
};

static inline CulList *cul_list_new_struct ();
static inline void     cul_list_free_struct(CulList *list);
static inline CulList *cul_list_init_struct(CulList *list, cul_ptr data, CulList *next, CulList *prev);

CulList *cul_list_new        (cul_ptr data);
CulList *cul_list_new_empty  ();
void     cul_list_free       (CulList *list, cul_free_f *free_f);
void     cul_list_free_all   (CulList *list, cul_free_f *free_f);

CulList *cul_list_first      (CulList *list);
CulList *cul_list_last       (CulList *list);
CulList *cul_list_half       (CulList *list);
CulList *cul_list_nth        (CulList *list, size_t n);
size_t   cul_list_size       (CulList *list);

CulList *cul_list_insert_next(CulList *list, cul_ptr data);
CulList *cul_list_insert_prev(CulList *list, cul_ptr data);
CulList *cul_list_remove     (CulList *list, cul_free_f *free_f);

CulList *cul_list_copy       (CulList *list);
CulList *cul_list_detach     (CulList *list, cul_clone_f *clone_f);
CulList *cul_list_reverse    (CulList *list);

CulList *cul_list_sort       (CulList *list, cul_cmp_f *cmp_f);
size_t   cul_list_unique     (CulList *list, cul_cmp_f *cmp_f, cul_free_f *free_f);
CulList *cul_list_find       (CulList *list, cul_ptr data, cul_cmp_f *cmp_f);
void     cul_list_each       (CulList *list, cul_each_f *each_f);
void     cul_list_each_prv   (CulList *list, cul_each_prv_f *each_prv_f, cul_ptr prv);

/* implementations */

static inline CulList *cul_list_new_struct(void) {
	return cul_slab_new(sizeof(CulList));
}

static inline void cul_list_free_struct(CulList *list) {
	cul_slab_free(sizeof(CulList), list);
}

static inline CulList *cul_list_init_struct(CulList *list, cul_ptr data, CulList *next, CulList *prev) {
	list->data = data;
	list->next = next;
	list->prev = prev;
	return list;
}

#endif /* __CUL_LIST_H__ */

