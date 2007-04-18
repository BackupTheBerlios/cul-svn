#if !defined(CUL_MEM_H)
#define CUL_MEM_H

#include <cul/cul_global.h>

#define cul_slab_new_struct(type)       ((type *)cul_slab_new(sizeof(type)))
#define cul_slab_free_struct(type, ptr) (cul_slab_free(sizeof(type), ptr))

void *cul_slab_new(size_t size);
void cul_slab_free(size_t size, void *ptr);

#endif
