void FUNCTION(set_all)(ATOM *data, size_t size, ATOM value) {
	const ATOM *end = data + size;
	for( ; data < end; ++data)
		*data = value;
	return;
}

void FUNCTION(set_all_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride)
		*data = value;
	return;
}

void FUNCTION(add_scalar)(ATOM *data, size_t size, ATOM value) {
	const ATOM *end = data + size;
	for( ; data < end; ++data)
		*data += value;
	return;
}

void FUNCTION(add_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride)
		*data += value;
	return;
}

void FUNCTION(mul_scalar)(ATOM *data, size_t size, ATOM value) {
	const ATOM *end = data + size;
	for( ; data < end; ++data)
		*data *= value;
	return;
}

void FUNCTION(mul_scalar_stride)(ATOM *data, size_t size, size_t stride, ATOM value) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride)
		*data *= value;
	return;
}

void FUNCTION(add)(ATOM *data_out, const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	for( ; data < end; ++data, ++data_out)
		*data_out += *data;
	return;
}

void FUNCTION(add_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride, data += stride_out)
		*data_out += *data;
	return;
}

void FUNCTION(sub)(ATOM *data_out, const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	for( ; data < end; ++data, ++data_out)
		*data_out -= *data;
	return;
}

void FUNCTION(sub_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
	const ATOM *end = data + size * stride;
	for(end = data + size; data < end; data += stride, data += stride_out)
		*data_out -= *data;
	return;
}

void FUNCTION(mul)(ATOM *data_out, const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	for( ; data < end; ++data, ++data_out)
		*data_out *= *data;
	return;
}

void FUNCTION(mul_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride, data += stride_out)
		*data_out *= *data;
	return;
}

void FUNCTION(div)(ATOM *data_out, const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	for( ; data < end; ++data, ++data_out)
		*data_out /= *data;
	return;
}

void FUNCTION(div_stride)(ATOM *data_out, const ATOM *data, size_t size, size_t stride_out, size_t stride) {
	const ATOM *end = data + size * stride;
	for( ; data < end; data += stride, data += stride_out)
		*data_out /= *data;
	return;
}
