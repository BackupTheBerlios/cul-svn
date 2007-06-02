#ifndef CUL_IMATRIX_H
#define CUL_IMATRIX_H

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

static inline CulIMatrix *cul_imatrix_new_struct(void);
static inline void cul_imatrix_free_struct(CulCVector *m);
static inline CulIMatrix *cul_imatrix_init_struct(CulIMatrix *m, int *data, size_t size_x, size_t size_y);

static inline CulIMatrixView *cul_imatrixview_new_struct(void);
static inline void cul_imatrixview_free_struct(CulIMatrixView *m);
static inline CulIMatrixView *cul_imatrixview_init_struct(CulIMatrixView *mv, int *data, size_t size_x, size_t size_y, size_t tda);

static inline int cul_imatrix_get(const CulIMatrix *m, size_t x, size_t y);
static inline void cul_imatrix_set(CulIMatrix *m, size_t x, size_t y, int val);
static inline int *cul_imatrix_ptr(CulIMatrix *m, size_t x, size_t y);
static inline const int *cul_imatrix_const_ptr(const CulIMatrix *m, size_t x, size_t y);

static inline int cul_imatrixview_get(const CulIMatrixView *mv, size_t x, size_t y);
static inline void cul_imatrixview_set(CulIMatrixView *mv, size_t x, size_t y, int val);
static inline int *cul_imatrixview_ptr(CulIMatrixView *mv, size_t x, size_t y);
static inline const int *cul_imatrixview_const_ptr(const CulIMatrixView *mv, size_t x, size_t y);

CulIMatrix     *cul_imatrix_new(size_t x, size_t y);
CulIMatrix     *cul_imatrix_new_empty(void);
void            cul_imatrix_free(CulIMatrix *m);
CulIMatrixView *cul_imatrixview_new(void);
void            cul_imatrixview_free(CulIMatrixView *mv);

CulIMatrixView *cul_imatrixview_matrix(CulIMatrixView *mv, CulIMatrix *base_m);
CulIMatrixView *cul_imatrixview_submatrix(CulIMatrixView *mv, CulIMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulIVectorView *cul_imatrixview_row(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_row);
CulIVectorView *cul_imatrixview_col(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_col);
CulIVectorView *cul_imatrixview_diag(CulIVectorView *vv, const CulIMatrix *base_m);
CulIVectorView *cul_imatrixview_subdiag(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_k);
CulIVectorView *cul_imatrixview_superdiag(CulIVectorView *vv, const CulIMatrix *base_m, size_t base_k);

cul_errno cul_imatrix_copy(CulIMatrix *m, const CulIMatrix *base_m);
cul_errno cul_imatrix_copy_offset(CulIMatrix *m, const CulIMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_imatrix_copy_submatrix(CulIMatrix *m, const CulIMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_imatrix_copy_view(CulIMatrix *m, const CulIMatrixView *base_mv);
cul_errno cul_imatrixview_copy(CulIMatrixView *mv, const CulIMatrixView *base_mv);

cul_errno cul_imatrix_copy_row(CulIMatrix *m, const CulIMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_imatrix_copy_col(CulIMatrix *m, const CulIMatrix *base_m, size_t col, size_t base_col);

cul_errno cul_imatrix_swap(CulIMatrix *ma, CulIMatrix *mb);
cul_errno cul_imatrix_swap_row(CulIMatrix *ma, CulIMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_imatrix_swap_col(CulIMatrix *ma, CulIMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_imatrix_resize(CulIMatrix *m, size_t x, size_t y);
cul_errno cul_imatrix_resize_empty(CulIMatrix *m, size_t x, size_t y);

cul_errno cul_imatrix_transpose(CulIMatrix *m);

int       cul_imatrix_min(const CulIMatrix *m);
size_t    cul_imatrix_min_index(const CulIMatrix *m);
int       cul_imatrix_max(const CulIMatrix *m);
size_t    cul_imatrix_max_index(const CulIMatrix *m);
void      cul_imatrix_minmax(const CulIMatrix *m, int *min, int *max);
void      cul_imatrix_minmax_index(const CulIMatrix *m, size_t *min_i, size_t *max_i);

cul_errno cul_imatrix_fprintf(FILE *stream, const CulIMatrix *m, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_imatrix_fscanf(FILE *stream, CulIMatrix *m, const char *format, const char *separator, const char *begin, const char *end, const char *row);

/* implementation */

static inline CulIMatrix *cul_imatrix_new_struct(void) {
	return cul_slab_new(sizeof(CulIMatrix));
}

static inline void cul_imatrix_free_struct(CulCVector *m) {
	cul_slab_free(sizeof(CulIMatrix), m);
}

static inline CulIMatrix *cul_imatrix_init_struct(CulIMatrix *m, int *data, size_t size_x, size_t size_y) {
	m->data = data;
	m->size_x = size_x;
	m->size_y = size_y;
	return m;
}

static inline CulIMatrixView *cul_imatrixview_new_struct(void) {
	return cul_slab_new(sizeof(CulIMatrixView));
}

static inline void cul_imatrixview_free_struct(CulIMatrixView *m) {
	cul_slab_free(sizeof(CulIMatrixView), m);
}

static inline CulIMatrixView *cul_imatrixview_init_struct(CulIMatrixView *mv, int *data, size_t size_x, size_t size_y, size_t tda) {
	mv->data = data;
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	return mv;
}

static inline int cul_imatrix_get(const CulIMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return *(m->data + m->size_x * y + x);
}

static inline void cul_imatrix_set(CulIMatrix *m, size_t x, size_t y, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(m->data + m->size_x * y + x) = value;
}

static inline int *cul_imatrix_ptr(CulIMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline const int *cul_imatrix_const_ptr(const CulIMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline int cul_imatrixview_get(const CulIMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return mv->data[mv->tda * y + x];
}

static inline void cul_imatrixview_set(CulIMatrixView *mv, size_t x, size_t y, int value) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	mv->data[mv->tda * y + x] = value;
}

static inline int *cul_imatrixview_ptr(CulIMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

static inline const int *cul_imatrixview_const_ptr(const CulIMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

#endif /* CUL_IMATRIX_H */
