#ifndef __CUL_SLIST_H__
#define __CUL_SLIST_H__

#include <cul/cul_global.h>

#define CUL_SLIST(ptr) ((CulSList *)(ptr))

typedef struct _CulSList CulSList;

struct _CulSList {
	cul_ptr data;     /* data associated with list element */
	CulSList *next;   /* next element in the list */
};

/* Allocation */

static inline CulSList *cul_slist_new_struct(void);
static inline void      cul_slist_free_struct(CulSList *this);
static inline CulSList *cul_slist_init_struct(CulSList *this, CulSList *next, cul_ptr data);

CulSList *cul_slist_new(cul_ptr data);
CulSList *cul_slist_new_empty();
void      cul_slist_free(CulSList *this, cul_free_f *free_f);
void      cul_slist_free_all(CulSList *this, cul_free_f *free_f);

/* Basic List Operators */

static inline CulSList *cul_slist_next(CulSList *this);
CulSList *cul_slist_last(CulSList *this);
CulSList *cul_slist_half(CulSList *this);
CulSList *cul_slist_nth(CulSList *this, size_t n);
size_t    cul_slist_size(CulSList *this);

/* Resize */

CulSList *cul_slist_insert_next(CulSList *this, cul_ptr data);
CulSList *cul_slist_remove(CulSList *this, cul_free_f *free_f);
CulSList *cul_slist_remove_next(CulSList *this, cul_free_f *free_f);

/* Copy */

CulSList *cul_slist_copy(CulSList *this);
CulSList *cul_slist_detach(CulSList *this, cul_cpy_f *cpy_f);
CulSList *cul_slist_reverse(CulSList *this);

/* Basic Algorithms */

CulSList *cul_slist_sort(CulSList *this, cul_cmp_f *cmp_f);
size_t    cul_slist_unique_free(CulSList *this, cul_cmp_f *cmp_f, cul_free_f *free_f);
CulSList *cul_slist_find(CulSList *this, cul_ptr data, cul_cmp_f *cmp_f);
void      cul_slist_each(CulSList *this, cul_each_f *each_f, cul_ptr user_data);

/* implementations */

static inline CulSList *cul_slist_new_struct(void) {
	return cul_slab_new(sizeof(CulSList));
}

static inline void cul_slist_free_struct(CulSList *this) {
	cul_slab_free(sizeof(CulSList), this);
}

static inline CulSList *cul_slist_init_struct(CulSList *this, CulSList *next, cul_ptr data) {
	this->data = data;
	this->next = next;
	return this;
}

static inline CulSList *cul_slist_next(CulSList *this) {
#ifdef CUL_RANGE_CHECK
	if( this == NULL ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return this->next;
}

#endif
