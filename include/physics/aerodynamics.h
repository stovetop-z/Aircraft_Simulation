#pragma once
#include "physics/state_vector.h"

namespace Aerodynamics
{
    constexpr float MAX_THRUST = 30.0f;
    
    constexpr float MASS = 2.0f;
    constexpr float AIR_DENSITY = 1.225f;
    constexpr float GRAVITY = 9.81f;

    constexpr float WING_AREA = 0.5;
    constexpr float WING_SPAN = 2.5f;
    constexpr float WING_CHORD = 0.2f;

    constexpr float I_XX = 0.15f;
    constexpr float I_YY = 0.20f;
    constexpr float I_ZZ = 0.25f;

    constexpr float C_L_delta_a = 0.15f;
    constexpr float C_M_delta_e = -0.15f;
    constexpr float C_N_delta_r = -0.08f;

    constexpr float C_L_p = -0.04f;
    constexpr float C_M_q = -1.2f;
    constexpr float C_N_r = -0.15f;

    void compute_physics(const AircraftState& state, AircraftDerivative& d, const Controller& controller);
};