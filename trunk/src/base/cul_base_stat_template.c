double FUNCTION(sum)(const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	double sum = 0.0;
	for(; data < end; ++data)
		sum += *data;
	return sum;
}

double FUNCTION(sum_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *end = data + size * stride;
	double sum = 0.0;
	for(; data < end; data += stride)
		sum += *data;
	return sum;
}

double FUNCTION(mean)(const ATOM *data, size_t size) {
	const ATOM *end = data + size;
	double mean = 0.0;
	for(; data < end; ++data)
		mean += *data;
	return mean /= size;
}

double FUNCTION(mean_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *end = data + size * stride;
	double mean = 0.0;
	for(; data < end; data += stride)
		mean += *data;
	return mean /= size;
}

double FUNCTION(variance)(const ATOM *data, size_t size, double mean) {
	const ATOM *end = data + size;
	double variance = 0.0;
	for(; data < end; ++data)
		variance += (*data - mean)*(*data - mean);
	return variance /= size;
}

double FUNCTION(variance_stride)(const ATOM *data, size_t size, size_t stride, double mean) {
	const ATOM *end = data + size * stride;
	double variance = 0.0;
	for(; data < end; data += stride)
		variance += (*data - mean)*(*data - mean);
	return variance /= size;
}
