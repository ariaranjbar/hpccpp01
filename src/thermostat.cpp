#include "thermostat.h"
#include "units.h"

void berendsen_thermostat(Atoms &atoms, double temperature, double timestep,
                          double relaxation_time) {
    const double lambda = sqrt(1 + ((temperature / atoms.temperature()) - 1) *
                                       (timestep / relaxation_time));
    atoms.velocities = atoms.velocities * lambda;
}