#ifndef CUL_DVECTOR_H
#define CUL_DVECTOR_H

#include <cul/cul_global.h>
#include <stdio.h>

#define CUL_DVECTOR(ptr)     ((CulDVector *)(ptr))
#define CUL_DVECTORVIEW(ptr) ((CulDVectorView *)(ptr))

typedef struct _CulDVector     CulDVector;
typedef struct _CulDVectorView CulDVectorView;

struct _CulDVector {
	double *data;
	size_t size;
	size_t reserved;
};

struct _CulDVectorView {
	double *data;
	size_t size;
	size_t stride;
};

static inline CulDVector *cul_dvector_new_struct(void);
static inline void cul_dvector_free_struct(CulDVector *v);
static inline CulDVector *cul_dvector_init_struct(CulDVector *v, double *data, size_t reserved, size_t size);

static inline CulDVectorView *cul_dvectorview_new_struct(void);
static inline void cul_dvectorview_free_struct(CulDVectorView *vv);
static inline CulDVectorView *cul_dvectorview_init_struct(CulDVectorView *vv, double *data, size_t size, size_t stride);

static inline double cul_dvector_get(const CulDVector *v, size_t x);
static inline void cul_dvector_set(CulDVector *v, size_t x, double val);
static inline double *cul_dvector_ptr(CulDVector *v, size_t x);
static inline const double *cul_dvector_const_ptr(const CulDVector *v, size_t x);

static inline double cul_dvectorview_get(const CulDVectorView *vv, size_t x);
static inline void cul_dvectorview_set(CulDVectorView *vv, size_t x, double val);
static inline double *cul_dvectorview_ptr(CulDVectorView *vv, size_t x);
static inline const double *cul_dvectorview_const_ptr(const CulDVectorView *vv, size_t x);
static inline double *cul_dvectorview_next(CulDVectorView *vv, double *ptr);
static inline const double *cul_dvectorview_const_next(const CulDVectorView *vv, const double *ptr);

CulDVector     *cul_dvector_new(size_t size);
CulDVector     *cul_dvector_new_empty(void);
void            cul_dvector_free(CulDVector *v);
CulDVectorView *cul_dvectorview_new(void);
void            cul_dvectorview_free(CulDVectorView *vv);

