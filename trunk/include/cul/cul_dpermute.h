#ifndef __CUL_DPERMUTE_H__
#define __CUL_DPERMUTE_H__

#include <cul/cul_global.h>
#include <cul/cul_dvector.h>
#include <cul/cul_uvector.h>

cul_errno cul_dvector_permute    (CulDVector *this, const CulUVector *permutation);
cul_errno cul_dvectorview_permute(CulDVectorView *this, const CulUVector *permutation);

#endif /* __CUL_DPERMUTE_H__ */


