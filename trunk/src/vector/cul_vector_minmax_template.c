ATOM FUNCTION(vector_min)(const TYPE(Vector) *v) {
	return FUNCTION(min)(v->data, v->size);
}

size_t FUNCTION(vector_min_index)(const TYPE(Vector) *v) {
	return FUNCTION(min_index)(v->data, v->size);
}

ATOM FUNCTION(vector_max)(const TYPE(Vector) *v) {
	return FUNCTION(max)(v->data, v->size);
}

size_t FUNCTION(vector_max_index)(const TYPE(Vector) *v) {
	return FUNCTION(max_index)(v->data, v->size);
}

void FUNCTION(vector_minmax)(const TYPE(Vector) *v, ATOM *min, ATOM *max) {
	FUNCTION(minmax)(v->data, v->size, min, max);
}

void FUNCTION(vector_minmax_index)(const TYPE(Vector) *v, size_t *min_i, size_t *max_i) {
	FUNCTION(minmax_index)(v->data, v->size, min_i, max_i);
}

ATOM FUNCTION(vectorview_min)(const VIEW(Vector) *vv) {
	return FUNCTION(min_stride)(vv->data, vv->size, vv->stride);
}

size_t FUNCTION(vectorview_min_index)(const VIEW(Vector) *vv) {
	return FUNCTION(min_index_stride)(vv->data, vv->size, vv->stride);
}

ATOM FUNCTION(vectorview_max)(const VIEW(Vector) *vv) {
	return FUNCTION(max_stride)(vv->data, vv->size, vv->stride);
}

size_t FUNCTION(vectorview_max_index)(const VIEW(Vector) *vv) {
	return FUNCTION(max_index_stride)(vv->data, vv->size, vv->stride);
}

void FUNCTION(vectorview_minmax)(const VIEW(Vector) *vv, ATOM *min, ATOM *max) {
	FUNCTION(minmax_stride)(vv->data, vv->size, vv->stride, min, max);
}

void FUNCTION(vectorview_minmax_index)(const VIEW(Vector) *vv, size_t *min_i, size_t *max_i) {
	FUNCTION(minmax_index_stride)(vv->data, vv->size, vv->stride, min_i, max_i);
}
