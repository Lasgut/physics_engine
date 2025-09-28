#define SENSOR_EMULATOR_H
#ifdef SENSOR_EMULATOR_H

#pragma once

#include "uav_data_types/SensorData.h"
#include "Entity.h"
#include "Clock.h"

namespace UAV
{
class SensorEmulator
{
    public:
        SensorEmulator() = default;

    protected:
        void emulateSensors(Kinematics* kinematics);
        SensorData& getSensorData();

    private:
        std::mutex      sensorMtx_;
        SensorData sensorData_{};
        Clock           clock_{"SensorEmulator"};
};
}

#endif