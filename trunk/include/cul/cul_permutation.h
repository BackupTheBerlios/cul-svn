#ifndef __CUL_PERMUTATION_H__
#define __CUL_PERMUTATION_H__

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>
#include <cul/cul_rng.h>

cul_bool cul_permutation_valid       (const CulUVector *this);
cul_bool cul_permutationview_valid   (const CulUVectorView *this);

void     cul_permutation_identity    (CulUVector *this);
void     cul_permutation_shuffle     (CulUVector *this, const CulRng *rng);
void     cul_permutation_reverse     (CulUVector *this);
void     cul_permutationview_identity(CulUVectorView *this);
void     cul_permutationview_shuffle (CulUVectorView *this, const CulRng *rng);
void     cul_permutationview_reverse (CulUVectorView *this);

#endif /* __CUL_PERMUTATION_H__ */
