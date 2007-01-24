ATOM FUNCTION(matrix_min)(const TYPE(Matrix) *m) {
	return FUNCTION(min)(m->data, m->size_x * m->size_y);
}

size_t FUNCTION(matrix_min_index)(const TYPE(Matrix) *m) {
	return FUNCTION(min_index)(m->data, m->size_x * m->size_y);
}

ATOM FUNCTION(matrix_max)(const TYPE(Matrix) *m) {
	return FUNCTION(max)(m->data, m->size_x * m->size_y);
}

size_t FUNCTION(matrix_max_index)(const TYPE(Matrix) *m) {
	return FUNCTION(max_index)(m->data, m->size_x * m->size_y);
}

void FUNCTION(matrix_minmax)(const TYPE(Matrix) *m, ATOM *min, ATOM *max) {
	return FUNCTION(minmax)(m->data, m->size_x * m->size_y, min, max);
}

void FUNCTION(matrix_minmax_index)(const TYPE(Matrix) *m, size_t *min_i, size_t *max_i) {
	return FUNCTION(minmax_index)(m->data, m->size_x * m->size_y, min_i, max_i);
}
