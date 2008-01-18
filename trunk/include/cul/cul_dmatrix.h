#ifndef __CUL_DMATRIX_H__
#define __CUL_DMATRIX_H__

#include <cul/cul_global.h>
#include <cul/cul_dvector.h>

#define CUL_DMATRIX(ptr)     ((CulDMatrix *)(ptr))
#define CUL_DMATRIXVIEW(ptr) ((CulDMatrixView *)(ptr))

typedef struct _CulDMatrix     CulDMatrix;
typedef struct _CulDMatrixView CulDMatrixView;

struct _CulDMatrix {
	double *data;
	size_t size_x;
	size_t size_y;
};

struct _CulDMatrixView {
	double *data;
	size_t size_x;
	size_t size_y;
	size_t tda;
};

static inline CulDMatrix     *cul_dmatrix_new_struct     ();
static inline void            cul_dmatrix_free_struct    (CulDMatrix *this);
static inline CulDMatrix     *cul_dmatrix_init_struct    (CulDMatrix *this, double *data, size_t size_x, size_t size_y);
static inline CulDMatrixView *cul_dmatrixview_new_struct ();
static inline void            cul_dmatrixview_free_struct(CulDMatrixView *this);
static inline CulDMatrixView *cul_dmatrixview_init_struct(CulDMatrixView *this, double *data, size_t size_x, size_t size_y, size_t tda);

static inline double          cul_dmatrix_get            (const CulDMatrix *this, size_t x, size_t y);
static inline void            cul_dmatrix_set            (CulDMatrix *this, size_t x, size_t y, double value);
static inline double         *cul_dmatrix_ptr            (CulDMatrix *this, size_t x, size_t y);
static inline const double   *cul_dmatrix_const_ptr      (const CulDMatrix *this, size_t x, size_t y);
static inline double          cul_dmatrixview_get        (const CulDMatrixView *this, size_t x, size_t y);
static inline void            cul_dmatrixview_set        (CulDMatrixView *this, size_t x, size_t y, double value);
static inline double         *cul_dmatrixview_ptr        (CulDMatrixView *this, size_t x, size_t y);
static inline const double   *cul_dmatrixview_const_ptr  (const CulDMatrixView *this, size_t x, size_t y);

CulDMatrix     *cul_dmatrix_new          (size_t x, size_t y);
CulDMatrix     *cul_dmatrix_new_empty    ();
CulDMatrix     *cul_dmatrix_clone        (CulDMatrix *this);
CulDMatrix     *cul_dmatrix_clone_view   (CulDMatrixView *this);
void            cul_dmatrix_free         (CulDMatrix *this);
CulDMatrixView *cul_dmatrixview_new      ();
void            cul_dmatrixview_free     (CulDMatrixView *this);

