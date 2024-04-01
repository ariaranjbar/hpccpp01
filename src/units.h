#ifndef UNITS_H
#define UNITS_H

// Boltzmann's constant: 1.380649e-23 j/K = 8.617333e-5 eV/K
constexpr double BOLTZMANN_CONSTANT = 0.00008617333;

// mass:    1.0 = 1 amu  = 1.66e-27 kg
constexpr double DEFAULT_MASS = 1.0;

// length:  1.0 = 1 A   = 1.0e-10 m
constexpr double DEFAULT_SIGMA = 3.4; // for Argon
constexpr double DEFAULT_LATTICE_SPACING = 3.8;
constexpr double DEFAULT_CUTOFF = 5.0 * DEFAULT_LATTICE_SPACING;

// temp:    1.0 = 1 K    = 2.7315e2 c
constexpr double DEFAULT_TEMP = 300.0;

// time:    1.0 = 10.18 fs   = 1.018e-14 s
constexpr double DEFAULT_TIMESTEP = 0.005; // ~ 0.05 Femtoseconds
constexpr double DEFAULT_TAU = 1.0;        // ~ 10.0  Femtoseconds
constexpr double DEFAULT_SIM_TIME = 200.0; // ~ 2000.0 Femtoseconds
constexpr double DEFAULT_FRAME_TIME = 0.5; // ~ 5 Femtoseconds

// energy:  1.0 = 1 eV   = 1.6e-19 j
constexpr double DEFAULT_EPSILON = 120 * BOLTZMANN_CONSTANT; // for Argon
constexpr double eps = 10.2 * BOLTZMANN_CONSTANT;

#endif // __UNITS_H
