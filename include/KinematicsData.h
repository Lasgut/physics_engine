#ifndef KINEMATICSDATA_H
#define KINEMATICSDATA_H

#pragma once
#include <Eigen/Dense>

struct KinematicsData 
{
    Eigen::Vector<float,3> position             {0.0f, 0.0f, 0.0f};
    Eigen::Vector<float,3> velocity             {0.0f, 0.0f, 0.0f};
    Eigen::Vector<float,3> acceleration         {0.0f, 0.0f, 0.0f};
    Eigen::Vector<float,3> orientation          {0.0f, 0.0f, 0.0f};
    Eigen::Vector<float,3> angularVelocity      {0.0f, 0.0f, 0.0f};
    Eigen::Vector<float,3> angularAcceleration  {0.0f, 0.0f, 0.0f};
    
    float mass;
    float gravity{9.81};
};

#endif