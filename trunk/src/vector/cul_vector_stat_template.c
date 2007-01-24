double FUNCTION(vector_sum)(const TYPE(Vector)  *v) {
	return FUNCTION(sum)(v->data, v->size);
}

double FUNCTION(vector_mean)(const TYPE(Vector)  *v) {
	return FUNCTION(mean)(v->data, v->size);
}

double FUNCTION(vector_variance)(const TYPE(Vector)  *v, double mean) {
	return FUNCTION(variance)(v->data, v->size, mean);
}

double FUNCTION(vectorview_sum)(const VIEW(Vector)  *vv) {
	return FUNCTION(sum_stride)(vv->data, vv->size, vv->stride);
}

double FUNCTION(vectorview_mean)(const VIEW(Vector)  *vv) {
	return FUNCTION(mean_stride)(vv->data, vv->size, vv->stride);
}

double FUNCTION(vectorview_variance)(const VIEW(Vector)  *vv, double mean) {
	return FUNCTION(variance_stride)(vv->data, vv->size, vv->stride, mean);
}
