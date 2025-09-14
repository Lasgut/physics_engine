#include "ControlSystem.h"
#include <iostream>
#include "kinematics/Utilities.h"

ActuatorStates 
ControlSystem::iterateControlLoop(SensorData& sensorData)
{
    if (!clock_.rateLimit(20))
    {
        return actuatorInput_;
    }

    // handle command inputs
    processCommands();
    auto cmdControlWrench = getCommandControlWrench();
    auto cmdStates        = getCommandStates();

    // state estimation step
    auto estimatedStates = estimateStates(sensorData);

    // Compute error states
    EntityStates errorStates;
    errorStates.velocity[0] = 11.5 - estimatedStates.velocity[0]; // Target speed is 12 m/s

    // altitude control with pitch control
    if (clockAltitude_.rateLimit(5))
    {
        errorStates.position[2] = cmdStates.position[2] - estimatedStates.position[2]; // Target altitude is 100 m
        desiredPitch_ = altitudeController_.control(errorStates.position[2]);          // altitudeControl
    }
    auto maxPitch = Lib::Kinematics::Utils::deg2rad(5.0);
    desiredPitch_ = std::clamp(desiredPitch_, -maxPitch, maxPitch);
    errorStates.pitch = desiredPitch_ - estimatedStates.pitch;

    // controller step, PID
    auto controlWrench = computeDesiredControlWrench(errorStates);

    controlWrench += cmdControlWrench;

    if (clockDebug_.rateLimit(1))
    {
        std::cout << "DEBUG: pitchEstimate: " << estimatedStates.pitch << " desired: " << desiredPitch_ << " pitchError: " << errorStates.pitch 
        << " moment: " << controlWrench[4] << " altitude: " << sensorData.gps.altitude 
        << " vel: " << sensorData.gps.speed
        << std::endl;
    }

    // actuator allocation step
    actuatorInput_     = allocateActuators(controlWrench);

    return actuatorInput_;
}