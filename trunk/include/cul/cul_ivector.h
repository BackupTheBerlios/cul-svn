#ifndef CUL_IVECTOR_H
#define CUL_IVECTOR_H

#include <cul/cul_global.h>
#include <stdio.h>

#define CUL_IVECTOR(ptr)     ((CulIVector *)(ptr))
#define CUL_IVECTORVIEW(ptr) ((CulIVectorView *)(ptr))

typedef struct _CulIVector     CulIVector;
typedef struct _CulIVectorView CulIVectorView;

struct _CulIVector {
	int *data;
	size_t size;
	size_t reserved;
};

struct _CulIVectorView {
	int *data;
	size_t size;
	size_t stride;
};

static inline CulIVector *cul_ivector_new_struct(void);
static inline void cul_ivector_free_struct(CulIVector *v);
static inline CulIVector *cul_ivector_init_struct(CulIVector *v, int *data, size_t reserved, size_t size);

static inline CulIVectorView *cul_ivectorview_new_struct(void);
static inline void cul_ivectorview_free_struct(CulIVectorView *vv);
static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *vv, int *data, size_t size, size_t stride);

static inline int cul_ivector_get(const CulIVector *v, size_t x);
static inline void cul_ivector_set(CulIVector *v, size_t x, int val);
static inline int *cul_ivector_ptr(CulIVector *v, size_t x);
static inline const int *cul_ivector_const_ptr(const CulIVector *v, size_t x);

static inline int cul_ivectorview_get(const CulIVectorView *vv, size_t x);
static inline void cul_ivectorview_set(CulIVectorView *vv, size_t x, int val);
static inline int *cul_ivectorview_ptr(CulIVectorView *vv, size_t x);
static inline int *cul_ivectorview_next(CulIVectorView *vv, int *ptr);

CulIVector     *cul_ivector_new(size_t size);
CulIVector     *cul_ivector_new_empty(void);
void            cul_ivector_free(CulIVector *v);
CulIVectorView *cul_ivectorview_new(void);
void            cul_ivectorview_free(CulIVectorView *vv);

