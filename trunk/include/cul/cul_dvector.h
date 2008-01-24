#ifndef __CUL_DVECTOR_H__
#define __CUL_DVECTOR_H__

#include <cul/cul_global.h>

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

static inline CulDVector     *cul_dvector_new_struct     ();
static inline void            cul_dvector_free_struct    (CulDVector *this);
static inline CulDVector     *cul_dvector_init_struct    (CulDVector *this, double *data, size_t reserved, size_t size);
static inline CulDVectorView *cul_dvectorview_new_struct ();
static inline void            cul_dvectorview_free_struct(CulDVectorView *this);
static inline CulDVectorView *cul_dvectorview_init_struct(CulDVectorView *this, double *data, size_t size, size_t stride);

static inline double          cul_dvector_get            (const CulDVector *this, size_t x);
static inline void            cul_dvector_set            (CulDVector *this, size_t x, double value);
static inline double         *cul_dvector_ptr            (CulDVector *this, size_t x);
static inline const double   *cul_dvector_const_ptr      (const CulDVector *this, size_t x);
static inline double          cul_dvectorview_get        (const CulDVectorView *this, size_t x);
static inline void            cul_dvectorview_set        (CulDVectorView *this, size_t x, double value);
static inline double         *cul_dvectorview_ptr        (CulDVectorView *this, size_t x);
static inline const double   *cul_dvectorview_const_ptr  (const CulDVectorView *this, size_t x);
static inline double         *cul_dvectorview_next       (CulDVectorView *this, double *ptr);
static inline const double   *cul_dvectorview_const_next (const CulDVectorView *this, const double *ptr);

CulDVector     *cul_dvector_new          (size_t size);
CulDVector     *cul_dvector_new_empty    ();
CulDVector     *cul_dvector_clone        (CulDVector *this);
CulDVector     *cul_dvector_clone_view   (CulDVectorView *this);
void            cul_dvector_free         (CulDVector *this);
CulDVectorView *cul_dvectorview_new      ();
void            cul_dvectorview_free     (CulDVectorView *this);

CulDVectorView *cul_dvectorview_vector   (CulDVectorView *this, const CulDVector *base);
CulDVectorView *cul_dvectorview_subvector(CulDVectorView *this, const CulDVector *base, size_t base_offset, size_t base_size, size_t base_stride);

cul_errno cul_dvector_copy                 (CulDVector *this, const CulDVector *other);
cul_errno cul_dvector_copy_offset          (CulDVector *this, const CulDVector *other, size_t offset);
cul_errno cul_dvector_copy_subvector       (CulDVector *this, const CulDVector *other, size_t other_offset);
cul_errno cul_dvector_copy_view            (CulDVector *this, const CulDVectorView *other);
cul_errno cul_dvector_copy_view_offset     (CulDVector *this, const CulDVectorView *other, size_t offset);
cul_errno cul_dvectorview_copy             (CulDVectorView *this, const CulDVectorView *other);
cul_errno cul_dvectorview_copy_vector      (CulDVectorView *this, const CulDVector *other);

cul_errno cul_dvector_swap                 (CulDVector *this, CulDVector *other);
cul_errno cul_dvectorview_swap             (CulDVectorView *this, CulDVectorView *other);
void      cul_dvector_reverse              (CulDVector *this);
void      cul_dvectorview_reverse          (CulDVectorView *this);

cul_errno cul_dvector_resize               (CulDVector *this, size_t size);
cul_errno cul_dvector_resize_empty         (CulDVector *this, size_t size);
cul_errno cul_dvector_reserve              (CulDVector *this, size_t size);
cul_errno cul_dvector_shrink               (CulDVector *this);
cul_errno cul_dvector_insert               (CulDVector *this, size_t offset, double value);
cul_errno cul_dvector_insert_vector        (CulDVector *this, size_t offset, const CulDVector *other);
cul_errno cul_dvector_insert_view          (CulDVector *this, size_t offset, const CulDVectorView *other);
cul_errno cul_dvector_push_back            (CulDVector *this, double value);
cul_errno cul_dvector_remove               (CulDVector *this, size_t offset);
cul_errno cul_dvector_remove_range         (CulDVector *this, size_t offset, size_t size);
cul_errno cul_dvector_pop_back             (CulDVector *this);

void      cul_dvector_set_all              (CulDVector *this, double value);
void      cul_dvector_set_basis            (CulDVector *this, size_t index, double value, double basis);
void      cul_dvector_add_constant         (CulDVector *this, double value);
void      cul_dvector_scale                (CulDVector *this, double value);
void      cul_dvector_zero                 (CulDVector *this);
cul_errno cul_dvector_add                  (CulDVector *this, const CulDVector *other);
cul_errno cul_dvector_sub                  (CulDVector *this, const CulDVector *other);
cul_errno cul_dvector_mul                  (CulDVector *this, const CulDVector *other);
cul_errno cul_dvector_div                  (CulDVector *this, const CulDVector *other);
void      cul_dvectorview_set_all          (CulDVectorView *this, double value);
void      cul_dvectorview_set_basis        (CulDVectorView *this, size_t index, double value, double basis);
void      cul_dvectorview_add_constant     (CulDVectorView *this, double value);
void      cul_dvectorview_scale            (CulDVectorView *this, double value);
cul_errno cul_dvectorview_add              (CulDVectorView *this, const CulDVectorView *other);
cul_errno cul_dvectorview_sub              (CulDVectorView *this, const CulDVectorView *other);
cul_errno cul_dvectorview_mul              (CulDVectorView *this, const CulDVectorView *other);
cul_errno cul_dvectorview_div              (CulDVectorView *this, const CulDVectorView *other);