CulDVectorView *cul_dvectorview_vector(CulDVectorView *vv, const CulDVector *base_v);
CulDVectorView *cul_dvectorview_subvector(CulDVectorView *vv, const CulDVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

void      cul_dvector_set_all(CulDVector *v, double val);
void      cul_dvector_set_zero(CulDVector *v);
void      cul_dvector_set_basis(CulDVector *v, size_t index);
void      cul_dvectorview_set_all(CulDVectorView *vv, double val);
void      cul_dvectorview_set_zero(CulDVectorView *vv);
void      cul_dvectorview_set_basis(CulDVectorView *vv, size_t index);

cul_errno cul_dvector_copy(CulDVector *v, const CulDVector *base_v);
cul_errno cul_dvector_copy_offset(CulDVector *v, const CulDVector *base_v, size_t offset);
cul_errno cul_dvector_copy_subvector(CulDVector *v, const CulDVector *base_v, size_t base_offset);
cul_errno cul_dvector_copy_view(CulDVector *v, const CulDVectorView *base_vv);
cul_errno cul_dvectorview_copy(CulDVectorView *vv, const CulDVectorView *base_vv);

cul_errno cul_dvector_swap(CulDVector *a, CulDVector *b);
cul_errno cul_dvectorview_swap(CulDVectorView *va, CulDVectorView *vb);
void      cul_dvector_reverse(CulDVector *v);
void      cul_dvectorview_reverse(CulDVectorView *vv);

int       cul_dvector_compare(const CulDVector *a, const CulDVector *b);
int       cul_dvectorview_compare(const CulDVectorView *va, const CulDVectorView *vb);

cul_errno cul_dvector_resize(CulDVector *v, size_t size);
cul_errno cul_dvector_resize_empty(CulDVector *v, size_t size);
cul_errno cul_dvector_reserve(CulDVector *v, size_t size);
cul_errno cul_dvector_push_back(CulDVector *v, double val);
cul_errno cul_dvector_pop_back(CulDVector *v);

double    cul_dvector_min(const CulDVector *v);
size_t    cul_dvector_min_index(const CulDVector *v);
double    cul_dvector_max(const CulDVector *v);
size_t    cul_dvector_max_index(const CulDVector *v);
void      cul_dvector_minmax(const CulDVector *v, double *min, double *max);
void      cul_dvector_minmax_index(const CulDVector *v, size_t *min_i, size_t *max_i);
double    cul_dvectorview_min(const CulDVectorView *vv);
size_t    cul_dvectorview_min_index(const CulDVectorView *vv);
double    cul_dvectorview_max(const CulDVectorView *vv);
size_t    cul_dvectorview_max_index(const CulDVectorView *vv);
void      cul_dvectorview_minmax(const CulDVectorView *vv, double *min, double *max);
void      cul_dvectorview_minmax_index(const CulDVectorView *vv, size_t *min_i, size_t *max_i);

double    cul_dvector_sum(const CulDVector *v);
double    cul_dvector_mean(const CulDVector *v);
double    cul_dvector_variance(const CulDVector *v, double mean);
double    cul_dvectorview_sum(const CulDVectorView *vv);
double    cul_dvectorview_mean(const CulDVectorView *vv);
double    cul_dvectorview_variance(const CulDVectorView *vv, double mean);

void      cul_dvector_sort_asc(CulDVector *v);
void      cul_dvector_sort_desc(CulDVector *v);
size_t    cul_dvector_unique(CulDVector *v);
void      cul_dvectorview_sort_asc(CulDVectorView *vv);
void      cul_dvectorview_sort_desc(CulDVectorView *vv);
size_t    cul_dvectorview_unique(CulDVectorView *vv);

void      cul_dvector_add_scalar(CulDVector *v, double val);
void      cul_dvector_mul_scalar(CulDVector *v, double val);
cul_errno cul_dvector_add(CulDVector *a, const CulDVector *b);
cul_errno cul_dvector_sub(CulDVector *a, const CulDVector *b);
cul_errno cul_dvector_mul(CulDVector *a, const CulDVector *b);
cul_errno cul_dvector_div(CulDVector *a, const CulDVector *b);
void      cul_dvectorview_add_scalar(CulDVectorView *vv, double val);
void      cul_dvectorview_mul_scalar(CulDVectorView *vv, double val);
cul_errno cul_dvectorview_add(CulDVectorView *va, const CulDVectorView *vb);
cul_errno cul_dvectorview_sub(CulDVectorView *va, const CulDVectorView *vb);
cul_errno cul_dvectorview_mul(CulDVectorView *va, const CulDVectorView *vb);
cul_errno cul_dvectorview_div(CulDVectorView *va, const CulDVectorView *vb);

cul_errno cul_dvector_fprintf(FILE *stream, const CulDVector *v, const char *format, const char *separator);
cul_errno cul_dvector_fscanf(FILE *stream, CulDVector *v, const char *format, const char *separator);
cul_errno cul_dvectorview_fprintf(FILE *stream, const CulDVectorView *vv, const char *format, const char *separator);
cul_errno cul_dvectorview_fscanf(FILE *stream, CulDVectorView *vv, const char *format, const char *separator);

/* implementations */

static inline CulDVector *cul_dvector_new_struct(void) {
	return cul_slab_new(sizeof(CulDVector));
}

static inline void cul_dvector_free_struct(CulDVector *v) {
	cul_slab_free(sizeof(CulDVector), v);
}

static inline CulDVector *cul_dvector_init_struct(CulDVector *v, double *data, size_t reserved, size_t size) {
	v->reserved = reserved;
	v->size = size;
	v->data = data;
	return v;
}

static inline CulDVectorView *cul_dvectorview_new_struct(void) {
	return cul_slab_new(sizeof(CulDVectorView));
}

static inline void cul_dvectorview_free_struct(CulDVectorView *vv) {
	cul_slab_free(sizeof(CulDVectorView), vv);
}

static inline CulDVectorView *cul_dvectorview_init_struct(CulDVectorView *vv, double *data, size_t size, size_t stride) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline double cul_dvector_get(const CulDVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return v->data[x];
}

static inline void cul_dvector_set(CulDVector *v, size_t x, double val) {
#ifdef CUL_RANGE_CHECK
	if( x >= v->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	v->data[x] = val;
}

static inline double *cul_dvector_ptr(CulDVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline const double *cul_dvector_const_ptr(const CulDVector *v, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline double cul_dvectorview_get(const CulDVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return vv->data[x * vv->stride];
}

static inline void cul_dvectorview_set(CulDVectorView *vv, size_t x, double val) {
#ifdef CUL_RANGE_CHECK
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	vv->data[x * vv->stride] = val;
}

static inline double *cul_dvectorview_ptr(CulDVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline const double *cul_dvectorview_const_ptr(const CulDVectorView *vv, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline double *cul_dvectorview_next(CulDVectorView *vv, double *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline const double *cul_dvectorview_const_next(const CulDVectorView *vv, const double *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

#endif /* CUL_DVECTOR_H */
