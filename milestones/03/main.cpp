#include "verlet.h"
#include <Eigen/Dense>
#include <iostream>

#ifdef USE_MPI
#include <mpi.h>
#endif

int main(int argc, char *argv[]) {
    int rank = 0, size = 1;

    // Below is some MPI code, try compiling with `cmake -DUSE_MPI=ON ..`
#ifdef USE_MPI
    MPI_Init(&argc, &argv);

    // Retrieve process infos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif

    std::cout << "Hello I am milestone 3 of 9\n";

    if (rank == 0) {

        Positions_t positions(3, 10);
        positions.setZero();
        positions.row(0) =
            Eigen::ArrayXd::LinSpaced(positions.cols(), 0.0, 100.0);
        positions.row(1) =
            Eigen::ArrayXd::LinSpaced(positions.cols(), 0.0, 10.0);
        Velocities_t velocities(3, positions.cols());
        velocities.setZero();
        Forces_t forces(3, positions.cols());
        forces.setZero();
        forces.row(0) = forces.row(0) + 0.5;
        forces.row(1) = forces.row(1) + 0.1;
        forces.row(2) = forces.row(2) + 0.3;

        std::cout << "forces: " << std::endl;
        std::cout << forces << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < 100; i++) {
            verlet_step1(positions, velocities, forces, 1);
            verlet_step2(velocities, forces, 1);

            std::cout << "positions: " << std::endl;
            std::cout << positions << std::endl;
            std::cout << std::endl;
            std::cout << "velocities: " << std::endl;
            std::cout << velocities << std::endl;
            std::cout << std::endl;
        };
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif

    return 0;
}
