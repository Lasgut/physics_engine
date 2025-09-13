#include "SensorEmulator.h"
#include "Entity.h"
#include <iostream>


SensorData 
SensorEmulator::emulateSensorData(Kinematics& kinematics)
{
    if (!clock_.rateLimit(40)) // sensor sampling time
    {
        return sensorData_;
    }
    auto deltaTime = clock_.getDeltaTime();
    sensorData_.imu.acceleration      = kinematics.getAcceleration();
    sensorData_.imu.angularVelocity   = kinematics.getAngularVelocity();
    sensorData_.imu.timestamp         = clock_.now(); // TODO: add timestamp

    sensorData_.gps.latitude          = kinematics.getPosition()[0];
    sensorData_.gps.longitude         = kinematics.getPosition()[1];
    sensorData_.gps.altitude          = kinematics.getPosition()[2];
    sensorData_.gps.speed             = kinematics.getVelocity().norm();
    sensorData_.gps.heading           = kinematics.getEulerAngles()[2]; // Yaw as heading
    sensorData_.gps.timestamp         = clock_.now(); // TODO: add timestamp

    std::cout << "DEBUG: emulateSensorData: " << sensorData_.gps.speed << std::endl;

    return sensorData_;
}
