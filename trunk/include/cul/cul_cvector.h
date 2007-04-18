#ifndef CUL_CVECTOR_H
#define CUL_CVECTOR_H

#include <cul/cul_global.h>
#include <stdio.h>

#define CUL_CVECTOR(ptr)     ((CulCVector *)(ptr))
#define CUL_CVECTORVIEW(ptr) ((CulCVectorView *)(ptr))

typedef struct _CulCVector     CulCVector;
typedef struct _CulCVectorView CulCVectorView;

struct _CulCVector {
	char *data;
	size_t size;
	size_t reserved;
};

struct _CulCVectorView {
	char *data;
	size_t size;
	size_t stride;
};

static inline CulCVector *cul_cvector_new_struct(void);
static inline void cul_cvector_free_struct(CulCVector *v);
static inline CulCVector *cul_cvector_init_struct(CulCVector *v, char *data, size_t size, size_t reserved);

static inline CulCVectorView *cul_cvectorview_new_struct(void);
static inline void cul_cvectorview_free_struct(CulCVectorView *vv);
static inline CulCVectorView *cul_cvectorview_init_struct(CulCVectorView *vv, char *data, size_t size, size_t stride);

CulCVector *cul_cvector_new(size_t size);
CulCVector *cul_cvector_new_empty(void);
void cul_cvector_free(CulCVector *v);

CulCVectorView *cul_cvectorview_new(void);
void cul_cvectorview_free(CulCVectorView *vv);

