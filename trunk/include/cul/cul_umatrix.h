#ifndef __CUL_UMATRIX_H__
#define __CUL_UMATRIX_H__

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>

#define CUL_UMATRIX(ptr)     ((CulUMatrix *)(ptr))
#define CUL_UMATRIXVIEW(ptr) ((CulUMatrixView *)(ptr))

typedef struct _CulUMatrix     CulUMatrix;
typedef struct _CulUMatrixView CulUMatrixView;

struct _CulUMatrix {
	size_t *data;
	size_t size_x;
	size_t size_y;
};

struct _CulUMatrixView {
	size_t *data;
	size_t size_x;
	size_t size_y;
	size_t tda;
};

static inline CulUMatrix     *cul_umatrix_new_struct     ();
static inline void            cul_umatrix_free_struct    (CulUMatrix *this);
static inline CulUMatrix     *cul_umatrix_init_struct    (CulUMatrix *this, size_t *data, size_t size_x, size_t size_y);
static inline CulUMatrixView *cul_umatrixview_new_struct ();
static inline void            cul_umatrixview_free_struct(CulUMatrixView *this);
static inline CulUMatrixView *cul_umatrixview_init_struct(CulUMatrixView *this, size_t *data, size_t size_x, size_t size_y, size_t tda);

static inline size_t          cul_umatrix_get            (const CulUMatrix *this, size_t x, size_t y);
static inline void            cul_umatrix_set            (CulUMatrix *this, size_t x, size_t y, size_t val);
static inline size_t         *cul_umatrix_ptr            (CulUMatrix *this, size_t x, size_t y);
static inline const size_t   *cul_umatrix_const_ptr      (const CulUMatrix *this, size_t x, size_t y);
static inline size_t          cul_umatrixview_get        (const CulUMatrixView *this, size_t x, size_t y);
static inline void            cul_umatrixview_set        (CulUMatrixView *this, size_t x, size_t y, size_t val);
static inline size_t         *cul_umatrixview_ptr        (CulUMatrixView *this, size_t x, size_t y);
static inline const size_t   *cul_umatrixview_const_ptr  (const CulUMatrixView *this, size_t x, size_t y);

CulUMatrix     *cul_umatrix_new          (size_t x, size_t y);
CulUMatrix     *cul_umatrix_new_empty    ();
CulUMatrix     *cul_umatrix_clone        (CulUMatrix *this);
CulUMatrix     *cul_umatrix_clone_view   (CulUMatrixView *this);
void            cul_umatrix_free         (CulUMatrix *this);
CulUMatrixView *cul_umatrixview_new      ();
void            cul_umatrixview_free     (CulUMatrixView *this);

