#if !defined(CUL_MATRIX_DOUBLE_H)
#define CUL_MATRIX_DOUBLE_H

#include <cul/cul_global.h>
#include <cul/cul_vector_double.h>

typedef struct _CulDMatrix CulDMatrix;
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

/* Allocation */

/* Uninitialized data elements */
CulDMatrix *cul_dmatrix_new(size_t x, size_t y);
CulDMatrix *cul_dmatrix_new_empty(void);
CulDMatrix *cul_dmatrix_init(CulDMatrix *m, size_t x, size_t y);
CulDMatrix *cul_dmatrix_init_empty(CulDMatrix *m);
static inline CulDMatrix *cul_dmatrix_init_all(CulDMatrix *m, size_t x, size_t y, double *data);

CulDMatrixView *cul_dmatrixview_new(void);
CulDMatrixView *cul_dmatrixview_init(CulDMatrixView *mv);
CulDMatrixView *cul_dmatrixview_init_matrix(CulDMatrixView *mv, CulDMatrix *base_m);
CulDMatrixView *cul_dmatrixview_init_submatrix(CulDMatrixView *mv, CulDMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
static inline CulDMatrixView *cul_dmatrixview_init_all(CulDMatrixView *mv, size_t size_x, size_t size_y, size_t tda, double *data);

CulDVectorView *cul_dmatrix_row(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_row);
CulDVectorView *cul_dmatrix_col(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_col);
CulDVectorView *cul_dmatrix_diag(CulDVectorView *vv, const CulDMatrix *base_m);
CulDVectorView *cul_dmatrix_subdiag(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_k);
CulDVectorView *cul_dmatrix_superdiag(CulDVectorView *vv, const CulDMatrix *base_m, size_t base_k);

/* Free */
void cul_dmatrix_free(CulDMatrix *m);
void cul_dmatrix_free_data(CulDMatrix *m);
void cul_dmatrix_free_null(CulDMatrix **m);
void cul_dmatrixview_free(CulDMatrixView *mv);

/* Data Access */

static inline double cul_dmatrix_get(const CulDMatrix *m, size_t x, size_t y);
static inline void cul_dmatrix_set(CulDMatrix *m, size_t x, size_t y, double val);
static inline double *cul_dmatrix_ptr(CulDMatrix *m, size_t x, size_t y);
static inline const double *cul_dmatrix_const_ptr(const CulDMatrix *m, size_t x, size_t y);

static inline double cul_dmatrixview_get(const CulDMatrixView *mv, size_t x, size_t y);
static inline void cul_dmatrixview_set(CulDMatrixView *mv, size_t x, size_t y, double val);
static inline double *cul_dmatrixview_ptr(CulDMatrixView *mv, size_t x, size_t y);
static inline const double *cul_dmatrixview_const_ptr(const CulDMatrixView *mv, size_t x, size_t y);

/* Data Copy */

cul_errno cul_dmatrix_copy(CulDMatrix *m, const CulDMatrix *base_m);
cul_errno cul_dmatrix_copy_offset(CulDMatrix *m, const CulDMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_dmatrix_copy_submatrix(CulDMatrix *m, const CulDMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_dmatrix_copy_view(CulDMatrix *m, const CulDMatrixView *base_mv);
cul_errno cul_dmatrixview_copy(CulDMatrixView *mv, const CulDMatrixView *base_mv);

cul_errno cul_dmatrix_copy_row(CulDMatrix *m, const CulDMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_dmatrix_copy_col(CulDMatrix *m, const CulDMatrix *base_m, size_t col, size_t base_col);
cul_errno cul_dmatrixview_copy_row(CulDMatrixView *mv, const CulDMatrixView *base_mv, size_t row, size_t base_row);
cul_errno cul_dmatrixview_copy_col(CulDMatrixView *mv, const CulDMatrixView *base_mv, size_t col, size_t base_col);

cul_errno cul_dmatrix_get_row(CulDVector *v, const CulDMatrix *m, size_t row);
cul_errno cul_dmatrix_get_col(CulDVector *v, const CulDMatrix *m, size_t col);
cul_errno cul_dmatrix_set_row(CulDMatrix *m, const CulDVector *v, size_t row);
cul_errno cul_dmatrix_set_col(CulDMatrix *m, const CulDVector *v, size_t col);

cul_errno cul_dmatrix_swap(CulDMatrix *ma, CulDMatrix *mb);
cul_errno cul_dmatrix_swap_row(CulDMatrix *ma, CulDMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_dmatrix_swap_col(CulDMatrix *ma, CulDMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_dmatrix_transpose(CulDMatrix *m);
cul_errno cul_dmatrix_transpose_copy(CulDMatrix *m, const CulDMatrix *base_m);

/* Data Resize */

CulDMatrix *cul_dmatrix_resize(CulDMatrix *m, size_t x, size_t y);
CulDMatrix *cul_dmatrix_resize_rows(CulDMatrix *m, size_t x);
CulDMatrix *cul_dmatrix_resize_cols(CulDMatrix *m, size_t y);

/* Min/Max */

double cul_dmatrix_min(const CulDMatrix *m);
size_t cul_dmatrix_min_index(const CulDMatrix *m);
double cul_dmatrix_max(const CulDMatrix *m);
size_t cul_dmatrix_max_index(const CulDMatrix *m);
void cul_dmatrix_minmax(const CulDMatrix *m, double *min, double *max);
void cul_dmatrix_minmax_index(const CulDMatrix *m, size_t *min_i, size_t *max_i);

/* Input/Output */

cul_errno cul_dmatrix_print_stream(const CulDMatrix *m, const char *format, const char *separator);
cul_errno cul_dmatrix_fprintf(FILE *id, const CulDMatrix *m, const char *format, const char *separator);
cul_errno cul_dmatrix_fscanf(FILE *id, CulDMatrix *m, const char *format, const char *separator);

/* implementation */

static inline CulDMatrix *cul_dmatrix_init_all(CulDMatrix *m, size_t x, size_t y, double *data) {
	m->size_x = x;
	m->size_y = y;
	m->data = data;
	return m;
}

static inline CulDMatrixView *cul_dmatrixview_init_all(CulDMatrixView *mv, size_t size_x, size_t size_y, size_t tda, double *data) {
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	mv->data = data;
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
