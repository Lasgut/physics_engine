#include "SensorEmulator.h"
#include "Entity.h"


namespace UAV
{
void
SensorEmulator::emulateSensors(Kinematics* kinematics)
{
    if (!clock_.rateLimit(40)) // sensor sampling time
    {
        return;
    }
    auto deltaTime = clock_.getDeltaTime();

    std::lock_guard<std::mutex> lock(sensorMtx_);
    sensorData_.imu.acceleration      = kinematics->getAcceleration();
    sensorData_.imu.angularVelocity   = kinematics->getAngularVelocity();
    sensorData_.imu.timestamp         = clock_.now(); 

    sensorData_.gps.latitude          = kinematics->getPosition()[0];
    sensorData_.gps.longitude         = kinematics->getPosition()[1];
    sensorData_.gps.altitude          = -kinematics->getPosition()[2]; // NED to ENU
    sensorData_.gps.speed             = kinematics->getVelocity().norm();
    sensorData_.gps.heading           = kinematics->getEulerAngles()[2]; // Yaw as heading
    sensorData_.gps.timestamp         = clock_.now(); 

    sensorData_.attitudeSensor.roll      = kinematics->getEulerAngles()[0];
    sensorData_.attitudeSensor.pitch     = kinematics->getEulerAngles()[1];
    sensorData_.attitudeSensor.yaw       = kinematics->getEulerAngles()[2];
    sensorData_.attitudeSensor.timestamp = clock_.now();
}


SensorData&
SensorEmulator::getSensorData()
{
    std::lock_guard<std::mutex> lock(sensorMtx_);
    return sensorData_;
}
}
