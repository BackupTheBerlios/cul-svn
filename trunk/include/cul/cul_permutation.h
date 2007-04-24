#ifndef CUL_PERMUTATION_H
#define CUL_PERMUTATION_H

#include <cul/cul_global.h>
#include <cul/cul_uvector.h>
#include <cul/cul_rng.h>

cul_bool cul_permutation_valid(const CulUVector *p);

void cul_permutation_identity(CulUVector *p);
void cul_permutation_shuffle(CulUVector *p, const CulRng *rng);

void cul_permutation_reverse(CulUVector *p);

#endif /*CUL_PERMUTATION_H*/
