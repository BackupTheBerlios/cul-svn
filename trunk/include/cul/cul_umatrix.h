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

static inline CulUMatrix     *cul_umatrix_new_struct(void);
static inline void            cul_umatrix_free_struct(CulUMatrix *m);
static inline CulUMatrix     *cul_umatrix_init_struct(CulUMatrix *m, size_t *data, size_t size_x, size_t size_y);

static inline CulUMatrixView *cul_umatrixview_new_struct(void);
static inline void            cul_umatrixview_free_struct(CulUMatrixView *m);
static inline CulUMatrixView *cul_umatrixview_init_struct(CulUMatrixView *mv, size_t *data, size_t size_x, size_t size_y, size_t tda);

static inline size_t          cul_umatrix_get(const CulUMatrix *m, size_t x, size_t y);
static inline void            cul_umatrix_set(CulUMatrix *m, size_t x, size_t y, size_t val);
static inline size_t         *cul_umatrix_ptr(CulUMatrix *m, size_t x, size_t y);
static inline const size_t   *cul_umatrix_const_ptr(const CulUMatrix *m, size_t x, size_t y);

static inline size_t          cul_umatrixview_get(const CulUMatrixView *mv, size_t x, size_t y);
static inline void            cul_umatrixview_set(CulUMatrixView *mv, size_t x, size_t y, size_t val);
static inline size_t         *cul_umatrixview_ptr(CulUMatrixView *mv, size_t x, size_t y);
static inline const size_t   *cul_umatrixview_const_ptr(const CulUMatrixView *mv, size_t x, size_t y);

CulUMatrix     *cul_umatrix_new(size_t x, size_t y);
CulUMatrix     *cul_umatrix_new_empty(void);
void            cul_umatrix_free(CulUMatrix *m);
CulUMatrixView *cul_umatrixview_new(void);
void            cul_umatrixview_free(CulUMatrixView *mv);

CulUMatrixView *cul_umatrixview_matrix(CulUMatrixView *mv, CulUMatrix *base_m);
CulUMatrixView *cul_umatrixview_submatrix(CulUMatrixView *mv, CulUMatrix *base_m, size_t base_offset_x, size_t base_offset_y, size_t base_size_x, size_t base_size_y);
CulUVectorView *cul_umatrixview_row(CulUVectorView *vv, const CulUMatrix *base_m, size_t base_row);
CulUVectorView *cul_umatrixview_col(CulUVectorView *vv, const CulUMatrix *base_m, size_t base_col);
CulUVectorView *cul_umatrixview_diag(CulUVectorView *vv, const CulUMatrix *base_m);
CulUVectorView *cul_umatrixview_subdiag(CulUVectorView *vv, const CulUMatrix *base_m, size_t base_k);
CulUVectorView *cul_umatrixview_superdiag(CulUVectorView *vv, const CulUMatrix *base_m, size_t base_k);

void      cul_umatrix_zero(CulUMatrix *m);

cul_errno cul_umatrix_copy(CulUMatrix *m, const CulUMatrix *base_m);
cul_errno cul_umatrix_copy_offset(CulUMatrix *m, const CulUMatrix *base_m, size_t offset_x, size_t offset_y);
cul_errno cul_umatrix_copy_submatrix(CulUMatrix *m, const CulUMatrix *base_m, size_t base_offset_x, size_t base_offset_y);
cul_errno cul_umatrix_copy_view(CulUMatrix *m, const CulUMatrixView *base_mv);
cul_errno cul_umatrixview_copy(CulUMatrixView *mv, const CulUMatrixView *base_mv);

cul_errno cul_umatrix_copy_row(CulUMatrix *m, const CulUMatrix *base_m, size_t row, size_t base_row);
cul_errno cul_umatrix_copy_col(CulUMatrix *m, const CulUMatrix *base_m, size_t col, size_t base_col);

