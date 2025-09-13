#define SENSOR_DATA_H
#ifdef SENSOR_DATA_H

#pragma once

#include <Eigen/Dense>

struct SensorData 
{
    struct IMU
    {
        Eigen::Vector3d acceleration{0,0,0}; // m/s^2
        Eigen::Vector3d angularVelocity{0,0,0}; // rad/s
        Eigen::Vector3d magneticField{0,0,0}; // microtesla
        int timestamp{0}; // microseconds
    } imu;

    struct GPS
    {
        double latitude{0};  // degrees
        double longitude{0}; // degrees
        double altitude{0};  // meters
        double speed{0};     // m/s
        double heading{0};   // degrees from north
        int timestamp{0};    // microseconds
    } gps;

    struct Barometer
    {
        double pressure{0}; // Pascals
        double altitude{0}; // meters
        int timestamp{0};   // microseconds
    } barometer;
};

#endif