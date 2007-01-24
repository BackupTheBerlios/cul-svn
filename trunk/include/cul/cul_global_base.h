#if !defined(CUL_GLOBAL_BASE_H)
#define CUL_GLOBAL_BASE_H

#include <cul/cul_config.h>
#include <stddef.h>
#include <stdint.h>

#define CUL_TRUE   (_Bool)1
#define CUL_FALSE  (_Bool)0

/* basic types */

typedef unsigned int CulHash;
typedef void* CulPtr;
typedef _Bool CulBool;

/* type mappings */

typedef CulPtr  cul_ptr;
typedef CulBool cul_bool;
typedef CulHash cul_hash;

/* base callback functions */

typedef cul_bool cul_eq_f(const void *a, const void *b);
typedef int cul_cmp_f(const void *a, const void *b);

typedef void cul_free_f(cul_ptr data);
typedef void *cul_cpy_f(const cul_ptr data);

typedef cul_bool cul_foreach_f(cul_ptr data);
typedef cul_bool cul_foreach_key_f(cul_ptr key, cul_ptr data);
typedef cul_bool cul_foreach_hash_f(cul_hash hash, cul_ptr data);

#define CUL_EQ_T(ptr)  ((cul_eq_f *)(ptr))
#define CUL_CMP_T(ptr) ((cul_cmp_f *)(ptr))

#define CUL_FREE_ITEM_T(ptr) ((cul_free_f *)(ptr))
#define CUL_CPY_ITEM_T(ptr)  ((cul_cpy_f *)(ptr))

#endif
