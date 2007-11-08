#include <cul/cul_list.h>

CulList *cul_list_new(cul_ptr data) {
	CulList *this;
	if( (this = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_list_init_struct(this, NULL, NULL, data);
}

CulList *cul_list_new_empty() {
	return cul_list_new(NULL);
}

void cul_list_free(CulList *this, cul_free_f *free_f) {
	if( this != NULL && free_f != NULL ) {
		free_f(this->data);
		cul_list_free_struct(this);
	}
}

void cul_list_free_all(CulList *this, cul_free_f *free_f) {
	for( CulList *n; this != NULL; this = n) {
		n = cul_list_next(this);
		if( free_f != NULL )
			free_f(this->data);
		cul_list_free_struct(this);
	}
}

CulList *cul_list_first(CulList *this) {
	if( this != NULL )
		while( cul_list_prev(this) != NULL )
			this = cul_list_prev(this);
	return this;
}

CulList *cul_list_last(CulList *this) {
	if( this != NULL )
		while( cul_list_next(this) != NULL )
			this = cul_list_next(this);
	return this;
}

CulList *cul_list_half(CulList *this) {
	CulList *n = this;
	for( ; this != NULL; this = cul_list_next(this)) {
		if( (this = cul_list_next(this)) == NULL )
			break;
		n = cul_list_next(n);
	}
	return n;
}

CulList *cul_list_nth(CulList *this, size_t n) {
	while( this != NULL && n-- )
		this = cul_list_next(this);
	return this;
}

size_t cul_list_size(CulList *this) {
	size_t size = 0;
	for( ; this != NULL; this = cul_list_next(this))
		++size;
	return size;
}

CulList *cul_list_insert_next(CulList *this, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( this != NULL ) {
		CulList *next = cul_list_next(this);

		cul_list_init_struct(n, next, this, data);
		/* adjust list pointers */
		if( next != NULL )
			next->prev = n;
		this->next = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_insert_prev(CulList *this, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( this != NULL ) {
		CulList *prev = cul_list_prev(this);

		cul_list_init_struct(n, this, prev, data);
		/* adjust list pointers */
		if( prev != NULL )
			prev->next = n;
		this->prev = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_remove(CulList *this, cul_free_f *free_f) {
	if( this != NULL ) {
		CulList *n = NULL;
		if( cul_list_prev(this) != NULL ) {
			n = cul_list_prev(this);
			n->next = cul_list_next(this);
		}
		if( cul_list_next(this) != NULL ) {
			n = cul_list_next(this);
			n->prev = cul_list_prev(this);
		}
		cul_list_free(this, free_f);
		return n;
	}
	return this;
}

CulList *cul_list_copy(CulList *this) {
	CulList *first = NULL, *n;
	if( this != NULL ) {
		if( (first = cul_list_insert_next(first, this->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, this = cul_list_next(this); this != NULL; this = cul_list_next(this))
			if( (n = cul_list_insert_next(n, this->data)) == NULL ) {
				cul_list_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulList *cul_list_detach(CulList *this, cul_cpy_f *cpy_f) {
	CulList *first = this;
	for( ; this != NULL; this = cul_list_next(this)) {
		if( (this->data = cpy_f(this->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( this = cul_list_next(this); this != NULL; this = cul_list_next(this))
				this->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulList *cul_list_reverse(CulList *this) {
	CulList *last;
	for( last = this; this != NULL; last = this) {
		this = cul_list_next(last);
		last->next = cul_list_prev(last);
		last->prev = this;
	}
	return last;
}

CulList *_cul_list_sort(CulList *this, cul_cmp_f *cmp, size_t size);
CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f);

CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f) {
	CulList *l_prev, *this, *result;

	/* initialise result (head of return list) */
	if( cmp_f(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = cul_list_next(l1);
	} else {
		result = l2;
		l2 = cul_list_next(l2);
	}
	result->prev = NULL;

	/* initialize processing */
	this = result;
	l_prev = this;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp_f(l1->data, l2->data) <= 0 ) {
			this->next = l1;
			l1 = cul_list_next(l1);
		} else {
			this->next = l2;
			l2 = cul_list_next(l2);
		}
		this = cul_list_next(this);
		this->prev = l_prev;
		l_prev = this;
	}

	/* merge last item */
	this->next = l1 != NULL? l1: l2;
	cul_list_next(this)->prev = this;

	return result;
}

CulList *_cul_list_sort(CulList *this, cul_cmp_f *cmp_f, size_t size) {
	CulList *l_half;

	if( size == 1 )
		return this;

	const size_t i_half = size >> 1;
	l_half = cul_list_nth(this, i_half);
	cul_list_prev(l_half)->next = NULL;

	return _cul_list_merge(_cul_list_sort(this, cmp_f, i_half), _cul_list_sort(l_half, cmp_f, size - i_half), cmp_f);
}

CulList *cul_list_sort(CulList *this, cul_cmp_f *cmp_f) {
	if( this == NULL )
		return NULL;

	return _cul_list_sort(this, cmp_f, cul_list_size(this));
}

size_t cul_list_unique(CulList *this, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( this == NULL )
		return 0;

	size_t unique = 0;
	CulList *l_last = this, *next = cul_list_next(this);

	for(this = next; this != NULL; this = next)
		if( cmp_f(l_last->data, this->data) == 0 ) {
			/* item is not unique */
			next = cul_list_next(this);
			l_last->next = next;
			next->prev = l_last;

			/* free item */
			if( free_f != NULL )
				free_f(this->data);
			cul_list_free_struct(this);
		} else {
			/* item is unique */
			next = cul_list_next(this);
			l_last = this;
			++unique;
		}

	return unique;
}

CulList *cul_list_find(CulList *this, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; this != NULL; this = cul_list_next(this))
			if( this->data == data )
				return this;
	else
		for( ; this != NULL; this = cul_list_next(this))
			if( !cmp_f(this->data, data) )
				return this;
	return NULL;
}

void cul_list_each(CulList *this, cul_each_f *each_f, cul_ptr user_data) {
	for(; this != NULL; this = cul_list_next(this))
		each_f(this->data, user_data);
}
