#include <cul/cul_mem.h>
#include <stdlib.h>

typedef struct _CulSlabMagazine CulSlabMagazine;
typedef struct _CulSlabShelf CulSlabShelf;

struct _CulSlabShelf {
	void *cache;
	size_t level;
};

struct _CulSlabMagazine {
};

void *cul_slab_new(size_t size) {
	return malloc(size);
}

void cul_slab_free(size_t size, void *ptr) {
	CUL_UNUSED(size);
	free(ptr);
}
