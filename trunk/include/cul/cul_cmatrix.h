#ifndef __CUL_CMATRIX_H__
#define __CUL_CMATRIX_H__

#include <cul/cul_global.h>
#include <cul/cul_cvector.h>

#define CUL_CMATRIX(ptr)     ((CulCMatrix *)(ptr))
#define CUL_CMATRIXVIEW(ptr) ((CulCMatrixView *)(ptr))

typedef struct _CulCMatrix     CulCMatrix;
typedef struct _CulCMatrixView CulCMatrixView;

struct _CulCMatrix {
	char *data;
	size_t size_x;
	size_t size_y;
};

struct _CulCMatrixView {
	char *data;
	size_t size_x;
	size_t size_y;
	size_t tda;
};

static inline CulCMatrix     *cul_cmatrix_new_struct     ();
static inline void            cul_cmatrix_free_struct    (CulCMatrix *this);
static inline CulCMatrix     *cul_cmatrix_init_struct    (CulCMatrix *this, char *data, size_t size_x, size_t size_y);
static inline CulCMatrixView *cul_cmatrixview_new_struct ();
static inline void            cul_cmatrixview_free_struct(CulCMatrixView *this);
static inline CulCMatrixView *cul_cmatrixview_init_struct(CulCMatrixView *this, char *data, size_t size_x, size_t size_y, size_t tda);

static inline char            cul_cmatrix_get            (const CulCMatrix *this, size_t x, size_t y);
static inline void            cul_cmatrix_set            (CulCMatrix *this, size_t x, size_t y, char value);
static inline char           *cul_cmatrix_ptr            (CulCMatrix *this, size_t x, size_t y);
static inline const char     *cul_cmatrix_const_ptr      (const CulCMatrix *this, size_t x, size_t y);
static inline char            cul_cmatrixview_get        (const CulCMatrixView *this, size_t x, size_t y);
static inline void            cul_cmatrixview_set        (CulCMatrixView *this, size_t x, size_t y, char value);
static inline char           *cul_cmatrixview_ptr        (CulCMatrixView *this, size_t x, size_t y);
static inline const char     *cul_cmatrixview_const_ptr  (const CulCMatrixView *this, size_t x, size_t y);

CulCMatrix     *cul_cmatrix_new          (size_t x, size_t y);
CulCMatrix     *cul_cmatrix_new_empty    ();
CulCMatrix     *cul_cmatrix_clone        (CulCMatrix *this);
CulCMatrix     *cul_cmatrix_clone_view   (CulCMatrixView *this);
void            cul_cmatrix_free         (CulCMatrix *this);
CulCMatrixView *cul_cmatrixview_new      ();
void            cul_cmatrixview_free     (CulCMatrixView *this);

