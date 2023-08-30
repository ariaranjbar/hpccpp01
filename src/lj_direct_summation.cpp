#include "lj_direct_summation.h"

double lj_direct_summation(Atoms &atoms, double epsilon, double sigma) {
    double e = 0.0;
    atoms.forces.setZero();
    for (size_t i = 0; i < atoms.nb_atoms(); i++) {
        for (size_t j = 0; j < atoms.nb_atoms(); j++) {
            if (i == j)
                continue;
            Eigen::Vector3d ri =
                atoms.positions.col(j) - atoms.positions.col(i);
            double dist = ri.norm();
            double sig_over_dist = sigma / dist;
            double s_o_d_6 = pow(sig_over_dist, 6);
            double s_o_d_12 = s_o_d_6 * s_o_d_6;
            auto dir = (atoms.positions.col(j) - atoms.positions.col(i)) / dist;
            atoms.forces.col(i) -=
                4 * epsilon * (12 * s_o_d_12 / dist - 6 * s_o_d_6 / dist) * dir;

            e += 2 * epsilon * (s_o_d_12 - s_o_d_6);
        }
    }
    return e;
}