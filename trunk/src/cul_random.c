#include <cul/cul_random.h>

double cul_random_uniform(const CulRng *rng, double min, double max) {
	double val = cul_rng_get_real(rng);
	return min*(1.0-val) + max*val;
}
