#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "StlMesh.h"
#include "Kinematics.h"
#include "PidController.h"
#include "Clock.h"
#include "Axes.h"

class Entity
{
    public:
        Entity(const std::string& meshPath, const std::string& kinematicsFilePath);

        void update(const ShaderHandler& shaderHandler);
        Eigen::Vector3<double> getPosition()        const;
        Eigen::Quaterniond     getOrientation()     const;

        glm::vec3 getPositionAsGlm()    const;
        glm::quat getOrientationAsGlm() const;

    private:
        void init(const std::string& kinematicsFilePath);

        Eigen::Vector<double,6> computeControlForces();

        StlMesh       shape_;
        Kinematics    kinematics_;
        PidController pitchController_{1,0,0,7};
        PidController pitchRateController_{1,0,0,20};
        PidController rollRateController_{1,0,0,20};
        PidController velocityController_{1,0,0,20};
};

#endif