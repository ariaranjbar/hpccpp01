#ifndef LJ_DIRECT_SUMMATION
#define LJ_DIRECT_SUMMATION

#include "atoms.h"
#include "neighbors.h"
#include "units.h"

double lj_neighbors(Atoms &atoms, NeighborList &neighbor_list, double cutoff,
                    double epsilon = DEFAULT_EPSILON,
                    double sigma = DEFAULT_SIGMA);

#endif // __LJ_DIRECT_SUMMATION