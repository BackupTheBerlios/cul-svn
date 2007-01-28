#if !defined(CUL_VECTOR_INT_H)
#define CUL_VECTOR_INT_H

#include <cul/cul_global.h>
#include <stdio.h>

#define CUL_IVECTOR(ptr) ((CulIVector *)(ptr))
#define CUL_IVECTORVIEW(ptr) ((CulIVectorView *)(ptr))

typedef struct _CulIVector CulIVector;
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

/* Allocation */

static inline CulIVector *cul_ivector_new_struct(void);
static inline void cul_ivector_free_struct(CulIVector *v);
static inline CulIVector *cul_ivector_init_struct(CulIVector *v, size_t reserved, size_t size, int *data);

static inline CulIVectorView *cul_ivectorview_new_struct(void);
static inline void cul_ivectorview_free_struct(CulIVectorView *vv);
static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *vv, size_t size, size_t stride, int *data);

/* Uninitialized data elements */
CulIVector *cul_ivector_new(size_t size);
CulIVector *cul_ivector_new_empty(void);
CulIVector *cul_ivector_init(CulIVector *v, size_t size);
CulIVector *cul_ivector_init_empty(CulIVector *v);

CulIVectorView *cul_ivectorview_new(void);
CulIVectorView *cul_ivectorview_init(CulIVectorView *vv);
CulIVectorView *cul_ivectorview_init_vector(CulIVectorView *vv, const CulIVector *base_v);
CulIVectorView *cul_ivectorview_init_subvector(CulIVectorView *vv, const CulIVector *base_v, size_t base_offset, size_t base_size);
CulIVectorView *cul_ivectorview_init_subvector_stride(CulIVectorView *vv, const CulIVector *base_v, size_t base_offset, size_t base_size, size_t base_stride);

/* Free */

void cul_ivector_free(CulIVector *v);
void cul_ivector_free_data(CulIVector *v);
void cul_ivectorview_free(CulIVectorView *vv);

/* Initialization */

void cul_ivector_set_all(CulIVector *v, int val);
void cul_ivector_set_zero(CulIVector *v);
void cul_ivector_set_basis(CulIVector *v, size_t index);

void cul_ivectorview_set_all(CulIVectorView *vv, int val);
void cul_ivectorview_set_zero(CulIVectorView *vv);
void cul_ivectorview_set_basis(CulIVectorView *vv, size_t index);

/* Data Access */

static inline int cul_ivector_get(const CulIVector *v, size_t x);
static inline void cul_ivector_set(CulIVector *v, size_t x, int val);
static inline int *cul_ivector_ptr(CulIVector *v, size_t x);
static inline const int *cul_ivector_const_ptr(const CulIVector *v, size_t x);

static inline int cul_ivectorview_get(const CulIVectorView *vv, size_t x);
static inline void cul_ivectorview_set(CulIVectorView *vv, size_t x, int val);
static inline int *cul_ivectorview_ptr(CulIVectorView *vv, size_t x);
static inline int *cul_ivectorview_next(CulIVectorView *vv, int *ptr);

/* Data Copy */

cul_errno cul_ivector_copy(CulIVector *v, const CulIVector *base_v);
cul_errno cul_ivector_copy_offset(CulIVector *v, const CulIVector *base_v, size_t offset);
cul_errno cul_ivector_copy_subvector(CulIVector *v, const CulIVector *base_v, size_t base_offset);
cul_errno cul_ivector_copy_view(CulIVector *v, const CulIVectorView *base_vv);
cul_errno cul_ivectorview_copy(CulIVectorView *vv, const CulIVectorView *base_vv);

cul_errno cul_ivector_swap(CulIVector *a, CulIVector *b);
cul_errno cul_ivectorview_swap(CulIVectorView *a, CulIVectorView *b);
void cul_ivector_reverse(CulIVector *v);
void cul_ivectorview_reverse(CulIVectorView *vv);

/* Data Resize */

CulIVector *cul_ivector_resize(CulIVector *v, size_t size);
CulIVector *cul_ivector_reserve(CulIVector *v, size_t size);
CulIVector *cul_ivector_push_back(CulIVector *v, int val);
CulIVector *cul_ivector_pop_back(CulIVector *v);

/* Min/Max */

int cul_ivector_min(const CulIVector *v);
size_t cul_ivector_min_index(const CulIVector *v);
int cul_ivector_max(const CulIVector *v);
size_t cul_ivector_max_index(const CulIVector *v);
void cul_ivector_minmax(const CulIVector *v, int *min, int *max);
void cul_ivector_minmax_index(const CulIVector *v, size_t *min_i, size_t *max_i);

int cul_ivectorview_min(const CulIVectorView *vv);
size_t cul_ivectorview_min_index(const CulIVectorView *vv);
int cul_ivectorview_max(const CulIVectorView *vv);
size_t cul_ivectorview_max_index(const CulIVectorView *vv);
void cul_ivectorview_minmax(const CulIVectorView *vv, int *min, int *max);
void cul_ivectorview_minmax_index(const CulIVectorView *vv, size_t *min_i, size_t *max_i);

