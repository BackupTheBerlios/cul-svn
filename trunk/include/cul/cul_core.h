#ifndef __CUL_CORE_H__
#define __CUL_CORE_H__

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

#define CUL_PTR(ptr)    ((cul_ptr)ptr)

/* base callback functions */
typedef cul_bool cul_eq_f          (cul_const_ptr a, cul_const_ptr b);
typedef int      cul_cmp_f         (cul_const_ptr a, cul_const_ptr b);
typedef void     cul_free_f        (cul_ptr data);
typedef cul_ptr  cul_clone_f       (cul_const_ptr data);
typedef void     cul_cpy_f         (cul_ptr copy, cul_const_ptr data);
typedef cul_bool cul_each_f        (cul_ptr data);
typedef cul_bool cul_each_prv_f    (cul_ptr data, cul_ptr prv);
typedef cul_bool cul_each_key_f    (cul_ptr key, cul_ptr data);
typedef cul_bool cul_each_key_prv_f(cul_ptr key, cul_ptr data, cul_ptr prv);

/* base callback macro helpers */
#define CUL_EQ_F(ptr)           ((cul_eq_f *)(ptr))
#define CUL_CMP_F(ptr)          ((cul_cmp_f *)(ptr))
#define CUL_FREE_F(ptr)         ((cul_free_f *)(ptr))
#define CUL_CLONE_F(ptr)        ((cul_clone_f *)(ptr))
#define CUL_CPY_F(ptr)          ((cul_cpy_f *)(ptr))
#define CUL_EACH_F(ptr)         ((cul_each_f *)(ptr))
#define CUL_EACH_PRV_F(ptr)     ((cul_each_prv_f *)(ptr))
#define CUL_EACH_KEY_F(ptr)     ((cul_each_key_f *)(ptr))
#define CUL_EACH_KEY_PRV_F(ptr) ((cul_each_key_prv_f *)(ptr))

#endif /* __CUL_CORE_H__ */
