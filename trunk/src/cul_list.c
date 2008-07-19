#include <cul/cul_list.h>

CulList *cul_list_new(cul_ptr data) {
	CulList *list;
	if( (list = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_list_init_struct(list, data, NULL, NULL);
}

CulList *cul_list_new_empty() {
	return cul_list_new(NULL);
}

void cul_list_free(CulList *list, cul_free_f *free_f) {
	if( list != NULL && free_f != NULL ) {
		free_f(list->data);
		cul_list_free_struct(list);
	}
}

void cul_list_free_all(CulList *list, cul_free_f *free_f) {
	for( CulList *n; list != NULL; list = n) {
		n = list->next;
		if( free_f != NULL )
			free_f(list->data);
		cul_list_free_struct(list);
	}
}

CulList *cul_list_first(CulList *list) {
	if( list != NULL )
		while( list->prev != NULL )
			list = list->prev;
	return list;
}

CulList *cul_list_last(CulList *list) {
	if( list != NULL )
		while( list->next != NULL )
			list = list->next;
	return list;
}

CulList *cul_list_half(CulList *list) {
	CulList *n = list;
	for( ; list != NULL; list = list->next) {
		if( (list = list->next) == NULL )
			break;
		n = n->next;
	}
	return n;
}

CulList *cul_list_nth(CulList *list, size_t n) {
	while( list != NULL && n-- )
		list = list->next;
	return list;
}

size_t cul_list_size(CulList *list) {
	size_t size = 0;
	for( ; list != NULL; list = list->next)
		++size;
	return size;
}

CulList *cul_list_insert_next(CulList *list, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( list != NULL ) {
		CulList *next = list->next;

		cul_list_init_struct(n, data, next, list);
		/* adjust list pointers */
		if( next != NULL )
			next->prev = n;
		list->next = n;
	}
	else
		cul_list_init_struct(n, data, NULL, NULL);
	return n;
}

CulList *cul_list_insert_prev(CulList *list, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( list != NULL ) {
		CulList *prev = list->prev;

		cul_list_init_struct(n, data, list, prev);
		/* adjust list pointers */
		if( prev != NULL )
			prev->next = n;
		list->prev = n;
	}
	else
		cul_list_init_struct(n, data, NULL, NULL);
	return n;
}

CulList *cul_list_remove(CulList *list, cul_free_f *free_f) {
	if( list != NULL ) {
		CulList *n = NULL;
		if( list->prev != NULL ) {
			n = list->prev;
			n->next = list->next;
		}
		if( list->next != NULL ) {
			n = list->next;
			n->prev = list->prev;
		}
		cul_list_free(list, free_f);
		return n;
	}
	return list;
}

CulList *cul_list_copy(CulList *list) {
	CulList *first = NULL, *n;
	if( list != NULL ) {
		if( (first = cul_list_insert_next(first, list->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, list = list->next; list != NULL; list = list->next)
			if( (n = cul_list_insert_next(n, list->data)) == NULL ) {
				cul_list_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulList *cul_list_detach(CulList *list, cul_clone_f *clone_f) {
	CulList *first = list;
	for( ; list != NULL; list = list->next) {
		if( (list->data = clone_f(list->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( list = list->next; list != NULL; list = list->next)
				list->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulList *cul_list_reverse(CulList *list) {
	CulList *last = NULL;
	while( list != NULL ) {
		last = list;

		/* swap nodes */
		list = last->next;
		last->next = last->prev;
		last->prev = list;
	}
	return last;
}

CulList *_cul_list_sort(CulList *list, cul_cmp_f *cmp, size_t size);
CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f);

CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp_f) {
	CulList *l_prev, *list, *result;

	/* initialise result (head of return list) */
	if( cmp_f(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = l1->next;
	} else {
		result = l2;
		l2 = l2->next;
	}
	result->prev = NULL;

	/* initialize processing */
	list = result;
	l_prev = list;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp_f(l1->data, l2->data) <= 0 ) {
			list->next = l1;
			l1 = l1->next;
		} else {
			list->next = l2;
			l2 = l2->next;
		}
		list = list->next;
		list->prev = l_prev;
		l_prev = list;
	}

	/* merge last item */
	list->next = l1 != NULL? l1: l2;
	list->next->prev = list;

	return result;
}

CulList *_cul_list_sort(CulList *list, cul_cmp_f *cmp_f, size_t size) {
	CulList *l_half;

	if( size == 1 )
		return list;

	const size_t i_half = size >> 1;
	l_half = cul_list_nth(list, i_half);
	l_half->prev->next = NULL;

	return _cul_list_merge(
			_cul_list_sort(list, cmp_f, i_half),
			_cul_list_sort(l_half, cmp_f, size - i_half),
			cmp_f);
}

CulList *cul_list_sort(CulList *list, cul_cmp_f *cmp_f) {
	if( list == NULL )
		return NULL;

	return _cul_list_sort(list, cmp_f, cul_list_size(list));
}

size_t cul_list_unique(CulList *list, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( list == NULL )
		return 0;

	size_t unique = 0;
	CulList *l_last = list, *next = list->next;

	for(list = next; list != NULL; list = next)
		if( cmp_f(l_last->data, list->data) == 0 ) {
			/* item is not unique */
			next = list->next;
			l_last->next = next;
			next->prev = l_last;

			/* free item */
			if( free_f != NULL )
				free_f(list->data);
			cul_list_free_struct(list);
		} else {
			/* item is unique */
			next = list->next;
			l_last = list;
			++unique;
		}

	return unique;
}

CulList *cul_list_find(CulList *list, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; list != NULL; list = list->next)
			if( list->data == data )
				return list;
	else
		for( ; list != NULL; list = list->next)
			if( !cmp_f(list->data, data) )
				return list;
	return NULL;
}

void cul_list_each(CulList *list, cul_each_f *each_f) {
	for(CulList *next; list != NULL; list = next) {
		next = list->next;
		each_f(list->data);
	}
}

void cul_list_each_prv(CulList *list, cul_each_prv_f *each_prv_f, cul_ptr prv) {
	for(CulList *next; list != NULL; list = next) {
		next = list->next;
		each_prv_f(list->data, prv);
	}
}

