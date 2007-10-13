#ifndef __CUL_UVECTOR_H__
#define __CUL_UVECTOR_H__

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

static inline CulUVector     *cul_uvector_new_struct     ();
static inline void            cul_uvector_free_struct    (CulUVector *this);
static inline CulUVector     *cul_uvector_init_struct    (CulUVector *this, size_t *data, size_t reserved, size_t size);
static inline CulUVectorView *cul_uvectorview_new_struct ();
static inline void            cul_uvectorview_free_struct(CulUVectorView *this);
static inline CulUVectorView *cul_uvectorview_init_struct(CulUVectorView *this, size_t *data, size_t size, size_t stride);

static inline size_t          cul_uvector_get            (const CulUVector *this, size_t x);
static inline void            cul_uvector_set            (CulUVector *this, size_t x, size_t value);
static inline size_t         *cul_uvector_ptr            (CulUVector *this, size_t x);
static inline const size_t   *cul_uvector_const_ptr      (const CulUVector *this, size_t x);
static inline size_t          cul_uvectorview_get        (const CulUVectorView *this, size_t x);
static inline void            cul_uvectorview_set        (CulUVectorView *this, size_t x, size_t value);
static inline size_t         *cul_uvectorview_ptr        (CulUVectorView *this, size_t x);
static inline size_t         *cul_uvectorview_next       (CulUVectorView *this, size_t *ptr);
static inline const size_t   *cul_uvectorview_const_ptr  (const CulUVectorView *this, size_t x);
static inline const size_t   *cul_uvectorview_const_next (const CulUVectorView *this, const size_t *ptr);

CulUVector     *cul_uvector_new          (size_t size);
CulUVector     *cul_uvector_new_empty    ();
CulUVector     *cul_uvector_clone        (CulUVector *this);
CulUVector     *cul_uvector_clone_view   (CulUVectorView *this);
void            cul_uvector_free         (CulUVector *this);
CulUVectorView *cul_uvectorview_new      ();
void            cul_uvectorview_free     (CulUVectorView *this);

CulUVectorView *cul_uvectorview_vector   (CulUVectorView *this, const CulUVector *base);
CulUVectorView *cul_uvectorview_subvector(CulUVectorView *this, const CulUVector *base, size_t base_offset, size_t base_size, size_t base_stride);

cul_errno cul_uvector_copy             (CulUVector *this, const CulUVector *other);
cul_errno cul_uvector_copy_offset      (CulUVector *this, const CulUVector *other, size_t offset);
cul_errno cul_uvector_copy_subvector   (CulUVector *this, const CulUVector *other, size_t other_offset);
cul_errno cul_uvector_copy_view        (CulUVector *this, const CulUVectorView *other);
cul_errno cul_uvectorview_copy         (CulUVectorView *this, const CulUVectorView *other);
cul_errno cul_uvectorview_copy_vector  (CulUVectorView *this, const CulUVector *other);

cul_errno cul_uvector_swap             (CulUVector *this, CulUVector *other);
cul_errno cul_uvectorview_swap         (CulUVectorView *this, CulUVectorView *other);
void      cul_uvector_reverse          (CulUVector *this);
void      cul_uvectorview_reverse      (CulUVectorView *this);

cul_errno cul_uvector_resize           (CulUVector *this, size_t size);
cul_errno cul_uvector_resize_empty     (CulUVector *this, size_t size);
cul_errno cul_uvector_reserve          (CulUVector *this, size_t size);
cul_errno cul_uvector_shrink           (CulUVector *this);
cul_errno cul_uvector_insert           (CulUVector *this, size_t offset, size_t value);
cul_errno cul_uvector_insert_vector    (CulUVector *this, size_t offset, const CulUVector *other);
cul_errno cul_uvector_insert_view      (CulUVector *this, size_t offset, const CulUVectorView *other);
cul_errno cul_uvector_push_back        (CulUVector *this, size_t value);
cul_errno cul_uvector_remove           (CulUVector *this, size_t offset);
cul_errno cul_uvector_remove_range     (CulUVector *this, size_t offset, size_t size);
cul_errno cul_uvector_pop_back         (CulUVector *this);

void      cul_uvector_set_all          (CulUVector *this, size_t value);
void      cul_uvector_set_basis        (CulUVector *this, size_t index, size_t value, size_t basis);
void      cul_uvector_add_constant     (CulUVector *this, double value);
void      cul_uvector_scale            (CulUVector *this, double value);
void      cul_uvector_zero             (CulUVector *this);
cul_errno cul_uvector_add              (CulUVector *this, const CulUVector *other);
cul_errno cul_uvector_sub              (CulUVector *this, const CulUVector *other);
cul_errno cul_uvector_mul              (CulUVector *this, const CulUVector *other);
cul_errno cul_uvector_div              (CulUVector *this, const CulUVector *other);
void      cul_uvectorview_set_all      (CulUVectorView *this, size_t value);
void      cul_uvectorview_set_basis    (CulUVectorView *this, size_t index, size_t value, size_t basis);
void      cul_uvectorview_add_constant (CulUVectorView *this, double value);
void      cul_uvectorview_scale        (CulUVectorView *this, double value);
cul_errno cul_uvectorview_add          (CulUVectorView *this, const CulUVectorView *other);
cul_errno cul_uvectorview_sub          (CulUVectorView *this, const CulUVectorView *other);
cul_errno cul_uvectorview_mul          (CulUVectorView *this, const CulUVectorView *other);
cul_errno cul_uvectorview_div          (CulUVectorView *this, const CulUVectorView *other);

