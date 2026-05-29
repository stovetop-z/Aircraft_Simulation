#include "physics/aerodynamics.h"
#include <cmath>

namespace Aerodynamics
{
    float C_L(float angle_of_attack)
    {
        if(angle_of_attack > 0.226) return 0.5;
        return 2.0 * M_PI * angle_of_attack;
    }

    float C_d(float cl)
    {
        float cd0 = 0.2f;
        float k = 0.05f;
        return cd0 + (k * cl * cl);
    }

    void compute_physics(const AircraftState& state, AircraftDerivative& d, const Controller& controls)
    {
        // Wind speed and angle of attack
        float u = state.vel[0];
        float w = state.vel[1];

        float v_sqr = (u * u) + (w * w);
        float airspeed = std::sqrtf(v_sqr);

        float alpha = std::atan2f(w, u);

        float dynamic_pressure = 0.5f * AIR_DENSITY * v_sqr;

        // Lift and drag
        float lift = dynamic_pressure * C_L(alpha) * WING_AREA;
        float drag = dynamic_pressure * C_d(alpha) * WING_AREA;
        float thrust = controls.throttle * MAX_THRUST;

        float Fx = thrust - drag * std::cosf(alpha) + lift * std::sinf(alpha);
        float Fz = -drag * std::sin(alpha) - lift * std::cos(alpha) + (MASS * GRAVITY);

        // Torques and moments
        float p = state.rates[0];
        float q = state.rates[1];
        float r = state.rates[2];

        float C_l = (C_L_delta_a * controls.aileron)  + (C_L_p * (p * WING_SPAN) / (2.0f * airspeed));
        float C_m = (-0.4f * alpha) + (C_M_delta_e * controls.elevator) + (C_M_q * (q * WING_CHORD) / (2.0f * airspeed));
        float C_n = (C_N_delta_r * controls.rudder)   + (C_N_r * (r * WING_SPAN) / (2.0f * airspeed));

        // Convert coefficients into physical torque (Newton-meters)
        float L_aero = dynamic_pressure * WING_AREA * WING_SPAN * C_l;  
        float M_aero = dynamic_pressure * WING_AREA * WING_CHORD * C_m; 
        float N_aero = dynamic_pressure * WING_AREA * WING_SPAN * C_n;  


        // Accelerations
        
        d.d_pos[0] = state.vel[0];
        d.d_pos[1] = state.vel[1];
        d.d_pos[2] = state.vel[2];

        d.d_vel[0] = Fx / MASS;
        d.d_vel[1] = 0.0f; 
        d.d_vel[2] = Fz / MASS;

        d.d_rates[0] = (L_aero - (I_ZZ - I_YY) * q * r) / I_XX;
        d.d_rates[1] = (M_aero - (I_XX - I_ZZ) * p * r) / I_YY;
        d.d_rates[2] = (N_aero - (I_YY - I_XX) * p * q) / I_ZZ;

        float q0 = state.q.q0, q1 = state.q.q1, q2 = state.q.q2, q3 = state.q.q3;
        d.d_q[0] = 0.5f * (-q1*p - q2*q - q3*r);
        d.d_q[1] = 0.5f * ( q0*p - q3*q + q2*r);
        d.d_q[2] = 0.5f * ( q3*p + q0*q - q1*r);
        d.d_q[3] = 0.5f * (-q2*p + q1*q + q0*r);
    }
}