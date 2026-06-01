#include "physics/state_vector.h"
#include "physics/aerodynamics.h"
#include "math/rk4.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

int main() {
    std::cout << "--- AEROSPACE FLIGHT EXECUTIVE BOOTING ---\n";

    // =================================================================
    // 1. ALLOCATE THE MASTER MEMORY (On the Stack)
    // =================================================================
    AircraftState current_state;
    Controller controls;

    // Set initial flight conditions (e.g., dropping from the sky at 50 m/s)
    current_state.vel[0] = 50.0f;     // Forward airspeed
    current_state.pos[2] = 1000.0f;   // Altitude (meters)

    // =================================================================
    // 2. THE TIMING BUDGET (100 Hz)
    // =================================================================
    const float dt = 0.01f; // 10 milliseconds per frame
    const auto frame_duration = std::chrono::duration<float>(dt);

    std::cout << "System initialized. Entering 100Hz Flight Loop...\n\n";
    std::cout << "Initial Alt: " << current_state.pos[2] << " | " 
            <<  "Initial Vel: " << current_state.vel[0] << " | "
            << "Initial roll: " << current_state.rates[0] << std::endl << std::endl;

    // =================================================================
    // 3. THE INFINITE FLIGHT LOOP
    // =================================================================
    while (true) {
        // Mark the exact nanosecond the frame starts
        auto frame_start = std::chrono::steady_clock::now();

        // --- A. READ INPUTS ---
        // (Later, we will read these from a UDP socket connected to your ML Python script)
        // For now, let's command a slight right roll to test the math
        controls.aileron = 0.0f; 
        controls.throttle = 1.0f; // Full throttle

        // --- B. EXECUTE PHYSICS ---
        // Step the RK4 integrator forward by 10ms
        step_rk4(current_state, controls, dt, Aerodynamics::compute_physics);

        // --- C. TELEMETRY OUTPUT ---
        // Print the aircraft's state cleanly to the console using \r to overwrite the line
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\rAlt: " << current_state.pos[2] << "m | "
                  << "Vel: " << current_state.vel[0] << "m/s | "
                  << "Roll Rate: " << current_state.rates[0] << "rad/s" 
                  << std::flush;

        // --- D. ENFORCE DETERMINISM (The Sleep Guard) ---
        auto frame_end = std::chrono::steady_clock::now();
        auto elapsed = frame_end - frame_start;

        if (elapsed < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed);
        } else {
            // Soft warning instead of a hard break
            std::cout << "\n[WARN] OS scheduling delayed frame by " 
                      << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - frame_duration).count() 
                      << "ms\n";
        }
    }

    return 0;
}