size_t    cul_uvector_min              (const CulUVector *this);
size_t    cul_uvector_min_index        (const CulUVector *this);
size_t    cul_uvector_max              (const CulUVector *this);
size_t    cul_uvector_max_index        (const CulUVector *this);
void      cul_uvector_minmax           (const CulUVector *this, size_t *min, size_t *max);
void      cul_uvector_minmax_index     (const CulUVector *this, size_t *min_i, size_t *max_i);
size_t    cul_uvectorview_min          (const CulUVectorView *this);
size_t    cul_uvectorview_min_index    (const CulUVectorView *this);
size_t    cul_uvectorview_max          (const CulUVectorView *this);
size_t    cul_uvectorview_max_index    (const CulUVectorView *this);
void      cul_uvectorview_minmax       (const CulUVectorView *this, size_t *min, size_t *max);
void      cul_uvectorview_minmax_index (const CulUVectorView *this, size_t *min_i, size_t *max_i);

double    cul_uvector_sum              (const CulUVector *this);
double    cul_uvector_mean             (const CulUVector *this);
double    cul_uvector_variance         (const CulUVector *this);
double    cul_uvector_variance_mean    (const CulUVector *this, double mean);
double    cul_uvectorview_sum          (const CulUVectorView *this);
double    cul_uvectorview_mean         (const CulUVectorView *this);
double    cul_uvectorview_variance     (const CulUVectorView *this);
double    cul_uvectorview_variance_mean(const CulUVectorView *this, double mean);

void      cul_uvector_sort_asc         (CulUVector *this);
void      cul_uvector_sort_desc        (CulUVector *this);
size_t    cul_uvector_unique           (CulUVector *this);
size_t    cul_uvector_find             (const CulUVector *this, size_t offset, size_t key);
size_t    cul_uvector_bfind            (const CulUVector *this, size_t key);
void      cul_uvectorview_sort_asc     (CulUVectorView *this);
void      cul_uvectorview_sort_desc    (CulUVectorView *this);
size_t    cul_uvectorview_unique       (CulUVectorView *this);
size_t    cul_uvectorview_find         (const CulUVectorView *this, size_t offset, size_t key);
size_t    cul_uvectorview_bfind        (const CulUVectorView *this, size_t key);

cul_errno cul_uvector_fprintf          (FILE *stream, const CulUVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvector_fscanf           (FILE *stream, CulUVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fprintf      (FILE *stream, const CulUVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_uvectorview_fscanf       (FILE *stream, CulUVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline CulUVector *cul_uvector_new_struct() {
	return cul_slab_new(sizeof(CulUVector));
}

static inline void cul_uvector_free_struct(CulUVector *this) {
	cul_slab_free(sizeof(CulUVector), this);
}

static inline CulUVector *cul_uvector_init_struct(CulUVector *this, size_t *data, size_t reserved, size_t size) {
	this->reserved = reserved;
	this->size = size;
	this->data = data;
	return this;
}

static inline CulUVectorView *cul_uvectorview_new_struct() {
	return cul_slab_new(sizeof(CulUVectorView));
}

static inline void cul_uvectorview_free_struct(CulUVectorView *this) {
	cul_slab_free(sizeof(CulUVectorView), this);
}

static inline CulUVectorView *cul_uvectorview_init_struct(CulUVectorView *this, size_t *data, size_t size, size_t stride) {
	this->size = size;
	this->stride = stride;
	this->data = data;
	return this;
}

static inline size_t cul_uvector_get(const CulUVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x];
}

static inline void cul_uvector_set(CulUVector *this, size_t x, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x] = value;
}

static inline size_t *cul_uvector_ptr(CulUVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline const size_t *cul_uvector_const_ptr(const CulUVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline size_t cul_uvectorview_get(const CulUVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x * this->stride];
}

static inline void cul_uvectorview_set(CulUVectorView *this, size_t x, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x * this->stride] = value;
}

static inline size_t *cul_uvectorview_ptr(CulUVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline size_t *cul_uvectorview_next(CulUVectorView *this, size_t *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

static inline const size_t *cul_uvectorview_const_ptr(const CulUVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline const size_t *cul_uvectorview_const_next(const CulUVectorView *this, const size_t *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

#endif /* __CUL_UVECTOR_H__ */
