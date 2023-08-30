#include "verlet_single.h"
#include "units.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;

void verlet_step1(double &x, double &y, double &z, double &vx, double &vy,
                  double &vz, double fx, double fy, double fz,
                  double timestep) {

    vx += 0.5 * fx * timestep / DEFAULT_MASS;
    vy += 0.5 * fy * timestep / DEFAULT_MASS;
    vz += 0.5 * fz * timestep / DEFAULT_MASS;
    x += vx * timestep;
    y += vy * timestep;
    z += vz * timestep;
}

void verlet_step2(double &vx, double &vy, double &vz, double fx, double fy,
                  double fz, double timestep) {

    vx += 0.5 * fx * timestep / DEFAULT_MASS;
    vy += 0.5 * fy * timestep / DEFAULT_MASS;
    vz += 0.5 * fz * timestep / DEFAULT_MASS;
}
