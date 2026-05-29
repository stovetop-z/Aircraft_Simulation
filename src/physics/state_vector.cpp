#include "physics/state_vector.h"

AircraftState::AircraftState()
{
    for(unsigned short i = 0; i < 13; i++)
        data[i] = 0.0f;
    q.q0 = 1.0f;
}

AircraftDerivative::AircraftDerivative()
{
    for(unsigned short i = 0; i < 13; i++)
        d_data[i] = 0.0f;
}

Controller::Controller() : aileron(0.0f), elevator(0.0f), rudder(0.0f), throttle(0.0f) {}