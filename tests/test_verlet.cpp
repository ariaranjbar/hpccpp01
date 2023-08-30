// Include a library file to make sure proper includes are set
#include "verlet.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(VerletTest, ConstantForce) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
    // Testing if we can call a function from our MD library

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

        Positions_t initial_p = positions;
        Positions_t initial_v = velocities;

        std::cout << "forces: " << std::endl;
        std::cout << forces << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < 100; i++) {
            double id = i;
            ASSERT_TRUE(positions.isApprox(0.5 * forces * id * id + initial_v * id + initial_p, 1e-6));
            verlet_step1(positions, velocities, forces, 1);
            verlet_step2(velocities, forces, 1);

        };


}
