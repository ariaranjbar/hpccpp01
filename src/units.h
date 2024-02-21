#ifndef UNITS_H
#define UNITS_H

// mass:    1.0 = 1amu  = 1.66054e-27 kg
constexpr double DEFAULT_MASS = 1.0;

// length:  1.0 = 1nm   = 1.0e-9 m
constexpr double DEFAULT_SIGMA = 1.0;
constexpr double DEFAULT_LATTICE_SPACING = 1.0;
constexpr double DEFAULT_CUTOFF = 3.0 * DEFAULT_LATTICE_SPACING;

// temp:    1.0 = 1K    = 2.7315e2 c
constexpr double DEFAULT_TEMP = 300.0;

// energy:  1.0 = 1eu   = 6.2129205e-21 j =
constexpr double DEFAULT_EPSILON = 1.0;

// time:    1.0 = 1tu   = 3.6556261e-13 s (365.56261 Femtoseconds)
constexpr double DEFAULT_TIMESTEP = 0.00141421; // ~ 0.5 Femtoseconds
constexpr double DEFAULT_TAU = 14.1421;         // ~ 5.0 picoseconds
constexpr double DEFAULT_SIM_TIME = 141.421;    // ~ 50.0 picoseconds
constexpr double DEFAULT_FRAME_TIME = 0.141421; // ~ 0.05 picoseconds

// Boltzmann's constant: 1.380649e-23 j/K = 0.002222222eu/K
constexpr double BOLTZMANN_CONSTANT = 0.002222222;

#endif // __UNITS_H
