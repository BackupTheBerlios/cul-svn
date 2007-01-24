#include <cul/cul_list.h>

CulList *cul_list_new(cul_ptr data) {
	CulList *l;
	if( (l = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	if( cul_list_init(l, data) == NULL ) {
		cul_list_free_struct(l);
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_EINIT);
	}
	return l;
}

CulList *cul_list_init(CulList *l, cul_ptr data) {
	cul_list_init_struct(l, NULL, NULL, data);
	return l;
}

void cul_list_free(CulList *l, cul_free_f *free_data) {
	if( l != NULL && free_data != NULL )
		free_data(l->data);
	cul_list_free_struct(l);
}

void cul_list_free_all(CulList *l, cul_free_f *free_data) {
	CulList *n;
	for( ; l != NULL; l = n) {
		n = l->next;
		if( free_data != NULL )
			free_data(l->data);
		cul_list_free_struct(l);
	}
}

void cul_list_free_all_null(CulList **l, cul_free_f *free_item) {
	cul_list_free_all(*l, free_item);
	*l = NULL;
}

CulList *cul_list_first(CulList *l) {
	if( l != NULL )
		while( l->prev != NULL )
			l = l->prev;
	return l;
}

CulList *cul_list_last(CulList *l) {
	if( l != NULL )
		while( l->next != NULL )
			l = l->next;
	return l;
}

CulList *cul_list_half(CulList *l) {
	CulList *n = NULL;
	for( ; l != NULL; l = l->next) {
		if( (l = l->next) == NULL )
			break;
		n = n->next;
	}
	return n;
}

CulList *cul_list_nth(CulList *l, size_t n) {
	while( l != NULL && n-- )
		l = l->next;
	return l;
}

size_t cul_list_size(CulList *l) {
	size_t size = 0;
	for( ; l != NULL; l = l->next)
		++size;
	return size;
}

CulList *cul_list_insert_next(CulList *l, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		cul_list_init_struct(n, l->next, l, data);
		/* adjust list pointers */
		if( l->next != NULL )
			l->next->prev = n;
		l->next = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_insert_next_node(CulList *l, CulList *node) {
	if( l != NULL ) {
		/* init node */
		node->next = l->next;
		node->prev = l;

		/* adjust list */
		if( l->next != NULL )
			l->next->prev = node;
		l->next = node;
	}
	return node;
}

CulList *cul_list_insert_prev(CulList *l, cul_ptr data) {
	CulList *n;
	if( (n = cul_list_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		cul_list_init_struct(n, l, l->prev, data);
		/* adjust list pointers */
		if( l->prev != NULL )
			l->prev->next = n;
		l->prev = n;
	}
	else
		cul_list_init_struct(n, NULL, NULL, data);
	return n;
}

CulList *cul_list_insert_prev_node(CulList *l, CulList *node) {
	if( l != NULL ) {
		/* init node */
		node->next = l;
		node->prev = l->prev;

		/* adjust list */
		if( l->prev != NULL )
			l->prev->next = node;
		l->prev = node;
	}
	return node;
}

CulList *cul_list_remove(CulList *l, cul_free_f *free_item) {
	if( l != NULL ) {
		CulList *n = NULL;
		if( l->prev != NULL ) {
			n = l->prev;
			n->next = l->next;
		}
		if( l->next != NULL ) {
			n = l->next;
			n->prev = l->prev;
		}
		cul_list_free(l, free_item);
		return n;
	}
	return l;
}

void cul_list_remove_all(CulList *l, cul_free_f *free_item) {
	if( l != NULL ) {
		if( l->prev != NULL )
			l->prev->next = NULL;
		cul_list_free_all(l, free_item);
	}
}

CulList *cul_list_copy(CulList *l) {
	CulList *first = NULL, *n;
	if( l != NULL ) {
		if( (first = cul_list_insert_next(first, l->data)) == NULL ) {
			cul_list_free_all(l, NULL);
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		}
		for( n = first, l = l->next; l != NULL; l = l->next)
			if( (n = cul_list_insert_next(n, l->data)) == NULL ) {
			cul_list_free_all(first, NULL);
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulList *cul_list_detach(CulList *l, cul_cpy_f *cpy) {
	CulList *first = l;
	for( ; l != NULL; l = l->next) {
		if( (l->data = cpy(l->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( l = l->next; l != NULL; l = l->next)
				l->data = NULL;
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulList *cul_list_reverse(CulList *l) {
	CulList *last;
	for( last = l; l != NULL; last = l) {
		l = last->next;
		last->next = last->prev;
		last->prev = l;
	}
	return last;
}

CulList *cul_list_find(CulList *l, cul_ptr data, cul_eq_f *eq) {
	if( eq == NULL )
		for( ; l != NULL; l = l->next)
			if( l->data == data )
				return l;
	else
		for( ; l != NULL; l = l->next)
			if( eq(l->data, data) )
				return l;
	return NULL;
}

CulList *_cul_list_sort(CulList *l, cul_cmp_f *cmp, size_t size);
CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp);

CulList *_cul_list_merge(CulList *l1, CulList *l2, cul_cmp_f *cmp) {
	CulList *l_prev, *l, *result;

	/* initialise result (head of return list) */
	if( cmp(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = l1->next;
	}
	else {
		result = l2;
		l2 = l2->next;
	}
	result->prev = NULL;

	l = result;
	l_prev = l;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp(l1->data, l2->data) <= 0 ) {
			l->next = l1;
			l1 = l1->next;
		}
		else {
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
		l->prev = l_prev;
		l_prev = l;
	}

	l->next = l1 != NULL? l1: l2;
	l->next->prev = l;

	return result;
}

CulList *_cul_list_sort(CulList *l, cul_cmp_f *cmp, size_t size) {
	const size_t i_half = size >> 1;
	CulList *l_half;

	if( size == 1 )
		return l;

	l_half = cul_list_nth(l, i_half);
	l_half->prev->next = NULL;

	return _cul_list_merge(_cul_list_sort(l, cmp, i_half), _cul_list_sort(l_half, cmp, size - i_half), cmp);
}

CulList *cul_list_sort(CulList *l, cul_cmp_f *cmp) {
	if( l == NULL )
		return NULL;

	return _cul_list_sort(l, cmp, cul_list_size(l));
}

size_t cul_list_unique(CulList *l, cul_eq_f *eq) {
	CUL_UNUSED(l);
	CUL_UNUSED(eq);
	return 0;
}

size_t cul_list_foreach(CulList *l, cul_foreach_f *foreach) {
	size_t i_foreach = 0;
	for( ; l != NULL; l = l->next, ++i_foreach )
		if( foreach(l->data) )
			break;

	return i_foreach;
}
