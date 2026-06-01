#pragma once
#include "physics/state_vector.h"

// Define a clean type for our physics function pointer
using PhysicsFunction = void(*)(const AircraftState&, AircraftDerivative&, const Controller&);

// By making this 'inline', we eliminate the function call overhead in the main loop
inline void step_rk4(AircraftState& state, Controller controls, float dt, PhysicsFunction compute_physics) {
    
    // As discussed, these invoke the default constructor to guarantee zeroed memory
    AircraftDerivative k1, k2, k3, k4;
    AircraftState temp_state;

    // --- SAMPLE 1 (Start) ---
    compute_physics(state, k1, controls);

    // --- SAMPLE 2 (Midpoint using k1) ---
    for(int i = 0; i < 13; ++i) {
        temp_state.data[i] = state.data[i] + k1.d_data[i] * (dt * 0.5f);
    }
    temp_state.q.normalize(); // Must normalize partial rotations
    compute_physics(temp_state, k2, controls);

    // --- SAMPLE 3 (Midpoint using k2) ---
    for(int i = 0; i < 13; ++i) {
        temp_state.data[i] = state.data[i] + k2.d_data[i] * (dt * 0.5f);
    }
    temp_state.q.normalize();
    compute_physics(temp_state, k3, controls);

    // --- SAMPLE 4 (End using k3) ---
    for(int i = 0; i < 13; ++i) {
        temp_state.data[i] = state.data[i] + k3.d_data[i] * dt;
    }
    temp_state.q.normalize();
    compute_physics(temp_state, k4, controls);

    // --- FINAL WEIGHTED INTEGRATION ---
    // Update the master state with the RK4 average
    for(int i = 0; i < 13; ++i) {
        state.data[i] += (dt / 6.0f) * (k1.d_data[i] + 2.0f * k2.d_data[i] + 2.0f * k3.d_data[i] + k4.d_data[i]);
    }
    
    // The final safeguard against floating-point drift
    state.q.normalize(); 
}