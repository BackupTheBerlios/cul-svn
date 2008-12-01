#include <cul/cul_snode.h>

static inline CulSNode *cul_snode_struct_new()
{
    return cul_slab_new(sizeof(CulSNode));
}

static inline void cul_snode_struct_free(CulSNode *node)
{
    cul_slab_free(sizeof(CulSNode), node);
}

static inline void cul_snode_struct_set(CulSNode *node,
                                        cul_ptr data,
                                        CulSNode *next)
{
    node->data = data;
    node->next = next;
}

static inline void cul_snode_struct_init(CulSNode *node,
                                         cul_ptr data)
{
    cul_snode_struct_set(node, data, NULL);
}

static inline void cul_snode_struct_init_empty(CulSNode *node)
{
    cul_snode_struct_set(node, NULL, NULL);
}

CulSNode *cul_snode_new(cul_ptr data)
{
    CulSNode *node;

    if ((node = cul_snode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_snode_struct_init(node, data);

    return node;
}

CulSNode *cul_snode_new_empty()
{
    CulSNode *node;

    if ((node = cul_snode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_snode_struct_init_empty(node);

    return node;
}

void cul_snode_free(CulSNode *node,
                    cul_free_f *free_f)
{
    if (node != NULL) {
        if (free_f != NULL)
            free_f(node->data);
        cul_snode_struct_free(node);
    }
}

void cul_snode_init(CulSNode *node,
                    cul_ptr data)
{
    cul_snode_struct_init(node, data);
}

void cul_snode_init_empty(CulSNode *node)
{
    cul_snode_struct_init_empty(node);
}

CulSNode *cul_snode_last(CulSNode *node)
{
    if (node != NULL)
        while (node->next != NULL)
            node = node->next;

    return node;
}

CulSNode *cul_snode_nth(CulSNode *node,
                        size_t n)
{
    while (node != NULL && n--)
        node = node->next;

    return node;
}

size_t cul_snode_size(CulSNode *node,
                      CulSNode *end)
{
    size_t size;

    for (size = 0; node != end; node = node->next)
        ++size;

    return size;
}

CulSNode *cul_snode_insert_next(CulSNode *node,
                                cul_ptr data)
{
    CulSNode *insert;

    if ((insert = cul_snode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

    if (node != NULL) {
        cul_snode_struct_set(insert, data, node->next);
        node->next = insert;
    } else
        cul_snode_struct_set(insert, data, NULL);

    return insert;
}

CulSNode *cul_snode_insert_prev(CulSNode *node,
                                cul_ptr data)
{
    CulSNode *insert;

    if ((insert = cul_snode_struct_new()) == NULL)
        CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
    cul_snode_struct_set(insert, data, node);

    return insert;
}

CulSNode *cul_snode_remove(CulSNode *node,
                           cul_free_f *free_f)
{
    CulSNode *next;

    if (node != NULL) {
        next = node->next;
        cul_snode_free(node, free_f);

        /* return next node */
        return next;
    } else
        return NULL;
}

CulSNode *cul_snode_copy(CulSNode *node,
                         CulSNode *end)
{
    CulSNode *first, *copy;

    if (node != end) {
        /* copy first node */
        if ((first = cul_snode_insert_next(NULL, node->data)) == NULL)
            CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);

        /* copy other nodes */
        for (copy = first, node = node->next; node != end; node = node->next)
            if ((copy = cul_snode_insert_next(copy, node->data)) == NULL) {
                cul_snode_each_free(first, NULL, NULL);
                CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
            }

        return first;
    } else
        return NULL;
}

CulSNode *cul_snode_detach(CulSNode *node,
                           CulSNode *end,
                           cul_clone_f *clone_f)
{
    CulSNode *first;

    for (first = node; node != end; node = node->next)
        if ((node->data = clone_f(node->data)) == NULL) {
            /* clear rest of undetached pointers */
            for (node = node->next; node != end; node = node->next)
                node->data = NULL;
            CUL_ERROR_ERRNO_RET(NULL, CUL_ENOMEM);
        }

    return first;
}

CulSNode *cul_snode_reverse(CulSNode *node,
                            CulSNode *end)
{
    CulSNode *first, *last, *next;

    /* check if we have more than one node */
    if (node == NULL || node->next == end)
        return node;

    /* remember last node */
    first = last = node;
    node = node->next;

    /* swap nodes */
    next = node->next;
    node->next = first;

    /* move to next node */
    first = node;
    node = next;

    while (node != end) {
        /* swap node */
        next = node->next;
        node->next = first;

        /* move to next node */
        first = node;
        node = next;
    }

    /* process last node */
    last->next = node;

    return first;
}

static CulSNode *_cul_snode_merge(CulSNode *n1,
                                  CulSNode *n2,
                                  cul_cmp_f *cmp_f)
{
    CulSNode *node, *head;

    /* initialise result (head of return list) */
    if (cmp_f(n1->data, n2->data) <= 0) {
        head = n1;
        n1 = n1->next;
    } else {
        head = n2;
        n2 = n2->next;
    }

    /* initialize processing */
    node = head;

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
    }

    /* merge last item */
    node->next = n1 != NULL ? n1 : n2;

    return head;
}

static CulSNode *_cul_snode_sort(CulSNode *node,
                                 cul_cmp_f *cmp_f,
                                 size_t size)
{
    CulSNode *half, *half_prev;

    if (size == 1)
        return node;

    const size_t i_half = size >> 1;
    half_prev = cul_snode_nth(node, i_half - 1);
    half = half_prev->next;
    half_prev->next = NULL;

    return _cul_snode_merge(_cul_snode_sort(node, cmp_f, i_half),
                            _cul_snode_sort(half, cmp_f, size - i_half),
                            cmp_f);
}

CulSNode *cul_snode_sort(CulSNode *node,
                         CulSNode *end,
                         cul_cmp_f *cmp_f)
{
    const size_t size = cul_snode_size(node, end);
    return _cul_snode_sort(node, cmp_f, size);
}

CulSNode *cul_snode_unique(CulSNode *node,
                           CulSNode *end,
                           cul_cmp_f *cmp_f,
                           cul_free_f *free_f)
{
    CulSNode *last, *next;

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

                if (free_f != NULL)
                    free_f(node->data);
                cul_snode_struct_free(node);
            } else
                last = node;
        }
    } else {
        for (node = next; node != end; node = next) {
            next = node->next;

            /* check if item is unique */
            if (!cmp_f(last->data, node->data)) {
                last->next = next;

                if (free_f != NULL)
                    free_f(node->data);
                cul_snode_struct_free(node);
            } else
                last = node;
        }
    }

    return last;
}

CulSNode *cul_snode_find(CulSNode *node,
                         CulSNode *end,
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

void cul_snode_each(CulSNode *node,
                    CulSNode *end,
                    cul_each_f *each_f)
{
    for (; node != end; node = node->next)
        each_f(node->data);
}

void cul_snode_each_data(CulSNode *node,
                         CulSNode *end,
                         cul_each_data_f *each_f,
                         cul_ptr data)
{
    for (; node != end; node = node->next)
        each_f(node->data, data);
}

void cul_snode_each_free(CulSNode *node,
                         CulSNode *end,
                         cul_free_f *free_f)
{
    for (CulSNode *next = node; node != end; node = next) {
        next = node->next;
        if (free_f != NULL)
            free_f(node->data);
        cul_snode_struct_free(node);
    }
}

