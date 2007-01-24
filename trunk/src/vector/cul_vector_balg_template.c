void FUNCTION(vector_sort)(TYPE(Vector) *v, cul_cmp_f *cmp) {
	FUNCTION(sort)(v->data, v->size, cmp);
}

void FUNCTION(vectorview_sort)(VIEW(Vector) *vv, cul_cmp_f *cmp) {
	FUNCTION(sort_stride)(vv->data, vv->size, vv->stride, cmp);
}

#if !defined(PTR_HANDLER)
	void FUNCTION(vector_sort_asc)(TYPE(Vector) *v) {
		FUNCTION(sort_asc)(v->data, v->size);
	}

	void FUNCTION(vector_sort_desc)(TYPE(Vector) *v) {
		FUNCTION(sort_desc)(v->data, v->size);
	}

	void FUNCTION(vectorview_sort_asc)(VIEW(Vector) *vv) {
		FUNCTION(sort_asc_stride)(vv->data, vv->size, vv->stride);
	}

	void FUNCTION(vectorview_sort_desc)(VIEW(Vector) *vv) {
		FUNCTION(sort_desc_stride)(vv->data, vv->size, vv->stride);
	}
#endif

size_t FUNCTION(vector_unique)(TYPE(Vector)  *v, cul_eq_f *eq) {
	return (size_t)(FUNCTION(unique)(v->data, v->size, eq) - v->data);
}

size_t FUNCTION(vectorview_unique)(VIEW(Vector)  *vv, cul_eq_f *eq) {
	return (size_t)(FUNCTION(unique_stride)(vv->data, vv->size, vv->stride, eq) - vv->data)/vv->stride;
}

#if !defined(PTR_HANDLER)
	size_t FUNCTION(vector_unique_eq)(TYPE(Vector)  *v) {
		return (size_t)(FUNCTION(unique_eq)(v->data, v->size) - v->data);
	}

	size_t FUNCTION(vectorview_unique_eq)(VIEW(Vector)  *vv) {
		return (size_t)(FUNCTION(unique_eq_stride)(vv->data, vv->size, vv->stride) - vv->data)/vv->stride;
	}
#endif
