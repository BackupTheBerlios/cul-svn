#ifndef __CUL_IVECTOR_H__
#define __CUL_IVECTOR_H__

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

static inline CulIVector     *cul_ivector_new_struct     ();
static inline void            cul_ivector_free_struct    (CulIVector *this);
static inline CulIVector     *cul_ivector_init_struct    (CulIVector *this, int *data, size_t reserved, size_t size);
static inline CulIVectorView *cul_ivectorview_new_struct ();
static inline void            cul_ivectorview_free_struct(CulIVectorView *this);
static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *this, int *data, size_t size, size_t stride);

static inline int             cul_ivector_get            (const CulIVector *this, size_t x);
static inline void            cul_ivector_set            (CulIVector *this, size_t x, int value);
static inline int            *cul_ivector_ptr            (CulIVector *this, size_t x);
static inline const int      *cul_ivector_const_ptr      (const CulIVector *this, size_t x);
static inline int             cul_ivectorview_get        (const CulIVectorView *this, size_t x);
static inline void            cul_ivectorview_set        (CulIVectorView *this, size_t x, int value);
static inline int            *cul_ivectorview_ptr        (CulIVectorView *this, size_t x);
static inline int            *cul_ivectorview_next       (CulIVectorView *this, int *ptr);
static inline int            *cul_ivectorview_next       (CulIVectorView *this, int *ptr);
static inline const int      *cul_ivectorview_const_next (const CulIVectorView *this, const int *ptr);

CulIVector     *cul_ivector_new          (size_t size);
CulIVector     *cul_ivector_new_empty    ();
CulIVector     *cul_ivector_clone        (CulIVector *this);
CulIVector     *cul_ivector_clone_view   (CulIVectorView *this);
void            cul_ivector_free         (CulIVector *this);
CulIVectorView *cul_ivectorview_new      ();
void            cul_ivectorview_free     (CulIVectorView *this);

CulIVectorView *cul_ivectorview_vector   (CulIVectorView *this, const CulIVector *base);
CulIVectorView *cul_ivectorview_subvector(CulIVectorView *this, const CulIVector *base, size_t base_offset, size_t base_size, size_t base_stride);

cul_errno cul_ivector_copy             (CulIVector *this, const CulIVector *other);
cul_errno cul_ivector_copy_offset      (CulIVector *this, const CulIVector *other, size_t offset);
cul_errno cul_ivector_copy_subvector   (CulIVector *this, const CulIVector *other, size_t other_offset);
cul_errno cul_ivector_copy_view        (CulIVector *this, const CulIVectorView *other);
cul_errno cul_ivectorview_copy         (CulIVectorView *this, const CulIVectorView *other);
cul_errno cul_ivectorview_copy_vector  (CulIVectorView *this, const CulIVector *other);

cul_errno cul_ivector_swap             (CulIVector *this, CulIVector *other);
cul_errno cul_ivectorview_swap         (CulIVectorView *this, CulIVectorView *other);
void      cul_ivector_reverse          (CulIVector *this);
void      cul_ivectorview_reverse      (CulIVectorView *this);

cul_errno cul_ivector_resize           (CulIVector *this, size_t size);
cul_errno cul_ivector_resize_empty     (CulIVector *this, size_t size);
cul_errno cul_ivector_reserve          (CulIVector *this, size_t size);
cul_errno cul_ivector_shrink           (CulIVector *this);
cul_errno cul_ivector_insert           (CulIVector *this, size_t offset, int value);
cul_errno cul_ivector_insert_vector    (CulIVector *this, size_t offset, const CulIVector *other);
cul_errno cul_ivector_insert_view      (CulIVector *this, size_t offset, const CulIVectorView *other);
cul_errno cul_ivector_push_back        (CulIVector *this, int value);
cul_errno cul_ivector_remove           (CulIVector *this, size_t offset);
cul_errno cul_ivector_remove_range     (CulIVector *this, size_t offset, size_t size);
cul_errno cul_ivector_pop_back         (CulIVector *this);

void      cul_ivector_set_all          (CulIVector *this, int value);
void      cul_ivector_set_basis        (CulIVector *this, size_t index, int value, int basis);
void      cul_ivector_add_constant     (CulIVector *this, double value);
void      cul_ivector_scale            (CulIVector *this, double value);
void      cul_ivector_zero             (CulIVector *this);
cul_errno cul_ivector_add              (CulIVector *this, const CulIVector *other);
cul_errno cul_ivector_sub              (CulIVector *this, const CulIVector *other);
cul_errno cul_ivector_mul              (CulIVector *this, const CulIVector *other);
cul_errno cul_ivector_div              (CulIVector *this, const CulIVector *other);
void      cul_ivectorview_set_all      (CulIVectorView *this, int value);
void      cul_ivectorview_set_basis    (CulIVectorView *this, size_t index, int value, int basis);
void      cul_ivectorview_add_constant (CulIVectorView *this, double value);
void      cul_ivectorview_scale        (CulIVectorView *this, double value);
cul_errno cul_ivectorview_add          (CulIVectorView *this, const CulIVectorView *other);
cul_errno cul_ivectorview_sub          (CulIVectorView *this, const CulIVectorView *other);
cul_errno cul_ivectorview_mul          (CulIVectorView *this, const CulIVectorView *other);
cul_errno cul_ivectorview_div          (CulIVectorView *this, const CulIVectorView *other);

