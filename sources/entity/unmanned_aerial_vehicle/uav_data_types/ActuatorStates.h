#define ACTUATOR_STATES_H
#ifdef ACTUATOR_STATES_H

#pragma once

#include <algorithm> // For std::clamp

struct ActuatorStates
{
private:
    double throttle_{0}; // 0 to 1
    double aileron_{0};  // -1 to 1
    double elevator_{0}; // -1 to 1
    double rudder_{0};   // -1 to 1

public:
    // Setters with saturation
    void setThrottle(double value)  { throttle_ = std::clamp(value, 0.0, 1.0); }
    void setAileron(double value)   { aileron_  = std::clamp(value, -1.0, 1.0); }
    void setElevator(double value)  { elevator_ = std::clamp(value, -1.0, 1.0); }
    void setRudder(double value)    { rudder_   = std::clamp(value, -1.0, 1.0); }

    // Getters
    double getThrottle() const { return throttle_; }
    double getAileron()  const { return aileron_; }
    double getElevator() const { return elevator_; }
    double getRudder()   const { return rudder_; }
};

#endif