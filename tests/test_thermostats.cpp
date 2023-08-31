
#include <gtest/gtest.h>

#include "atoms.h"
#include "lj_direct_summation.h"
#include "thermostat.h"
#include "verlet.h"

TEST(ThermostatTest, Temprature) {
    constexpr double target_temp = 100;
    constexpr int lattice_size = 4;
    constexpr double lattice_spacing = 1;
    Atoms atoms(lattice_size, lattice_spacing);
    std::cout << std::setprecision(10) << std::setw(20) << "time"
              << std::setw(20) << "current_dist" << std::setw(20) << "last_dist"
              << std::endl;

    // if not within 15 Kelvin of the thermostat temprature, make sure it is
    // steadily approching it.
    double last_average = 0;

    double temp_cache = 0;
    unsigned int num_measured = 0;
    unsigned int discard = 2;
    for (int i = 0;
         i < static_cast<int>((DEFAULT_SIM_TIME * 2 / DEFAULT_TIMESTEP)); i++) {
        verlet_step1(atoms.positions, atoms.velocities, atoms.forces,
                     DEFAULT_TIMESTEP);
        lj_direct_summation(atoms);
        verlet_step2(atoms.velocities, atoms.forces, DEFAULT_TIMESTEP);
        berendsen_thermostat(atoms, target_temp, DEFAULT_TIMESTEP, DEFAULT_TAU);
        temp_cache += atoms.temprature();
        num_measured++;
        if (i % static_cast<int>(
                    (DEFAULT_FRAME_TIME * 100 / DEFAULT_TIMESTEP)) ==
            0) {
            if (discard) {
                discard--;
                last_average = temp_cache / num_measured;
                temp_cache = 0;
                num_measured = 0;
                continue;
            }
            double current_average = temp_cache / num_measured;
            double current_distance = std::abs(current_average - target_temp);
            double last_distance = std::abs(last_average - target_temp);
            std::cout << std::setw(20) << std::fixed
                      << std::min(DEFAULT_TIMESTEP * i, 99999999.0)
                      << std::setw(20) << std::fixed
                      << std::min(current_distance, 99999999.0) << std::setw(20)
                      << std::fixed << std::min(last_distance, 99999999.0)
                      << std::endl;
            ASSERT_TRUE((current_distance < last_distance) ||
                        (current_distance < 15));
            last_average = current_average;
            temp_cache = 0;
            num_measured = 0;
        }
    };
}