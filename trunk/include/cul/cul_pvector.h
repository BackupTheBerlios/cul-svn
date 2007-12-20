#ifndef __CUL_PVECTOR_H__
#define __CUL_PVECTOR_H__

#include <cul/cul_global.h>

#define CUL_PVECTOR(ptr)     ((CulPVector *)(ptr))
#define CUL_PVECTORVIEW(ptr) ((CulPVectorView *)(ptr))

typedef struct _CulPVector     CulPVector;
typedef struct _CulPVectorView CulPVectorView;

struct _CulPVector {
	cul_ptr *data;
	size_t size;
	size_t reserved;
};

struct _CulPVectorView {
	cul_ptr *data;
	size_t size;
	size_t stride;
};

static inline CulPVector     *cul_pvector_new_struct     ();
static inline void            cul_pvector_free_struct    (CulPVector *this);
static inline CulPVector     *cul_pvector_init_struct    (CulPVector *this, cul_ptr *data, size_t size, size_t reserved);
static inline CulPVectorView *cul_pvectorview_new_struct ();
static inline void            cul_pvectorview_free_struct(CulPVectorView *this);
static inline CulPVectorView *cul_pvectorview_init_struct(CulPVectorView *this, cul_ptr *data, size_t size, size_t stride);

static inline cul_ptr         cul_pvector_get            (const CulPVector *this, size_t x);
static inline void            cul_pvector_set            (CulPVector *this, size_t x, cul_ptr value);
static inline cul_ptr        *cul_pvector_ptr            (CulPVector *this, size_t x);
static inline cul_const_ptr  *cul_pvector_const_ptr      (const CulPVector *this, size_t x);
static inline cul_ptr         cul_pvectorview_get        (const CulPVectorView *this, size_t x);
static inline void            cul_pvectorview_set        (CulPVectorView *this, size_t x, cul_ptr value);
static inline cul_ptr        *cul_pvectorview_ptr        (CulPVectorView *this, size_t x);
static inline cul_ptr        *cul_pvectorview_next       (CulPVectorView *this, cul_ptr *ptr);
static inline cul_const_ptr  *cul_pvectorview_const_ptr  (const CulPVectorView *this, size_t x);
static inline cul_const_ptr  *cul_pvectorview_const_next (const CulPVectorView *this, const cul_ptr *ptr);

CulPVector     *cul_pvector_new          (size_t size);
CulPVector     *cul_pvector_new_empty    ();
CulPVector     *cul_pvector_clone        (CulPVector *this);
CulPVector     *cul_pvector_clone_view   (CulPVectorView *this);
void            cul_pvector_free         (CulPVector *this, cul_free_f *free_f);
CulPVectorView *cul_pvectorview_new      ();
void            cul_pvectorview_free     (CulPVectorView *this);

CulPVectorView *cul_pvectorview_vector   (CulPVectorView *this, const CulPVector *base);
CulPVectorView *cul_pvectorview_subvector(CulPVectorView *this, const CulPVector *base, size_t base_offset, size_t base_size, size_t base_stride);

cul_errno cul_pvector_copy            (CulPVector *this, const CulPVector *other);
cul_errno cul_pvector_copy_offset     (CulPVector *this, const CulPVector *other, size_t offset);
cul_errno cul_pvector_copy_subvector  (CulPVector *this, const CulPVector *other, size_t other_offset);
cul_errno cul_pvector_copy_view       (CulPVector *this, const CulPVectorView *other);
cul_errno cul_pvector_copy_view_offset(CulPVector *this, const CulPVectorView *other, size_t offset);
cul_errno cul_pvectorview_copy        (CulPVectorView *this, const CulPVectorView *other);
cul_errno cul_pvectorview_copy_vector (CulPVectorView *this, const CulPVector *other);

cul_errno cul_pvector_swap            (CulPVector *this, CulPVector *other);
cul_errno cul_pvectorview_swap        (CulPVectorView *this, CulPVectorView *other);
void      cul_pvector_reverse         (CulPVector *this);
void      cul_pvectorview_reverse     (CulPVectorView *this);

