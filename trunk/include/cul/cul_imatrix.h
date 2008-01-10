#ifndef __CUL_IMATRIX_H__
#define __CUL_IMATRIX_H__

#include <cul/cul_global.h>
#include <cul/cul_ivector.h>

#define CUL_IMATRIX(ptr)     ((CulIMatrix *)(ptr))
#define CUL_IMATRIXVIEW(ptr) ((CulIMatrixView *)(ptr))

typedef struct _CulIMatrix     CulIMatrix;
typedef struct _CulIMatrixView CulIMatrixView;

struct _CulIMatrix {
	int *data;
	size_t size_x;
	size_t size_y;
};

struct _CulIMatrixView {
	int *data;
	size_t size_x;
	size_t size_y;
	size_t tda;
};

static inline CulIMatrix     *cul_imatrix_new_struct     ();
static inline void            cul_imatrix_free_struct    (CulIMatrix *this);
static inline CulIMatrix     *cul_imatrix_init_struct    (CulIMatrix *this, int *data, size_t size_x, size_t size_y);
static inline CulIMatrixView *cul_imatrixview_new_struct ();
static inline void            cul_imatrixview_free_struct(CulIMatrixView *this);
static inline CulIMatrixView *cul_imatrixview_init_struct(CulIMatrixView *this, int *data, size_t size_x, size_t size_y, size_t tda);

static inline int             cul_imatrix_get            (const CulIMatrix *this, size_t x, size_t y);
static inline void            cul_imatrix_set            (CulIMatrix *this, size_t x, size_t y, int value);
static inline int            *cul_imatrix_ptr            (CulIMatrix *this, size_t x, size_t y);
static inline const int      *cul_imatrix_const_ptr      (const CulIMatrix *this, size_t x, size_t y);
static inline int             cul_imatrixview_get        (const CulIMatrixView *this, size_t x, size_t y);
static inline void            cul_imatrixview_set        (CulIMatrixView *this, size_t x, size_t y, int value);
static inline int            *cul_imatrixview_ptr        (CulIMatrixView *this, size_t x, size_t y);
static inline const int      *cul_imatrixview_const_ptr  (const CulIMatrixView *this, size_t x, size_t y);

CulIMatrix     *cul_imatrix_new          (size_t x, size_t y);
CulIMatrix     *cul_imatrix_new_empty    ();
CulIMatrix     *cul_imatrix_clone        (CulIMatrix *this);
CulIMatrix     *cul_imatrix_clone_view   (CulIMatrixView *this);
void            cul_imatrix_free         (CulIMatrix *this);
CulIMatrixView *cul_imatrixview_new      ();
void            cul_imatrixview_free     (CulIMatrixView *this);

