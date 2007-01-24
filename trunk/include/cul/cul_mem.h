#if !defined(CUL_MEM_H)
#define CUL_MEM_H

#include <stdlib.h>
#include <string.h>

static inline void *cul_malloc(size_t size) {
	return malloc(size);
}

static inline void *cul_realloc(void *ptr, size_t size) {
	return realloc(ptr, size);
}

static inline void cul_free(void *ptr) {
	free(ptr);
}

static inline void cul_free_null(void **ptr) {
	cul_free(*ptr);
	*ptr = NULL;
}

static inline void *cul_memset(void *data, int set, size_t size) {
	return memset(data, set, size);
}

static inline void *cul_memcpy(void *dest, const void *source, size_t size) {
	return memcpy(dest, source, size);
}

static inline void *cul_memmove(void *dest, const void *source, size_t size) {
	return memmove(dest, source, size);
}

static inline int cul_memcmp(const void *data, const void *cmp, size_t size) {
	return memcmp(data, cmp, size);
}

static inline void *cul_memchr(const void *data, int find, size_t size) {
	return memchr(data, find, size);
}

#define cul_slab_new_struct(type)       ((type *)cul_slab_new(sizeof(type)))
#define cul_slab_free_struct(type, ptr) (cul_slab_free(sizeof(type), ptr))

void *cul_slab_new(size_t size);
void cul_slab_free(size_t size, void *ptr);

#endif
