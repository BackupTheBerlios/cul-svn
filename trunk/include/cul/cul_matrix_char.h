#if !defined(CUL_MATRIX_CHAR_H)
#define CUL_MATRIX_CHAR_H

#include <cul/cul_global.h>
#include <cul/cul_vector_char.h>

typedef struct _CulCMatrix CulCMatrix;
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

/* Allocation */

/* Uninitialized data elements */
CulCMatrix *cul_cmatrix_new(size_t x, size_t y);
CulCMatrix *cul_cmatrix_new_empty(void);
CulCMatrix *cul_cmatrix_init(CulCMatrix *m, size_t x, size_t y);
CulCMatrix *cul_cmatrix_init_empty(CulCMatrix *m);
static inline CulCMatrix *cul_cmatrix_init_all(CulCMatrix *m, size_t x, size_t y, char *data);

CulCMatrixView *cul_cmatrixview_new(void);
CulCMatrixView *cul_cmatrixview_init(CulCMatrixView *mv);
static inline CulCMatrixView *cul_cmatrixview_init_all(CulCMatrixView *mv, size_t size_x, size_t size_y, size_t tda, char *data);

/* Assign views */
CulCMatrixView *cul_cmatrix_view_matrix(CulCMatrixView *mv, CulCMatrix *base_m);
CulCMatrixView *cul_cmatrix_view_submatrix(CulCMatrixView *mv, CulCMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulCVectorView *cul_cmatrix_view_row(CulCVectorView *vv, const CulCMatrix *base_m, size_t base_row);
CulCVectorView *cul_cmatrix_view_col(CulCVectorView *vv, const CulCMatrix *base_m, size_t base_col);
CulCVectorView *cul_cmatrix_view_diag(CulCVectorView *vv, const CulCMatrix *base_m);
CulCVectorView *cul_cmatrix_view_subdiag(CulCVectorView *vv, const CulCMatrix *base_m, size_t base_k);
CulCVectorView *cul_cmatrix_view_superdiag(CulCVectorView *vv, const CulCMatrix *base_m, size_t base_k);

/* Free */
void cul_cmatrix_free(CulCMatrix *m);
void cul_cmatrix_free_data(CulCMatrix *m);
void cul_cmatrixview_free(CulCMatrixView *mv);

/* Data Access */

static inline char cul_cmatrix_get(const CulCMatrix *m, size_t x, size_t y);
static inline void cul_cmatrix_set(CulCMatrix *m, size_t x, size_t y, char val);
static inline char *cul_cmatrix_ptr(CulCMatrix *m, size_t x, size_t y);
static inline const char *cul_cmatrix_const_ptr(const CulCMatrix *m, size_t x, size_t y);

static inline char cul_cmatrixview_get(const CulCMatrixView *mv, size_t x, size_t y);
static inline void cul_cmatrixview_set(CulCMatrixView *mv, size_t x, size_t y, char val);
static inline char *cul_cmatrixview_ptr(CulCMatrixView *mv, size_t x, size_t y);
static inline const char *cul_cmatrixview_const_ptr(const CulCMatrixView *mv, size_t x, size_t y);

/* Data Copy */

cul_errno cul_cmatrix_copy(CulCMatrix *m, const CulCMatrix *base_m);
cul_errno cul_cmatrix_copy_offset(CulCMatrix *m, const CulCMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_cmatrix_copy_submatrix(CulCMatrix *m, const CulCMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_cmatrix_copy_view(CulCMatrix *m, const CulCMatrixView *base_mv);
cul_errno cul_cmatrixview_copy(CulCMatrixView *mv, const CulCMatrixView *base_mv);

cul_errno cul_cmatrix_copy_row(CulCMatrix *m, const CulCMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_cmatrix_copy_col(CulCMatrix *m, const CulCMatrix *base_m, size_t col, size_t base_col);
cul_errno cul_cmatrixview_copy_row(CulCMatrixView *mv, const CulCMatrixView *base_mv, size_t row, size_t base_row);
cul_errno cul_cmatrixview_copy_col(CulCMatrixView *mv, const CulCMatrixView *base_mv, size_t col, size_t base_col);

cul_errno cul_cmatrix_get_row(CulCVector *v, const CulCMatrix *m, size_t row);
cul_errno cul_cmatrix_get_col(CulCVector *v, const CulCMatrix *m, size_t col);
cul_errno cul_cmatrix_set_row(CulCMatrix *m, const CulCVector *v, size_t row);
cul_errno cul_cmatrix_set_col(CulCMatrix *m, const CulCVector *v, size_t col);

cul_errno cul_cmatrix_swap(CulCMatrix *ma, CulCMatrix *mb);
cul_errno cul_cmatrix_swap_row(CulCMatrix *ma, CulCMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_cmatrix_swap_col(CulCMatrix *ma, CulCMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_cmatrix_transpose(CulCMatrix *m);
cul_errno cul_cmatrix_transpose_copy(CulCMatrix *m, const CulCMatrix *base_m);

/* Data Resize */

CulCMatrix *cul_cmatrix_resize(CulCMatrix *m, size_t x, size_t y);
CulCMatrix *cul_cmatrix_resize_rows(CulCMatrix *m, size_t x);
CulCMatrix *cul_cmatrix_resize_cols(CulCMatrix *m, size_t y);

/* Min/Max */

char cul_cmatrix_min(const CulCMatrix *m);
size_t cul_cmatrix_min_index(const CulCMatrix *m);
char cul_cmatrix_max(const CulCMatrix *m);
size_t cul_cmatrix_max_index(const CulCMatrix *m);
void cul_cmatrix_minmax(const CulCMatrix *m, char *min, char *max);
void cul_cmatrix_minmax_index(const CulCMatrix *m, size_t *min_i, size_t *max_i);

/* Input/Output */

cul_errno cul_cmatrix_print_stream(const CulCMatrix *m, const char *format, const char *separator);
cul_errno cul_cmatrix_fprintf(FILE *id, const CulCMatrix *m, const char *format, const char *separator);
cul_errno cul_cmatrix_fscanf(FILE *id, CulCMatrix *m, const char *format, const char *separator);

/* implementation */

static inline CulCMatrix *cul_cmatrix_init_all(CulCMatrix *m, size_t x, size_t y, char *data) {
	m->size_x = x;
	m->size_y = y;
	m->data = data;
	return m;
}

static inline CulCMatrixView *cul_cmatrixview_init_all(CulCMatrixView *mv, size_t size_x, size_t size_y, size_t tda, char *data) {
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	mv->data = data;
	return mv;
}

static inline char cul_cmatrix_get(const CulCMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return *(m->data + m->size_x * y + x);
}

static inline void cul_cmatrix_set(CulCMatrix *m, size_t x, size_t y, char value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	*(m->data + m->size_x * y + x) = value;
}

static inline char *cul_cmatrix_ptr(CulCMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline const char *cul_cmatrix_const_ptr(const CulCMatrix *m, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline char cul_cmatrixview_get(const CulCMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(0, CUL_EBADPOS);
#endif
	return mv->data[mv->tda * y + x];
}

static inline void cul_cmatrixview_set(CulCMatrixView *mv, size_t x, size_t y, char value) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(CUL_EBADPOS);
#endif
	mv->data[mv->tda * y + x] = value;
}

static inline char *cul_cmatrixview_ptr(CulCMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

static inline const char *cul_cmatrixview_const_ptr(const CulCMatrixView *mv, size_t x, size_t y) {
#if defined(CUL_RANGE_CHECK)
	if( x >= mv->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

#endif
