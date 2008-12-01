#include <cul/cul_slist.h>

struct _CulSList {
    CulSNode *first;   /* first node in the list */
    CulSNode *last;    /* last node in the list */
};

static inline CulSList *cul_slist_struct_new()
{
    return cul_slab_new(sizeof(CulSList));
}

static inline void cul_slist_struct_free(CulSList *list)
{
    cul_slab_free(sizeof(CulSList), list);
}

static inline void cul_slist_struct_set(CulSList *list,
                                        CulSNode *first,
                                        CulSNode *last)
{
    list->first = first;
    list->last = last;
}

static inline void cul_slist_struct_init(CulSList *list,
                                         CulSNode *first)
{
    if (first != NULL)
        cul_slist_struct_set(list, first, cul_snode_last(first));
    else
        cul_slist_struct_set(list, NULL, NULL);
}

static inline void cul_slist_struct_init_empty(CulSList *list)
{
    cul_slist_struct_set(list, NULL, NULL);
}

CulSList *cul_slist_new(CulSNode *first)
{
    CulSList *list;

    if ((list = cul_slist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_slist_struct_init(list, first);

    return list;
}

CulSList *cul_slist_new_empty()
{
    CulSList *list;

    if ((list = cul_slist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_slist_struct_init_empty(list);

    return list;
}

void cul_slist_free(CulSList *list, cul_free_f *free_f)
{
    if (list != NULL) {
        cul_snode_each_free(list->first, NULL, free_f);
        cul_slist_struct_free(list);
    }
}

void cul_slist_init(CulSList *list,
                    CulSNode *first)
{
    cul_slist_struct_init(list, first);
}

void cul_slist_init_empty(CulSList *list)
{
    cul_slist_struct_init_empty(list);
}

CulSNode *cul_slist_first(CulSList *list)
{
    return list->first;
}

CulSNode *cul_slist_last(CulSList *list)
{
    return list->last;
}

CulSNode *cul_slist_nth(CulSList *list, size_t n)
{
    return cul_snode_nth(list->first, n);
}

size_t cul_slist_size(CulSList *list)
{
    return cul_snode_size(list->first, NULL);
}

cul_bool cul_slist_valid(CulSList *list)
{
    CulSNode *prev, *node;

    /* check if list is empty */
    if (list->first == NULL && list->last == NULL)
        return CUL_TRUE;

    /* check presence of basic links */
    if ((list->first == NULL && list->last != NULL) ||
        (list->first != NULL && list->last == NULL))
        return CUL_FALSE;

    /* check basic links */
    if (list->last->next != NULL)
        return CUL_FALSE;

    /* scan other links */
    prev = list->first;
    node = list->first->next;
    for (; node != NULL; prev = node, node = node->next)
        ;

    /* check last link (should be last prev) */
    if (prev != list->last)
        return CUL_FALSE;

    /* list appears to be valid */
    return CUL_TRUE;
}

CulSNode *cul_slist_insert(CulSList *list,
                           CulSNode *node,
                           cul_ptr data)
{
    if (node == list->first)
        return cul_slist_push_front(list, data);
}

CulSNode *cul_slist_insert_next(CulSList *list,
                                CulSNode *node,
                                cul_ptr data)
{
    if (node == list->last)
        return cul_slist_push_back(list, data);
    else
        return cul_snode_insert_next(node, data);
}

void cul_slist_remove(CulSList *list,
                      CulSNode *node,
                      cul_free_f *free_f)
{
    CulSNode *prev, *rm;

    if (list->first == node)
        cul_slist_pop_front(list, free_f);
    else if (list->last == node)
        cul_slist_pop_back(list, free_f);
    else if (node != NULL) {
        /* extract previous node */
        for (rm = list->first; rm != node; rm = rm->next)
            prev = rm;

        prev->next = node->next;
        cul_snode_free(node, free_f);
    }
}

void cul_slist_remove_next(CulSList *list,
                           CulSNode *node,
                           cul_free_f *free_f)
{
    CulSNode *rm;

    if (node != NULL) {
        if ((rm = node->next) == NULL)
            return;

        /* update last node if needed */
        if (list->last == rm) {
            list->last = node;
            list->last->next = NULL;
        } else
            node->next = rm->next;

        cul_snode_free(rm, free_f);
    }
}

CulSNode *cul_slist_push_front(CulSList *list,
                               cul_ptr data)
{
    CulSNode *first;

    if ((first = cul_snode_insert_prev(list->first, data)) == NULL)
        return NULL;

    /* update list links */
    if (list->last == NULL)
        list->last = first;
    list->first = first;

    return first;
}

void cul_slist_pop_front(CulSList *list,
                         cul_free_f *free_f)
{
    CulSNode *first = list->first;

    if (first != NULL) {
        /* adjust nodes */
        if (list->last == first) {
            list->first = NULL;
            list->last = NULL;
        } else
            list->first = first->next;

        /* free node */
        cul_snode_free(first, free_f);
    }
}

CulSNode *cul_slist_push_back(CulSList *list,
                              cul_ptr data)
{
    CulSNode *last;

    if ((last = cul_snode_insert_next(list->last, data)) == NULL)
        return NULL;

    /* update list links */
    if (list->first == NULL)
        list->first = last;
    list->last = last;

    return last;
}

void cul_slist_pop_back(CulSList *list,
                        cul_free_f *free_f)
{
    CulSNode *prev, *rm;
    CulSNode *last = list->last;

    if (last != NULL) {
        /* adjust nodes */
        if (list->first == last) {
            list->first = NULL;
            list->last = NULL;
        } else {
            /* extract previous node */
            for (rm = list->first; rm != last; rm = rm->next)
                prev = rm;

            list->last = prev;
            prev->next = NULL;
        }

        /* remove node */
        cul_snode_free(last, free_f);
    }
}

CulSList *cul_slist_copy(CulSList *list)
{
    CulSNode *node = list->first, *n;
    CulSList *copy;

    if ((copy = cul_slist_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

    if (node != NULL) {
        /* copy first node */
        if ((n = cul_snode_insert_next(NULL, node->data)) == NULL) {
            cul_slist_struct_free(copy);
            return NULL;
        }

        /* set first node */
        copy->first = n;

        /* copy other nodes */
        for (node = node->next; node != NULL; node = node->next)
            if ((n = cul_snode_insert_next(n, node->data)) == NULL) {
                cul_snode_each_free(copy->first, NULL, NULL);
                cul_slist_struct_free(copy);
                return NULL;
            }

        /* set last node */
        copy->last = n;
    } else
        cul_slist_struct_init_empty(copy);

    return copy;
}

cul_bool cul_slist_detach(CulSList *list,
                          cul_clone_f *clone_f)
{
    if (cul_snode_detach(list->first, NULL, clone_f) == NULL) {
        /* when list is empty then detach returns NULL */
        if (list->first == NULL)
            return CUL_TRUE;
        return CUL_FALSE;
    } else
        return CUL_TRUE;
}

void cul_slist_reverse(CulSList *list)
{
    CulSNode *swap;

    cul_snode_reverse(list->first, NULL);
    CUL_SWAP(list->first, list->last, swap);
}

void cul_slist_sort(CulSList *list,
                    cul_cmp_f *cmp_f)
{
    list->first = cul_snode_sort(list->first, NULL, cmp_f);
    list->last = cul_snode_last(list->first);
}

void cul_slist_unique(CulSList *list,
                      cul_cmp_f *cmp_f,
                      cul_free_f *free_f)
{
    list->last = cul_snode_unique(list->first, NULL, cmp_f, free_f);
}

CulSNode *cul_slist_find(CulSList *list,
                         cul_cmp_f *cmp_f,
                         cul_ptr data)
{
    return cul_snode_find(list->first, NULL, cmp_f, data);
}

void cul_slist_each(CulSList *list,
                    cul_each_f *each_f)
{
    cul_snode_each(list->first, NULL, each_f);
}

void cul_slist_each_data(CulSList *list,
                         cul_each_data_f *each_f,
                         cul_ptr data)
{
    cul_snode_each_data(list->first, NULL, each_f, data);
}