CulDMatrixView *cul_dmatrixview_matrix         (CulDMatrixView *this, CulDMatrix *base);
CulDMatrixView *cul_dmatrixview_submatrix      (CulDMatrixView *this, CulDMatrix *base, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulDVectorView *cul_dvectorview_matrix_row     (CulDVectorView *this, const CulDMatrix *base, size_t base_row);
CulDVectorView *cul_dvectorview_matrix_col     (CulDVectorView *this, const CulDMatrix *base, size_t base_col);
CulDVectorView *cul_dvectorview_matrix_diag    (CulDVectorView *this, const CulDMatrix *base, size_t offset, int sub_or_sup);
CulDVectorView *cul_dvectorview_matrixview_row (CulDVectorView *this, const CulDMatrixView *base, size_t base_row);
CulDVectorView *cul_dvectorview_matrixview_col (CulDVectorView *this, const CulDMatrixView *base, size_t base_col);
CulDVectorView *cul_dvectorview_matrixview_diag(CulDVectorView *this, const CulDMatrixView *base, size_t offset, int sub_or_sup);

cul_errno cul_dmatrix_copy             (CulDMatrix *this, const CulDMatrix *other);
cul_errno cul_dmatrix_copy_offset      (CulDMatrix *this, const CulDMatrix *other, size_t offset_x, size_t offset_y);
cul_errno cul_dmatrix_copy_submatrix   (CulDMatrix *this, const CulDMatrix *other, size_t other_offset_x, size_t other_offset_y);
cul_errno cul_dmatrix_copy_row         (CulDMatrix *this, const CulDMatrix *other, size_t row, size_t other_row);
cul_errno cul_dmatrix_copy_col         (CulDMatrix *this, const CulDMatrix *other, size_t col, size_t other_col);
cul_errno cul_dmatrix_copy_view        (CulDMatrix *this, const CulDMatrixView *other);
cul_errno cul_dmatrix_copy_view_offset (CulDMatrix *this, const CulDMatrixView *other, size_t offset_x, size_t offset_y);
cul_errno cul_dmatrixview_copy         (CulDMatrixView *this, const CulDMatrixView *other);
cul_errno cul_dmatrixview_copy_matrix  (CulDMatrixView *this, const CulDMatrix *other);

cul_errno cul_dmatrix_swap             (CulDMatrix *this, CulDMatrix *other);
cul_errno cul_dmatrix_swap_row         (CulDMatrix *this, CulDMatrix *other, size_t row, size_t other_row);
cul_errno cul_dmatrix_swap_col         (CulDMatrix *this, CulDMatrix *other, size_t col, size_t other_col);
cul_errno cul_dmatrixview_swap         (CulDMatrixView *this, CulDMatrixView *other);
cul_errno cul_dmatrix_transpose        (CulDMatrix *this);
cul_errno cul_dmatrixview_transpose    (CulDMatrixView *this);

cul_errno cul_dmatrix_resize           (CulDMatrix *this, size_t x, size_t y);
cul_errno cul_dmatrix_resize_empty     (CulDMatrix *this, size_t x, size_t y);
cul_errno cul_dmatrix_insert_row       (CulDMatrix *this, size_t row);
cul_errno cul_dmatrix_insert_col       (CulDMatrix *this, size_t col);
cul_errno cul_dmatrix_remove_row       (CulDMatrix *this, size_t row);
cul_errno cul_dmatrix_remove_col       (CulDMatrix *this, size_t col);

void      cul_dmatrix_set_all          (CulDMatrix *this, double value);
void      cul_dmatrix_set_diag         (CulDMatrix *this, double value, double diag);
void      cul_dmatrix_add_constant     (CulDMatrix *this, double value);
void      cul_dmatrix_scale            (CulDMatrix *this, double value);
void      cul_dmatrix_zero             (CulDMatrix *this);
cul_errno cul_dmatrix_add              (CulDMatrix *this, const CulDMatrix *other);
cul_errno cul_dmatrix_sub              (CulDMatrix *this, const CulDMatrix *other);
cul_errno cul_dmatrix_mul              (CulDMatrix *this, const CulDMatrix *other);
cul_errno cul_dmatrix_div              (CulDMatrix *this, const CulDMatrix *other);
void      cul_dmatrixview_set_all      (CulDMatrixView *this, double value);
void      cul_dmatrixview_set_diag     (CulDMatrixView *this, double value, double diag);
void      cul_dmatrixview_add_constant (CulDMatrixView *this, double value);
void      cul_dmatrixview_scale        (CulDMatrixView *this, double value);
cul_errno cul_dmatrixview_add          (CulDMatrixView *this, const CulDMatrixView *other);
cul_errno cul_dmatrixview_sub          (CulDMatrixView *this, const CulDMatrixView *other);
cul_errno cul_dmatrixview_mul          (CulDMatrixView *this, const CulDMatrixView *other);
cul_errno cul_dmatrixview_div          (CulDMatrixView *this, const CulDMatrixView *other);

double    cul_dmatrix_min              (const CulDMatrix *this);
size_t    cul_dmatrix_min_index        (const CulDMatrix *this);
double    cul_dmatrix_max              (const CulDMatrix *this);
size_t    cul_dmatrix_max_index        (const CulDMatrix *this);
void      cul_dmatrix_minmax           (const CulDMatrix *this, double *min, double *max);
void      cul_dmatrix_minmax_index     (const CulDMatrix *this, size_t *min_i, size_t *max_i);
double    cul_dmatrixview_min          (const CulDMatrixView *this);
size_t    cul_dmatrixview_min_index    (const CulDMatrixView *this);
double    cul_dmatrixview_max          (const CulDMatrixView *this);
size_t    cul_dmatrixview_max_index    (const CulDMatrixView *this);
void      cul_dmatrixview_minmax       (const CulDMatrixView *this, double *min, double *max);
void      cul_dmatrixview_minmax_index (const CulDMatrixView *this, size_t *min_i, size_t *max_i);

double    cul_dmatrix_mean             (const CulDMatrix *this);
double    cul_dmatrix_variance         (const CulDMatrix *this);
double    cul_dmatrix_variance_mean    (const CulDMatrix *this, double mean);
double    cul_dmatrixview_mean         (const CulDMatrixView *this);
double    cul_dmatrixview_variance     (const CulDMatrixView *this);
double    cul_dmatrixview_variance_mean(const CulDMatrixView *this, double mean);

cul_errno cul_dmatrix_fprintf          (FILE *stream, const CulDMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_dmatrix_fscanf           (FILE *stream, CulDMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

/* implementation */

static inline CulDMatrix *cul_dmatrix_new_struct() {
	return cul_slab_new(sizeof(CulDMatrix));
}

static inline void cul_dmatrix_free_struct(CulDMatrix *this) {
	cul_slab_free(sizeof(CulDMatrix), this);
}

static inline CulDMatrix *cul_dmatrix_init_struct(CulDMatrix *this, double *data, size_t size_x, size_t size_y) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	return this;
}

static inline CulDMatrixView *cul_dmatrixview_new_struct() {
	return cul_slab_new(sizeof(CulDMatrixView));
}

static inline void cul_dmatrixview_free_struct(CulDMatrixView *this) {
	cul_slab_free(sizeof(CulDMatrixView), this);
}

static inline CulDMatrixView *cul_dmatrixview_init_struct(CulDMatrixView *this, double *data, size_t size_x, size_t size_y, size_t tda) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	this->tda = tda;
	return this;
}

static inline double cul_dmatrix_get(const CulDMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0.0, CUL_EBADPOS);
#endif
	return *(this->data + this->size_x * y + x);
}

static inline void cul_dmatrix_set(CulDMatrix *this, size_t x, size_t y, double value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(this->data + this->size_x * y + x) = value;
}

static inline double *cul_dmatrix_ptr(CulDMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline const double *cul_dmatrix_const_ptr(const CulDMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline double cul_dmatrixview_get(const CulDMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0.0, CUL_EBADPOS);
#endif
	return this->data[this->tda * y + x];
}

static inline void cul_dmatrixview_set(CulDMatrixView *this, size_t x, size_t y, double value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[this->tda * y + x] = value;
}

static inline double *cul_dmatrixview_ptr(CulDMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

static inline const double *cul_dmatrixview_const_ptr(const CulDMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

#endif /* __CUL_DMATRIX_H__ */
