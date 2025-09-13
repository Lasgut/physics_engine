#define ACTUATOR_STATES_H
#ifdef ACTUATOR_STATES_H

#pragma once

struct ActuatorStates
{
    double throttle{0}; // 0 to 1
    double aileron{0};  // -1 to 1
    double elevator{0}; // -1 to 1
    double rudder{0};   // -1 to 1
};

#endif