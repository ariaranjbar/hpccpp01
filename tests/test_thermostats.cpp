
#include <gtest/gtest.h>

#include "atoms.h"
#include "lj_direct_summation.h"
#include "thermostat.h"
#include "verlet.h"

TEST(ThermostatTest, Temprature) {
    constexpr int lattice_size = 5;
    constexpr double lattice_spacing = 1.2;
    Atoms atoms(lattice_size, lattice_spacing, 0.0);
    std::cout << std::setprecision(10) << std::setw(20) << "time"
              << std::setw(20) << "avg_temprature" << std::endl;

    double temp_cache = 0;
    unsigned int num_measured = 0;
    bool discard = true;
    for (int i = 0;
         i < static_cast<int>((DEFAULT_SIM_TIME * 5 / DEFAULT_TIMESTEP)); i++) {
        verlet_step1(atoms.positions, atoms.velocities, atoms.forces,
                     DEFAULT_TIMESTEP);
        lj_direct_summation(atoms);
        verlet_step2(atoms.velocities, atoms.forces, DEFAULT_TIMESTEP);
        berendsen_thermostat(atoms, DEFAULT_TEMP, DEFAULT_TIMESTEP,
                             DEFAULT_TAU * 2);
        temp_cache += atoms.temprature();
        num_measured++;
        if (i % static_cast<int>(
                    (DEFAULT_FRAME_TIME * 500 / DEFAULT_TIMESTEP)) ==
            0) {
            if (discard) {
                discard = false;
                temp_cache = 0;
                num_measured = 0;
                continue;
            }
            std::cout << std::setw(20) << std::fixed
                      << std::min(DEFAULT_TIMESTEP * i, 99999999.0)
                      << std::setw(20) << std::fixed
                      << std::min(temp_cache / num_measured, 99999999.0)
                      << std::endl;
            temp_cache = 0;
            num_measured = 0;
        }
    };
}