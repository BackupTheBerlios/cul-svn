#include <cul/cul_slist.h>

CulSList *cul_slist_new(cul_ptr data) {
	CulSList *l;
	if( (l = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
	cul_slist_init_struct(l, NULL, data);
	return l;
}

CulSList *cul_slist_new_empty() {
	return cul_slist_new(NULL);
}

void cul_slist_free(CulSList *l, cul_free_f *free_data) {
	if( l != NULL && free_data != NULL )
		free_data(l->data);
	cul_slist_free_struct(l);
}

void cul_slist_free_all(CulSList *l, cul_free_f *free_data) {
	for( CulSList *n; l != NULL; l = n) {
		n = cul_slist_next(l);
		if( free_data != NULL )
			free_data(l->data);
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
		CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);

	if( l != NULL ) {
		cul_slist_init_struct(n, cul_slist_next(l), data);
		l->next = n;
	}
	else
		cul_slist_init_struct(n, NULL, data);
	return n;
}

CulSList *cul_slist_remove(CulSList *l, cul_free_f *free_data) {
	if( l != NULL ) {
		CulSList *n = cul_slist_next(l);
		cul_slist_free(l, free_data);
		return n;
	}
	return l;
}

CulSList *cul_slist_remove_next(CulSList *l, cul_free_f *free_data) {
	if( l != NULL ) {
		CulSList *n = cul_slist_next(l);
		if( n != NULL ) {
			l->next = cul_slist_next(n);
			cul_slist_free(n, free_data);
		}
	}
	return l;
}

CulSList *cul_slist_copy(CulSList *l) {
	CulSList *first = NULL, *n;
	if( l != NULL ) {
		if( (first = cul_slist_insert_next(first, l->data)) == NULL )
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
		for( n = first, l = cul_slist_next(l); l != NULL; l = cul_slist_next(l))
			if( (n = cul_slist_insert_next(n, l->data)) == NULL ) {
				cul_slist_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulSList *cul_slist_detach(CulSList *l, cul_cpy_f *cpy) {
	CulSList *first = l;
	for( ; l != NULL; l = cul_slist_next(l)) {
		if( (l->data = cpy(l->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( l = cul_slist_next(l); l != NULL; l = cul_slist_next(l))
				l->data = NULL;
			CUL_ERROR_ERRNO_RET_VAL(NULL, CUL_ENOMEM);
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

CulSList *cul_slist_find(CulSList *l, cul_ptr data, cul_eq_f *eq) {
	if( eq == NULL )
		for( ; l != NULL; l = cul_slist_next(l))
			if( l->data == data )
				return l;
	else
		for( ; l != NULL; l = cul_slist_next(l))
			if( eq(l->data, data) )
				return l;
	return NULL;
}

CulSList *cul_slist_sort(CulSList *l, cul_cmp_f *cmp) {
	CUL_UNUSED(l);
	CUL_UNUSED(cmp);
	return NULL;
}

size_t cul_slist_unique(CulSList *l, cul_eq_f *eq) {
	CUL_UNUSED(l);
	CUL_UNUSED(eq);
	return 0;
}

size_t cul_slist_foreach(CulSList *l, cul_foreach_f *foreach) {
	size_t i_foreach = 0;
	for( ; l != NULL; l = cul_slist_next(l), ++i_foreach )
		if( foreach(l->data) )
			break;

	return i_foreach;
}

size_t cul_slist_foreach_data(CulSList *l, cul_foreach_data_f *foreach, cul_ptr data) {
	size_t i_foreach = 0;
	for( ; l != NULL; l = cul_slist_next(l), ++i_foreach )
		if( foreach(l->data, data) )
			break;

	return i_foreach;
}

