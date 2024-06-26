
#include "atoms.h"
#include "lj_direct_summation.h"
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
    /**********MUST BECOME ARGS**********/
    // --mode 0 | 1
    // 0 = file, 1 = lattice
    int mode = 0;

    // --atoms_in "lj54"
    std::string atomsInputFileName = "lj54";

    // --lattice_size 5
    unsigned int latticeSize = 5;

    // --lattice_spacing 3.0
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

    // --lj_epsilon 0.01035486
    double ljEpsilon = DEFAULT_EPSILON;

    // --lj_sigma 3.4
    double ljSigma = DEFAULT_SIGMA;

    // --element "Ar"
    std::string elementName = "Ar";

    // --init_velocity 0.05
    double initVelocity = 0.05;
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
                         "create cubic lattice. Defaut: "
                      << mode << std::endl;
            std::cout << "\t--atoms_in: Name of the input xyz file without "
                         "extension. Default: "
                      << atomsInputFileName << std::endl;
            std::cout << "\t--lattice_size: Number of atoms in one edge of the "
                         "cubic lattice. Default: "
                      << latticeSize << std::endl;
            std::cout
                << "\t--lattice_spacing: Distance of neighbor atoms in the "
                   "cubic lattice. Default: "
                << latticeSpacing << std::endl;
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
            std::cout << "\t--lj_epsilon: Value of epsilon in Lennard-Jones "
                         "potentional. "
                         "Default: "
                      << ljEpsilon << std::endl;
            std::cout << "\t--lj_epsilon: Value of sigma in Lennard-Jones "
                         "potentional. "
                         "Default: "
                      << ljSigma << std::endl;
            std::cout << "\t--element: Name of the element the lattice is "
                         "made from. Default: "
                      << elementName << std::endl;
            std::cout << "\t--init_velocity: multiplier of initial random "
                         "velocities of atoms. "
                         "Default: "
                      << initVelocity << std::endl;
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
        } else if (std::string(argv[i]) == "--timestep" && i + 1 < argc) {
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
        } else if (std::string(argv[i]) == "--temp" && i + 1 < argc) {
            temp = std::atof(argv[i + 1]);
            header += "thermostat_temperature:" + std::to_string(temp);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--tau" && i + 1 < argc) {
            relaxation = std::atof(argv[i + 1]);
            header += "relaxation_time:" + std::to_string(relaxation);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--lj_epsilon" && i + 1 < argc) {
            ljEpsilon = std::atof(argv[i + 1]);
            header += "lj_epsilon:" + std::to_string(ljEpsilon);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--lj_sigma" && i + 1 < argc) {
            ljSigma = std::atof(argv[i + 1]);
            header += "lj_sigma:" + std::to_string(ljSigma);
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--element" && i + 1 < argc) {
            elementName = std::string(argv[i + 1]);
            header += "element:" + elementName;
            header += " ";
            reading_value = true;
        } else if (std::string(argv[i]) == "--init_velocity" && i + 1 < argc) {
            initVelocity = std::atof(argv[i + 1]);
            header += "init_velocity:" + std::to_string(initVelocity);
            header += " ";
            reading_value = true;
        } else {
            std::cout << "Invalid option \"" << argv[i] << "\". Exiting."
                      << std::endl;
            return 1;
        }
    }

    std::cout << "Hello I am milestone 5 of 9\n";

    if (rank == 0) {

        Atoms atoms;

        switch (mode) { // XYZ file structure
        case 0: {
            auto [names, positions, velocities]{
                read_xyz_with_velocities(atomsInputFileName + ".xyz")};
            atoms = Atoms(names, positions, velocities);
        } break;
        case 1: { // Cubic lattice structure
            atoms = Atoms(latticeSize, latticeSpacing,
                          element_names::ELEMENT_NUMBER.at(elementName),
                          initVelocity);
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
                      << std::setw(20) << "temperature" << std::endl;

        double avg_temperature = 0;
        double avg_potential_energy = 0;
        double avg_kinetic_energy = 0;

        for (int i = 0; i < static_cast<int>((simTime / timeStep)); i++) {
            verlet_step1(atoms, timeStep);
            double potentioal_energy =
                lj_direct_summation(atoms, ljEpsilon, ljSigma);
            verlet_step2(atoms, timeStep);
            berendsen_thermostat(atoms, temp, timeStep, relaxation);

            avg_temperature += atoms.temperature();
            avg_potential_energy += potentioal_energy;
            avg_kinetic_energy += atoms.kinetic_energy();

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
