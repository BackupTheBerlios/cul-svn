#ifndef __CUL_UPERMUTE_H__
#define __CUL_UPERMUTE_H__

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>

cul_errno cul_uvector_permute    (CulUVector *this, const CulUVector *permutation);
cul_errno cul_uvectorview_permute(CulUVectorView *this, const CulUVector *permutation);

#endif /* __CUL_UPERMUTE_H__ */


