ATOM FUNCTION(min)(const ATOM *data, size_t size) {
	const ATOM *end;
	ATOM min;

	end = data + size;
	min = *data;
	for( ++data; data < end; ++data) {
		if( *data < min )
			min = *data;
	}
	return min;
}

ATOM FUNCTION(min_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;
	ATOM min;

	end = data + size * stride;
	min = *data;
	for( data += stride; data < end; data += stride) {
		if( *data < min )
			min = *data;
	}
	return min;
}

size_t FUNCTION(min_index)(const ATOM *data, size_t size) {
	const ATOM *begin, *end, *index;
	ATOM min;

	begin = data;
	end = data + size;
	min = *data; index = data;
	for( ++data; data < end; ++data) {
		if( *data < min ) {
			min = *data;
			index = data;
		}
	}
	return (size_t)(index - begin);
}

size_t FUNCTION(min_index_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *begin, *end, *index;
	ATOM min;

	begin = data;
	end = data + size * stride;
	min = *data; index = data;
	for( data += stride; data < end; data += stride) {
		if( *data < min ) {
			min = *data;
			index = data;
		}
	}
	return (size_t)(index - begin)/stride;
}

ATOM FUNCTION(max)(const ATOM *data, size_t size) {
	const ATOM *end;
	ATOM max;

	end = data + size;
	max = *data;
	for( ++data; data < end; ++data) {
		if( *data > max )
			max = *data;
	}
	return max;
}

ATOM FUNCTION(max_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *end;
	ATOM max;

	end = data + size * stride;
	max = *data;
	for( data += stride; data < end; data += stride) {
		if( *data > max )
			max = *data;
	}
	return max;
}

size_t FUNCTION(max_index)(const ATOM *data, size_t size) {
	const ATOM *begin, *end, *index;
	ATOM max;

	begin = data;
	end = data + size;
	max = *data; index = data;
	for( ++data; data < end; ++data) {
		if( *data > max ) {
			max = *data;
			index = data;
		}
	}
	return (size_t)(index - begin);
}

size_t FUNCTION(max_index_stride)(const ATOM *data, size_t size, size_t stride) {
	const ATOM *begin, *end, *index;
	ATOM max;

	begin = data;
	end = data + size * stride;
	max = *data; index = data;
	for( data += stride; data < end; data += stride) {
		if( *data > max ) {
			max = *data;
			index = data;
		}
	}
	return (size_t)(index - begin)/stride;
}

void FUNCTION(minmax)(const ATOM *data, size_t size, ATOM *min_out, ATOM *max_out) {
	const ATOM *end;
	ATOM min, max;

	end = data + size;
	min = *data;
	max = *data;
	for( ++data; data < end; ++data) {
		if( *data < min )
			min = *data;
		if( *data > max )
			max = *data;
	}
	*min_out = min;
	*max_out = max;
	return;
}

void FUNCTION(minmax_stride)(const ATOM *data, size_t size, size_t stride, ATOM *min_out, ATOM *max_out) {
	const ATOM *end;
	ATOM min, max;

	end = data + size * stride;
	min = *data;
	max = *data;
	for( data += stride; data < end; data += stride) {
		if( *data < min )
			min = *data;
		if( *data > max )
			max = *data;
	}
	*min_out = min;
	*max_out = max;
	return;
}

void FUNCTION(minmax_index)(const ATOM *data, size_t size, size_t *min_index_out, size_t *max_index_out) {
	const ATOM *begin, *end, *min_index, *max_index;
	ATOM min, max;

	begin = data;
	end = data + size;
	min = *data; min_index = data;
	max = *data; max_index = data;
	for( ++data; data < end; ++data) {
		if( *data < min ) {
			min = *data;
			min_index = data;
		}
		if( *data > max ) {
			max = *data;
			max_index = data;
		}
	}
	*min_index_out = (size_t)(min_index - begin);
	*max_index_out = (size_t)(max_index - begin);
	return;
}

void FUNCTION(minmax_index_stride)(const ATOM *data, size_t size, size_t stride, size_t *min_index_out, size_t *max_index_out) {
	const ATOM *begin, *end, *min_index, *max_index;
	ATOM min, max;

	begin = data;
	end = data + size * stride;
	min = *data; min_index = data;
	max = *data; max_index = data;
	for( data += stride; data < end; data += stride) {
		if( *data < min ) {
			min = *data;
			min_index = data;
		}
		if( *data > max ) {
			max = *data;
			max_index = data;
		}
	}
	*min_index_out = (size_t)(min_index - begin)/stride;
	*max_index_out = (size_t)(max_index - begin)/stride;
	return;
}
