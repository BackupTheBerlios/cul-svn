#ifndef __CUL_CVECTOR_H__
#define __CUL_CVECTOR_H__

#include <cul/cul_global.h>

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

static inline CulCVector     *cul_cvector_new_struct     ();
static inline void            cul_cvector_free_struct    (CulCVector *this);
static inline CulCVector     *cul_cvector_init_struct    (CulCVector *this, char *data, size_t size, size_t reserved);
static inline CulCVectorView *cul_cvectorview_new_struct ();
static inline void            cul_cvectorview_free_struct(CulCVectorView *this);
static inline CulCVectorView *cul_cvectorview_init_struct(CulCVectorView *this, char *data, size_t size, size_t stride);

static inline char            cul_cvector_get            (const CulCVector *this, size_t x);
static inline void            cul_cvector_set            (CulCVector *this, size_t x, char value);
static inline char           *cul_cvector_ptr            (CulCVector *this, size_t x);
static inline const char     *cul_cvector_const_ptr      (const CulCVector *this, size_t x);
static inline char            cul_cvectorview_get        (const CulCVectorView *this, size_t x);
static inline void            cul_cvectorview_set        (CulCVectorView *this, size_t x, char value);
static inline char           *cul_cvectorview_ptr        (CulCVectorView *this, size_t x);
static inline char           *cul_cvectorview_next       (CulCVectorView *this, char *ptr);
static inline const char     *cul_cvectorview_const_ptr  (const CulCVectorView *this, size_t x);
static inline const char     *cul_cvectorview_const_next (const CulCVectorView *this, const char *ptr);

CulCVector     *cul_cvector_new          (size_t size);
CulCVector     *cul_cvector_new_empty    ();
CulCVector     *cul_cvector_clone        (CulCVector *this);
CulCVector     *cul_cvector_clone_view   (CulCVectorView *this);
void            cul_cvector_free         (CulCVector *this);
CulCVectorView *cul_cvectorview_new      ();
void            cul_cvectorview_free     (CulCVectorView *this);

CulCVectorView *cul_cvectorview_vector   (CulCVectorView *this, const CulCVector *base);
CulCVectorView *cul_cvectorview_subvector(CulCVectorView *this, const CulCVector *base, size_t base_offset, size_t base_size, size_t base_stride);

cul_errno cul_cvector_copy             (CulCVector *this, const CulCVector *other);
cul_errno cul_cvector_copy_offset      (CulCVector *this, const CulCVector *other, size_t offset);
cul_errno cul_cvector_copy_subvector   (CulCVector *this, const CulCVector *other, size_t other_offset);
cul_errno cul_cvector_copy_view        (CulCVector *this, const CulCVectorView *other);
cul_errno cul_cvector_copy_view_offset (CulCVector *this, const CulCVectorView *other, size_t offset);
cul_errno cul_cvectorview_copy         (CulCVectorView *this, const CulCVectorView *other);
cul_errno cul_cvectorview_copy_vector  (CulCVectorView *this, const CulCVector *other);

cul_errno cul_cvector_swap             (CulCVector *this, CulCVector *other);
cul_errno cul_cvectorview_swap         (CulCVectorView *this, CulCVectorView *other);
void      cul_cvector_reverse          (CulCVector *this);
void      cul_cvectorview_reverse      (CulCVectorView *this);

cul_errno cul_cvector_resize           (CulCVector *this, size_t size);
cul_errno cul_cvector_resize_empty     (CulCVector *this, size_t size);
cul_errno cul_cvector_reserve          (CulCVector *this, size_t size);
cul_errno cul_cvector_shrink           (CulCVector *this);
cul_errno cul_cvector_insert           (CulCVector *this, size_t offset, char value);
cul_errno cul_cvector_insert_vector    (CulCVector *this, size_t offset, const CulCVector *other);
cul_errno cul_cvector_insert_view      (CulCVector *this, size_t offset, const CulCVectorView *other);
cul_errno cul_cvector_push_back        (CulCVector *this, char value);
cul_errno cul_cvector_remove           (CulCVector *this, size_t offset);
cul_errno cul_cvector_remove_range     (CulCVector *this, size_t offset, size_t size);
cul_errno cul_cvector_pop_back         (CulCVector *this);

