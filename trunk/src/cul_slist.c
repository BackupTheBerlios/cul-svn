#include <cul/cul_slist.h>

CulSList *cul_slist_new(cul_ptr data) {
	CulSList *l;
	if( (l = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_slist_init_struct(l, NULL, data);
}

CulSList *cul_slist_new_empty() {
	return cul_slist_new(NULL);
}

void cul_slist_free(CulSList *l, cul_free_f *free_f) {
	if( l != NULL && free_f != NULL )
		free_f(l->data);
	cul_slist_free_struct(l);
}

void cul_slist_free_all(CulSList *l, cul_free_f *free_f) {
	for( CulSList *n; l != NULL; l = n) {
		n = cul_slist_next(l);
		if( free_f != NULL )
			free_f(l->data);
		cul_slist_free_struct(l);
	}
}

CulSList *cul_slist_last(CulSList *l) {
	if( l != NULL )
		while( cul_slist_next(l) != NULL )
			l = cul_slist_next(l);
	return l;
}

CulSList *cul_slist_half(CulSList *l) {
	CulSList *n = l;
	for( ; l != NULL; l = cul_slist_next(l)) {
		if( (l = cul_slist_next(l)) == NULL )
			break;
		n = cul_slist_next(n);
	}
	return n;
}

CulSList *cul_slist_nth(CulSList *l, size_t n) {
	while( l != NULL && n-- )
		l = cul_slist_next(l);
	return l;
}

size_t cul_slist_size(CulSList *l) {
	size_t size = 0;
	for( ; l != NULL; l = cul_slist_next(l))
		++size;
	return size;
}

CulSList *cul_slist_insert_next(CulSList *l, cul_ptr data) {
	CulSList *n;
	if( (n = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		cul_slist_init_struct(n, cul_slist_next(l), data);
		l->next = n;
	}
	else
		cul_slist_init_struct(n, NULL, data);
	return n;
}

CulSList *cul_slist_remove(CulSList *l, cul_free_f *free_f) {
	if( l != NULL ) {
		CulSList *n = cul_slist_next(l);
		cul_slist_free(l, free_f);
		return n;
	}
	return l;
}

CulSList *cul_slist_remove_next(CulSList *l, cul_free_f *free_f) {
	if( l != NULL ) {
		CulSList *n = cul_slist_next(l);
		if( n != NULL ) {
			l->next = cul_slist_next(n);
			cul_slist_free(n, free_f);
		}
	}
	return l;
}

CulSList *cul_slist_copy(CulSList *l) {
	CulSList *first = NULL, *n;
	if( l != NULL ) {
		if( (first = cul_slist_insert_next(first, l->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, l = cul_slist_next(l); l != NULL; l = cul_slist_next(l))
			if( (n = cul_slist_insert_next(n, l->data)) == NULL ) {
				cul_slist_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulSList *cul_slist_detach(CulSList *l, cul_cpy_f *cpy_f) {
	CulSList *first = l;
	for( ; l != NULL; l = cul_slist_next(l)) {
		if( (l->data = cpy_f(l->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( l = cul_slist_next(l); l != NULL; l = cul_slist_next(l))
				l->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulSList *cul_slist_reverse(CulSList *l) {
	CulSList *prev = NULL, *next;
	for( ; l != NULL; prev = l, l = next) {
		next = cul_slist_next(l);
		l->next = prev;
	}
	return prev;
}

CulSList *cul_slist_sort(CulSList *l, cul_cmp_f *cmp_f) {
	CUL_UNUSED(l);
	CUL_UNUSED(cmp_f);
	/* TODO cul_slist_sort stub */
	CUL_ERROR_ERRNO_RET(NULL, CUL_ESTUB);
}

size_t cul_slist_unique_free(CulSList *l, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( l == NULL )
		return 0;

	size_t unique = 0;
	CulSList *l_last = l, *next = cul_slist_next(l);

	for(l = next; l != NULL; l = next)
		if( cmp_f(l_last->data, l->data) == 0 ) {
			/* item is not unique */
			next = cul_slist_next(l);
			l_last->next = next;

			/* free item */
			if( free_f != NULL )
				free_f(l->data);
			cul_slist_free_struct(l);
		} else {
			/* item is unique */
			next = cul_slist_next(l);
			l_last = l;
			++unique;
		}

	return unique;
}

CulSList *cul_slist_find(CulSList *l, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; l != NULL; l = cul_slist_next(l))
			if( l->data == data )
				return l;
	else
		for( ; l != NULL; l = cul_slist_next(l))
			if( !cmp_f(l->data, data) )
				return l;
	return NULL;
}

void cul_slist_foreach(CulSList *l, cul_foreach_f *foreach_f, cul_ptr user_data) {
	for(; l != NULL; l = cul_slist_next(l))
		foreach_f(l->data, user_data);
}
