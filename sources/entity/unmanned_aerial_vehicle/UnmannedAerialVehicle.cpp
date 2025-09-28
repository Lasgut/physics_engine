#include "UnmannedAerialVehicle.h"
#include "EventState.h"
#include "Entity.h"
#include <iostream>
#include <thread>

UnmannedAerialVehicle::UnmannedAerialVehicle(const std::string &kinematicsFilePath)
    : Entity(kinematicsFilePath)
{
    startSensors();
    startControlSystem();
}


void 
UnmannedAerialVehicle::startControlSystem()
{
    controlSystemThread_ = std::thread([&]()
    {
        pthread_setname_np(pthread_self(), "ControlSystem");
        while (true) 
        {
            iterateControlLoop(getSensorData());
        }
    }); 
}


void 
UnmannedAerialVehicle::startSensors()
{
    sensorsThread_ = std::thread([&]()
    {
        pthread_setname_np(pthread_self(), "SensorsEmulator");
        while (true) 
        {
            emulateSensors(this);
        }
    }); 
}

Eigen::Vector<double, 6>
UnmannedAerialVehicle::appliedForcesAndMoments()
{
    return emulateActuatorDynamics(getDesiredActuatorStates());
}