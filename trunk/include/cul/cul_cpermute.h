#ifndef __CUL_CPERMUTE_H__
#define __CUL_CPERMUTE_H__

#include <cul/cul_global.h>
#include <cul/cul_cvector.h>
#include <cul/cul_uvector.h>

cul_errno cul_cvector_permute    (CulCVector *this, const CulUVector *permutation);
cul_errno cul_cvectorview_permute(CulCVectorView *this, const CulUVector *permutation);

#endif /* __CUL_CPERMUTE_H__ */


