#include <cul/cul_dlist.h>

struct _CulDList {
    CulDNode *first;   /* first node in the list */
    CulDNode *last;    /* last node in the list */
};

static inline CulDList *cul_dlist_struct_new()
{
    return cul_slab_new(sizeof(CulDList));
}

static inline void cul_dlist_struct_free(CulDList *list)
{
    cul_slab_free(sizeof(CulDList), list);
}

static inline void cul_dlist_struct_set(CulDList *list,
                                        CulDNode *first,
                                        CulDNode *last)
{
    list->first = first;
    list->last = last;
}

static inline void cul_dlist_struct_init(CulDList *list,
                                         CulDNode *first)
{
    if (first != NULL) {
        /* adjust first links */
        if (first->prev != NULL) {
            first->prev->next = NULL;
            first->prev = NULL;
        }

        cul_dlist_struct_set(list, first, cul_dnode_last(first));
    } else
        cul_dlist_struct_set(list, NULL, NULL);
}

static inline void cul_dlist_struct_init_empty(CulDList *list)
{
    cul_dlist_struct_set(list, NULL, NULL);
}

CulDList *cul_dlist_new(CulDNode *first)
{
    CulDList *list;

    if ((list = cul_dlist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_dlist_struct_init(list, first);

    return list;
}

CulDList *cul_dlist_new_empty()
{
    CulDList *list;

    if ((list = cul_dlist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_dlist_struct_init_empty(list);

    return list;
}

void cul_dlist_free(CulDList *list, cul_free_f *free_f)
{
    if (list != NULL) {
        cul_dnode_each_free(list->first, NULL, free_f);
        cul_dlist_struct_free(list);
    }
}

void cul_dlist_init(CulDList *list,
                    CulDNode *first)
{
    cul_dlist_struct_init(list, first);
}

void cul_dlist_init_empty(CulDList *list)
{
    cul_dlist_struct_init_empty(list);
}

CulDNode *cul_dlist_first(CulDList *list)
{
    return list->first;
}

CulDNode *cul_dlist_last(CulDList *list)
{
    return list->last;
}

CulDNode *cul_dlist_nth(CulDList *list, size_t n)
{
    return cul_dnode_nth(list->first, n);
}

size_t cul_dlist_size(CulDList *list)
{
    return cul_dnode_size(list->first, NULL);
}

cul_bool cul_dlist_valid(CulDList *list)
{
    CulDNode *prev, *node;

    /* check if list is empty */
    if (list->first == NULL && list->last == NULL)
        return CUL_TRUE;

    /* check presence of basic links */
    if ((list->first == NULL && list->last != NULL) ||
        (list->first != NULL && list->last == NULL))
        return CUL_FALSE;

    /* check basic links */
    if (list->first->prev != NULL ||
        list->last->next != NULL)
        return CUL_FALSE;

    /* scan other links */
    prev = list->first;
    node = list->first->next;
    for (; node != NULL; prev = node, node = node->next)
        if (node->prev != prev)
            return CUL_FALSE;

    /* check last link (should be last prev) */
    if (prev != list->last)
        return CUL_FALSE;

    /* list appears to be valid */
    return CUL_TRUE;
}

CulDNode *cul_dlist_insert(CulDList *list,
                           CulDNode *node,
                           cul_ptr data)
{
    if (node == list->first)
        return cul_dlist_push_front(list, data);
    else if (node == list->last)
        return cul_dlist_push_back(list, data);
    else
        return cul_dnode_insert_prev(node, data);
}

void cul_dlist_remove(CulDList *list,
                      CulDNode *node,
                      cul_free_f *free_f)
{
    if (node == list->first)
        cul_dlist_pop_front(list, free_f);
    else if (node == list->last)
        cul_dlist_pop_back(list, free_f);
    else
        cul_dnode_remove(node, free_f);
}

CulDNode *cul_dlist_push_front(CulDList *list,
                               cul_ptr data)
{
    CulDNode *first;

    if ((first = cul_dnode_insert_prev(data, list->first)) == NULL)
        return NULL;

    /* update list links */
    if (list->last == NULL)
        list->last = first;
    list->first = first;

    return first;
}

void cul_dlist_pop_front(CulDList *list,
                         cul_free_f *free_f)
{
    CulDNode *first = list->first;

    if (first != NULL) {
        /* adjust nodes */
        if (list->last == first) {
            list->first = NULL;
            list->last = NULL;
        } else {
            list->first = first->next;
            if (list->first != NULL)
                list->first->prev = NULL;
        }

        /* free node */
        cul_dnode_free(first, free_f);
    }
}

CulDNode *cul_dlist_push_back(CulDList *list,
                              cul_ptr data)
{
    CulDNode *last;

    if ((last = cul_dnode_insert_next(list->last, data)) == NULL)
        return NULL;

    /* update list links */
    if (list->first == NULL)
        list->first = last;
    list->last = last;

    return last;
}

void cul_dlist_pop_back(CulDList *list,
                        cul_free_f *free_f)
{
    CulDNode *last = list->last;

    if (last != NULL) {
        /* adjust nodes */
        if (list->first == last) {
            list->first = NULL;
            list->last = NULL;
        } else {
            list->last = last->prev;
            if (list->last != NULL)
                list->last->next = NULL;
        }

        /* remove node */
        cul_dnode_free(last, free_f);
    }
}

CulDList *cul_dlist_copy(CulDList *list)
{
    CulDNode *node = list->first, *n;
    CulDList *copy;

    if ((copy = cul_dlist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

    if (node != NULL) {
        /* copy first node */
        if ((n = cul_dnode_insert_next(NULL, node->data)) == NULL) {
            cul_dlist_struct_free(copy);
            return NULL;
        }

        /* set first node */
        copy->first = n;

        /* copy other nodes */
        for (node = node->next; node != NULL; node = node->next)
            if ((n = cul_dnode_insert_next(n, node->data)) == NULL) {
                cul_dnode_each_free(copy->first, NULL, NULL);
                cul_dlist_struct_free(copy);
               return NULL;
            }

        /* set last node */
        copy->last = n;
    } else
        cul_dlist_struct_init_empty(copy);

    return copy;
}

cul_bool cul_dlist_detach(CulDList *list,
                          cul_clone_f *clone_f)
{
    if (cul_dnode_detach(list->first, NULL, clone_f) == NULL) {
        /* when list is empty then detach returns NULL */
        if (list->first == NULL)
            return CUL_TRUE;
        return CUL_FALSE;
    } else
        return CUL_TRUE;
}

void cul_dlist_reverse(CulDList *list)
{
    CulDNode *swap;

    cul_dnode_reverse(list->first, NULL);
    CUL_SWAP(list->first, list->last, swap);
}

void cul_dlist_sort(CulDList *list,
                    cul_cmp_f *cmp_f)
{
    list->first = cul_dnode_sort(list->first, NULL, cmp_f);
    list->last = cul_dnode_last(list->first);
}

void cul_dlist_unique(CulDList *list,
                      cul_cmp_f *cmp_f,
                      cul_free_f *free_f)
{
    list->last = cul_dnode_unique(list->first, NULL, cmp_f, free_f);
}

CulDNode *cul_dlist_find(CulDList *list,
                         cul_cmp_f *cmp_f,
                         cul_ptr data)
{
    return cul_dnode_find(list->first, NULL, cmp_f, data);
}

void cul_dlist_each(CulDList *list,
                    cul_each_f *each_f)
{
    cul_dnode_each(list->first, NULL, each_f);
}

void cul_dlist_each_data(CulDList *list,
                         cul_each_data_f *each_f,
                         cul_ptr data)
{
    cul_dnode_each_data(list->first, NULL, each_f, data);
}

