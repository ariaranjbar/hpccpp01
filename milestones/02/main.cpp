#include "verlet_single.h"
#include <Eigen/Dense>
#include <iostream>

#ifdef USE_MPI
#include <mpi.h>
#endif

int main(int argc, char *argv[]) {
    int rank = 1, size = 1;

    // Below is some MPI code, try compiling with `cmake -DUSE_MPI=ON ..`
#ifdef USE_MPI
    MPI_Init(&argc, &argv);

    // Retrieve process infos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif

    std::cout << "Hello I am rank " << rank << " of " << size << "\n";

    if (rank == 1) {
        double px = 0.0;
        double py = 0.0;
        double pz = 0.0;
        double vx = 0.0;
        double vy = 0.0;
        double vz = 0.0;
        double fx = 0.5;
        double fy = 0.1;
        double fz = 0.3;
        for (int i = 0; i < 100; i++) {
            verlet_step1(px, py, pz, vx, vy, vz, fx, fy, fz, 1);
            verlet_step2(vx, vy, vz, fx, fy, fz, 1);
            
            std::cout << "px:   " << px << "py:   " << py << "py:   " << py << std::endl;
            std::cout << "vx:   " << vx << "vy:   " << vy << "vy:   " << vy << std::endl;
        };
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif

    return 0;
}
