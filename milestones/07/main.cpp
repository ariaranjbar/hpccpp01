
#include "atoms.h"
#include "ducastelle.h"
#include "neighbors.h"
#include "thermostat.h"
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
    int rank = 0, size = 1;

    // Below is some MPI code, try compiling with `cmake -DUSE_MPI=ON ..`
#ifdef USE_MPI
    MPI_Init(&argc, &argv);

    // Retrieve process infos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
    /**********Program State**********/
    // --mode 0 | 1
    // 0 = file, 1 = lattice
    int mode = 0;

    // --cutoff 15.0
    double cutoff = DEFAULT_CUTOFF;

    // --atoms_in "cluster_923"
    std::string atomsInputFileName = "cluster_923";

    // --lattice_size 5
    unsigned int latticeSize = 5;

    // --lattice_spacing 1.0
    double latticeSpacing = DEFAULT_LATTICE_SPACING;

    // --output "output"
    std::string outFileName = "output";

    // --timestep 0.005
    double timeStep = DEFAULT_TIMESTEP;

    // --sim_time 200.0
    double simTime = DEFAULT_SIM_TIME;

    // --frame_time 0.5
    double frameTime = DEFAULT_FRAME_TIME;

    // --temp 300
    double temp = DEFAULT_TEMP;

    // --tau 1.0
    double relaxation = DEFAULT_TAU;
    /************************************/

    /**********Parse Command-Line Arguments**********/
    // A: Construct header
    std::string header = "";
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--help" ||
             std::string(argv[i]) == "-h") &&
            i < argc) {
            std::cout << "Options:" << std::endl;
            std::cout << "\t--help, -h: Display this message" << std::endl;
            std::cout << "\t--mode: Set program mode for atomic structure. 0 = "
                         "read from file, 1 = "
                         "create cubic lattice. Defaut: "
                      << mode << std::endl;
            std::cout << "\t--cutoff: Cutoff radius for neighbor search. "
                         "Default: "
                      << cutoff << std::endl;
            std::cout << "\t--atoms_in: Name of the input xyz file without "
                         "extension. Default: "
                      << atomsInputFileName << std::endl;
            std::cout << "\t--lattice_size: Number of atoms in one edge of the "
                         "cubic lattice. Default: "
                      << latticeSize << std::endl;
            std::cout
                << "\t--lattice_spacing: Distance of neighbor atoms in the "
                   "cubic lattice. Default: 1.0"
                << std::endl;
            std::cout << "\t--output: Name of the output files. "
                         "Default: "
                      << outFileName << std::endl;
            std::cout << "\t--timestep: Value of the simulation time step. "
                         "Default: "
                      << timeStep << std::endl;
            std::cout
                << "\t--sim_time: Value of the time duration of simulation. "
                   "Default: "
                << simTime << std::endl;
            std::cout << "\t--frame_time: Value of the time difference between "
                         "consecutive frames. "
                         "Default: "
                      << frameTime << std::endl;
            std::cout << "\t--temp: Value of the thermostat's themprature in "
                         "Kelvin. "
                         "Default: "
                      << temp << std::endl;
            std::cout
                << "\t--tau: Value of the relaxation time of the simulation. "
                   "Default: "
                << relaxation << std::endl;
            return 1;
        }
    }

    // B: Load program state
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--mode" && i + 1 < argc) {
            i++;
            mode = std::atoi(argv[i]);
            header += "mode:" + std::to_string(mode);
            header += " ";
        } else if (std::string(argv[i]) == "--cutoff" && i + 1 < argc) {
            i++;
            cutoff = std::atof(argv[i]);
            header += "cutoff_radius:" + std::to_string(cutoff);
            header += " ";
        } else if (std::string(argv[i]) == "--atoms_in" && i + 1 < argc) {
            i++;
            atomsInputFileName = std::string(argv[i]);
            header += "atoms_input:" + atomsInputFileName;
            header += " ";
        } else if (std::string(argv[i]) == "--lattice_size" && i + 1 < argc) {
            i++;
            latticeSize = std::atoi(argv[i]);
            header += "lattice_size:" + std::to_string(latticeSize);
            header += " ";
        } else if (std::string(argv[i]) == "--lattice_spacing" &&
                   i + 1 < argc) {
            i++;
            latticeSpacing = std::atof(argv[i]);
            header += "lattice_spacing:" + std::to_string(latticeSpacing);
            header += " ";
        } else if (std::string(argv[i]) == "--output" && i + 1 < argc) {
            i++;
            outFileName = std::string(argv[i]);
            header += "output:" + outFileName;
            header += " ";
        } else if (std::string(argv[i]) == "--timestep" && i + 1 < argc) {
            i++;
            timeStep = std::atof(argv[i]);
            header += "timestep:" + std::to_string(timeStep);
            header += " ";
        } else if (std::string(argv[i]) == "--sim_time" && i + 1 < argc) {
            i++;
            simTime = std::atof(argv[i]);
            header += "sim_time:" + std::to_string(simTime);
            header += " ";
        } else if (std::string(argv[i]) == "--frame_time" && i + 1 < argc) {
            i++;
            frameTime = std::atof(argv[i]);
            header += "frame_time:" + std::to_string(frameTime);
            header += " ";
        } else if (std::string(argv[i]) == "--temp" && i + 1 < argc) {
            i++;
            temp = std::atof(argv[i]);
            header += "thermostat_temperature:" + std::to_string(temp);
            header += " ";
        } else if (std::string(argv[i]) == "--tau" && i + 1 < argc) {
            i++;
            relaxation = std::atof(argv[i]);
            header += "relaxation_time:" + std::to_string(relaxation);
            header += " ";
        } else {
            std::cout
                << "Invalid option \"" << argv[i]
                << "\". Use -h to see a list of available options. Exiting."
                << std::endl;
            return 1;
        }
    }
    /************************************************/

    std::cout << "Hello I am milestone 7 of 9\n";

    if (rank == 0) {
        Atoms atoms;

        // Initiate atomic structure
        switch (mode) { // XYZ file structure
        case 0: {
            auto [names, positions, velocities]{
                read_xyz_with_velocities(atomsInputFileName + ".xyz")};
            atoms = Atoms(names, positions);
        } break;
        case 1: { // Cubic lattice structure
            atoms = Atoms(latticeSize, latticeSpacing, element_names::Au);
        } break;
        default: { // Invalid state: --mode
            std::cout << "Invalid mode \"" << mode
                      << "\". Choose --mode 0 to read the atomic sructure from "
                         "a file or --mode 1 for a lattice structure. Exiting."
                      << std::endl;
        }
            return 1;
        }

        NeighborList neighbor_list;

        // Initiate outputs
        std::ofstream traj(outFileName + ".xyz");
        std::ofstream energy_stream(outFileName + ".txt");
        energy_stream << header << std::endl;
        energy_stream << std::setprecision(10) << std::setw(20) << "time"
                      << std::setw(20) << "total_energy" << std::setw(20)
                      << "kinetic_energy" << std::setw(20) << "potential_energy"
                      << std::setw(20) << "temperature" << std::endl;

        double avg_temperature = 0;
        double avg_potential_energy = 0;
        double avg_kinetic_energy = 0;

        double start_temp = atoms.temperature();
        double temp_slider = start_temp;
        double delta_temp = (temp - start_temp) * (timeStep / simTime);

        std::cout << "start  temp: " << start_temp << std::endl;
        std::cout << "target temp: " << temp << std::endl;
        std::cout << "delta  temp: " << delta_temp << std::endl;

        // Simulation loop
        for (int i = 0; i < static_cast<int>((simTime / timeStep)); i++) {
            temp_slider += delta_temp;
            verlet_step1(atoms, timeStep);
            double potentioal_energy = ducastelle(atoms, neighbor_list, cutoff);
            verlet_step2(atoms, timeStep);
            berendsen_thermostat(atoms, temp_slider, timeStep, relaxation);

            avg_temperature += atoms.temperature();
            avg_potential_energy += potentioal_energy;
            avg_kinetic_energy += atoms.kinetic_energy();

            // Write step
            if (i % static_cast<int>((frameTime / timeStep)) == 0) {
                const int n = static_cast<int>((frameTime / timeStep));
                avg_temperature /= n;
                avg_kinetic_energy /= n;
                avg_potential_energy /= n;
                write_xyz(traj, atoms);

                energy_stream
                    << std::setw(20) << std::fixed
                    << std::min(timeStep * i, 99999999.0) << std::setw(20)
                    << std::fixed
                    << std::min(avg_kinetic_energy + avg_potential_energy,
                                99999999.0)
                    << std::setw(20) << std::fixed
                    << std::min(avg_kinetic_energy, 99999999.0) << std::setw(20)
                    << std::fixed << std::min(avg_potential_energy, 99999999.0)
                    << std::setw(20) << std::fixed
                    << std::min(avg_temperature, 99999999.0) << std::endl;

                avg_temperature = 0;
                avg_kinetic_energy = 0;
                avg_potential_energy = 0;
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
