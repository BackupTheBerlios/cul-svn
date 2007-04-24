#ifndef CUL_BASE_GLOBAL_H
#define CUL_BASE_GLOBAL_H

#include <cul/cul_config.h>
#include <stddef.h>
#include <stdint.h>

#define CUL_TRUE   (_Bool)1
#define CUL_FALSE  (_Bool)0

/* basic types */

typedef unsigned long CulHash;
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
typedef cul_bool cul_foreach_data_f(cul_ptr data, cul_ptr user_data);

#define CUL_EQ_T(ptr)  ((cul_eq_f *)(ptr))
#define CUL_CMP_T(ptr) ((cul_cmp_f *)(ptr))

#define CUL_FREE_F(ptr) ((cul_free_f *)(ptr))
#define CUL_CPY_F(ptr)  ((cul_cpy_f *)(ptr))

#endif /* CUL_BASE_GLOBAL_H */