cul_errno cul_pvector_resize          (CulPVector *this, size_t size, cul_free_f *free_f);
cul_errno cul_pvector_resize_empty    (CulPVector *this, size_t size);
cul_errno cul_pvector_reserve         (CulPVector *this, size_t size);
cul_errno cul_pvector_shrink          (CulPVector *this);
cul_errno cul_pvector_insert          (CulPVector *this, size_t offset, cul_ptr value);
cul_errno cul_pvector_insert_vector   (CulPVector *this, size_t offset, const CulPVector *other);
cul_errno cul_pvector_insert_view     (CulPVector *this, size_t offset, const CulPVectorView *other);
cul_errno cul_pvector_push_back       (CulPVector *this, cul_ptr value);
cul_errno cul_pvector_remove          (CulPVector *this, size_t offset, cul_free_f *free_f);
cul_errno cul_pvector_remove_range    (CulPVector *this, size_t offset, size_t size, cul_free_f *free_f);
cul_errno cul_pvector_pop_back        (CulPVector *this, cul_free_f *free_f);

cul_errno cul_pvector_detach          (CulPVector *this, cul_clone_f *clone_f);
cul_errno cul_pvector_detach_range    (CulPVector *this, size_t offset, size_t size, cul_clone_f *clone_f);
cul_errno cul_pvectorview_detach      (CulPVectorView *this, cul_clone_f *clone_f);

void      cul_pvector_set_all         (CulPVector *this, cul_ptr value);
void      cul_pvector_set_basis       (CulPVector *this, size_t index, cul_ptr value, cul_ptr basis);
void      cul_pvector_zero            (CulPVector *this);
void      cul_pvectorview_set_all     (CulPVectorView *this, cul_ptr value);
void      cul_pvectorview_set_basis   (CulPVectorView *this, size_t index, cul_ptr value, cul_ptr basis);

void      cul_pvector_sort            (CulPVector *this, cul_cmp_f *cmp_f);
size_t    cul_pvector_unique          (CulPVector *this, cul_eq_f *eq_f);
size_t    cul_pvector_find            (const CulPVector *this, size_t offset, cul_ptr key, cul_eq_f *eq_f);
size_t    cul_pvector_bfind           (const CulPVector *this, cul_ptr key, cul_cmp_f *cmp_f);
void      cul_pvector_each            (CulPVector *this, cul_each_f *each_f, cul_ptr user_data);
void      cul_pvectorview_sort        (CulPVectorView *this, cul_cmp_f *cmp_f);
size_t    cul_pvectorview_unique      (CulPVectorView *this, cul_eq_f *eq_f);
size_t    cul_pvectorview_find        (const CulPVectorView *this, size_t offset, cul_ptr key, cul_eq_f *eq_f);
size_t    cul_pvectorview_bfind       (const CulPVectorView *this, cul_ptr key, cul_cmp_f *cmp_f);
void      cul_pvectorview_each        (CulPVectorView *this, cul_each_f *each_f, cul_ptr user_data);

/* implementations */

static inline CulPVector *cul_pvector_new_struct() {
	return cul_slab_new(sizeof(CulPVector));
}

static inline void cul_pvector_free_struct(CulPVector *this) {
	cul_slab_free(sizeof(CulPVector), this);
}

static inline CulPVector *cul_pvector_init_struct(CulPVector *this, cul_ptr *data, size_t size, size_t reserved) {
	this->reserved = reserved;
	this->size = size;
	this->data = data;
	return this;
}

static inline CulPVectorView *cul_pvectorview_new_struct() {
	return cul_slab_new(sizeof(CulPVectorView));
}

static inline void cul_pvectorview_free_struct(CulPVectorView *this) {
	cul_slab_free(sizeof(CulPVectorView), this);
}

static inline CulPVectorView *cul_pvectorview_init_struct(CulPVectorView *this, cul_ptr *data, size_t size, size_t stride) {
	this->size = size;
	this->stride = stride;
	this->data = data;
	return this;
}

static inline cul_ptr cul_pvector_get(const CulPVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x];
}

static inline void cul_pvector_set(CulPVector *this, size_t x, cul_ptr value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x] = value;
}

static inline cul_ptr *cul_pvector_ptr(CulPVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline cul_const_ptr *cul_pvector_const_ptr(const CulPVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(this->data + x);
}

static inline cul_ptr cul_pvectorview_get(const CulPVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x * this->stride];
}

static inline void cul_pvectorview_set(CulPVectorView *this, size_t x, cul_ptr value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x * this->stride] = value;
}

static inline cul_ptr *cul_pvectorview_ptr(CulPVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline cul_ptr *cul_pvectorview_next(CulPVectorView *this, cul_ptr *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

static inline cul_const_ptr *cul_pvectorview_const_ptr(const CulPVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(this->data + x * this->stride);
}

static inline cul_const_ptr *cul_pvectorview_const_next(const CulPVectorView *this, const cul_ptr *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(ptr + this->stride);
}

#endif /* __CUL_PVECTOR_H__ */
