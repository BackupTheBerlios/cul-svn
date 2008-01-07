#ifndef __CUL_PPERMUTE_H__
#define __CUL_PPERMUTE_H__

#include <cul/cul_global.h>
#include <cul/cul_pvector.h>
#include <cul/cul_uvector.h>

cul_errno cul_pvector_permute    (CulPVector *this, const CulUVector *permutation);
cul_errno cul_pvectorview_permute(CulPVectorView *this, const CulUVector *permutation);

#endif /* __CUL_PPERMUTE_H__ */

