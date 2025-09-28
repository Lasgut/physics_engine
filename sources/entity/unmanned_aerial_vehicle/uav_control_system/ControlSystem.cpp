#include "ControlSystem.h"
#include "EntityStates.h"
#include <iostream>
#include "MathLib.h"
#include "Settings.h"

namespace UAV
{
void
ControlSystem::iterateControlLoop(SensorData& sensorData)
{
    if (!clock_.rateLimit(40) && !Settings::getInstance().simulation.isRunning)
    {
        return;
    }

    // handle command inputs
    processCommands();
    auto cmdControlWrench = getCommandControlWrench();
    auto cmdStates        = getCommandStates();

    // map control system data
    controlSystemData_.timeStamp = clock_.now();
    double& desiredPitch    = controlSystemData_.desiredPitch;
    double& desiredAltitude = controlSystemData_.desiredAltitude;
    desiredAltitude         = cmdStates.position[2];

    // state estimation step
    auto estimatedStates = estimateStates(sensorData);

    // Compute error states
    EntityStates errorStates;
    errorStates.velocity[0] = 11.5 - estimatedStates.velocity[0]; // Target speed is 12 m/s

    // altitude control with pitch control
    if (clockAltitude_.rateLimit(10))
    {
        errorStates.position[2] = desiredAltitude - estimatedStates.position[2];
        desiredPitch = altitudeController_.control(errorStates.position[2]);          // altitudeControl
    }
    auto maxPitch = Lib::Math::Utils::deg2rad(5.0);
    desiredPitch = std::clamp(desiredPitch, -maxPitch, maxPitch);
    errorStates.eulerAngels[1] = desiredPitch - estimatedStates.eulerAngels[1];

    // controller step, PID
    auto controlWrench = computeDesiredControlWrench(errorStates);

    controlWrench += cmdControlWrench;

    // actuator allocation step
    std::lock_guard<std::mutex> lock(actuatorMtx_);
    actuatorInput_ = allocateActuators(controlWrench);
}


ActuatorStates&
ControlSystem::getDesiredActuatorStates()
{
    std::lock_guard<std::mutex> lock(actuatorMtx_);
    return actuatorInput_;
}


ControlSystemData& 
ControlSystem::getControlSystemData()
{
    return controlSystemData_;
}
}