int       cul_ivector_min              (const CulIVector *this);
size_t    cul_ivector_min_index        (const CulIVector *this);
int       cul_ivector_max              (const CulIVector *this);
size_t    cul_ivector_max_index        (const CulIVector *this);
void      cul_ivector_minmax           (const CulIVector *this, int *min, int *max);
void      cul_ivector_minmax_index     (const CulIVector *this, size_t *min_i, size_t *max_i);
int       cul_ivectorview_min          (const CulIVectorView *this);
size_t    cul_ivectorview_min_index    (const CulIVectorView *this);
int       cul_ivectorview_max          (const CulIVectorView *this);
size_t    cul_ivectorview_max_index    (const CulIVectorView *this);
void      cul_ivectorview_minmax       (const CulIVectorView *this, int *min, int *max);
void      cul_ivectorview_minmax_index (const CulIVectorView *this, size_t *min_i, size_t *max_i);

double    cul_ivector_sum              (const CulIVector *this);
double    cul_ivector_mean             (const CulIVector *this);
double    cul_ivector_variance         (const CulIVector *this);
double    cul_ivector_variance_mean    (const CulIVector *this, double mean);
double    cul_ivectorview_sum          (const CulIVectorView *this);
double    cul_ivectorview_mean         (const CulIVectorView *this);
double    cul_ivectorview_variance     (const CulIVectorView *this);
double    cul_ivectorview_variance_mean(const CulIVectorView *this, double mean);

void      cul_ivector_sort_asc         (CulIVector *this);
void      cul_ivector_sort_desc        (CulIVector *this);
size_t    cul_ivector_unique           (CulIVector *this);
size_t    cul_ivector_find             (const CulIVector *this, size_t offset, int key);
size_t    cul_ivector_bfind            (const CulIVector *this, int key);
void      cul_ivectorview_sort_asc     (CulIVectorView *this);
void      cul_ivectorview_sort_desc    (CulIVectorView *this);
size_t    cul_ivectorview_unique       (CulIVectorView *this);
size_t    cul_ivectorview_find         (const CulIVectorView *this, size_t offset, int key);
size_t    cul_ivectorview_bfind        (const CulIVectorView *this, int key);

cul_errno cul_ivector_fprintf          (FILE *stream, const CulIVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivector_fscanf           (FILE *stream, CulIVector *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fprintf      (FILE *stream, const CulIVectorView *this, const char *format, const char *separator, const char *begin, const char *end);
cul_errno cul_ivectorview_fscanf       (FILE *stream, CulIVectorView *this, const char *format, const char *separator, const char *begin, const char *end);

/* implementations */

static inline CulIVector *cul_ivector_new_struct() {
	return cul_slab_new(sizeof(CulIVector));
}

static inline void cul_ivector_free_struct(CulIVector *this) {
	cul_slab_free(sizeof(CulIVector), this);
}

static inline CulIVector *cul_ivector_init_struct(CulIVector *this, int *data, size_t reserved, size_t size) {
	this->reserved = reserved;
	this->size = size;
	this->data = data;
	return this;
}

static inline CulIVectorView *cul_ivectorview_new_struct() {
	return cul_slab_new(sizeof(CulIVectorView));
}

static inline void cul_ivectorview_free_struct(CulIVectorView *this) {
	cul_slab_free(sizeof(CulIVectorView), this);
}

static inline CulIVectorView *cul_ivectorview_init_struct(CulIVectorView *this, int *data, size_t size, size_t stride) {
	this->size = size;
	this->stride = stride;
	this->data = data;
	return this;
}

static inline int cul_ivector_get(const CulIVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x];
}

static inline void cul_ivector_set(CulIVector *this, size_t x, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x] = value;
	return;
}

static inline int *cul_ivector_ptr(CulIVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline const int *cul_ivector_const_ptr(const CulIVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline int cul_ivectorview_get(const CulIVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x * this->stride];
}

static inline void cul_ivectorview_set(CulIVectorView *this, size_t x, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x * this->stride] = value;
	return;
}

static inline int *cul_ivectorview_ptr(CulIVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline const int *cul_ivectorview_const_ptr(const CulIVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline int *cul_ivectorview_next(CulIVectorView *this, int *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

static inline const int *cul_ivectorview_const_next(const CulIVectorView *this, const int *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

#endif /* __CUL_IVECTOR_H__ */