CulIMatrixView *cul_imatrixview_matrix   (CulIMatrixView *this, CulIMatrix *base);
CulIMatrixView *cul_imatrixview_submatrix(CulIMatrixView *this, CulIMatrix *base, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulIVectorView *cul_imatrixview_row      (CulIVectorView *this, const CulIMatrix *base, size_t base_row);
CulIVectorView *cul_imatrixview_col      (CulIVectorView *this, const CulIMatrix *base, size_t base_col);
CulIVectorView *cul_imatrixview_diag     (CulIVectorView *this, const CulIMatrix *base);
CulIVectorView *cul_imatrixview_subdiag  (CulIVectorView *this, const CulIMatrix *base, size_t base_k);
CulIVectorView *cul_imatrixview_superdiag(CulIVectorView *this, const CulIMatrix *base, size_t base_k);

cul_errno cul_imatrix_copy             (CulIMatrix *this, const CulIMatrix *other);
cul_errno cul_imatrix_copy_offset      (CulIMatrix *this, const CulIMatrix *other, size_t offset_x, size_t offset_y);
cul_errno cul_imatrix_copy_submatrix   (CulIMatrix *this, const CulIMatrix *other, size_t other_offset_x, size_t other_offset_y);
cul_errno cul_imatrix_copy_row         (CulIMatrix *this, const CulIMatrix *other, size_t row, size_t other_row);
cul_errno cul_imatrix_copy_col         (CulIMatrix *this, const CulIMatrix *other, size_t col, size_t other_col);
cul_errno cul_imatrix_copy_view        (CulIMatrix *this, const CulIMatrixView *other);
cul_errno cul_imatrix_copy_view_offset (CulIMatrix *this, const CulIMatrixView *other, size_t offset_x, size_t offset_y);
cul_errno cul_imatrixview_copy         (CulIMatrixView *this, const CulIMatrixView *other);
cul_errno cul_imatrixview_copy_matrix  (CulIMatrixView *this, const CulIMatrix *other);

cul_errno cul_imatrix_swap             (CulIMatrix *this, CulIMatrix *other);
cul_errno cul_imatrix_swap_row         (CulIMatrix *this, CulIMatrix *other, size_t row, size_t other_row);
cul_errno cul_imatrix_swap_col         (CulIMatrix *this, CulIMatrix *other, size_t col, size_t other_col);
cul_errno cul_imatrixview_swap         (CulIMatrixView *this, CulIMatrixView *other);
cul_errno cul_imatrix_transpose        (CulIMatrix *this);
cul_errno cul_imatrixview_transpose    (CulIMatrixView *this);

cul_errno cul_imatrix_resize           (CulIMatrix *this, size_t x, size_t y);
cul_errno cul_imatrix_resize_empty     (CulIMatrix *this, size_t x, size_t y);

void      cul_imatrix_set_all          (CulIMatrix *this, int value);
void      cul_imatrix_set_diag         (CulIMatrix *this, int value, int diag);
void      cul_imatrix_add_constant     (CulIMatrix *this, double value);
void      cul_imatrix_scale            (CulIMatrix *this, double value);
void      cul_imatrix_zero             (CulIMatrix *this);
cul_errno cul_imatrix_add              (CulIMatrix *this, const CulIMatrix *other);
cul_errno cul_imatrix_sub              (CulIMatrix *this, const CulIMatrix *other);
cul_errno cul_imatrix_mul              (CulIMatrix *this, const CulIMatrix *other);
cul_errno cul_imatrix_div              (CulIMatrix *this, const CulIMatrix *other);
void      cul_imatrixview_set_all      (CulIMatrixView *this, int value);
void      cul_imatrixview_set_diag     (CulIMatrixView *this, int value, int diag);
void      cul_imatrixview_add_constant (CulIMatrixView *this, double value);
void      cul_imatrixview_scale        (CulIMatrixView *this, double value);
cul_errno cul_imatrixview_add          (CulIMatrixView *this, const CulIMatrixView *other);
cul_errno cul_imatrixview_sub          (CulIMatrixView *this, const CulIMatrixView *other);
cul_errno cul_imatrixview_mul          (CulIMatrixView *this, const CulIMatrixView *other);
cul_errno cul_imatrixview_div          (CulIMatrixView *this, const CulIMatrixView *other);

int       cul_imatrix_min              (const CulIMatrix *this);
size_t    cul_imatrix_min_index        (const CulIMatrix *this);
int       cul_imatrix_max              (const CulIMatrix *this);
size_t    cul_imatrix_max_index        (const CulIMatrix *this);
void      cul_imatrix_minmax           (const CulIMatrix *this, int *min, int *max);
void      cul_imatrix_minmax_index     (const CulIMatrix *this, size_t *min_i, size_t *max_i);

double    cul_imatrix_mean             (const CulIMatrix *this);
double    cul_imatrix_variance         (const CulIMatrix *this);
double    cul_imatrix_variance_mean    (const CulIMatrix *this, double mean);
double    cul_imatrixview_mean         (const CulIMatrixView *this);
double    cul_imatrixview_variance     (const CulIMatrixView *this);
double    cul_imatrixview_variance_mean(const CulIMatrixView *this, double mean);

cul_errno cul_imatrix_fprintf          (FILE *stream, const CulIMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_imatrix_fscanf           (FILE *stream, CulIMatrix *this, const char *format, const char *separator, const char *begin, const char *end, const char *row);

/* implementation */

static inline CulIMatrix *cul_imatrix_new_struct() {
	return cul_slab_new(sizeof(CulIMatrix));
}

static inline void cul_imatrix_free_struct(CulIMatrix *this) {
	cul_slab_free(sizeof(CulIMatrix), this);
}

static inline CulIMatrix *cul_imatrix_init_struct(CulIMatrix *this, int *data, size_t size_x, size_t size_y) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	return this;
}

static inline CulIMatrixView *cul_imatrixview_new_struct() {
	return cul_slab_new(sizeof(CulIMatrixView));
}

static inline void cul_imatrixview_free_struct(CulIMatrixView *this) {
	cul_slab_free(sizeof(CulIMatrixView), this);
}

static inline CulIMatrixView *cul_imatrixview_init_struct(CulIMatrixView *this, int *data, size_t size_x, size_t size_y, size_t tda) {
	this->data = data;
	this->size_x = size_x;
	this->size_y = size_y;
	this->tda = tda;
	return this;
}

static inline int cul_imatrix_get(const CulIMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return *(this->data + this->size_x * y + x);
}

static inline void cul_imatrix_set(CulIMatrix *this, size_t x, size_t y, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(this->data + this->size_x * y + x) = value;
}

static inline int *cul_imatrix_ptr(CulIMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline const int *cul_imatrix_const_ptr(const CulIMatrix *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->size_x * y + x);
}

static inline int cul_imatrixview_get(const CulIMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return this->data[this->tda * y + x];
}

static inline void cul_imatrixview_set(CulIMatrixView *this, size_t x, size_t y, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	this->data[this->tda * y + x] = value;
}

static inline int *cul_imatrixview_ptr(CulIMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

static inline const int *cul_imatrixview_const_ptr(const CulIMatrixView *this, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= this->size_x || y >= this->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (this->data + this->tda * y + x);
}

#endif /* __CUL_IMATRIX_H__ */
