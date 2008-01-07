#ifndef __CUL_IPERMUTE_H__
#define __CUL_IPERMUTE_H__

#include <cul/cul_global.h>
#include <cul/cul_ivector.h>
#include <cul/cul_uvector.h>

cul_errno cul_ivector_permute    (CulIVector *this, const CulUVector *permutation);
cul_errno cul_ivectorview_permute(CulIVectorView *this, const CulUVector *permutation);

#endif /* __CUL_IPERMUTE_H__ */


