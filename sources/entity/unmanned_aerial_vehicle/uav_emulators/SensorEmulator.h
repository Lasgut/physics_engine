#define SENSOR_EMULATOR_H
#ifdef SENSOR_EMULATOR_H

#pragma once

#include "uav_data_types/SensorData.h"
#include "Entity.h"
#include "Clock.h"

class SensorEmulator
{
    public:
        SensorEmulator() = default;

    protected:
        SensorData emulateSensorData(Kinematics& kinematics);

    private:
        SensorData sensorData_{};
        Clock      clock_;
};

#endif