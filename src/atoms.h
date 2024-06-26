#ifndef ATOMS_H
#define ATOMS_H

#include "element_names.h"
#include "types.h"
#include "units.h"
#include <iostream>

class Atoms {
  public:
    Names_t names;
    Masses_t masses;
    Positions_t positions;
    Velocities_t velocities;
    Forces_t forces;

    Atoms() {
    }

    Atoms(const Names_t &n)
        : names{n},
          masses{n.rows()},
          positions{3, n.rows()},
          velocities{3, n.rows()},
          forces{3, n.rows()} {
        positions.setZero();
        velocities.setZero();
        forces.setZero();
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(masses.rows() == positions.cols());
    }

    Atoms(const Positions_t &p)
        : names{p.cols()},
          masses{p.cols()},
          positions{p},
          velocities{3, p.cols()},
          forces{3, p.cols()} {
        velocities.setZero();
        forces.setZero();
        names = element_names::Au;
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(std::abs(masses.sum() / positions.cols() -
                        element_names::ELEMENT_MASS[element_names::Au]) < 1e-8);
        assert(masses.rows() == positions.cols());
    }

    Atoms(const Names_t &n, const Positions_t &p)
        : names{n},
          masses{n.rows()},
          positions{p},
          velocities{3, p.cols()},
          forces{3, p.cols()} {
        assert(p.cols() == n.rows());
        velocities.setZero();
        forces.setZero();
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(masses.rows() == positions.cols());
    }

    Atoms(const Positions_t &p, const Velocities_t &v)
        : names{p.cols()},
          masses{p.cols()},
          positions{p},
          velocities{v},
          forces{3, p.cols()} {
        assert(p.cols() == v.cols());
        forces.setZero();
        names = element_names::Au;
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(std::abs(masses.sum() / positions.cols() -
                        element_names::ELEMENT_MASS[element_names::Au]) < 1e-8);
        assert(masses.rows() == positions.cols());
    }

    Atoms(const Names_t &n, const Positions_t &p, const Velocities_t &v)
        : names{n},
          masses{n.rows()},
          positions{p},
          velocities{v},
          forces{3, p.cols()} {
        assert(p.cols() == v.cols());
        assert(p.cols() == n.rows());
        forces.setZero();
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(masses.rows() == positions.cols());
    }

    Atoms(const int nb_atoms)
        : names{nb_atoms},
          masses{nb_atoms},
          positions{3, nb_atoms},
          velocities{3, nb_atoms},
          forces{3, nb_atoms} {
        positions.setZero();
        velocities.setZero();
        forces.setZero();
        names = element_names::Au;
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[element_names::Au];
        }
        assert(masses.sum() / positions.cols() ==
               element_names::ELEMENT_MASS[element_names::Au]);
        assert(masses.rows() == positions.cols());
    }

    Atoms(const unsigned int lattice_size, const double lattice_spacing,
          const unsigned char element_name,
          const double initial_velocity_multiplier = 0.25)
        : names{lattice_size * lattice_size * lattice_size} {
        names = element_name;
        positions = Positions_t(3, names.rows());
        velocities = Velocities_t(3, names.rows());
        velocities.setRandom();
        velocities *= initial_velocity_multiplier;
        forces = Forces_t(3, names.rows());
        forces.setZero();
        masses = Masses_t(names.rows());
        for (unsigned int i = 0; i < masses.rows(); i++) {
            masses(i) = element_names::ELEMENT_MASS[names(i)];
        }
        assert(std::abs(masses.sum() / positions.cols() -
                        element_names::ELEMENT_MASS[element_name]) < 1e-8);
        assert(masses.rows() == positions.cols());

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
        return (masses.transpose() * velocities.colwise().norm().pow(2) / 2)
            .sum();
    }

    double temperature() {
        return (kinetic_energy() / (1.5 * nb_atoms() * BOLTZMANN_CONSTANT));
    }

    double min_distance() {
        double minDistance = std::numeric_limits<double>::max();

        // Compute the pairwise distances between all particles
        for (int i = 0; i < positions.cols() - 1; ++i) {
            for (int j = i + 1; j < positions.cols(); ++j) {
                // Calculate the Euclidean distance between particles i and j
                double distance =
                    (positions.col(i) - positions.col(j)).matrix().norm();
                // Update minDistance if the current distance is smaller
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }
        }

        return minDistance;
    }
};

#endif // __ATOMS_H