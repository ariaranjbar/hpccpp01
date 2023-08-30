#ifndef LJ_DIRECT_SUMMATION
#define LJ_DIRECT_SUMMATION

#include "atoms.h"
#include "units.h"

double lj_direct_summation(Atoms &atoms, double epsilon = DEFAULT_EPSILON,
                           double sigma = DEFAULT_SIGMA);

#endif // __LJ_DIRECT_SUMMATION