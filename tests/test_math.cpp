#include "math/quaternion.h"
#include "math/rk4.h"
#include "physics/state_vector.h"
#include <cassert>
#include <iostream>
#include <cmath>

// A tiny tolerance for floating-point comparisons
constexpr float EPSILON = 0.0001f;

void test_quaternion_normalization() {
    // Create a badly scaled quaternion (e.g., accumulated drift)
    quaternion q(2.0f, 0.0f, 0.0f, 0.0f);
    q.normalize();

    // It must snap back to exactly 1.0
    float length_sq = q.q0*q.q0 + q.q1*q.q1 + q.q2*q.q2 + q.q3*q.q3;
    assert(std::abs(length_sq - 1.0f) < EPSILON && "FATAL: Quaternion failed to normalize!");
    std::cout << "[PASS] Quaternion Normalization\n";
}

// A dummy physics function strictly to test RK4 time integration
void dummy_freefall_physics(const AircraftState& state, AircraftDerivative& d, const Controller& controls) {
    // Hardcode a constant 9.81 downward acceleration
    for (int i = 0; i < 13; ++i) d.d_data[i] = 0.0f; 
    d.d_vel[2] = 9.81f; 
}

void test_rk4_integration() {
    AircraftState state; 
    Controller controls;
    float dt = 1.0f; // 1 full second

    // Call the RK4 engine using our dummy physics
    // Note: Because we removed ControlInput from the dummy for testing, 
    // you may need to mock it if your rk4.h strictly requires the control struct.
    step_rk4(state, controls, dt, dummy_freefall_physics);

    // If initial velocity was 0, and acceleration is 9.81 for 1 second,
    // final velocity must be exactly 9.81.
    assert(std::abs(state.vel[2] - 9.81f) < EPSILON && "FATAL: RK4 integration drift!");
    std::cout << "[PASS] RK4 Numerical Integration\n";
}

int main() {
    std::cout << "--- RUNNING MATH VERIFICATION ---\n";
    test_quaternion_normalization();
    test_rk4_integration();
    std::cout << "All Math tests passed. System is deterministic.\n";
    return 0;
}