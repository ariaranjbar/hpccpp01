
#include "atoms.h"
#include "lj_direct_summation.h"
#include "units.h"
#include "verlet.h"
#include "xyz.h"
#include <Eigen/Dense>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef USE_MPI
#include <mpi.h>
#endif

int main(int argc, char *argv[]) {
    int ms = 4, size = 9;

    // Below is some MPI code, try compiling with `cmake -DUSE_MPI=ON ..`
#ifdef USE_MPI
    MPI_Init(&argc, &argv);

    // Retrieve process infos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
    /**********MUST BECOME ARGS**********/
    // --mode 0 | 1
    // 0 = file, 1 = lattice
    int mode = 0;

    // --atoms_in "lj54"
    std::string atomsInputFileName = "lj54";

    // --lattice_size 5
    int latticeSize = 3;

    // --lattice_spacing 2.0
    double latticeSpacing = 2;

    // --output "output"
    std::string outFileName = "output";

    // --time_step 0.00141421
    double timeStep = DEFAULT_TIMESTEP;

    // --sim_time 141.421
    double simTime = DEFAULT_SIM_TIME;

    // --frame_time 0.141421
    double frameTime = DEFAULT_FRAME_TIME;
    /************************************/

    // Parse command-line arguments
    std::string header = "";
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--help" ||
             std::string(argv[i]) == "-h") &&
            i < argc) {
            std::cout << "Options:" << std::endl;
            std::cout << "\t--help, -h: Display this message" << std::endl;
            std::cout << "\t--mode: set program mode. 0 = read from file, 1 = "
                         "create cubic lattice. Defaut: 0"
                      << std::endl;
            std::cout << "\t--atoms_in: Name of the input xyz file without "
                         "extension. Default: lj54 "
                      << std::endl;
            std::cout << "\t--lattice_size: Number of atoms in one edge of the "
                         "cubic lattice. Default: 3"
                      << std::endl;
            std::cout
                << "\t--lattice_spacing: Distance of neighbor atoms in the "
                   "cubic lattice. Default: 2"
                << std::endl;
            std::cout << "\t--output: Name of the output files. "
                         "Default: output"
                      << std::endl;
            std::cout << "\t--time_step: Value of the simulation time step. "
                         "Default: 0.00141421"
                      << std::endl;
            std::cout
                << "\t--sim_time: Value of the time duration of simulation. "
                   "Default: 141.421"
                << std::endl;
            std::cout << "\t--frame_time: Value of the time difference between "
                         "consecutive frames. "
                         "Default: 0.141421"
                      << std::endl;
            return 1;
        }
    }
    bool reading_value = false;
    for (int i = 1; i < argc; ++i) {
        if (reading_value) {
            reading_value = false;
            continue;
        }
        if (std::string(argv[i]) == "--mode" && i + 1 < argc) {
            mode = std::atoi(argv[i + 1]);
            header += "mode:" + std::to_string(mode);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--atoms_in" && i + 1 < argc) {
            atomsInputFileName = std::string(argv[i + 1]);
            header += "atoms_input:" + atomsInputFileName;
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--lattice_size" && i + 1 < argc) {
            latticeSize = std::atoi(argv[i + 1]);
            header += "lattice_size:" + std::to_string(latticeSize);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--lattice_spacing" &&
                   i + 1 < argc) {
            latticeSpacing = std::atof(argv[i + 1]);
            header += "lattice_spacing:" + std::to_string(latticeSpacing);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--output" && i + 1 < argc) {
            outFileName = std::string(argv[i + 1]);
            header += "output:" + outFileName;
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--time_step" && i + 1 < argc) {
            timeStep = std::atof(argv[i + 1]);
            header += "timestep:" + std::to_string(timeStep);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--sim_time" && i + 1 < argc) {
            simTime = std::atof(argv[i + 1]);
            header += "sim_time:" + std::to_string(simTime);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--frame_time" && i + 1 < argc) {
            frameTime = std::atof(argv[i + 1]);
            header += "frame_time:" + std::to_string(frameTime);
            header += " ";
            reading_value = true;
        } else {
            std::cout << "Invalid option \"" << argv[i] << "\". Exiting."
                      << std::endl;
            return 1;
        }
    }

    std::cout << "Hello I am milestone " << ms << " of " << size << "\n";

    if (ms == 4) {

        Atoms atoms;

        switch (mode) { // XYZ file structure
        case 0: {
            auto [names, positions, velocities]{
                read_xyz_with_velocities(atomsInputFileName + ".xyz")};
            atoms = Atoms(positions, velocities);
        } break;
        case 1: { // Cubic lattice structure
            atoms = Atoms(latticeSize, latticeSpacing);
        } break;
        default:
            std::cout << "Invalid mode \"" << mode << "\". Exiting."
                      << std::endl;
            return 1;
        }

        std::ofstream traj(outFileName + ".xyz");
        std::ofstream energy_stream(outFileName + ".txt");
        energy_stream << header << std::endl;
        energy_stream << std::setprecision(10) << std::setw(20) << "time"
                      << std::setw(20) << "total_energy" << std::setw(20)
                      << "kinetic_energy" << std::setw(20) << "potential_energy"
                      << std::endl;

        for (int i = 0; i < static_cast<int>((simTime / timeStep)); i++) {
            verlet_step1(atoms.positions, atoms.velocities, atoms.forces,
                         timeStep);
            double potentioal_energy = lj_direct_summation(atoms);
            verlet_step2(atoms.velocities, atoms.forces, timeStep);

            if (i % static_cast<int>((frameTime / timeStep)) == 0) {
                double kinetic_energy = atoms.kinetic_energy();
                write_xyz(traj, atoms);

                energy_stream
                    << std::setw(20) << std::fixed
                    << std::min(timeStep * i, 99999999.0) << std::setw(20)
                    << std::fixed
                    << std::min(kinetic_energy + potentioal_energy, 99999999.0)
                    << std::setw(20) << std::fixed
                    << std::min(kinetic_energy, 99999999.0) << std::setw(20)
                    << std::fixed << std::min(potentioal_energy, 99999999.0)
                    << std::endl;
            }
        };
        traj.close();
        energy_stream.close();
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif

    return 0;
}