CulCMatrixView *cul_cmatrixview_matrix         (CulCMatrixView *this, CulCMatrix *base);
CulCMatrixView *cul_cmatrixview_submatrix      (CulCMatrixView *this, CulCMatrix *base, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulCVectorView *cul_cvectorview_matrix_row     (CulCVectorView *this, const CulCMatrix *base, size_t base_row);
CulCVectorView *cul_cvectorview_matrix_col     (CulCVectorView *this, const CulCMatrix *base, size_t base_col);
CulCVectorView *cul_cvectorview_matrix_diag    (CulCVectorView *this, const CulCMatrix *base, size_t offset, int sub_or_sup);
CulCVectorView *cul_cvectorview_matrixview_row (CulCVectorView *this, const CulCMatrixView *base, size_t base_row);
CulCVectorView *cul_cvectorview_matrixview_col (CulCVectorView *this, const CulCMatrixView *base, size_t base_col);
CulCVectorView *cul_cvectorview_matrixview_diag(CulCVectorView *this, const CulCMatrixView *base, size_t offset, int sub_or_sup);

cul_errno cul_cmatrix_copy             (CulCMatrix *this, const CulCMatrix *other);
cul_errno cul_cmatrix_copy_offset      (CulCMatrix *this, const CulCMatrix *other, size_t offset_x, size_t offset_y);
cul_errno cul_cmatrix_copy_submatrix   (CulCMatrix *this, const CulCMatrix *other, size_t other_offset_x, size_t other_offset_y);
cul_errno cul_cmatrix_copy_row         (CulCMatrix *this, const CulCMatrix *other, size_t row, size_t other_row);
cul_errno cul_cmatrix_copy_col         (CulCMatrix *this, const CulCMatrix *other, size_t col, size_t other_col);
cul_errno cul_cmatrix_copy_view        (CulCMatrix *this, const CulCMatrixView *other);
cul_errno cul_cmatrix_copy_view_offset (CulCMatrix *this, const CulCMatrixView *other, size_t offset_x, size_t offset_y);
cul_errno cul_cmatrixview_copy         (CulCMatrixView *this, const CulCMatrixView *other);
cul_errno cul_cmatrixview_copy_matrix  (CulCMatrixView *this, const CulCMatrix *other);

cul_errno cul_cmatrix_swap             (CulCMatrix *this, CulCMatrix *other);
cul_errno cul_cmatrix_swap_row         (CulCMatrix *this, CulCMatrix *other, size_t row, size_t other_row);
cul_errno cul_cmatrix_swap_col         (CulCMatrix *this, CulCMatrix *other, size_t col, size_t other_col);
cul_errno cul_cmatrixview_swap         (CulCMatrixView *this, CulCMatrixView *other);
cul_errno cul_cmatrix_transpose        (CulCMatrix *this);
cul_errno cul_cmatrixview_transpose    (CulCMatrixView *this);

cul_errno cul_cmatrix_resize           (CulCMatrix *this, size_t x, size_t y);
cul_errno cul_cmatrix_resize_empty     (CulCMatrix *this, size_t x, size_t y);
cul_errno cul_cmatrix_insert_row       (CulCMatrix *this, size_t row);
cul_errno cul_cmatrix_insert_col       (CulCMatrix *this, size_t col);
cul_errno cul_cmatrix_remove_row       (CulCMatrix *this, size_t row);
cul_errno cul_cmatrix_remove_col       (CulCMatrix *this, size_t col);

void      cul_cmatrix_set_all          (CulCMatrix *this, char value);
void      cul_cmatrix_set_diag         (CulCMatrix *this, char value, char diag);
void      cul_cmatrix_add_constant     (CulCMatrix *this, double value);
void      cul_cmatrix_scale            (CulCMatrix *this, double value);
void      cul_cmatrix_zero             (CulCMatrix *this);
cul_errno cul_cmatrix_add              (CulCMatrix *this, const CulCMatrix *other);
cul_errno cul_cmatrix_sub              (CulCMatrix *this, const CulCMatrix *other);
cul_errno cul_cmatrix_mul              (CulCMatrix *this, const CulCMatrix *other);
cul_errno cul_cmatrix_div              (CulCMatrix *this, const CulCMatrix *other);
void      cul_cmatrixview_set_all      (CulCMatrixView *this, char value);
void      cul_cmatrixview_set_diag     (CulCMatrixView *this, char value, char diag);
void      cul_cmatrixview_add_constant (CulCMatrixView *this, double value);
void      cul_cmatrixview_scale        (CulCMatrixView *this, double value);
cul_errno cul_cmatrixview_add          (CulCMatrixView *this, const CulCMatrixView *other);
cul_errno cul_cmatrixview_sub          (CulCMatrixView *this, const CulCMatrixView *other);
cul_errno cul_cmatrixview_mul          (CulCMatrixView *this, const CulCMatrixView *other);
cul_errno cul_cmatrixview_div          (CulCMatrixView *this, const CulCMatrixView *other);

char      cul_cmatrix_min              (const CulCMatrix *this);
size_t    cul_cmatrix_min_index        (const CulCMatrix *this);
char      cul_cmatrix_max              (const CulCMatrix *this);
size_t    cul_cmatrix_max_index        (const CulCMatrix *this);
void      cul_cmatrix_minmax           (const CulCMatrix *this, char *min, char *max);
void      cul_cmatrix_minmax_index     (const CulCMatrix *this, size_t *min_i, size_t *max_i);
char      cul_cmatrixview_min          (const CulCMatrixView *this);
size_t    cul_cmatrixview_min_index    (const CulCMatrixView *this);
char      cul_cmatrixview_max          (const CulCMatrixView *this);
size_t    cul_cmatrixview_max_index    (const CulCMatrixView *this);
void      cul_cmatrixview_minmax       (const CulCMatrixView *this, char *min, char *max);
void      cul_cmatrixview_minmax_index (const CulCMatrixView *this, size_t *min_i, size_t *max_i);

double    cul_cmatrix_mean             (const CulCMatrix *this);
double    cul_cmatrix_variance         (const CulCMatrix *this);
double    cul_cmatrix_variance_mean    (const CulCMatrix *this, double mean);
double    cul_cmatrixview_mean         (const CulCMatrixView *this);
double    cul_cmatrixview_variance     (const CulCMatrixView *this);
double    cul_cmatrixview_variance_mean(const CulCMatrixView *this, double mean);

/* implementation */

static inline CulCMatrix *cul_cmatrix_new_struct() {
	return cul_slab_new(sizeof(CulCMatrix));
}

static inline void cul_cmatrix_free_struct(CulCMatrix *this) {
	cul_slab_free(sizeof(CulCMatrix), this);
}

static inline CulCMatrix *cul_cmatrix_init_struct(CulCMatrix *this, char *data, size_t size_x, size_t size_y) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	return this;
}

static inline CulCMatrixView *cul_cmatrixview_new_struct() {
	return cul_slab_new(sizeof(CulCMatrixView));
}

static inline void cul_cmatrixview_free_struct(CulCMatrixView *this) {
	cul_slab_free(sizeof(CulCMatrixView), this);
}

static inline CulCMatrixView *cul_cmatrixview_init_struct(CulCMatrixView *this, char *data, size_t size_x, size_t size_y, size_t tda) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	this->tda = tda;
	return this;
}

static inline char cul_cmatrix_get(const CulCMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return *(this->data + this->size_x * y + x);
}

static inline void cul_cmatrix_set(CulCMatrix *this, size_t x, size_t y, char value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(this->data + this->size_x * y + x) = value;
}

static inline char *cul_cmatrix_ptr(CulCMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline const char *cul_cmatrix_const_ptr(const CulCMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline char cul_cmatrixview_get(const CulCMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[this->tda * y + x];
}

static inline void cul_cmatrixview_set(CulCMatrixView *this, size_t x, size_t y, char value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[this->tda * y + x] = value;
}

static inline char *cul_cmatrixview_ptr(CulCMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

static inline const char *cul_cmatrixview_const_ptr(const CulCMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

#endif /* __CUL_CMATRIX_H__ */
