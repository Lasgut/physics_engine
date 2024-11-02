#ifndef DRONE_H
#define DRONE_H

#pragma once
#include "Cube.h"
#include "Kinematics.h"

class Drone
{
public:
    Drone();
    ~Drone();

    void update(const ShaderHandler& shaderHandler);

private:
    Cube       shape_ = Cube(0.2, 0.15, 0.05);
    Kinematics kinematics_;

};

#endif