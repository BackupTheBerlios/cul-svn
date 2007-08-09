#ifndef CUL_BASE_GLOBAL_H
#define CUL_BASE_GLOBAL_H

#include <cul/cul_config.h>
#include <stddef.h>
#include <stdint.h>

#define CUL_TRUE   (_Bool)1
#define CUL_FALSE  (_Bool)0

/* basic types */

typedef _Bool         CulBool;
typedef void         *CulPtr;
typedef const void   *CulConstPtr;
typedef unsigned long CulHash;

/* type mappings */

typedef CulBool     cul_bool;
typedef CulPtr      cul_ptr;
typedef CulConstPtr cul_const_ptr;
typedef CulHash     cul_hash;

/* base callback functions */

typedef int     cul_cmp_f    (cul_const_ptr a, cul_const_ptr b);
typedef void    cul_free_f   (cul_ptr data);
typedef cul_ptr cul_cpy_f    (cul_const_ptr data);
typedef void    cul_foreach_f(cul_ptr data, cul_ptr user_data);

#define CUL_CMP_F(ptr)     ((cul_cmp_f *)(ptr))
#define CUL_FREE_F(ptr)    ((cul_free_f *)(ptr))
#define CUL_CPY_F(ptr)     ((cul_cpy_f *)(ptr))
#define CUL_FOREACH_F(ptr) ((cul_foreach_f *)(ptr))

#endif /* CUL_BASE_GLOBAL_H */
