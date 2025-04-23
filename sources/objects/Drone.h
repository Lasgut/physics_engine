#ifndef DRONE_H
#define DRONE_H

#pragma once
#include "StlMesh.h"
#include "Kinematics.h"
#include "Clock.h"

class Drone
{
    public:
        Drone(const std::string& meshPath);

        void update(const ShaderHandler& shaderHandler, Clock& clock);

    private:
        void init();

        StlMesh    shape_;
        Kinematics kinematics_;
};

#endif