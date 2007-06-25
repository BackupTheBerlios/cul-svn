#ifndef CUL_LIST_H
#define CUL_LIST_H

#include <cul/cul_global.h>

#define CUL_LIST(ptr) ((CulList *)(ptr))

typedef struct _CulList CulList;

struct _CulList {
	cul_ptr data;     /* data associated with list element */
	CulList *next;    /* next element in the list */
	CulList *prev;    /* previous element in the list */
};

/* Allocation */

static inline CulList *cul_list_new_struct(void);
static inline void cul_list_free_struct(CulList *l);
static inline void cul_list_init_struct(CulList *l, CulList *next, CulList *prev, cul_ptr data);

CulList *cul_list_new(cul_ptr data);
CulList *cul_list_new_empty();
void cul_list_free(CulList *l, cul_free_f *free_f);
void cul_list_free_all(CulList *l, cul_free_f *free_f);

/* Basic List Operators */

static inline CulList *cul_list_next(CulList *l);
static inline CulList *cul_list_prev(CulList *l);
CulList *cul_list_first(CulList *l);
CulList *cul_list_last(CulList *l);
CulList *cul_list_half(CulList *l);
CulList *cul_list_nth(CulList *l, size_t n);
size_t   cul_list_size(CulList *l);

/* Resize */

CulList *cul_list_insert_next(CulList *l, cul_ptr data);
CulList *cul_list_insert_prev(CulList *l, cul_ptr data);
CulList *cul_list_remove(CulList *l, cul_free_f *free_f);

/* Copy */

CulList *cul_list_copy(CulList *l);
CulList *cul_list_detach(CulList *l, cul_cpy_f *cpy_f);
CulList *cul_list_reverse(CulList *l);

/* Basic Algorithms */

CulList *cul_list_find(CulList *l, cul_ptr data, cul_cmp_f *cmp_f);
CulList *cul_list_sort(CulList *l, cul_cmp_f *cmp_f);
size_t   cul_list_unique_free(CulList *l, cul_cmp_f *cmp_f, cul_free_f *free_f);
size_t   cul_list_foreach(CulList *l, cul_foreach_f *foreach);
size_t   cul_list_foreach_data(CulList *l, cul_foreach_data_f *foreach, cul_ptr data);

/* implementations */

static inline CulList *cul_list_new_struct(void) {
	return cul_slab_new(sizeof(CulList));
}

static inline void cul_list_free_struct(CulList *l) {
	cul_slab_free(sizeof(CulList), l);
}

static inline void cul_list_init_struct(CulList *l, CulList *next, CulList *prev, cul_ptr data) {
	l->data = data;
	l->next = next;
	l->prev = prev;
}

static inline CulList *cul_list_next(CulList *l) {
#ifdef CUL_RANGE_CHECK
	if( l == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return l->next;
}

static inline CulList *cul_list_prev(CulList *l) {
#ifdef CUL_RANGE_CHECK
	if( l == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return l->prev;
}

#endif
