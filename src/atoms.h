#ifndef ATOMS_H
#define ATOMS_H

#include "types.h"
#include "units.h"

using Positions_t = Eigen::Array3Xd;
using Velocities_t = Eigen::Array3Xd;
using Forces_t = Eigen::Array3Xd;

class Atoms {
  public:
    Positions_t positions;
    Velocities_t velocities;
    Forces_t forces;

    Atoms() {
    }

    Atoms(const Positions_t &p)
        : positions{p},
          velocities{3, p.cols()},
          forces{3, p.cols()} {
        velocities.setZero();
        forces.setZero();
    }

    Atoms(const Positions_t &p, const Velocities_t &v)
        : positions{p},
          velocities{v},
          forces{3, p.cols()} {
        assert(p.cols() == v.cols());
        forces.setZero();
    }

    Atoms(const int nb_atoms)
        : positions{3, nb_atoms},
          velocities{3, nb_atoms},
          forces{3, nb_atoms} {
        positions.setZero();
        velocities.setZero();
        forces.setZero();
    }

    Atoms(const unsigned int lattice_size, const double lattice_spacing,
          const double initial_velocity_multiplier = 0.25)
        : forces{3, lattice_size * lattice_size * lattice_size} {
        positions = Positions_t(3, forces.cols());
        velocities = Velocities_t(3, forces.cols());
        velocities.setRandom();
        velocities *= initial_velocity_multiplier;

        int index = 0;
        for (unsigned int x = 0; x < lattice_size; ++x) {
            for (unsigned int y = 0; y < lattice_size; ++y) {
                for (unsigned int z = 0; z < lattice_size; ++z) {
                    positions.col(index) << x * lattice_spacing,
                        y * lattice_spacing, z * lattice_spacing;
                    ++index;
                }
            }
        }
    }

    size_t nb_atoms() const {
        return positions.cols();
    }

    double kinetic_energy() {
        return (velocities.colwise().norm().pow(2) / 2).sum();
    }

    double temprature() {
        return (kinetic_energy() / (1.5 * nb_atoms() * BOLTZMANN_CONSTANT));
    }
};

#endif // __ATOMS_H