double    cul_dvector_min                  (const CulDVector *this);
size_t    cul_dvector_min_index            (const CulDVector *this);
double    cul_dvector_max                  (const CulDVector *this);
size_t    cul_dvector_max_index            (const CulDVector *this);
void      cul_dvector_minmax               (const CulDVector *this, double *min, double *max);
void      cul_dvector_minmax_index         (const CulDVector *this, size_t *min_i, size_t *max_i);
double    cul_dvectorview_min              (const CulDVectorView *this);
size_t    cul_dvectorview_min_index        (const CulDVectorView *this);
double    cul_dvectorview_max              (const CulDVectorView *this);
size_t    cul_dvectorview_max_index        (const CulDVectorView *this);
void      cul_dvectorview_minmax           (const CulDVectorView *this, double *min, double *max);
void      cul_dvectorview_minmax_index     (const CulDVectorView *this, size_t *min_i, size_t *max_i);

double    cul_dvector_mean                 (const CulDVector *this);
double    cul_dvector_mean_nan             (const CulDVector *this);
double    cul_dvector_variance             (const CulDVector *this);
double    cul_dvector_variance_nan         (const CulDVector *this);
double    cul_dvector_variance_mean        (const CulDVector *this, double mean);
double    cul_dvector_variance_mean_nan    (const CulDVector *this, double mean);
double    cul_dvectorview_mean             (const CulDVectorView *this);
double    cul_dvectorview_mean_nan         (const CulDVectorView *this);
double    cul_dvectorview_variance         (const CulDVectorView *this);
double    cul_dvectorview_variance_nan     (const CulDVectorView *this);
double    cul_dvectorview_variance_mean    (const CulDVectorView *this, double mean);
double    cul_dvectorview_variance_mean_nan(const CulDVectorView *this, double mean);

void      cul_dvector_sort_asc             (CulDVector *this);
void      cul_dvector_sort_desc            (CulDVector *this);
size_t    cul_dvector_unique               (CulDVector *this);
size_t    cul_dvector_find                 (const CulDVector *this, size_t offset, double key);
size_t    cul_dvector_bfind                (const CulDVector *this, double key);
void      cul_dvectorview_sort_asc         (CulDVectorView *this);
void      cul_dvectorview_sort_desc        (CulDVectorView *this);
size_t    cul_dvectorview_unique           (CulDVectorView *this);
size_t    cul_dvectorview_find             (const CulDVectorView *this, size_t offset, double key);
size_t    cul_dvectorview_bfind            (const CulDVectorView *this, double key);

/* implementations */

static inline CulDVector *cul_dvector_new_struct() {
	return cul_slab_new(sizeof(CulDVector));
}

static inline void cul_dvector_free_struct(CulDVector *this) {
	cul_slab_free(sizeof(CulDVector), this);
}

static inline CulDVector *cul_dvector_init_struct(CulDVector *this, double *data, size_t reserved, size_t size) {
	this->reserved = reserved;
	this->size = size;
	this->data = data;
	return this;
}

static inline CulDVectorView *cul_dvectorview_new_struct() {
	return cul_slab_new(sizeof(CulDVectorView));
}

static inline void cul_dvectorview_free_struct(CulDVectorView *this) {
	cul_slab_free(sizeof(CulDVectorView), this);
}

static inline CulDVectorView *cul_dvectorview_init_struct(CulDVectorView *this, double *data, size_t size, size_t stride) {
	this->size = size;
	this->stride = stride;
	this->data = data;
	return this;
}

static inline double cul_dvector_get(const CulDVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0.0, CUL_EBADPOS);
#endif
	return this->data[x];
}

static inline void cul_dvector_set(CulDVector *this, size_t x, double value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x] = value;
}

static inline double *cul_dvector_ptr(CulDVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline const double *cul_dvector_const_ptr(const CulDVector *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x);
}

static inline double cul_dvectorview_get(const CulDVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[x * this->stride];
}

static inline void cul_dvectorview_set(CulDVectorView *this, size_t x, double value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[x * this->stride] = value;
}

static inline double *cul_dvectorview_ptr(CulDVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline const double *cul_dvectorview_const_ptr(const CulDVectorView *this, size_t x) {
#ifdef CUL_RANGE_CHECK
	if( x > this->size ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + x * this->stride);
}

static inline double *cul_dvectorview_next(CulDVectorView *this, double *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

static inline const double *cul_dvectorview_const_next(const CulDVectorView *this, const double *ptr) {
#ifdef CUL_RANGE_CHECK
	if( ptr > this->data + this->size * this->stride ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (ptr + this->stride);
}

#endif /* __CUL_DVECTOR_H__ */