/* Statistics */

double cul_ivector_sum(const CulIVector *v);
double cul_ivector_mean(const CulIVector *v);
double cul_ivector_variance(const CulIVector *v, double mean);

double cul_ivectorview_sum(const CulIVectorView *vv);
double cul_ivectorview_mean(const CulIVectorView *vv);
double cul_ivectorview_variance(const CulIVectorView *vv, double mean);

/* Basic Algorithms */

void cul_ivector_sort(CulIVector *v, cul_cmp_f *cmp);
void cul_ivector_sort_asc(CulIVector *v);
void cul_ivector_sort_desc(CulIVector *v);

void cul_ivectorview_sort(CulIVectorView *vv, cul_cmp_f *cmp);
void cul_ivectorview_sort_asc(CulIVectorView *vv);
void cul_ivectorview_sort_desc(CulIVectorView *vv);

size_t cul_ivector_unique(CulIVector *v, cul_eq_f *eq);
size_t cul_ivector_unique_eq(CulIVector *v);

size_t cul_ivectorview_unique(CulIVectorView *vv, cul_eq_f *eq);
size_t cul_ivectorview_unique_eq(CulIVectorView *vv);

/* Operations */

void cul_ivector_add_scalar(CulIVector *v, int val);
void cul_ivector_mul_scalar(CulIVector *v, int val);
cul_errno cul_ivector_add(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_sub(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_mul(CulIVector *a, const CulIVector *b);
cul_errno cul_ivector_div(CulIVector *a, const CulIVector *b);

void cul_ivectorview_add_scalar(CulIVectorView *vv, int val);
void cul_ivectorview_mul_scalar(CulIVectorView *vv, int val);
cul_errno cul_ivectorview_add(CulIVectorView *a, const CulIVectorView *b);
cul_errno cul_ivectorview_sub(CulIVectorView *a, const CulIVectorView *b);
cul_errno cul_ivectorview_mul(CulIVectorView *a, const CulIVectorView *b);
cul_errno cul_ivectorview_div(CulIVectorView *a, const CulIVectorView *b);

/* Input/Output */

cul_errno cul_ivector_print_stream(const CulIVector *v, const char *format, const char *separator);
cul_errno cul_ivector_fprintf(FILE *id, const CulIVector *v, const char *format, const char *separator);
cul_errno cul_ivector_fscanf(FILE *id, CulIVector *v, const char *format, const char *separator);

cul_errno cul_ivectorview_print_stream(const CulIVectorView *vv, const char *format, const char *separator);
cul_errno cul_ivectorview_fprintf(FILE *id, const CulIVectorView *vv, const char *format, const char *separator);
cul_errno cul_ivectorview_fscanf(FILE *id, CulIVectorView *vv, const char *format, const char *separator);

/* implementations */

static inline CulIVector *cul_ivector_new_struct(void) {
	return cul_slab_new(sizeof(CulIVector));
}

static inline void cul_ivector_free_struct(CulIVector *v) {
	cul_slab_free(sizeof(CulIVector), v);
}

static inline CulIVector *cul_ivector_init_struct(CulIVector *v, size_t reserved, size_t size, int *data) {
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

static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *vv, size_t size, size_t stride, int *data) {
	vv->size = size;
	vv->stride = stride;
	vv->data = data;
	return vv;
}

static inline int cul_ivector_get(const CulIVector *v, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( x >= v->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return v->data[x];
}

static inline void cul_ivector_set(CulIVector *v, size_t x, int val) {
#if defined(CUL_RANGE_CHECK)
	if( x >= v->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	v->data[x] = val;
	return;
}

static inline int *cul_ivector_ptr(CulIVector *v, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( x > v->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline const int *cul_ivector_const_ptr(const CulIVector *v, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( x > v->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (v->data + x);
}

static inline int cul_ivectorview_get(const CulIVectorView *vv, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( i >= vv->size ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return vv->data[x * vv->stride];
}

static inline void cul_ivectorview_set(CulIVectorView *vv, size_t x, int val) {
#if defined(CUL_RANGE_CHECK)
	if( x >= vv->size ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	vv->data[x * vv->stride] = val;
	return;
}

static inline int *cul_ivectorview_ptr(CulIVectorView *vv, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline const int *cul_ivectorview_const_ptr(const CulIVectorView *vv, size_t x) {
#if defined(CUL_RANGE_CHECK)
	if( x > v->size ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (vv->data + x * vv->stride);
}

static inline int *cul_ivectorview_next(CulIVectorView *vv, int *ptr) {
#if defined(CUL_RANGE_CHECK)
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

static inline const int *cul_ivectorview_const_next(const CulIVectorView *vv, const int *ptr) {
#if defined(CUL_RANGE_CHECK)
	if( ptr > vv->data + vv->size * vv->stride ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	return (ptr + vv->stride);
}

#endif