CulUMatrixView *cul_umatrixview_matrix         (CulUMatrixView *this, CulUMatrix *base);
CulUMatrixView *cul_umatrixview_submatrix      (CulUMatrixView *this, CulUMatrix *base, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulUVectorView *cul_uvectorview_matrix_row     (CulUVectorView *this, const CulUMatrix *base, size_t base_row);
CulUVectorView *cul_uvectorview_matrix_col     (CulUVectorView *this, const CulUMatrix *base, size_t base_col);
CulUVectorView *cul_uvectorview_matrix_diag    (CulUVectorView *this, const CulUMatrix *base, size_t offset, int sub_or_sup);
CulUVectorView *cul_uvectorview_matrixview_row (CulUVectorView *this, const CulUMatrixView *base, size_t base_row);
CulUVectorView *cul_uvectorview_matrixview_col (CulUVectorView *this, const CulUMatrixView *base, size_t base_col);
CulUVectorView *cul_uvectorview_matrixview_diag(CulUVectorView *this, const CulUMatrixView *base, size_t offset, int sub_or_sup);

cul_errno cul_umatrix_copy             (CulUMatrix *this, const CulUMatrix *other);
cul_errno cul_umatrix_copy_offset      (CulUMatrix *this, const CulUMatrix *other, size_t offset_x, size_t offset_y);
cul_errno cul_umatrix_copy_submatrix   (CulUMatrix *this, const CulUMatrix *other, size_t other_offset_x, size_t other_offset_y);
cul_errno cul_umatrix_copy_row         (CulUMatrix *this, const CulUMatrix *other, size_t row, size_t other_row);
cul_errno cul_umatrix_copy_col         (CulUMatrix *this, const CulUMatrix *other, size_t col, size_t other_col);
cul_errno cul_umatrix_copy_view        (CulUMatrix *this, const CulUMatrixView *other);
cul_errno cul_umatrix_copy_view_offset (CulUMatrix *this, const CulUMatrixView *other, size_t offset_x, size_t offset_y);
cul_errno cul_umatrixview_copy         (CulUMatrixView *this, const CulUMatrixView *other);
cul_errno cul_umatrixview_copy_matrix  (CulUMatrixView *this, const CulUMatrix *other);

cul_errno cul_umatrix_swap             (CulUMatrix *this, CulUMatrix *other);
cul_errno cul_umatrix_swap_row         (CulUMatrix *this, CulUMatrix *other, size_t row, size_t other_row);
cul_errno cul_umatrix_swap_col         (CulUMatrix *this, CulUMatrix *other, size_t col, size_t other_col);
cul_errno cul_umatrixview_swap         (CulUMatrixView *this, CulUMatrixView *other);
cul_errno cul_umatrix_transpose        (CulUMatrix *this);
cul_errno cul_umatrixview_transpose    (CulUMatrixView *this);

cul_errno cul_umatrix_resize           (CulUMatrix *this, size_t x, size_t y);
cul_errno cul_umatrix_resize_empty     (CulUMatrix *this, size_t x, size_t y);
cul_errno cul_umatrix_insert_row       (CulUMatrix *this, size_t row);
cul_errno cul_umatrix_insert_col       (CulUMatrix *this, size_t col);
cul_errno cul_umatrix_remove_row       (CulUMatrix *this, size_t row);
cul_errno cul_umatrix_remove_col       (CulUMatrix *this, size_t col);

void      cul_umatrix_set_all          (CulUMatrix *this, size_t value);
void      cul_umatrix_set_diag         (CulUMatrix *this, size_t value, size_t diag);
void      cul_umatrix_add_constant     (CulUMatrix *this, double value);
void      cul_umatrix_scale            (CulUMatrix *this, double value);
void      cul_umatrix_zero             (CulUMatrix *this);
cul_errno cul_umatrix_add              (CulUMatrix *this, const CulUMatrix *other);
cul_errno cul_umatrix_sub              (CulUMatrix *this, const CulUMatrix *other);
cul_errno cul_umatrix_mul              (CulUMatrix *this, const CulUMatrix *other);
cul_errno cul_umatrix_div              (CulUMatrix *this, const CulUMatrix *other);
void      cul_umatrixview_set_all      (CulUMatrixView *this, size_t value);
void      cul_umatrixview_set_diag     (CulUMatrixView *this, size_t value, size_t diag);
void      cul_umatrixview_add_constant (CulUMatrixView *this, double value);
void      cul_umatrixview_scale        (CulUMatrixView *this, double value);
cul_errno cul_umatrixview_add          (CulUMatrixView *this, const CulUMatrixView *other);
cul_errno cul_umatrixview_sub          (CulUMatrixView *this, const CulUMatrixView *other);
cul_errno cul_umatrixview_mul          (CulUMatrixView *this, const CulUMatrixView *other);
cul_errno cul_umatrixview_div          (CulUMatrixView *this, const CulUMatrixView *other);

size_t    cul_umatrix_min              (const CulUMatrix *this);
size_t    cul_umatrix_min_index        (const CulUMatrix *this);
size_t    cul_umatrix_max              (const CulUMatrix *this);
size_t    cul_umatrix_max_index        (const CulUMatrix *this);
void      cul_umatrix_minmax           (const CulUMatrix *this, size_t *min, size_t *max);
void      cul_umatrix_minmax_index     (const CulUMatrix *this, size_t *min_i, size_t *max_i);
size_t    cul_umatrixview_min          (const CulUMatrixView *this);
size_t    cul_umatrixview_min_index    (const CulUMatrixView *this);
size_t    cul_umatrixview_max          (const CulUMatrixView *this);
size_t    cul_umatrixview_max_index    (const CulUMatrixView *this);
void      cul_umatrixview_minmax       (const CulUMatrixView *this, size_t *min, size_t *max);
void      cul_umatrixview_minmax_index (const CulUMatrixView *this, size_t *min_i, size_t *max_i);

double    cul_umatrix_mean             (const CulUMatrix *this);
double    cul_umatrix_variance         (const CulUMatrix *this);
double    cul_umatrix_variance_mean    (const CulUMatrix *this, double mean);
double    cul_umatrixview_mean         (const CulUMatrixView *this);
double    cul_umatrixview_variance     (const CulUMatrixView *this);
double    cul_umatrixview_variance_mean(const CulUMatrixView *this, double mean);

/* implementation */

static inline CulUMatrix *cul_umatrix_new_struct() {
	return cul_slab_new(sizeof(CulUMatrix));
}

static inline void cul_umatrix_free_struct(CulUMatrix *this) {
	cul_slab_free(sizeof(CulUMatrix), this);
}

static inline CulUMatrix *cul_umatrix_init_struct(CulUMatrix *this, size_t *data, size_t size_x, size_t size_y) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	return this;
}

static inline CulUMatrixView *cul_umatrixview_new_struct() {
	return cul_slab_new(sizeof(CulUMatrixView));
}

static inline void cul_umatrixview_free_struct(CulUMatrixView *this) {
	cul_slab_free(sizeof(CulUMatrixView), this);
}

static inline CulUMatrixView *cul_umatrixview_init_struct(CulUMatrixView *this, size_t *data, size_t size_x, size_t size_y, size_t tda) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	this->tda = tda;
	return this;
}

static inline size_t cul_umatrix_get(const CulUMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return *(this->data + this->size_x * y + x);
}

static inline void cul_umatrix_set(CulUMatrix *this, size_t x, size_t y, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(this->data + this->size_x * y + x) = value;
}

static inline size_t *cul_umatrix_ptr(CulUMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline const size_t *cul_umatrix_const_ptr(const CulUMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline size_t cul_umatrixview_get(const CulUMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[this->tda * y + x];
}

static inline void cul_umatrixview_set(CulUMatrixView *this, size_t x, size_t y, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[this->tda * y + x] = value;
}

static inline size_t *cul_umatrixview_ptr(CulUMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

static inline const size_t *cul_umatrixview_const_ptr(const CulUMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

#endif /* __CUL_IMATRIX_H__ */
