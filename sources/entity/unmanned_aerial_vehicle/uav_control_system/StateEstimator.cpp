#include "StateEstimator.h"
#include "uav_data_types/SensorData.h"

EntityStates
StateEstimator::estimateStates(SensorData& sensorData)
{
    EntityStates estimatedStates{};

    estimatedStates.position            = Eigen::Vector3d(sensorData.gps.latitude, sensorData.gps.longitude, sensorData.gps.altitude);
    estimatedStates.velocity            = Eigen::Vector3d(sensorData.gps.speed, 0, 0); // Simplified: assuming speed is along x-axis
    estimatedStates.acceleration        = sensorData.imu.acceleration;
    estimatedStates.roll                = sensorData.attitudeSensor.roll; // Using attitude sensor for roll
    estimatedStates.pitch               = sensorData.attitudeSensor.pitch; // Using attitude sensor for pitch
    estimatedStates.yaw                 = sensorData.attitudeSensor.yaw; // Using attitude sensor for yaw
    estimatedStates.angularVelocity     = sensorData.imu.angularVelocity;
    estimatedStates.angularAcceleration = Eigen::Vector3d(0,0,0); // Placeholder, real implementation would compute this from gyro data over time

    return estimatedStates;
}
