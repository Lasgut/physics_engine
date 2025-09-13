#ifndef ENTITYSTATES_H
#define ENTITYSTATES_H

#pragma once
#include <Eigen/Dense>

struct EntityStates 
{
    Eigen::Vector3d position{0,0,0};
    Eigen::Vector3d velocity{0,0,0};
    Eigen::Vector3d acceleration{0,0,0};

    double roll{0};
    double pitch{0};
    double yaw{0};

    Eigen::Vector3d angularVelocity{0,0,0};
    Eigen::Vector3d angularAcceleration{0,0,0};
};

#endif