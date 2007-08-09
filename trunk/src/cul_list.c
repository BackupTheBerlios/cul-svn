#include <cul/cul_list.h>

CulList *cul_list_new(cul_ptr data) {
	CulList *l;
	if( (l = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_list_init_struct(l, NULL, NULL, data);
}

CulList *cul_list_new_empty() {
	return cul_list_new(NULL);
}

void cul_list_free(CulList *l, cul_free_f *free_f) {
	if( l != NULL && free_f != NULL ) {
		free_f(l->data);
		cul_list_free_struct(l);
	}
}

void cul_list_free_all(CulList *l, cul_free_f *free_f) {
	for( CulList *n; l != NULL; l = n) {
		n = cul_list_next(l);
		if( free_f != NULL )
			free_f(l->data);
		cul_list_free_struct(l);
	}
}

CulList *cul_list_first(CulList *l) {
	if( l != NULL )
		while( cul_list_prev(l) != NULL )
			l = cul_list_prev(l);
	return l;
}

CulList *cul_list_last(CulList *l) {
	if( l != NULL )
		while( cul_list_next(l) != NULL )
			l = cul_list_next(l);
	return l;
}

CulList *cul_list_half(CulList *l) {
	CulList *n = l;
	for( ; l != NULL; l = cul_list_next(l)) {
		if( (l = cul_list_next(l)) == NULL )
			break;
		n = cul_list_next(n);
	}
	return n;
}

CulList *cul_list_nth(CulList *l, size_t n) {
	while( l != NULL && n-- )
		l = cul_list_next(l);
	return l;
}

size_t cul_list_size(CulList *l) {
	size_t size = 0;
	for( ; l != NULL; l = cul_list_next(l))
		++size;
	return size;
}

CulList *cul_list_insert_next(CulList *l, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		CulList *next = cul_list_next(l);

		cul_list_init_struct(n, next, l, data);
		/* adjust list pointers */
		if( next != NULL )
			next->prev = n;
		l->next = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_insert_prev(CulList *l, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		CulList *prev = cul_list_prev(l);

		cul_list_init_struct(n, l, prev, data);
		/* adjust list pointers */
		if( prev != NULL )
			prev->next = n;
		l->prev = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_remove(CulList *l, cul_free_f *free_f) {
	if( l != NULL ) {
		CulList *n = NULL;
		if( cul_list_prev(l) != NULL ) {
			n = cul_list_prev(l);
			n->next = cul_list_next(l);
		}
		if( cul_list_next(l) != NULL ) {
			n = cul_list_next(l);
			n->prev = cul_list_prev(l);
		}
		cul_list_free(l, free_f);
		return n;
	}
	return l;
}

CulList *cul_list_copy(CulList *l) {
	CulList *first = NULL, *n;
	if( l != NULL ) {
		if( (first = cul_list_insert_next(first, l->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, l = cul_list_next(l); l != NULL; l = cul_list_next(l))
			if( (n = cul_list_insert_next(n, l->data)) == NULL ) {
				cul_list_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulList *cul_list_detach(CulList *l, cul_cpy_f *cpy_f) {
	CulList *first = l;
	for( ; l != NULL; l = cul_list_next(l)) {
		if( (l->data = cpy_f(l->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( l = cul_list_next(l); l != NULL; l = cul_list_next(l))
				l->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulList *cul_list_reverse(CulList *l) {
	CulList *last;
	for( last = l; l != NULL; last = l) {
		l = cul_list_next(last);
		last->next = cul_list_prev(last);
		last->prev = l;
	}
	return last;
}

CulList *_cul_list_sort(CulList *l, cul_cmp_f *cmp, size_t size);
CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f);

CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f) {
	CulList *l_prev, *l, *result;

	/* initialise result (head of return list) */
	if( cmp_f(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = cul_list_next(l1);
	}
	else {
		result = l2;
		l2 = cul_list_next(l2);
	}
	result->prev = NULL;

	l = result;
	l_prev = l;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp_f(l1->data, l2->data) <= 0 ) {
			l->next = l1;
			l1 = cul_list_next(l1);
		}
		else {
			l->next = l2;
			l2 = cul_list_next(l2);
		}
		l = cul_list_next(l);
		l->prev = l_prev;
		l_prev = l;
	}

	l->next = l1 != NULL? l1: l2;
	cul_list_next(l)->prev = l;

	return result;
}

CulList *_cul_list_sort(CulList *l, cul_cmp_f *cmp_f, size_t size) {
	const size_t i_half = size >> 1;
	CulList *l_half;

	if( size == 1 )
		return l;

	l_half = cul_list_nth(l, i_half);
	cul_list_prev(l_half)->next = NULL;

	return _cul_list_merge(_cul_list_sort(l, cmp_f, i_half), _cul_list_sort(l_half, cmp_f, size - i_half), cmp_f);
}

CulList *cul_list_sort(CulList *l, cul_cmp_f *cmp_f) {
	if( l == NULL )
		return NULL;

	return _cul_list_sort(l, cmp_f, cul_list_size(l));
}

size_t cul_list_unique_free(CulList *l, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( l == NULL )
		return 0;

	size_t unique = 0;
	CulList *l_last = l, *next = cul_list_next(l);

	for(l = next; l != NULL; l = next)
		if( cmp_f(l_last->data, l->data) == 0 ) {
			/* item is not unique */
			next = cul_list_next(l);
			l_last->next = next;
			next->prev = l_last;

			/* free item */
			if( free_f != NULL )
				free_f(l->data);
			cul_list_free_struct(l);
		} else {
			/* item is unique */
			next = cul_list_next(l);
			l_last = l;
			++unique;
		}

	return unique;
}

CulList *cul_list_find(CulList *l, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; l != NULL; l = cul_list_next(l))
			if( l->data == data )
				return l;
	else
		for( ; l != NULL; l = cul_list_next(l))
			if( !cmp_f(l->data, data) )
				return l;
	return NULL;
}

void cul_list_foreach(CulList *l, cul_foreach_f *foreach_f, cul_ptr user_data) {
	for(; l != NULL; l = cul_list_next(l))
		foreach_f(l->data, user_data);
}
