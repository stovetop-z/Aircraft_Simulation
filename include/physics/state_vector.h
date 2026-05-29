#pragma once
#include "math/quaternion.h"

struct AircraftState
{
    union
    {
        float data[13];
        struct
        {
            float pos[3];
            float vel[3];
            quaternion q;
            float rates[3];
        };
    };
    
    AircraftState();
};

struct AircraftDerivative
{
    union 
    {
        float d_data[13];
        struct 
        {
            float d_pos[3];
            float d_vel[3];
            float d_q[4];
            float d_rates[3];
        };
    };
    
    AircraftDerivative();
};

struct Controller
{
    float aileron, elevator, rudder, throttle;
    
    Controller();
};