
#include <gtest/gtest.h>

#include "atoms.h"
#include "lj_direct_summation.h"
#include "thermostat.h"
#include "verlet.h"
#include <vector>

TEST(ThermostatTest, Temperature) {

    Positions_t positions(3, 27);

    std::vector<std::vector<double>> pos{
        {0.341104, 2.62266, -0.966323}, {-1.23524, 1.94952, 2.70025},
        {0.907826, 0.178143, 5.33784},  {1.42745, 5.5445, 0.604394},
        {1.40392, 3.49473, 4.85979},    {2.72238, 2.315, 8.1961},
        {2.56873, 6.74974, -2.97451},   {-0.736013, 6.02668, 3.88076},
        {-1.56187, 3.51062, 6.60343},   {2.29656, 1.12135, 1.91568},
        {4.54775, 1.04172, 5.0312},     {5.14086, -0.978318, 8.61955},
        {3.7251, 3.34757, -1.09228},    {4.25865, 3.94078, 2.40636},
        {4.55336, 4.69641, 5.97416},    {4.73998, 7.026, 0.27789},
        {2.99867, 6.97473, 3.63546},    {1.20202, 8.64591, 10.2609},
        {4.18442, -0.610042, -1.38233}, {8.19405, 0.061852, 5.43492},
        {6.44536, 2.4142, 7.80852},     {5.98817, 1.07305, 1.13527},
        {7.92994, 3.42799, 3.92663},    {8.33914, 5.84763, 6.59606},
        {7.31988, 4.56401, 0.457831},   {6.52231, 7.42815, 3.51481},
        {5.43306, 8.09608, 7.19629},
    };

    for (int i = 0; i < pos.size(); i++) {
        positions.col(i) << pos.at(i).at(0), pos.at(i).at(1), pos.at(i).at(2);
    }

    Velocities_t velocities(3, 27);

    std::vector<std::vector<double>> vel{{0.0287393, 0.000875541, -0.0104097},
                                         {-0.088899, 0.00710724, -0.0203421},
                                         {0.0725636, -0.0517285, 0.0230276},
                                         {0.012032, 0.0405964, 0.0394423},
                                         {0.0233822, -0.00346298, 0.054069},
                                         {0.0182664, 0.0380359, -0.0168654},
                                         {0.0601139, -0.0931044, 0.00965071},
                                         {-0.101977, -0.0263235, 0.00362696},
                                         {0.000774492, 0.0511253, -0.00487092},
                                         {-0.0394511, 0.0052059, -0.0579783},
                                         {-0.0844299, -0.0595249, -0.0152717},
                                         {-0.0158267, -0.0367262, 0.0232306},
                                         {-0.00637599, 0.025583, -0.0562355},
                                         {-0.0270046, -0.0722498, -0.0862381},
                                         {-0.0580436, -0.0170042, -0.119584},
                                         {-0.148536, 0.0928302, 0.043868},
                                         {0.016832, -0.00767178, 0.0302158},
                                         {0.0733926, 0.0113791, 0.0365277},
                                         {0.0687775, 0.0532173, 0.00325693},
                                         {0.0795504, -0.0133692, -0.00356889},
                                         {0.000211526, 0.0844381, -0.038646},
                                         {0.00339265, 0.021124, 0.0772312},
                                         {-0.0476053, 0.0249667, 0.00458169},
                                         {0.0427979, 0.00536527, 0.153772},
                                         {0.00188756, -0.0223123, 0.079375},
                                         {0.0798328, -0.0111386, -0.0389015},
                                         {0.0343844, -0.0441659, -0.112669}};

    for (int i = 0; i < vel.size(); i++) {
        velocities.col(i) << vel.at(i).at(0), vel.at(i).at(1), vel.at(i).at(2);
    }

    Names_t names(positions.cols());
    names = element_names::Ar;

    Atoms atoms = Atoms(names, positions, velocities);

    constexpr double target_temp = 100;
    constexpr double relaxation = 50.0;

    constexpr double timestep = 0.005;

    constexpr unsigned int sim_steps = 50;

    constexpr double sigma = 3.4;
    constexpr double epsilon = 0.0103407996;

    constexpr double e = 2.718281828459045235;
    std::cout << "!----start temperature: " << atoms.temperature() << std::endl;

    for (unsigned i = 0; i < sim_steps; i++) {

        // std::cout << "!--velocities, before lj:" << std::endl;
        // for (unsigned int i = 0; i < atoms.velocities.cols(); i++) {
        //     std::cout << atoms.velocities.col(i) << std::endl << std::endl;
        // }

        verlet_step1(atoms, timestep);
        double potentioal_energy = lj_direct_summation(atoms, epsilon, sigma);
        verlet_step2(atoms, timestep);

        double old_temperature = atoms.temperature();
        berendsen_thermostat(atoms, target_temp, timestep, relaxation);
        double new_temperature = atoms.temperature();
        double expected_temp =
            target_temp + ((old_temperature - target_temp) *
                           (pow(e, (-timestep / relaxation))));

        std::cout << "!------old temperature: " << old_temperature << std::endl;
        std::cout << "!------new temperature: " << new_temperature << std::endl;
        std::cout << "!-expected temperature: " << expected_temp << std::endl;
        std::cout << std::endl;

        EXPECT_NEAR(abs((new_temperature) - (expected_temp)), 0, 1e-5);
    }
}