void      cul_cvector_set_all          (CulCVector *this, char value);
void      cul_cvector_set_basis        (CulCVector *this, size_t index, char value, char basis);
void      cul_cvector_add_constant     (CulCVector *this, double value);
void      cul_cvector_scale            (CulCVector *this, double value);
void      cul_cvector_zero             (CulCVector *this);
cul_errno cul_cvector_add              (CulCVector *this, const CulCVector *other);
cul_errno cul_cvector_sub              (CulCVector *this, const CulCVector *other);
cul_errno cul_cvector_mul              (CulCVector *this, const CulCVector *other);
cul_errno cul_cvector_div              (CulCVector *this, const CulCVector *other);
void      cul_cvectorview_set_all      (CulCVectorView *this, char value);
void      cul_cvectorview_set_basis    (CulCVectorView *this, size_t index, char value, char basis);
void      cul_cvectorview_add_constant (CulCVectorView *this, double value);
void      cul_cvectorview_scale        (CulCVectorView *this, double value);
cul_errno cul_cvectorview_add          (CulCVectorView *this, const CulCVectorView *other);
cul_errno cul_cvectorview_sub          (CulCVectorView *this, const CulCVectorView *other);
cul_errno cul_cvectorview_mul          (CulCVectorView *this, const CulCVectorView *other);
cul_errno cul_cvectorview_div          (CulCVectorView *this, const CulCVectorView *other);

char      cul_cvector_min              (const CulCVector *this);
size_t    cul_cvector_min_index        (const CulCVector *this);
char      cul_cvector_max              (const CulCVector *this);
size_t    cul_cvector_max_index        (const CulCVector *this);
void      cul_cvector_minmax           (const CulCVector *this, char *min, char *max);
void      cul_cvector_minmax_index     (const CulCVector *this, size_t *min_i, size_t *max_i);
char      cul_cvectorview_min          (const CulCVectorView *this);
size_t    cul_cvectorview_min_index    (const CulCVectorView *this);
char      cul_cvectorview_max          (const CulCVectorView *this);
size_t    cul_cvectorview_max_index    (const CulCVectorView *this);
void      cul_cvectorview_minmax       (const CulCVectorView *this, char *min, char *max);
void      cul_cvectorview_minmax_index (const CulCVectorView *this, size_t *min_i, size_t *max_i);

double    cul_cvector_mean             (const CulCVector *this);
double    cul_cvector_variance         (const CulCVector *this);
double    cul_cvector_variance_mean    (const CulCVector *this, double mean);
double    cul_cvectorview_mean         (const CulCVectorView *this);
double    cul_cvectorview_variance     (const CulCVectorView *this);
double    cul_cvectorview_variance_mean(const CulCVectorView *this, double mean);

void      cul_cvector_sort_asc         (CulCVector *this);
void      cul_cvector_sort_desc        (CulCVector *this);
size_t    cul_cvector_find             (const CulCVector *this, size_t offset, char key);
size_t    cul_cvector_bfind            (const CulCVector *this, char key);
size_t    cul_cvector_unique           (CulCVector *this);
void      cul_cvectorview_sort_asc     (CulCVectorView *this);
void      cul_cvectorview_sort_desc    (CulCVectorView *this);
size_t    cul_cvectorview_unique       (CulCVectorView *this);
size_t    cul_cvectorview_find         (const CulCVectorView *this, size_t offset, char key);
size_t    cul_cvectorview_bfind        (const CulCVectorView *this, char key);

/* implementations */

static inline CulCVector *cul_cvector_new_struct() {
	return cul_slab_new(sizeof(CulCVector));
}

static inline void cul_cvector_free_struct(CulCVector *this) {
	cul_slab_free(sizeof(CulCVector), this);
}

static inline CulCVector *cul_cvector_init_struct(CulCVector *this, char *data, size_t size, size_t reserved) {
	this->reserved = reserved;
	this->size = size;
	this->data = data;
	return this;
}

static inline CulCVectorView *cul_cvectorview_new_struct() {
	return cul_slab_new(sizeof(CulCVectorView));
}

static inline void cul_cvectorview_free_struct(CulCVectorView *this) {
	cul_slab_free(sizeof(CulCVectorView), this);
}

static inline CulCVectorView *cul_cvectorview_init_struct(CulCVectorView *this, char *data, size_t size, size_t stride) {
	this->size = size;
	this->stride = stride;
	this->data = data;
	return this;
}

static inline char cul_cvector_get(const CulCVector *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[i];
}

static inline void cul_cvector_set(CulCVector *this, size_t i, char value) {
#ifdef CUL_RANGE_CHECK
	if( i >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[i] = value;
}

static inline char *cul_cvector_ptr(CulCVector *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + i);
}

static inline const char *cul_cvector_const_ptr(const CulCVector *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + i);
}

static inline char cul_cvectorview_get(const CulCVectorView *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[i * this->stride];
}

static inline void cul_cvectorview_set(CulCVectorView *this, size_t i, char value) {
#ifdef CUL_RANGE_CHECK
	if( i >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[i * this->stride] = value;
}

static inline char *cul_cvectorview_ptr(CulCVectorView *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + i * this->stride);
}

static inline char *cul_cvectorview_next(CulCVectorView *this, char *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

static inline const char *cul_cvectorview_const_ptr(const CulCVectorView *this, size_t i) {
#ifdef CUL_RANGE_CHECK
	if( i > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + i * this->stride);
}

static inline const char *cul_cvectorview_const_next(const CulCVectorView *this, const char *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

#endif /* __CUL_CVECTOR_H__ */
