#ifndef __CUL_PERMUTATION_H__
#define __CUL_PERMUTATION_H__

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>
#include <cul/cul_rng.h>

cul_bool cul_permutation_valid   (const CulUVector *this);

void     cul_permutation_identity(CulUVector *this);
void     cul_permutation_shuffle (CulUVector *this, const CulRng *rng);
void     cul_permutation_reverse (CulUVector *this);

#endif /* __CUL_PERMUTATION_H__ */
