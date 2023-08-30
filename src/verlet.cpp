#include "verlet.h"
#include "units.h"

void verlet_step1(Positions_t &positions, Velocities_t &velocities,
                  const Forces_t &forces, double timestep) {

    velocities += 0.5 * forces * timestep / DEFAULT_MASS;
    positions += velocities * timestep;
}

void verlet_step2(Velocities_t &velocities, const Forces_t &forces,
                  double timestep) {

    velocities += 0.5 * forces * timestep / DEFAULT_MASS;
}
