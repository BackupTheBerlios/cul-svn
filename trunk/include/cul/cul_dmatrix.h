#ifndef CUL_DMATRIX_H
#define CUL_DMATRIX_H

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

static inline CulDMatrix *cul_dmatrix_new_struct(void);
static inline void cul_dmatrix_free_struct(CulCVector *m);
static inline CulDMatrix *cul_dmatrix_init_struct(CulDMatrix *m, double *data, size_t size_x, size_t size_y);

static inline CulDMatrixView *cul_dmatrixview_new_struct(void);
static inline void cul_dmatrixview_free_struct(CulDMatrixView *m);
static inline CulDMatrixView *cul_dmatrixview_init_struct(CulDMatrixView *mv, double *data, size_t size_x, size_t size_y, size_t tda);

CulDMatrix *cul_dmatrix_new(size_t x, size_t y);
CulDMatrix *cul_dmatrix_new_empty(void);
void cul_dmatrix_free(CulDMatrix *m);

CulDMatrixView *cul_dmatrixview_new(void);
void cul_dmatrixview_free(CulDMatrixView *mv);

CulDMatrixView *cul_dmatrixview_matrix(CulDMatrixView *mv, CulDMatrix *base_m);
CulDMatrixView *cul_dmatrixview_submatrix(CulDMatrixView *mv, CulDMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulDVectorView *cul_dmatrixview_row(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_row);
CulDVectorView *cul_dmatrixview_col(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_col);
CulDVectorView *cul_dmatrixview_diag(CulDVectorView *vv, const CulDMatrix *base_m);
CulDVectorView *cul_dmatrixview_subdiag(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_k);
CulDVectorView *cul_dmatrixview_superdiag(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_k);

static inline double cul_dmatrix_get(const CulDMatrix *m, size_t x, size_t y);
static inline void cul_dmatrix_set(CulDMatrix *m, size_t x, size_t y, double val);
static inline double *cul_dmatrix_ptr(CulDMatrix *m, size_t x, size_t y);
static inline const double *cul_dmatrix_const_ptr(const CulDMatrix *m, size_t x, size_t y);

static inline double cul_dmatrixview_get(const CulDMatrixView *mv, size_t x, size_t y);
static inline void cul_dmatrixview_set(CulDMatrixView *mv, size_t x, size_t y, double val);
static inline double *cul_dmatrixview_ptr(CulDMatrixView *mv, size_t x, size_t y);
static inline const double *cul_dmatrixview_const_ptr(const CulDMatrixView *mv, size_t x, size_t y);

cul_errno cul_dmatrix_copy(CulDMatrix *m, const CulDMatrix *base_m);
cul_errno cul_dmatrix_copy_offset(CulDMatrix *m, const CulDMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_dmatrix_copy_submatrix(CulDMatrix *m, const CulDMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_dmatrix_copy_view(CulDMatrix *m, const CulDMatrixView *base_mv);
cul_errno cul_dmatrixview_copy(CulDMatrixView *mv, const CulDMatrixView *base_mv);

cul_errno cul_dmatrix_copy_row(CulDMatrix *m, const CulDMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_dmatrix_copy_col(CulDMatrix *m, const CulDMatrix *base_m, size_t col, size_t base_col);

cul_errno cul_dmatrix_swap(CulDMatrix *ma, CulDMatrix *mb);
cul_errno cul_dmatrix_swap_row(CulDMatrix *ma, CulDMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_dmatrix_swap_col(CulDMatrix *ma, CulDMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_dmatrix_transpose(CulDMatrix *m);

double cul_dmatrix_min(const CulDMatrix *m);
size_t cul_dmatrix_min_index(const CulDMatrix *m);
double cul_dmatrix_max(const CulDMatrix *m);
size_t cul_dmatrix_max_index(const CulDMatrix *m);
void cul_dmatrix_minmax(const CulDMatrix *m, double *min, double *max);
void cul_dmatrix_minmax_index(const CulDMatrix *m, size_t *min_i, size_t *max_i);

cul_errno cul_dmatrix_fprintf(FILE *stream, const CulDMatrix *m, const char *format, const char *separator);
cul_errno cul_dmatrix_fscanf(FILE *stream, CulDMatrix *m, const char *format, const char *separator);

/* implementation */

static inline CulDMatrix *cul_dmatrix_new_struct(void) {
	return cul_slab_new(sizeof(CulDMatrix));
}

static inline void cul_dmatrix_free_struct(CulCVector *m) {
	cul_slab_free(sizeof(CulDMatrix), m);
}

static inline CulDMatrix *cul_dmatrix_init_struct(CulDMatrix *m, double *data, size_t size_x, size_t size_y) {
	m->data = data;
	m->size_x = size_x;
	m->size_y = size_y;
	return m;
}

static inline CulDMatrixView *cul_dmatrixview_new_struct(void) {
	return cul_slab_new(sizeof(CulDMatrixView));
}

static inline void cul_dmatrixview_free_struct(CulDMatrixView *m) {
	cul_slab_free(sizeof(CulDMatrixView), m);
}

static inline CulDMatrixView *cul_dmatrixview_init_struct(CulDMatrixView *mv, double *data, size_t size_x, size_t size_y, size_t tda) {
	mv->data = data;
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	return mv;
}

static inline double cul_dmatrix_get(const CulDMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return *(m->data + m->size_x * y + x);
}

static inline void cul_dmatrix_set(CulDMatrix *m, size_t x, size_t y, double value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	*(m->data + m->size_x * y + x) = value;
}

static inline double *cul_dmatrix_ptr(CulDMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline const double *cul_dmatrix_const_ptr(const CulDMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline double cul_dmatrixview_get(const CulDMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return mv->data[mv->tda * y + x];
}

static inline void cul_dmatrixview_set(CulDMatrixView *mv, size_t x, size_t y, double value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	mv->data[mv->tda * y + x] = value;
}

static inline double *cul_dmatrixview_ptr(CulDMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

static inline const double *cul_dmatrixview_const_ptr(const CulDMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

#endif
