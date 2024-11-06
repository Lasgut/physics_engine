#ifndef KINEMATICSDATA_H
#define KINEMATICSDATA_H

#pragma once
#include <Eigen/Dense>

struct KinematicsData 
{
    Eigen::Vector3<float> position   {0.0f, 0.0f, 0.0f};
    Eigen::Vector3<float> velocity   {0.0f, 0.0f, 0.0f};
    Eigen::Vector3<float> orientation{0.0f, 0.0f, 0.0f};
    float     mass;
};

#endif