CulCVectorView *cul_cvectorview_vector(CulCVectorView *vv, const CulCVector *base_v);
CulCVectorView *cul_cvectorview_subvector(CulCVectorView *vv, const CulCVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

void cul_cvector_set_all(CulCVector *v, char val);
void cul_cvector_set_zero(CulCVector *v);
void cul_cvector_set_basis(CulCVector *v, size_t index);

void cul_cvectorview_set_all(CulCVectorView *vv, char val);
void cul_cvectorview_set_zero(CulCVectorView *vv);
void cul_cvectorview_set_basis(CulCVectorView *vv, size_t index);

static inline char cul_cvector_get(const CulCVector *v, size_t x);
static inline void cul_cvector_set(CulCVector *v, size_t x, char val);
static inline char *cul_cvector_ptr(CulCVector *v, size_t x);
static inline const char *cul_cvector_const_ptr(const CulCVector *v, size_t x);

static inline char cul_cvectorview_get(const CulCVectorView *vv, size_t x);
static inline void cul_cvectorview_set(CulCVectorView *vv, size_t x, char val);
static inline char *cul_cvectorview_ptr(CulCVectorView *vv, size_t x);
static inline const char *cul_cvectorview_const_ptr(const CulCVectorView *vv, size_t x);
static inline char *cul_cvectorview_next(CulCVectorView *vv, char *ptr);
static inline const char *cul_cvectorview_const_next(const CulCVectorView *vv, const char *ptr);

cul_errno cul_cvector_copy(CulCVector *v, const CulCVector *base_v);
cul_errno cul_cvector_copy_offset(CulCVector *v, const CulCVector *base_v, size_t offset);
cul_errno cul_cvector_copy_subvector(CulCVector *v, const CulCVector *base_v, size_t base_offset);
cul_errno cul_cvector_copy_view(CulCVector *v, const CulCVectorView *base_vv);
cul_errno cul_cvectorview_copy(CulCVectorView *vv, const CulCVectorView *base_vv);

cul_errno cul_cvector_swap(CulCVector *a, CulCVector *b);
cul_errno cul_cvectorview_swap(CulCVectorView *va, CulCVectorView *vb);
void cul_cvector_reverse(CulCVector *v);
void cul_cvectorview_reverse(CulCVectorView *vv);

CulCVector *cul_cvector_resize(CulCVector *v, size_t size);
CulCVector *cul_cvector_reserve(CulCVector *v, size_t size);
CulCVector *cul_cvector_push_back(CulCVector *v, char val);
CulCVector *cul_cvector_pop_back(CulCVector *v);

char cul_cvector_min(const CulCVector *v);
size_t cul_cvector_min_index(const CulCVector *v);
char cul_cvector_max(const CulCVector *v);
size_t cul_cvector_max_index(const CulCVector *v);
void cul_cvector_minmax(const CulCVector *v, char *min, char *max);
void cul_cvector_minmax_index(const CulCVector *v, size_t *min_i, size_t *max_i);

char cul_cvectorview_min(const CulCVectorView *vv);
size_t cul_cvectorview_min_index(const CulCVectorView *vv);
char cul_cvectorview_max(const CulCVectorView *vv);
size_t cul_cvectorview_max_index(const CulCVectorView *vv);
void cul_cvectorview_minmax(const CulCVectorView *vv, char *min, char *max);
void cul_cvectorview_minmax_index(const CulCVectorView *vv, size_t *min_i, size_t *max_i);

double cul_cvector_sum(const CulCVector *v);
double cul_cvector_mean(const CulCVector *v);
double cul_cvector_variance(const CulCVector *v, double mean);

double cul_cvectorview_sum(const CulCVectorView *vv);
double cul_cvectorview_mean(const CulCVectorView *vv);
double cul_cvectorview_variance(const CulCVectorView *vv, double mean);

void cul_cvector_sort_asc(CulCVector *v);
void cul_cvector_sort_desc(CulCVector *v);
void cul_cvectorview_sort_asc(CulCVectorView *vv);
void cul_cvectorview_sort_desc(CulCVectorView *vv);

size_t cul_cvector_unique(CulCVector *v);
size_t cul_cvectorview_unique(CulCVectorView *vv);

void cul_cvector_add_scalar(CulCVector *v, char val);
void cul_cvector_mul_scalar(CulCVector *v, char val);
cul_errno cul_cvector_add(CulCVector *a, const CulCVector *b);
cul_errno cul_cvector_sub(CulCVector *a, const CulCVector *b);
cul_errno cul_cvector_mul(CulCVector *a, const CulCVector *b);
cul_errno cul_cvector_div(CulCVector *a, const CulCVector *b);

void cul_cvectorview_add_scalar(CulCVectorView *vv, char val);
void cul_cvectorview_mul_scalar(CulCVectorView *vv, char val);
cul_errno cul_cvectorview_add(CulCVectorView *va, const CulCVectorView *vb);
cul_errno cul_cvectorview_sub(CulCVectorView *va, const CulCVectorView *vb);
cul_errno cul_cvectorview_mul(CulCVectorView *va, const CulCVectorView *vb);
cul_errno cul_cvectorview_div(CulCVectorView *va, const CulCVectorView *vb);

cul_errno cul_cvector_fprintf(FILE *stream, const CulCVector *v, const char *format, const char *separator);
cul_errno cul_cvector_fscanf(FILE *stream, CulCVector *v, const char *format, const char *separator);
cul_errno cul_cvectorview_fprintf(FILE *stream, const CulCVectorView *vv, const char *format, const char *separator);
cul_errno cul_cvectorview_fscanf(FILE *stream, CulCVectorView *vv, const char *format, const char *separator);

/* implementations */

static inline CulCVector *cul_cvector_new_struct(void) {
	return cul_slab_new(sizeof(CulCVector));
}

static inline void cul_cvector_free_struct(CulCVector *v) {
	cul_slab_free(sizeof(CulCVector), v);
}

static inline CulCVector *cul_cvector_init_struct(CulCVector *v, char *data, size_t size, size_t reserved) {
	v->reserved = reserved;
	v->size = size;
	v->data = data;
	return v;
}

static inline CulCVectorView *cul_cvectorview_new_struct(void) {
	return cul_slab_new(sizeof(CulCVectorView));
}

static inline void cul_cvectorview_free_struct(CulCVectorView *vv) {
	cul_slab_free(sizeof(CulCVectorView), vv);
}

static inline CulCVectorView *cul_cvectorview_init_struct(CulCVectorView *vv, char *data, size_t size, size_t stride) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline char cul_cvector_get(const CulCVector *v, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i >= v->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return v->data[i];
}

static inline void cul_cvector_set(CulCVector *v, size_t i, char val) {
#if defined(CUL_RANGE_CHECK)
	if( i >= v->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	v->data[i] = val;
}

static inline char *cul_cvector_ptr(CulCVector *v, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (v->data + i);
}

static inline const char *cul_cvector_const_ptr(const CulCVector *v, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (v->data + i);
}

static inline char cul_cvectorview_get(const CulCVectorView *vv, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i >= vv->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return vv->data[i * vv->stride];
}

static inline void cul_cvectorview_set(CulCVectorView *vv, size_t i, char val) {
#if defined(CUL_RANGE_CHECK)
	if( i >= vv->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	vv->data[i * vv->stride] = val;
}

static inline char *cul_cvectorview_ptr(CulCVectorView *vv, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i > vv->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (vv->data + i * vv->stride);
}

static inline const char *cul_cvectorview_const_ptr(const CulCVectorView *vv, size_t i) {
#if defined(CUL_RANGE_CHECK)
	if( i > vv->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (vv->data + i * vv->stride);
}

static inline char *cul_cvectorview_next(CulCVectorView *vv, char *ptr) {
#if defined(CUL_RANGE_CHECK)
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline const char *cul_cvectorview_const_next(const CulCVectorView *vv, const char *ptr) {
#if defined(CUL_RANGE_CHECK)
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

#endif /* CUL_CVECTOR_H */
