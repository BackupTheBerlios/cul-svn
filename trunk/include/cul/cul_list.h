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
static inline void     cul_list_free_struct(CulList *this);
static inline CulList *cul_list_init_struct(CulList *this, CulList *next, CulList *prev, cul_ptr data);
static inline CulList *cul_list_next       (CulList *this);
static inline CulList *cul_list_prev       (CulList *this);

CulList *cul_list_new        (cul_ptr data);
CulList *cul_list_new_empty  ();
void     cul_list_free       (CulList *this, cul_free_f *free_f);
void     cul_list_free_all   (CulList *this, cul_free_f *free_f);

CulList *cul_list_first      (CulList *this);
CulList *cul_list_last       (CulList *this);
CulList *cul_list_half       (CulList *this);
CulList *cul_list_nth        (CulList *this, size_t n);
size_t   cul_list_size       (CulList *this);

CulList *cul_list_insert_next(CulList *this, cul_ptr data);
CulList *cul_list_insert_prev(CulList *this, cul_ptr data);
CulList *cul_list_remove     (CulList *this, cul_free_f *free_f);

CulList *cul_list_copy       (CulList *this);
CulList *cul_list_detach     (CulList *this, cul_clone_f *clone_f);
CulList *cul_list_reverse    (CulList *this);

CulList *cul_list_sort       (CulList *this, cul_cmp_f *cmp_f);
size_t   cul_list_unique     (CulList *this, cul_cmp_f *cmp_f, cul_free_f *free_f);
CulList *cul_list_find       (CulList *this, cul_ptr data, cul_cmp_f *cmp_f);
void     cul_list_each       (CulList *this, cul_each_f *each_f);
void     cul_list_each_prv   (CulList *this, cul_each_prv_f *each_prv_f, cul_ptr prv);

/* implementations */

static inline CulList *cul_list_new_struct(void) {
	return cul_slab_new(sizeof(CulList));
}

static inline void cul_list_free_struct(CulList *this) {
	cul_slab_free(sizeof(CulList), this);
}

static inline CulList *cul_list_init_struct(CulList *this, CulList *next, CulList *prev, cul_ptr data) {
	this->data = data;
	this->next = next;
	this->prev = prev;
	return this;
}

static inline CulList *cul_list_next(CulList *this) {
#ifdef CUL_RANGE_CHECK
	if( this == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return this->next;
}

static inline CulList *cul_list_prev(CulList *this) {
#ifdef CUL_RANGE_CHECK
	if( this == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return this->prev;
}

#endif /* __CUL_LIST_H__ */

