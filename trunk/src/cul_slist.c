#include <cul/cul_slist.h>

CulSList *cul_slist_new(cul_ptr data) {
	CulSList *this;
	if( (this = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_slist_init_struct(this, NULL, data);
}

CulSList *cul_slist_new_empty() {
	return cul_slist_new(NULL);
}

void cul_slist_free(CulSList *this, cul_free_f *free_f) {
	if( this != NULL && free_f != NULL )
		free_f(this->data);
	cul_slist_free_struct(this);
}

void cul_slist_free_all(CulSList *this, cul_free_f *free_f) {
	for( CulSList *n; this != NULL; this = n) {
		n = cul_slist_next(this);
		if( free_f != NULL )
			free_f(this->data);
		cul_slist_free_struct(this);
	}
}

CulSList *cul_slist_last(CulSList *this) {
	if( this != NULL )
		while( cul_slist_next(this) != NULL )
			this = cul_slist_next(this);
	return this;
}

CulSList *cul_slist_half(CulSList *this) {
	CulSList *n = this;
	for( ; this != NULL; this = cul_slist_next(this)) {
		if( (this = cul_slist_next(this)) == NULL )
			break;
		n = cul_slist_next(n);
	}
	return n;
}

CulSList *cul_slist_nth(CulSList *this, size_t n) {
	while( this != NULL && n-- )
		this = cul_slist_next(this);
	return this;
}

size_t cul_slist_size(CulSList *this) {
	size_t size = 0;
	for( ; this != NULL; this = cul_slist_next(this))
		++size;
	return size;
}

CulSList *cul_slist_insert_next(CulSList *this, cul_ptr data) {
	CulSList *n;
	if( (n = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( this != NULL ) {
		cul_slist_init_struct(n, cul_slist_next(this), data);
		this->next = n;
	}
	else
		cul_slist_init_struct(n, NULL, data);
	return n;
}

CulSList *cul_slist_remove(CulSList *this, cul_free_f *free_f) {
	if( this != NULL ) {
		CulSList *n = cul_slist_next(this);
		cul_slist_free(this, free_f);
		return n;
	}
	return this;
}

CulSList *cul_slist_remove_next(CulSList *this, cul_free_f *free_f) {
	if( this != NULL ) {
		CulSList *n = cul_slist_next(this);
		if( n != NULL ) {
			this->next = cul_slist_next(n);
			cul_slist_free(n, free_f);
		}
	}
	return this;
}

CulSList *cul_slist_copy(CulSList *this) {
	CulSList *first = NULL, *n;
	if( this != NULL ) {
		if( (first = cul_slist_insert_next(first, this->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, this = cul_slist_next(this); this != NULL; this = cul_slist_next(this))
			if( (n = cul_slist_insert_next(n, this->data)) == NULL ) {
				cul_slist_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulSList *cul_slist_detach(CulSList *this, cul_clone_f *clone_f) {
	CulSList *first = this;
	for( ; this != NULL; this = cul_slist_next(this)) {
		if( (this->data = clone_f(this->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( this = cul_slist_next(this); this != NULL; this = cul_slist_next(this))
				this->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulSList *cul_slist_reverse(CulSList *this) {
	CulSList *prev = NULL, *next;
	for( ; this != NULL; prev = this, this = next) {
		next = cul_slist_next(this);
		this->next = prev;
	}
	return prev;
}

CulSList *_cul_slist_sort(CulSList *this, cul_cmp_f *cmp, size_t size);
CulSList *_cul_slist_merge(CulSList *l1, CulSList *l2, cul_cmp_f *cmp_f);

CulSList *_cul_slist_merge(CulSList *l1, CulSList *l2, cul_cmp_f *cmp_f) {
	CulSList *this, *result;

	/* initialize result (head of return list) */
	if( cmp_f(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = cul_slist_next(l1);
	} else {
		result = l2;
		l2 = cul_slist_next(l2);
	}

	/* initialize processing */
	this = result;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp_f(l1->data, l2->data) <= 0 ) {
			this->next = l1;
			l1 = cul_slist_next(l1);
		} else {
			this->next = l2;
			l2 = cul_slist_next(l2);
		}
		this = cul_slist_next(this);
	}

	/* merge last item */
	this->next = l1 != NULL? l1: l2;

	return result;
}

CulSList *_cul_slist_sort(CulSList *this, cul_cmp_f *cmp_f, size_t size) {
	CulSList *l_half, *l_half_prev;

	if( size == 1 )
		return this;

	const size_t i_half = size >> 1;
	l_half_prev = cul_slist_nth(this, i_half - 1);
	l_half = cul_slist_next(l_half_prev);
	l_half_prev->next = NULL;

	return _cul_slist_merge(_cul_slist_sort(this, cmp_f, i_half), _cul_slist_sort(l_half, cmp_f, size - i_half), cmp_f);
}

CulSList *cul_slist_sort(CulSList *this, cul_cmp_f *cmp_f) {
	if( this == NULL )
		return NULL;

	return _cul_slist_sort(this, cmp_f, cul_slist_size(this));
}

size_t cul_slist_unique(CulSList *this, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( this == NULL )
		return 0;

	size_t unique = 0;
	CulSList *l_last = this, *next = cul_slist_next(this);

	for(this = next; this != NULL; this = next)
		if( cmp_f(l_last->data, this->data) == 0 ) {
			/* item is not unique */
			next = cul_slist_next(this);
			l_last->next = next;

			/* free item */
			if( free_f != NULL )
				free_f(this->data);
			cul_slist_free_struct(this);
		} else {
			/* item is unique */
			next = cul_slist_next(this);
			l_last = this;
			++unique;
		}

	return unique;
}

CulSList *cul_slist_find(CulSList *this, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; this != NULL; this = cul_slist_next(this))
			if( this->data == data )
				return this;
	else
		for( ; this != NULL; this = cul_slist_next(this))
			if( !cmp_f(this->data, data) )
				return this;
	return NULL;
}

void cul_slist_each(CulSList *this, cul_each_f *each_f, cul_ptr user_data) {
	for(; this != NULL; this = cul_slist_next(this))
		each_f(this->data, user_data);
}
