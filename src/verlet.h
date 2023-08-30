#ifndef VERLET_H
#define VERLET_H

#include "types.h"


void verlet_step1(Positions_t &positions, Velocities_t &velocities,
                  const Forces_t &forces, double timestep);
void verlet_step2(Velocities_t &velocities, const Forces_t &forces, double timestep);


#endif // VERLET_H
