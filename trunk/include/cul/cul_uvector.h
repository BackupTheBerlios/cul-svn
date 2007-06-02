#ifndef CUL_UVECTOR_H
#define CUL_UVECTOR_H

#include <cul/cul_global.h>
#include <stdio.h>

#define CUL_UVECTOR(ptr)     ((CulUVector *)(ptr))
#define CUL_UVECTORVIEW(ptr) ((CulUVectorView *)(ptr))

typedef struct _CulUVector     CulUVector;
typedef struct _CulUVectorView CulUVectorView;

struct _CulUVector {
	size_t *data;
	size_t size;
	size_t reserved;
};

struct _CulUVectorView {
	size_t *data;
	size_t size;
	size_t stride;
};

static inline CulUVector *cul_uvector_new_struct(void);
static inline void cul_uvector_free_struct(CulUVector *v);
static inline CulUVector *cul_uvector_init_struct(CulUVector *v, size_t *data, size_t reserved, size_t size);

static inline CulUVectorView *cul_uvectorview_new_struct(void);
static inline void cul_uvectorview_free_struct(CulUVectorView *vv);
static inline CulUVectorView *cul_uvectorview_init_struct(CulUVectorView *vv, size_t *data, size_t size, size_t stride);

static inline size_t cul_uvector_get(const CulUVector *v, size_t x);
static inline void cul_uvector_set(CulUVector *v, size_t x, size_t val);
static inline size_t *cul_uvector_ptr(CulUVector *v, size_t x);
static inline const size_t *cul_uvector_const_ptr(const CulUVector *v, size_t x);

static inline size_t cul_uvectorview_get(const CulUVectorView *vv, size_t x);
static inline void cul_uvectorview_set(CulUVectorView *vv, size_t x, size_t val);
static inline size_t *cul_uvectorview_ptr(CulUVectorView *vv, size_t x);
static inline size_t *cul_uvectorview_next(CulUVectorView *vv, size_t *ptr);
static inline const size_t *cul_uvectorview_const_ptr(const CulUVectorView *vv, size_t x);
static inline const size_t *cul_uvectorview_const_next(const CulUVectorView *vv, const size_t *ptr);

CulUVector     *cul_uvector_new(size_t size);
CulUVector     *cul_uvector_new_empty(void);
void            cul_uvector_free(CulUVector *v);
CulUVectorView *cul_uvectorview_new(void);
void            cul_uvectorview_free(CulUVectorView *vv);

