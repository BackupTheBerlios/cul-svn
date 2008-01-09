#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(min)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return EMPTY;

		for( ++data; data < last; ++data) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	ATOM FUNCTION(min_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return EMPTY;

		for( data += stride; data < last; data += stride) {
			if( *data < min )
				min = *data;
		}
		return min;
	}

	size_t FUNCTION(min_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return 0;

		for( ++data; data < last; ++data) {
			if( *data < min ) {
				min = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(min_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin = data, *last = data + size * stride, *index = data;
		ATOM min;

		if( data < last )
			min = *data;
		else
			return 0;

		for( data += stride; data < last; data += stride) {
			if( *data < min ) {
				min = *data;
				index = data;
			}
		}
		return (size_t)(index - begin)/stride;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	ATOM FUNCTION(max)(const ATOM *data, size_t size) {
		const ATOM *last = data + size;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return EMPTY;

		for( ++data; data < last; ++data) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	ATOM FUNCTION(max_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *last = data + size * stride;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return EMPTY;

		for( data += stride; data < last; data += stride) {
			if( *data > max )
				max = *data;
		}
		return max;
	}

	size_t FUNCTION(max_index)(const ATOM *data, size_t size) {
		const ATOM *begin = data, *last = data + size, *index = data;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return 0;

		for( ++data; data < last; ++data) {
			if( *data > max ) {
				max = *data;
				index = data;
			}
		}
		return (size_t)(index - begin);
	}

	size_t FUNCTION(max_index_stride)(const ATOM *data, size_t size, size_t stride) {
		const ATOM *begin = data, *last = data + size * stride, *index = data;
		ATOM max;

		if( data < last )
			max = *data;
		else
			return 0;

		for( data += stride; data < last; data += stride) {
			if( *data > max ) {
				max = *data;
				index = data;
			}
		}
		return (size_t)(index - begin)/stride;
	}
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

#ifndef TEMPLATE_CUL_PTR
	void FUNCTION(minmax)(const ATOM *data, size_t size, ATOM *min_out, ATOM *max_out) {
		const ATOM *last = data + size;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_out = EMPTY;
			*max_out = EMPTY;
			return;
		}

		for( ++data; data < last; ++data) {
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
		const ATOM *last = data + size * stride;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_out = EMPTY;
			*max_out = EMPTY;
			return;
		}

		for( data += stride; data < last; data += stride) {
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
		const ATOM *begin = data, *last = data + size, *min_index = data, *max_index = data;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_index_out = 0;
			*max_index_out = 0;
			return;
		}

		for( ++data; data < last; ++data) {
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
		const ATOM *begin = data, *last = data + size * stride, *min_index = data, *max_index = data;
		ATOM min, max;

		if( data < last )
			min = max = *data;
		else {
			*min_index_out = 0;
			*max_index_out = 0;
			return;
		}

		for( data += stride; data < last; data += stride) {
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
#else /* TEMPLATE_CUL_PTR */
#endif /* TEMPLATE_CUL_PTR */

