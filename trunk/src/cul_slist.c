#include <cul/cul_slist.h>

CulSList *cul_slist_new(cul_ptr data) {
	CulSList *slist;
	if( (slist = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
	return cul_slist_init_struct(slist, data, NULL);
}

CulSList *cul_slist_new_empty() {
	return cul_slist_new(NULL);
}

void cul_slist_free(CulSList *slist, cul_free_f *free_f) {
	if( slist != NULL && free_f != NULL )
		free_f(slist->data);
	cul_slist_free_struct(slist);
}

void cul_slist_free_all(CulSList *slist, cul_free_f *free_f) {
	for( CulSList *n; slist != NULL; slist = n) {
		n = slist->next;
		if( free_f != NULL )
			free_f(slist->data);
		cul_slist_free_struct(slist);
	}
}

CulSList *cul_slist_last(CulSList *slist) {
	if( slist != NULL )
		while( slist->next != NULL )
			slist = slist->next;
	return slist;
}

CulSList *cul_slist_half(CulSList *slist) {
	CulSList *n = slist;
	for( ; slist != NULL; slist = slist->next) {
		if( (slist = slist->next) == NULL )
			break;
		n = n->next;
	}
	return n;
}

CulSList *cul_slist_nth(CulSList *slist, size_t n) {
	while( slist != NULL && n-- )
		slist = slist->next;
	return slist;
}

size_t cul_slist_size(CulSList *slist) {
	size_t size = 0;
	for( ; slist != NULL; slist = slist->next)
		++size;
	return size;
}

CulSList *cul_slist_insert_next(CulSList *slist, cul_ptr data) {
	CulSList *n;
	if( (n = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	if( slist != NULL ) {
		cul_slist_init_struct(n, data, slist->next);
		slist->next = n;
	}
	else
		cul_slist_init_struct(n, data, NULL);
	return n;
}

CulSList *cul_slist_insert_prev(CulSList *slist, cul_ptr data) {
	CulSList *n;
	if( (n = cul_slist_new_struct()) == NULL )
		CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

	cul_slist_init_struct(n, data, slist);
	return n;
}

CulSList *cul_slist_remove_node(CulSList *slist, cul_free_f *free_f) {
	if( slist != NULL ) {
		CulSList *n = slist->next;
		cul_slist_free(slist, free_f);
		return n;
	}
	return slist;
}

CulSList *cul_slist_remove_next(CulSList *slist, cul_free_f *free_f) {
	if( slist != NULL ) {
		CulSList *n = slist->next;
		if( n != NULL ) {
			slist->next = n->next;
			cul_slist_free(n, free_f);
		}
	}
	return slist;
}

CulSList *cul_slist_unlink_node(CulSList *slist) {
	if( slist != NULL )
		slist->next = NULL;
	return slist;
}

CulSList *cul_slist_unlink_next(CulSList *slist) {
	if( slist != NULL ) {
		CulSList *n = slist->next;
		if( n != NULL )
			slist->next = n->next;
		return n;
	}
	return slist;
}

CulSList *cul_slist_copy(CulSList *slist) {
	CulSList *first = NULL, *n;
	if( slist != NULL ) {
		if( (first = cul_slist_insert_next(first, slist->data)) == NULL )
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		for( n = first, slist = slist->next; slist != NULL; slist = slist->next)
			if( (n = cul_slist_insert_next(n, slist->data)) == NULL ) {
				cul_slist_free_all(first, NULL);
				CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
			}
	}
	return first;
}

CulSList *cul_slist_detach(CulSList *slist, cul_clone_f *clone_f) {
	CulSList *first = slist;
	for( ; slist != NULL; slist = slist->next) {
		if( (slist->data = clone_f(slist->data)) == NULL ) {
			/* erase rest of undetached pointers */
			for( slist = slist->next; slist != NULL; slist = slist->next)
				slist->data = NULL;
			CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
		}
	}
	return first;
}

CulSList *cul_slist_reverse(CulSList *slist) {
	CulSList *prev = NULL, *next;
	for( ; slist != NULL; prev = slist, slist = next) {
		next = slist->next;;
		slist->next = prev;
	}
	return prev;
}

CulSList *_cul_slist_sort(CulSList *slist, cul_cmp_f *cmp, size_t size);
CulSList *_cul_slist_merge(CulSList *l1, CulSList *l2, cul_cmp_f *cmp_f);

CulSList *_cul_slist_merge(CulSList *l1, CulSList *l2, cul_cmp_f *cmp_f) {
	CulSList *slist, *result;

	/* initialize result (head of return list) */
	if( cmp_f(l1->data, l2->data) <= 0 ) {
		result = l1;
		l1 = l1->next;
	} else {
		result = l2;
		l2 = l2->next;
	}

	/* initialize processing */
	slist = result;

	/* process rest */
	while( l1 != NULL && l2 != NULL ) {
		if( cmp_f(l1->data, l2->data) <= 0 ) {
			slist->next = l1;
			l1 = l1->next;
		} else {
			slist->next = l2;
			l2 = l2->next;
		}
		slist = slist->next;
	}

	/* merge last item */
	slist->next = l1 != NULL? l1: l2;

	return result;
}

CulSList *_cul_slist_sort(CulSList *slist, cul_cmp_f *cmp_f, size_t size) {
	CulSList *l_half, *l_half_prev;

	if( size == 1 )
		return slist;

	const size_t i_half = size >> 1;
	l_half_prev = cul_slist_nth(slist, i_half - 1);
	l_half = l_half_prev->next;
	l_half_prev->next = NULL;

	return _cul_slist_merge(
			_cul_slist_sort(slist, cmp_f, i_half),
			_cul_slist_sort(l_half, cmp_f, size - i_half),
			cmp_f);
}

CulSList *cul_slist_sort(CulSList *slist, cul_cmp_f *cmp_f) {
	if( slist == NULL )
		return NULL;

	return _cul_slist_sort(slist, cmp_f, cul_slist_size(slist));
}

size_t cul_slist_unique(CulSList *slist, cul_cmp_f *cmp_f, cul_free_f *free_f) {
	if( slist == NULL )
		return 0;

	size_t unique = 0;
	CulSList *l_last = slist, *next = slist->next;

	for(slist = next; slist != NULL; slist = next)
		if( cmp_f(l_last->data, slist->data) == 0 ) {
			/* item is not unique */
			next = slist->next;
			l_last->next = next;

			/* free item */
			if( free_f != NULL )
				free_f(slist->data);
			cul_slist_free_struct(slist);
		} else {
			/* item is unique */
			next = slist->next;
			l_last = slist;
			++unique;
		}

	return unique;
}

CulSList *cul_slist_find(CulSList *slist, cul_ptr data, cul_cmp_f *cmp_f) {
	if( cmp_f == NULL )
		for( ; slist != NULL; slist = slist->next)
			if( slist->data == data )
				return slist;
	else
		for( ; slist != NULL; slist = slist->next)
			if( !cmp_f(slist->data, data) )
				return slist;
	return NULL;
}

void cul_slist_each(CulSList *slist, cul_each_f *each_f) {
	for(CulSList *next; slist != NULL; slist = next) {
		next = slist->next;
		each_f(slist->data);
	}
}

void cul_slist_each_prv(CulSList *slist, cul_each_prv_f *each_prv_f, cul_ptr prv) {
	for(CulSList *next; slist != NULL; slist = next) {
		next = slist->next;
		each_prv_f(slist->data, prv);
	}
}

