// Include a library file to make sure proper includes are set
#include "verlet_single.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(VerletSingleTest, ConstantForce) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
    // Testing if we can call a function from our MD library

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
        ASSERT_NEAR(px, 0.5 * fx * i * i + 0.0 * i + 0.0, 1e-6);
        ASSERT_NEAR(py, 0.5 * fy * i * i + 0.0 * i + 0.0, 1e-6);
        ASSERT_NEAR(pz, 0.5 * fz * i * i + 0.0 * i + 0.0, 1e-6);
        ASSERT_NEAR(vx, fx * i + 0.0, 1e-6);
        ASSERT_NEAR(vy, fy * i + 0.0, 1e-6);
        ASSERT_NEAR(vz, fz * i + 0.0, 1e-6);
        verlet_step1(px, py, pz, vx, vy, vz, fx, fy, fz, 1);
        verlet_step2(vx, vy, vz, fx, fy, fz, 1);
    }
}
