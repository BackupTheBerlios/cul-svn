#include <cul/cul_dnode.h>

static inline CulDNode *cul_dnode_struct_new()
{
    return cul_slab_new(sizeof(CulDNode));
}

static inline void cul_dnode_struct_free(CulDNode *node)
{
    cul_slab_free(sizeof(CulDNode), node);
}

static inline void cul_dnode_struct_set(CulDNode *node,
                                        cul_ptr data,
                                        CulDNode *next,
                                        CulDNode *prev)
{
    node->data = data;
    node->next = next;
    node->prev = prev;
}

static inline void cul_dnode_struct_init(CulDNode *node,
                                         cul_ptr data)
{
    cul_dnode_struct_set(node, data, NULL, NULL);
}

static inline void cul_dnode_struct_init_empty(CulDNode *node)
{
    cul_dnode_struct_set(node, NULL, NULL, NULL);
}


CulDNode *cul_dnode_new(cul_ptr data)
{
    CulDNode *node;

    if ((node = cul_dnode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_dnode_struct_init(node, data);

    return node;
}

CulDNode *cul_dnode_new_empty()
{
    CulDNode *node;

    if ((node = cul_dnode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_dnode_struct_init_empty(node);

    return node;
}

void cul_dnode_free(CulDNode *node,
                    cul_free_f *free_f)
{
    if (node != NULL) {
        if (free_f != NULL)
            free_f(node->data);
        cul_dnode_struct_free(node);
    }
}

void cul_dnode_init(CulDNode *node,
                    cul_ptr data)
{
    cul_dnode_struct_init(node, data);
}

void cul_dnode_init_empty(CulDNode *node)
{
    cul_dnode_struct_init_empty(node);
}

CulDNode *cul_dnode_first(CulDNode *node)
{
    if (node != NULL)
        while (node->prev != NULL)
            node = node->prev;

    return node;
}

CulDNode *cul_dnode_last(CulDNode *node)
{
    if (node != NULL)
        while (node->next != NULL)
            node = node->next;

    return node;
}

CulDNode *cul_dnode_nth(CulDNode *node,
                        size_t n)
{
    while (node != NULL && n--)
        node = node->next;

    return node;
}

size_t cul_dnode_size(CulDNode *node,
                      CulDNode *end)
{
    size_t size;

    for (size = 0; node != end; node = node->next)
        ++size;

    return size;
}

CulDNode *cul_dnode_insert_next(CulDNode *node,
                                cul_ptr data)
{
    CulDNode *insert, *next;

    if ((insert = cul_dnode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

    if (node != NULL) {
        next = node->next;

        /* adjust node pointers */
        if (next != NULL)
            next->prev = insert;
        node->next = insert;

        cul_dnode_struct_set(insert, data, next, node);
    } else
        cul_dnode_struct_set(insert, data, NULL, NULL);

    return insert;
}

CulDNode *cul_dnode_insert_prev(CulDNode *node,
                                cul_ptr data)
{
    CulDNode *insert, *prev;

    if ((insert = cul_dnode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

    if (node != NULL) {
        prev = node->prev;

        /* adjust list pointers */
        if (prev != NULL)
            prev->next = insert;
        node->prev = insert;

        cul_dnode_struct_set(insert, data, node, prev);
    } else
        cul_dnode_struct_set(insert, data, NULL, NULL);

    return insert;
}

CulDNode *cul_dnode_remove(CulDNode *node,
                           cul_free_f *free_f)
{
    CulDNode *next_prev = NULL;

    if (node != NULL) {
        /* adjust prev pointer */
        if (node->prev != NULL) {
            next_prev = node->prev;
            next_prev->next = node->next;
        }

        /* adjust next pointer */
        if (node->next != NULL) {
            next_prev = node->next;
            next_prev->prev = node->prev;
        }

        cul_dnode_free(node, free_f);

        /* next node is preferred */
        return next_prev;
    } else
        return NULL;
}

CulDNode *cul_dnode_copy(CulDNode *node,
                         CulDNode *end)
{
    CulDNode *first, *copy;

    if (node != end) {
        /* copy first node */
        if ((first = cul_dnode_insert_next(NULL, node->data)) == NULL)
            CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

        /* copy other nodes */
        for (copy = first, node = node->next; node != end; node = node->next)
            if ((copy = cul_dnode_insert_next(copy, node->data)) == NULL) {
                cul_dnode_each_free(first, NULL, NULL);
                CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
            }

        return first;
    } else
        return NULL;
}

CulDNode *cul_dnode_detach(CulDNode *node,
                           CulDNode *end,
                           cul_clone_f *clone_f)
{
    CulDNode *first;

    for (first = node; node != end; node = node->next)
        if ((node->data = clone_f(node->data)) == NULL) {
            /* clear rest of undetached pointers */
            for (node = node->next; node != end; node = node->next)
                node->data = NULL;
            CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
        }

    return first;
}

CulDNode *cul_dnode_reverse(CulDNode *node,
                            CulDNode *end)
{
    CulDNode *first, *last;

    /* check if we have more than one node */
    if (node == end || node->next == end)
        return node;

    /* remember last node */
    last = node;

    /* process next node */
    first = node = node->next;

    /* swap nodes */
    node = node->next;
    first->next = first->prev;
    first->prev = node;

    /* process next nodes */
    while (node != end) {
        /* remember last node */
        first = node;

        /* swap nodes */
        node = node->next;
        first->next = first->prev;
        first->prev = node;
    }

    /* process last node, adjust first */
    first->prev = last->prev;
    last->prev = last->next;
    last->next = node;

    return first;
}

static CulDNode *_cul_dnode_merge(CulDNode *n1,
                                  CulDNode *n2,
                                  cul_cmp_f *cmp_f)
{
    CulDNode *prev, *node, *head;

    /* initialise result (head of return list) */
    if (cmp_f(n1->data, n2->data) <= 0) {
        head = n1;
        n1 = n1->next;
    } else {
        head = n2;
        n2 = n2->next;
    }
    head->prev = NULL;

    /* initialize processing */
    prev = node = head;

    /* process rest */
    while (n1 != NULL && n2 != NULL) {
        if (cmp_f(n1->data, n2->data) <= 0) {
            node->next = n1;
            n1 = n1->next;
        } else {
            node->next = n2;
            n2 = n2->next;
        }
        node = node->next;
        node->prev = prev;
        prev = node;
    }

    /* merge last item */
    node->next = n1 != NULL ? n1 : n2;
    node->next->prev = node;

    return head;
}

static CulDNode *_cul_dnode_sort(CulDNode *node,
                                 cul_cmp_f *cmp_f,
                                 size_t size)
{
    CulDNode *half;

    if (size == 1)
        return node;

    const size_t i_half = size >> 1;
    half = cul_dnode_nth(node, i_half);
    half->prev->next = NULL;

    return _cul_dnode_merge(_cul_dnode_sort(node, cmp_f, i_half),
                            _cul_dnode_sort(half, cmp_f, size - i_half),
                            cmp_f);
}

CulDNode *cul_dnode_sort(CulDNode *node,
                         CulDNode *end,
                         cul_cmp_f *cmp_f)
{
    const size_t size = cul_dnode_size(node, end);
    return _cul_dnode_sort(node, cmp_f, size);
}

CulDNode *cul_dnode_unique(CulDNode *node,
                           CulDNode *end,
                           cul_cmp_f *cmp_f,
                           cul_free_f *free_f)
{
    CulDNode *last, *next;

    if (node == end)
        return 0;

    last = node;
    next = node->next;

    if (cmp_f == NULL) {
        for (node = next; node != end; node = next) {
            next = node->next;

            /* check if item is unique */
            if (last->data == node->data) {
                last->next = next;
                if (next != NULL) next->prev = last;

                if (free_f != NULL)
                    free_f(node->data);
                cul_dnode_struct_free(node);
            } else
                last = node;
        }
    } else {
        for (node = next; node != end; node = next) {
            next = node->next;

            /* check if item is unique */
            if (!cmp_f(last->data, node->data)) {
                last->next = next;
                if (next != NULL) next->prev = last;

                if (free_f != NULL)
                    free_f(node->data);
                cul_dnode_struct_free(node);
            } else
                last = node;
        }
    }

    return last;
}

CulDNode *cul_dnode_find(CulDNode *node,
                         CulDNode *end,
                         cul_cmp_f *cmp_f,
                         cul_ptr data)
{
    if (cmp_f == NULL) {
        for (; node != end; node = node->next)
            if (node->data == data)
                return node;
    } else {
        for (; node != end; node = node->next)
            if (!cmp_f(node->data, data))
                return node;
    }
}

void cul_dnode_each(CulDNode *node,
                    CulDNode *end,
                    cul_each_f *each_f)
{
    for (; node != end; node = node->next)
        each_f(node->data);
}

void cul_dnode_each_data(CulDNode *node,
                         CulDNode *end,
                         cul_each_data_f *each_f,
                         cul_ptr data)
{
    for (; node != end; node = node->next)
        each_f(node->data, data);
}

void cul_dnode_each_free(CulDNode *node,
                         CulDNode *end,
                         cul_free_f *free_f)
{
    for (CulDNode *next = node; node != end; node = next) {
        next = node->next;
        if (free_f != NULL)
            free_f(node->data);
        cul_dnode_struct_free(node);
    }
}

