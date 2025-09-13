#include "StateEstimator.h"
#include "uav_data_types/SensorData.h"
#include <iostream>

EntityStates
StateEstimator::estimateStates(SensorData& sensorData)
{
    EntityStates estimatedStates{};

    estimatedStates.position            = Eigen::Vector3d(sensorData.gps.latitude, sensorData.gps.longitude, sensorData.gps.altitude);
    estimatedStates.velocity            = Eigen::Vector3d(sensorData.gps.speed, 0, 0); // Simplified: assuming speed is along x-axis
    estimatedStates.acceleration        = sensorData.imu.acceleration;
    estimatedStates.roll                = 0; // Placeholder, real implementation would use sensor fusion
    estimatedStates.pitch               = 0; // Placeholder, real implementation would use sensor fusion
    estimatedStates.yaw                 = sensorData.gps.heading * M_PI / 180.0; // Convert degrees to radians
    estimatedStates.angularVelocity     = sensorData.imu.angularVelocity;
    estimatedStates.angularAcceleration = Eigen::Vector3d(0,0,0); // Placeholder, real implementation would compute this from gyro data over time

    std::cout << "DEBUG: estimateStates: " << estimatedStates.velocity[0] << std::endl;
    return estimatedStates;
}