CulIVectorView *cul_ivectorview_vector(CulIVectorView *vv, const CulIVector *base_v);
CulIVectorView *cul_ivectorview_subvector(CulIVectorView *vv, const CulIVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

void      cul_ivector_set_all(CulIVector *v, int val);
void      cul_ivector_set_basis(CulIVector *v, size_t index, int val, int basis);
void      cul_ivectorview_set_all(CulIVectorView *vv, int val);
void      cul_ivectorview_set_basis(CulIVectorView *vv, size_t index, int val, int basis);

cul_errno cul_ivector_copy(CulIVector *v, const CulIVector *base_v);
cul_errno cul_ivector_copy_offset(CulIVector *v, const CulIVector *base_v, size_t offset);
cul_errno cul_ivector_copy_subvector(CulIVector *v, const CulIVector *base_v, size_t base_offset);
cul_errno cul_ivector_copy_view(CulIVector *v, const CulIVectorView *base_vv);
cul_errno cul_ivectorview_copy(CulIVectorView *vv, const CulIVectorView *base_vv);
cul_errno cul_ivectorview_copy_vector(CulIVectorView *vv, const CulIVector *base_v);

cul_errno cul_ivector_swap(CulIVector *a, CulIVector *b);
cul_errno cul_ivectorview_swap(CulIVectorView *va, CulIVectorView *vb);
void      cul_ivector_reverse(CulIVector *v);
void      cul_ivectorview_reverse(CulIVectorView *vv);

cul_errno cul_ivector_resize(CulIVector *v, size_t size);
cul_errno cul_ivector_resize_empty(CulIVector *v, size_t size);
cul_errno cul_ivector_reserve(CulIVector *v, size_t size);
cul_errno cul_ivector_push_back(CulIVector *v, int val);
cul_errno cul_ivector_pop_back(CulIVector *v);

int       cul_ivector_min(const CulIVector *v);
size_t    cul_ivector_min_index(const CulIVector *v);
int       cul_ivector_max(const CulIVector *v);
size_t    cul_ivector_max_index(const CulIVector *v);
void      cul_ivector_minmax(const CulIVector *v, int *min, int *max);
void      cul_ivector_minmax_index(const CulIVector *v, size_t *min_i, size_t *max_i);
int       cul_ivectorview_min(const CulIVectorView *vv);
size_t    cul_ivectorview_min_index(const CulIVectorView *vv);
int       cul_ivectorview_max(const CulIVectorView *vv);
size_t    cul_ivectorview_max_index(const CulIVectorView *vv);
void      cul_ivectorview_minmax(const CulIVectorView *vv, int *min, int *max);
void      cul_ivectorview_minmax_index(const CulIVectorView *vv, size_t *min_i, size_t *max_i);

double    cul_ivector_sum(const CulIVector *v);
double    cul_ivector_mean(const CulIVector *v);
double    cul_ivector_variance(const CulIVector *v, double mean);
double    cul_ivectorview_sum(const CulIVectorView *vv);
double    cul_ivectorview_mean(const CulIVectorView *vv);
double    cul_ivectorview_variance(const CulIVectorView *vv, double mean);

void      cul_ivector_sort_asc(CulIVector *v);
void      cul_ivector_sort_desc(CulIVector *v);
size_t    cul_ivector_unique(CulIVector *v);
size_t    cul_ivector_find(const CulIVector *v, size_t offset, int key);
size_t    cul_ivector_bfind(const CulIVector *v, int key);
void      cul_ivectorview_sort_asc(CulIVectorView *vv);
void      cul_ivectorview_sort_desc(CulIVectorView *vv);
size_t    cul_ivectorview_unique(CulIVectorView *vv);
size_t    cul_ivectorview_find(const CulIVectorView *vv, size_t offset, int key);
size_t    cul_ivectorview_bfind(const CulIVectorView *vv, int key);

void      cul_ivector_add_scalar(CulIVector *v, int val);
void      cul_ivector_mul_scalar(CulIVector *v, int val);
cul_errno cul_ivector_add(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_sub(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_mul(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_div(CulIVector *a, const CulIVector *b);
void      cul_ivectorview_add_scalar(CulIVectorView *vv, int val);
void      cul_ivectorview_mul_scalar(CulIVectorView *vv, int val);
cul_errno cul_ivectorview_add(CulIVectorView *va, const CulIVectorView *vb);
cul_errno cul_ivectorview_sub(CulIVectorView *va, const CulIVectorView *vb);
cul_errno cul_ivectorview_mul(CulIVectorView *va, const CulIVectorView *vb);
cul_errno cul_ivectorview_div(CulIVectorView *va, const CulIVectorView *vb);

cul_errno cul_ivector_fprintf(FILE *stream, const CulIVector *v, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivector_fscanf(FILE *stream, CulIVector *v, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fprintf(FILE *stream, const CulIVectorView *vv, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fscanf(FILE *stream, CulIVectorView *vv, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline CulIVector *cul_ivector_new_struct(void) {
	return cul_slab_new(sizeof(CulIVector));
}

static inline void cul_ivector_free_struct(CulIVector *v) {
	cul_slab_free(sizeof(CulIVector), v);
}

static inline CulIVector *cul_ivector_init_struct(CulIVector *v, int *data, size_t reserved, size_t size) {
	v->reserved = reserved;
	v->size = size;
	v->data = data;
	return v;
}

static inline CulIVectorView *cul_ivectorview_new_struct(void) {
	return cul_slab_new(sizeof(CulIVectorView));
}

static inline void cul_ivectorview_free_struct(CulIVectorView *vv) {
	cul_slab_free(sizeof(CulIVectorView), vv);
}

static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *vv, int *data, size_t size, size_t stride) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline int cul_ivector_get(const CulIVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return v->data[x];
}

static inline void cul_ivector_set(CulIVector *v, size_t x, int val) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	v->data[x] = val;
	return;
}

static inline int *cul_ivector_ptr(CulIVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline const int *cul_ivector_const_ptr(const CulIVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline int cul_ivectorview_get(const CulIVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return vv->data[x * vv->stride];
}

static inline void cul_ivectorview_set(CulIVectorView *vv, size_t x, int val) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	vv->data[x * vv->stride] = val;
	return;
}

static inline int *cul_ivectorview_ptr(CulIVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline const int *cul_ivectorview_const_ptr(const CulIVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > vv->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline int *cul_ivectorview_next(CulIVectorView *vv, int *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline const int *cul_ivectorview_const_next(const CulIVectorView *vv, const int *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

#endif /* CUL_IVECTOR_H */
