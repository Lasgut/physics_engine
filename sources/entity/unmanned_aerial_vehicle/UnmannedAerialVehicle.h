#ifndef UNMANNED_AERIAL_VEHICLE_H
#define UNMANNED_AERIAL_VEHICLE_H

#pragma once
#include "Entity.h"
#include "EntityStates.h"
#include "uav_control_system/ControlSystem.h"
#include "uav_emulators/SensorEmulator.h"
#include "uav_emulators/ActuatorEmulator.h"
#include "uav_data_types/SensorData.h"
#include "uav_data_types/ControlSystemData.h"

#include <thread>

using namespace UAV;

class UnmannedAerialVehicle
    : public Entity
    , public ControlSystem
    , public SensorEmulator
    , public ActuatorEmulator
{
    public:
        UnmannedAerialVehicle(const std::string& kinematicsFilePath);

    private:
        void startControlSystem();
        void startSensors();
        Eigen::Vector<double,6> appliedForcesAndMoments() override;

        std::thread controlSystemThread_;
        std::thread sensorsThread_;
};

#endif