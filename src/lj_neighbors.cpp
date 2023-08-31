#include "lj_neighbors.h"

double lj_neighbors(NeighborList &neighbor_list, double cutoff, Atoms &atoms,
                    double epsilon, double sigma) {
    double e = 0.0;
    atoms.forces.setZero();
    neighbor_list.update(atoms, cutoff);

    const double cutoff_energy_shift =
        2 * epsilon * (pow((sigma / cutoff), 12) - pow((sigma / cutoff), 6));

    for (auto [i, j] : neighbor_list) {
        if (i == j)
            continue;
        Eigen::Vector3d ri = atoms.positions.col(j) - atoms.positions.col(i);
        double dist = ri.norm();
        double sig_over_dist = sigma / dist;
        double s_o_d_6 = pow(sig_over_dist, 6);
        double s_o_d_12 = s_o_d_6 * s_o_d_6;
        auto dir = (atoms.positions.col(j) - atoms.positions.col(i)) / dist;
        atoms.forces.col(i) -=
            4 * epsilon * (12 * s_o_d_12 / dist - 6 * s_o_d_6 / dist) * dir;

        e += 2 * epsilon * (s_o_d_12 - s_o_d_6) + cutoff_energy_shift;
    }
    return e;
}