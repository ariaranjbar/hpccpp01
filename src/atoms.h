#ifndef ATOMS_H
#define ATOMS_H

#include "element_names.h"
#include "types.h"
#include "units.h"

class Atoms {
  public:
    Names_t names;
    Positions_t positions;
    Velocities_t velocities;
    Forces_t forces;

    Atoms() {
    }

    Atoms(const Names_t &n)
        : names{n},
          positions{3, n.rows()},
          velocities{3, n.rows()},
          forces{3, n.rows()} {
        positions.setZero();
        velocities.setZero();
        forces.setZero();
    }

    Atoms(const Positions_t &p)
        : names{p.cols()},
          positions{p},
          velocities{3, p.cols()},
          forces{3, p.cols()} {
        velocities.setZero();
        forces.setZero();
        names = element_names::Au;
    }

    Atoms(const Names_t &n, const Positions_t &p)
        : names{n},
          positions{p},
          velocities{3, p.cols()},
          forces{3, p.cols()} {
        assert(p.cols() == n.rows());
        velocities.setZero();
        forces.setZero();
    }

    Atoms(const Positions_t &p, const Velocities_t &v)
        : names{p.cols()},
          positions{p},
          velocities{v},
          forces{3, p.cols()} {
        assert(p.cols() == v.cols());
        forces.setZero();
        names = element_names::Au;
    }

    Atoms(const Names_t &n, const Positions_t &p, const Velocities_t &v)
        : names{n},
          positions{p},
          velocities{v},
          forces{3, p.cols()} {
        assert(p.cols() == v.cols());
        assert(p.cols() == n.rows());
        forces.setZero();
    }

    Atoms(const int nb_atoms)
        : names{nb_atoms},
          positions{3, nb_atoms},
          velocities{3, nb_atoms},
          forces{3, nb_atoms} {
        positions.setZero();
        velocities.setZero();
        forces.setZero();
        names = element_names::Au;
    }

    Atoms(const unsigned int lattice_size, const double lattice_spacing,
          const double initial_velocity_multiplier = 0.25)
        : names{lattice_size * lattice_size * lattice_size} {
        names = element_names::Au;
        positions = Positions_t(3, names.rows());
        velocities = Velocities_t(3, names.rows());
        velocities.setRandom();
        velocities *= initial_velocity_multiplier;
        forces = Forces_t(3, names.rows());
        forces.setZero();

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