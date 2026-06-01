#include "physics/aerodynamics.h"
#include "physics/state_vector.h"
#include <cassert>
#include <iostream>
#include <cmath>

constexpr float EPSILON = 0.001f;

void test_static_drop() {
    // 1. Setup: Aircraft at dead stop in the air
    AircraftState state;
    Controller controls; // All controls default to 0.0 (neutral)
    AircraftDerivative derivative;

    // 2. Execute: Run one frame of aerodynamic calculations
    Aerodynamics::compute_physics(state, derivative, controls);

    // 3. Verify: With zero airspeed, drag and lift are zero. 
    // Therefore, Z-acceleration MUST equal exact gravity (9.81).
    assert(std::abs(derivative.d_vel[2] - Aerodynamics::GRAVITY) < EPSILON 
           && "FATAL: Phantom lift/drag generated at zero airspeed!");
    
    // Verify: X-acceleration (forward) MUST be zero because thrust is 0.
    assert(std::abs(derivative.d_vel[0] - 0.0f) < EPSILON 
           && "FATAL: Phantom forward acceleration generated!");

    std::cout << "[PASS] Static Drop Aerodynamics (No phantom forces)\n";
}

void test_control_surface_moments() {
    AircraftState state;
    Controller controls;
    AircraftDerivative derivative;

    // 1. Setup: Give the plane 50 m/s forward velocity so control surfaces have air to bite into
    state.vel[0] = 50.0f;
    
    // 2. Action: Command full right aileron
    controls.aileron = 1.0f; 

    // 3. Execute
    Aerodynamics::compute_physics(state, derivative, controls);

    // 4. Verify: Full right aileron must produce a positive roll acceleration (d_rates[0] > 0)
    assert(derivative.d_rates[0] > 0.0f && "FATAL: Ailerons did not produce roll torque!");
    
    std::cout << "[PASS] Control Surface Deflection yields torque\n";
}

int main() {
    std::cout << "--- RUNNING PHYSICS VERIFICATION ---\n";
    test_static_drop();
    test_control_surface_moments();
    std::cout << "All Physics tests passed. Aerodynamics are stable.\n";
    return 0;
}