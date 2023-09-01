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

void verlet_step1(Atoms &atoms, double timestep) {

    atoms.velocities.row(0) +=
        0.5 * atoms.forces.row(0) * timestep / atoms.masses.transpose();
    atoms.positions.row(0) += atoms.velocities.row(0) * timestep;

    atoms.velocities.row(1) +=
        0.5 * atoms.forces.row(1) * timestep / atoms.masses.transpose();
    atoms.positions.row(1) += atoms.velocities.row(1) * timestep;

    atoms.velocities.row(2) +=
        0.5 * atoms.forces.row(2) * timestep / atoms.masses.transpose();
    atoms.positions.row(2) += atoms.velocities.row(2) * timestep;
}

void verlet_step2(Atoms &atoms, double timestep) {

    atoms.velocities.row(0) +=
        0.5 * atoms.forces.row(0) * timestep / atoms.masses.transpose();

    atoms.velocities.row(1) +=
        0.5 * atoms.forces.row(1) * timestep / atoms.masses.transpose();

    atoms.velocities.row(2) +=
        0.5 * atoms.forces.row(2) * timestep / atoms.masses.transpose();
}
