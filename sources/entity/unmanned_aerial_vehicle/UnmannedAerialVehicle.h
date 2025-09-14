#ifndef UNMANNED_AERIAL_VEHICLE_H
#define UNMANNED_AERIAL_VEHICLE_H

#pragma once
#include "Entity.h"
#include "EntityStates.h"
#include "uav_control_system/ControlSystem.h"
#include "uav_emulators/SensorEmulator.h"
#include "uav_emulators/ActuatorEmulator.h"
#include "uav_data_types/SensorData.h"

class UnmannedAerialVehicle
    : public Entity
    , public ControlSystem
    , public SensorEmulator
    , public ActuatorEmulator
{
    public:
        UnmannedAerialVehicle(const std::string& kinematicsFilePath);

    private:
        Eigen::Vector<double,6> appliedForcesAndMoments() override;

        EntityStates estimatedStates_{};
};

#endif