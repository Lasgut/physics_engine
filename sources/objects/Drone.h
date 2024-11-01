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
    Cube       shape_;//{0.2,0.2,0.2};
    Kinematics kinematics_;

};

#endif