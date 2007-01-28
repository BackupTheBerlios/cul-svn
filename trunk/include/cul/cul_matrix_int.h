#if !defined(CUL_MATRIX_INT_H)
#define CUL_MATRIX_INT_H

#include <cul/cul_global.h>
#include <cul/cul_vector_int.h>

typedef struct _CulIMatrix CulIMatrix;
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

/* Allocation */

/* Uninitialized data elements */
CulIMatrix *cul_imatrix_new(size_t x, size_t y);
CulIMatrix *cul_imatrix_new_empty(void);
CulIMatrix *cul_imatrix_init(CulIMatrix *m, size_t x, size_t y);
CulIMatrix *cul_imatrix_init_empty(CulIMatrix *m);
static inline CulIMatrix *cul_imatrix_init_all(CulIMatrix *m, size_t x, size_t y, int *data);

CulIMatrixView *cul_imatrixview_new(void);
CulIMatrixView *cul_imatrixview_init(CulIMatrixView *mv);
CulIMatrixView *cul_imatrixview_init_matrix(CulIMatrixView *mv, CulIMatrix *base_m);
CulIMatrixView *cul_imatrixview_init_submatrix(CulIMatrixView *mv, CulIMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
static inline CulIMatrixView *cul_imatrixview_init_all(CulIMatrixView *mv, size_t size_x, size_t size_y, size_t tda, int *data);

CulIVectorView *cul_imatrix_row(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_row);
CulIVectorView *cul_imatrix_col(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_col);
CulIVectorView *cul_imatrix_diag(CulIVectorView *vv, const CulIMatrix *base_m);
CulIVectorView *cul_imatrix_subdiag(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_k);
CulIVectorView *cul_imatrix_superdiag(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_k);

/* Free */
void cul_imatrix_free(CulIMatrix *m);
void cul_imatrix_free_data(CulIMatrix *m);
void cul_imatrix_free_null(CulIMatrix **m);
void cul_imatrixview_free(CulIMatrixView *mv);

/* Data Access */

static inline int cul_imatrix_get(const CulIMatrix *m, size_t x, size_t y);
static inline void cul_imatrix_set(CulIMatrix *m, size_t x, size_t y, int val);
static inline int *cul_imatrix_ptr(CulIMatrix *m, size_t x, size_t y);
static inline const int *cul_imatrix_const_ptr(const CulIMatrix *m, size_t x, size_t y);

static inline int cul_imatrixview_get(const CulIMatrixView *mv, size_t x, size_t y);
static inline void cul_imatrixview_set(CulIMatrixView *mv, size_t x, size_t y, int val);
static inline int *cul_imatrixview_ptr(CulIMatrixView *mv, size_t x, size_t y);
static inline const int *cul_imatrixview_const_ptr(const CulIMatrixView *mv, size_t x, size_t y);

/* Data Copy */

cul_errno cul_imatrix_copy(CulIMatrix *m, const CulIMatrix *base_m);
cul_errno cul_imatrix_copy_offset(CulIMatrix *m, const CulIMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_imatrix_copy_submatrix(CulIMatrix *m, const CulIMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_imatrix_copy_view(CulIMatrix *m, const CulIMatrixView *base_mv);
cul_errno cul_imatrixview_copy(CulIMatrixView *mv, const CulIMatrixView *base_mv);

cul_errno cul_imatrix_copy_row(CulIMatrix *m, const CulIMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_imatrix_copy_col(CulIMatrix *m, const CulIMatrix *base_m, size_t col, size_t base_col);
cul_errno cul_imatrixview_copy_row(CulIMatrixView *mv, const CulIMatrixView *base_mv, size_t row, size_t base_row);
cul_errno cul_imatrixview_copy_col(CulIMatrixView *mv, const CulIMatrixView *base_mv, size_t col, size_t base_col);

cul_errno cul_imatrix_get_row(CulIVector *v, const CulIMatrix *m, size_t row);
cul_errno cul_imatrix_get_col(CulIVector *v, const CulIMatrix *m, size_t col);
cul_errno cul_imatrix_set_row(CulIMatrix *m, const CulIVector *v, size_t row);
cul_errno cul_imatrix_set_col(CulIMatrix *m, const CulIVector *v, size_t col);

cul_errno cul_imatrix_swap(CulIMatrix *ma, CulIMatrix *mb);
cul_errno cul_imatrix_swap_row(CulIMatrix *ma, CulIMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_imatrix_swap_col(CulIMatrix *ma, CulIMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_imatrix_transpose(CulIMatrix *m);
cul_errno cul_imatrix_transpose_copy(CulIMatrix *m, const CulIMatrix *base_m);

/* Data Resize */

CulIMatrix *cul_imatrix_resize(CulIMatrix *m, size_t x, size_t y);
CulIMatrix *cul_imatrix_resize_rows(CulIMatrix *m, size_t x);
CulIMatrix *cul_imatrix_resize_cols(CulIMatrix *m, size_t y);

/* Min/Max */

int cul_imatrix_min(const CulIMatrix *m);
size_t cul_imatrix_min_index(const CulIMatrix *m);
int cul_imatrix_max(const CulIMatrix *m);
size_t cul_imatrix_max_index(const CulIMatrix *m);
void cul_imatrix_minmax(const CulIMatrix *m, int *min, int *max);
void cul_imatrix_minmax_index(const CulIMatrix *m, size_t *min_i, size_t *max_i);

/* Input/Output */

cul_errno cul_imatrix_print_stream(const CulIMatrix *m, const char *format, const char *separator);
cul_errno cul_imatrix_fprintf(FILE *id, const CulIMatrix *m, const char *format, const char *separator);
cul_errno cul_imatrix_fscanf(FILE *id, CulIMatrix *m, const char *format, const char *separator);

/* implementation */

static inline CulIMatrix *cul_imatrix_init_all(CulIMatrix *m, size_t x, size_t y, int *data) {
	m->size_x = x;
	m->size_y = y;
	m->data = data;
	return m;
}

static inline CulIMatrixView *cul_imatrixview_init_all(CulIMatrixView *mv, size_t size_x, size_t size_y, size_t tda, int *data) {
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	mv->data = data;
	return mv;
}

static inline int cul_imatrix_get(const CulIMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return *(m->data + m->size_x * y + x);
}

static inline void cul_imatrix_set(CulIMatrix *m, size_t x, size_t y, int value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	*(m->data + m->size_x * y + x) = value;
}

static inline int *cul_imatrix_ptr(CulIMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline const int *cul_imatrix_const_ptr(const CulIMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline int cul_imatrixview_get(const CulIMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return mv->data[mv->tda * y + x];
}

static inline void cul_imatrixview_set(CulIMatrixView *mv, size_t x, size_t y, int value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
	if( y >= mv->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	mv->data[mv->tda * y + x] = value;
}

static inline int *cul_imatrixview_ptr(CulIMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

static inline const int *cul_imatrixview_const_ptr(const CulIMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

#endif
