#ifndef CUL_SLIST_H
#define CUL_SLIST_H

#include <cul/cul_global.h>

#define CUL_SLIST(ptr) ((CulSList *)(ptr))

typedef struct _CulSList CulSList;

struct _CulSList {
	cul_ptr data;     /* data associated with list element */
	CulSList *next;   /* next element in the list */
};

/* Allocation */

static inline CulSList *cul_slist_new_struct(void);
static inline void cul_slist_free_struct(CulSList *l);
static inline void cul_slist_init_struct(CulSList *l, CulSList *next, cul_ptr data);

CulSList *cul_slist_new(cul_ptr data);
CulSList *cul_slist_new_empty();
void cul_slist_free(CulSList *l, cul_free_f *free_f);
void cul_slist_free_all(CulSList *l, cul_free_f *free_f);

/* Basic List Operators */

static inline CulSList *cul_slist_next(CulSList *l);
CulSList *cul_slist_last(CulSList *l);
CulSList *cul_slist_half(CulSList *l);
CulSList *cul_slist_nth(CulSList *l, size_t n);
size_t    cul_slist_size(CulSList *l);

/* Resize */

CulSList *cul_slist_insert_next(CulSList *l, cul_ptr data);
CulSList *cul_slist_remove(CulSList *l, cul_free_f *free_f);
CulSList *cul_slist_remove_next(CulSList *l, cul_free_f *free_f);

/* Copy */

CulSList *cul_slist_copy(CulSList *l);
CulSList *cul_slist_detach(CulSList *l, cul_cpy_f *cpy_f);
CulSList *cul_slist_reverse(CulSList *l);

/* Basic Algorithms */

CulSList *cul_slist_find(CulSList *l, cul_ptr data, cul_cmp_f *cmp_f);
CulSList *cul_slist_sort(CulSList *l, cul_cmp_f *cmp_f);
size_t    cul_slist_unique_free(CulSList *l, cul_cmp_f *cmp_f, cul_free_f *free_f);
CulSList *cul_slist_find(CulSList *l, cul_ptr data, cul_cmp_f *cmp_f);
size_t    cul_slist_foreach(CulSList *l, cul_foreach_f *foreach);
size_t    cul_slist_foreach_data(CulSList *l, cul_foreach_data_f *foreach, cul_ptr data);

/* implementations */

static inline CulSList *cul_slist_new_struct(void) {
	return cul_slab_new(sizeof(CulSList));
}

static inline void cul_slist_free_struct(CulSList *l) {
	cul_slab_free(sizeof(CulSList), l);
}

static inline void cul_slist_init_struct(CulSList *l, CulSList *next, cul_ptr data) {
	l->data = data;
	l->next = next;
}

static inline CulSList *cul_slist_next(CulSList *l) {
#ifdef CUL_RANGE_CHECK
	if( l == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return l->next;
}

#endif