CulUVectorView *cul_uvectorview_vector(CulUVectorView *vv, const CulUVector *base_v);
CulUVectorView *cul_uvectorview_subvector(CulUVectorView *vv, const CulUVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

void      cul_uvector_set_all(CulUVector *v, size_t val);
void      cul_uvector_set_zero(CulUVector *v);
void      cul_uvector_set_basis(CulUVector *v, size_t index);
void      cul_uvectorview_set_all(CulUVectorView *vv, size_t val);
void      cul_uvectorview_set_zero(CulUVectorView *vv);
void      cul_uvectorview_set_basis(CulUVectorView *vv, size_t index);

cul_errno cul_uvector_copy(CulUVector *v, const CulUVector *base_v);
cul_errno cul_uvector_copy_offset(CulUVector *v, const CulUVector *base_v, size_t offset);
cul_errno cul_uvector_copy_subvector(CulUVector *v, const CulUVector *base_v, size_t base_offset);
cul_errno cul_uvector_copy_view(CulUVector *v, const CulUVectorView *base_vv);
cul_errno cul_uvectorview_copy(CulUVectorView *vv, const CulUVectorView *base_vv);
cul_errno cul_uvectorview_copy_vector(CulUVectorView *vv, const CulUVector *base_v);

cul_errno cul_uvector_swap(CulUVector *a, CulUVector *b);
cul_errno cul_uvectorview_swap(CulUVectorView *va, CulUVectorView *vb);
void      cul_uvector_reverse(CulUVector *v);
void      cul_uvectorview_reverse(CulUVectorView *vv);

cul_errno cul_uvector_resize(CulUVector *v, size_t size);
cul_errno cul_uvector_resize_empty(CulUVector *v, size_t size);
cul_errno cul_uvector_reserve(CulUVector *v, size_t size);
cul_errno cul_uvector_push_back(CulUVector *v, size_t val);
cul_errno cul_uvector_pop_back(CulUVector *v);

size_t    cul_uvector_min(const CulUVector *v);
size_t    cul_uvector_min_index(const CulUVector *v);
size_t    cul_uvector_max(const CulUVector *v);
size_t    cul_uvector_max_index(const CulUVector *v);
void      cul_uvector_minmax(const CulUVector *v, size_t *min, size_t *max);
void      cul_uvector_minmax_index(const CulUVector *v, size_t *min_i, size_t *max_i);
size_t    cul_uvectorview_min(const CulUVectorView *vv);
size_t    cul_uvectorview_min_index(const CulUVectorView *vv);
size_t    cul_uvectorview_max(const CulUVectorView *vv);
size_t    cul_uvectorview_max_index(const CulUVectorView *vv);
void      cul_uvectorview_minmax(const CulUVectorView *vv, size_t *min, size_t *max);
void      cul_uvectorview_minmax_index(const CulUVectorView *vv, size_t *min_i, size_t *max_i);

double    cul_uvector_sum(const CulUVector *v);
double    cul_uvector_mean(const CulUVector *v);
double    cul_uvector_variance(const CulUVector *v, double mean);
double    cul_uvectorview_sum(const CulUVectorView *vv);
double    cul_uvectorview_mean(const CulUVectorView *vv);
double    cul_uvectorview_variance(const CulUVectorView *vv, double mean);

void      cul_uvector_sort_asc(CulUVector *v);
void      cul_uvector_sort_desc(CulUVector *v);
size_t    cul_uvector_unique(CulUVector *v);
void      cul_uvectorview_sort_asc(CulUVectorView *vv);
void      cul_uvectorview_sort_desc(CulUVectorView *vv);
size_t    cul_uvectorview_unique(CulUVectorView *vv);

void      cul_uvector_add_scalar(CulUVector *v, size_t val);
void      cul_uvector_mul_scalar(CulUVector *v, size_t val);
cul_errno cul_uvector_add(CulUVector *a, const CulUVector *b);
cul_errno cul_uvector_sub(CulUVector *a, const CulUVector *b);
cul_errno cul_uvector_mul(CulUVector *a, const CulUVector *b);
cul_errno cul_uvector_div(CulUVector *a, const CulUVector *b);
void      cul_uvectorview_add_scalar(CulUVectorView *vv, size_t val);
void      cul_uvectorview_mul_scalar(CulUVectorView *vv, size_t val);
cul_errno cul_uvectorview_add(CulUVectorView *va, const CulUVectorView *vb);
cul_errno cul_uvectorview_sub(CulUVectorView *va, const CulUVectorView *vb);
cul_errno cul_uvectorview_mul(CulUVectorView *va, const CulUVectorView *vb);
cul_errno cul_uvectorview_div(CulUVectorView *va, const CulUVectorView *vb);

cul_errno cul_uvector_fprintf(FILE *id, const CulUVector *v, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvector_fscanf(FILE *id, CulUVector *v, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fprintf(FILE *id, const CulUVectorView *vv, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fscanf(FILE *id, CulUVectorView *vv, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline CulUVector *cul_uvector_new_struct(void) {
	return cul_slab_new(sizeof(CulUVector));
}

static inline void cul_uvector_free_struct(CulUVector *v) {
	cul_slab_free(sizeof(CulUVector), v);
}

static inline CulUVector *cul_uvector_init_struct(CulUVector *v, size_t *data, size_t reserved, size_t size) {
	v->reserved = reserved;
	v->size = size;
	v->data = data;
	return v;
}

static inline CulUVectorView *cul_uvectorview_new_struct(void) {
	return cul_slab_new(sizeof(CulUVectorView));
}

static inline void cul_uvectorview_free_struct(CulUVectorView *vv) {
	cul_slab_free(sizeof(CulUVectorView), vv);
}

static inline CulUVectorView *cul_uvectorview_init_struct(CulUVectorView *vv, size_t *data, size_t size, size_t stride) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline size_t cul_uvector_get(const CulUVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return v->data[x];
}

static inline void cul_uvector_set(CulUVector *v, size_t x, size_t val) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	v->data[x] = val;
}

static inline size_t *cul_uvector_ptr(CulUVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline const size_t *cul_uvector_const_ptr(const CulUVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline size_t cul_uvectorview_get(const CulUVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return vv->data[x * vv->stride];
}

static inline void cul_uvectorview_set(CulUVectorView *vv, size_t x, size_t val) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	vv->data[x * vv->stride] = val;
}

static inline size_t *cul_uvectorview_ptr(CulUVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline size_t *cul_uvectorview_next(CulUVectorView *vv, size_t *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline const size_t *cul_uvectorview_const_ptr(const CulUVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline const size_t *cul_uvectorview_const_next(const CulUVectorView *vv, const size_t *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

#endif /* CUL_UVECTOR_H */
