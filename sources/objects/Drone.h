#ifndef DRONE_H
#define DRONE_H

#pragma once
#include "Cube.h"
#include "Kinematics.h"
#include "Clock.h"

class Drone
{
public:
    Drone();

    void update(const ShaderHandler& shaderHandler, Clock& clock);

private:
    void init();

    Cube       shape_ = Cube(0.2, 0.15, 0.05);
    Kinematics kinematics_;

};

#endif