cul_errno cul_umatrix_swap(CulUMatrix *ma, CulUMatrix *mb);
cul_errno cul_umatrix_swap_row(CulUMatrix *ma, CulUMatrix *mb, size_t row_a, size_t row_b);
cul_errno cul_umatrix_swap_col(CulUMatrix *ma, CulUMatrix *mb, size_t col_a, size_t col_b);

cul_errno cul_umatrix_resize(CulUMatrix *m, size_t x, size_t y);
cul_errno cul_umatrix_resize_empty(CulUMatrix *m, size_t x, size_t y);

cul_errno cul_umatrix_transpose(CulUMatrix *m);

size_t    cul_umatrix_min(const CulUMatrix *m);
size_t    cul_umatrix_min_index(const CulUMatrix *m);
size_t    cul_umatrix_max(const CulUMatrix *m);
size_t    cul_umatrix_max_index(const CulUMatrix *m);
void      cul_umatrix_minmax(const CulUMatrix *m, size_t *min, size_t *max);
void      cul_umatrix_minmax_index(const CulUMatrix *m, size_t *min_i, size_t *max_i);

cul_errno cul_umatrix_fprintf(FILE *stream, const CulUMatrix *m, const char *format, const char *separator, const char *begin, const char *end, const char *row);
cul_errno cul_umatrix_fscanf(FILE *stream, CulUMatrix *m, const char *format, const char *separator, const char *begin, const char *end, const char *row);

/* implementation */

static inline CulUMatrix *cul_umatrix_new_struct(void) {
	return cul_slab_new(sizeof(CulUMatrix));
}

static inline void cul_umatrix_free_struct(CulUMatrix *m) {
	cul_slab_free(sizeof(CulUMatrix), m);
}

static inline CulUMatrix *cul_umatrix_init_struct(CulUMatrix *m, size_t *data, size_t size_x, size_t size_y) {
	m->data = data;
	m->size_x = size_x;
	m->size_y = size_y;
	return m;
}

static inline CulUMatrixView *cul_umatrixview_new_struct(void) {
	return cul_slab_new(sizeof(CulUMatrixView));
}

static inline void cul_umatrixview_free_struct(CulUMatrixView *m) {
	cul_slab_free(sizeof(CulUMatrixView), m);
}

static inline CulUMatrixView *cul_umatrixview_init_struct(CulUMatrixView *mv, size_t *data, size_t size_x, size_t size_y, size_t tda) {
	mv->data = data;
	mv->size_x = size_x;
	mv->size_y = size_y;
	mv->tda = tda;
	return mv;
}

static inline size_t cul_umatrix_get(const CulUMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return *(m->data + m->size_x * y + x);
}

static inline void cul_umatrix_set(CulUMatrix *m, size_t x, size_t y, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	*(m->data + m->size_x * y + x) = value;
}

static inline size_t *cul_umatrix_ptr(CulUMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline const size_t *cul_umatrix_const_ptr(const CulUMatrix *m, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= m->size_x || y >= m->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (m->data + m->size_x * y + x);
}

static inline size_t cul_umatrixview_get(const CulUMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(0, CUL_EBADPOS);
#endif
	return mv->data[mv->tda * y + x];
}

static inline void cul_umatrixview_set(CulUMatrixView *mv, size_t x, size_t y, size_t value) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET_VOID(CUL_EBADPOS);
#endif
	mv->data[mv->tda * y + x] = value;
}

static inline size_t *cul_umatrixview_ptr(CulUMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

static inline const size_t *cul_umatrixview_const_ptr(const CulUMatrixView *mv, size_t x, size_t y) {
#ifdef CUL_RANGE_CHECK
	if( x >= mv->size_x || y >= mv->size_y ) CUL_ERROR_ERRNO_RET(NULL, CUL_EBADPOS);
#endif
	return (mv->data + mv->tda * y + x);
}

#endif /* __CUL_IMATRIX_H__ */
