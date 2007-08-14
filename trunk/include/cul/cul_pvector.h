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

static inline CulPVector     *cul_pvector_new_struct(void);
static inline void            cul_pvector_free_struct(CulPVector *v);
static inline CulPVector     *cul_pvector_init_struct(CulPVector *v, cul_ptr *data, size_t size, size_t reserved);

static inline CulPVectorView *cul_pvectorview_new_struct(void);
static inline void            cul_pvectorview_free_struct(CulPVectorView *vv);
static inline CulPVectorView *cul_pvectorview_init_struct(CulPVectorView *vv, cul_ptr *data, size_t size, size_t stride);

static inline cul_ptr         cul_pvector_get(const CulPVector *v, size_t x);
static inline void            cul_pvector_set(CulPVector *v, size_t x, cul_ptr val);
static inline cul_ptr        *cul_pvector_ptr(CulPVector *v, size_t x);
static inline cul_const_ptr  *cul_pvector_const_ptr(const CulPVector *v, size_t x);

static inline cul_ptr         cul_pvectorview_get(const CulPVectorView *vv, size_t x);
static inline void            cul_pvectorview_set(CulPVectorView *vv, size_t x, cul_ptr val);
static inline cul_ptr        *cul_pvectorview_ptr(CulPVectorView *vv, size_t x);
static inline cul_ptr        *cul_pvectorview_next(CulPVectorView *vv, cul_ptr *ptr);
static inline cul_const_ptr  *cul_pvectorview_const_ptr(const CulPVectorView *vv, size_t x);
static inline cul_const_ptr  *cul_pvectorview_const_next(const CulPVectorView *vv, const cul_ptr *ptr);

CulPVector     *cul_pvector_new(size_t size);
CulPVector     *cul_pvector_new_empty(void);
void            cul_pvector_free(CulPVector *v, cul_free_f *free_f);
CulPVectorView *cul_pvectorview_new(void);
void            cul_pvectorview_free(CulPVectorView *vv);

CulPVectorView *cul_pvectorview_vector(CulPVectorView *vv, const CulPVector *base_v);
CulPVectorView *cul_pvectorview_subvector(CulPVectorView *vv, const CulPVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

void      cul_pvector_zero(CulPVector *v);

void      cul_pvector_set_all(CulPVector *v, cul_ptr val);
void      cul_pvector_set_basis(CulPVector *v, size_t index, cul_ptr val, cul_ptr basis);
void      cul_pvectorview_set_all(CulPVectorView *vv, cul_ptr val);
void      cul_pvectorview_set_basis(CulPVectorView *v, size_t index, cul_ptr val, cul_ptr basis);

cul_errno cul_pvector_copy(CulPVector *v, const CulPVector *base_v);
cul_errno cul_pvector_copy_offset(CulPVector *v, const CulPVector *base_v, size_t offset);
cul_errno cul_pvector_copy_subvector(CulPVector *v, const CulPVector *base_v, size_t base_offset);
cul_errno cul_pvector_copy_view(CulPVector *v, const CulPVectorView *base_vv);
cul_errno cul_pvectorview_copy(CulPVectorView *vv, const CulPVectorView *base_vv);
cul_errno cul_pvectorview_copy_vector(CulPVectorView *vv, const CulPVector *base_v);

cul_errno cul_pvector_detach(CulPVector *v);
cul_errno cul_pvectorview_detach(CulPVectorView *vv);

cul_errno cul_pvector_swap(CulPVector *a, CulPVector *b);
cul_errno cul_pvectorview_swap(CulPVectorView *va, CulPVectorView *vb);
void      cul_pvector_reverse(CulPVector *v);
void      cul_pvectorview_reverse(CulPVectorView *vv);

cul_errno cul_pvector_resize(CulPVector *v, size_t size, cul_free_f *free_f);
cul_errno cul_pvector_resize_empty(CulPVector *v, size_t size);
cul_errno cul_pvector_reserve(CulPVector *v, size_t size);
cul_errno cul_pvector_push_back(CulPVector *v, cul_ptr val);
cul_errno cul_pvector_pop_back(CulPVector *v, cul_free_f *free_f);

void      cul_pvector_sort(CulPVector *v, cul_cmp_f *cmp_f);
size_t    cul_pvector_unique(CulPVector *v, cul_cmp_f *cmp_f);
size_t    cul_pvector_find(const CulPVector *v, size_t offset, cul_ptr key, cul_cmp_f *cmp_f);
size_t    cul_pvector_bfind(const CulPVector *v, cul_ptr key, cul_cmp_f *cmp_f);
void      cul_pvector_foreach(CulPVector *v, cul_foreach_f *foreach_f, cul_ptr user_data);
void      cul_pvectorview_sort(CulPVectorView *vv, cul_cmp_f *cmp_f);
size_t    cul_pvectorview_unique(CulPVectorView *vv, cul_cmp_f *cmp_f);
size_t    cul_pvectorview_find(const CulPVectorView *vv, size_t offset, cul_ptr key, cul_cmp_f *cmp_f);
size_t    cul_pvectorview_bfind(const CulPVectorView *vv, cul_ptr key, cul_cmp_f *cmp_f);
void      cul_pvectorview_foreach(CulPVectorView *vv, cul_foreach_f *foreach_f, cul_ptr user_data);

/* implementations */

static inline CulPVector *cul_pvector_new_struct(void) {
	return cul_slab_new(sizeof(CulPVector));
}

static inline void cul_pvector_free_struct(CulPVector *v) {
	cul_slab_free(sizeof(CulPVector), v);
}

static inline CulPVector *cul_pvector_init_struct(CulPVector *v, cul_ptr *data, size_t reserved, size_t size) {
	v->reserved = reserved;
	v->size = size;
	v->data = data;
	return v;
}

static inline CulPVectorView *cul_pvectorview_new_struct(void) {
	return cul_slab_new(sizeof(CulPVectorView));
}

static inline void cul_pvectorview_free_struct(CulPVectorView *vv) {
	cul_slab_free(sizeof(CulPVectorView), vv);
}

static inline CulPVectorView *cul_pvectorview_init_struct(CulPVectorView *vv, cul_ptr *data, size_t size, size_t stride) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline cul_ptr cul_pvector_get(const CulPVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return v->data[x];
}

static inline void cul_pvector_set(CulPVector *v, size_t x, cul_ptr val) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	v->data[x] = val;
}

static inline cul_ptr *cul_pvector_ptr(CulPVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline cul_const_ptr *cul_pvector_const_ptr(const CulPVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(v->data + x);
}

static inline cul_ptr cul_pvectorview_get(const CulPVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return vv->data[x * vv->stride];
}

static inline void cul_pvectorview_set(CulPVectorView *vv, size_t x, cul_ptr val) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	vv->data[x * vv->stride] = val;
}

static inline cul_ptr *cul_pvectorview_ptr(CulPVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline cul_ptr *cul_pvectorview_next(CulPVectorView *vv, cul_ptr *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline cul_const_ptr *cul_pvectorview_const_ptr(const CulPVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(vv->data + x * vv->stride);
}

static inline cul_const_ptr *cul_pvectorview_const_next(const CulPVectorView *vv, const cul_ptr *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (cul_const_ptr *)(ptr + vv->stride);
}

#endif /* __CUL_PVECTOR_H__ */
