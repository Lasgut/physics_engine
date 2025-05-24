#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "StlMesh.h"
#include "Kinematics.h"
#include "Clock.h"
#include "Axes.h"

class Entity
{
    public:
        Entity(const std::string& meshPath, const std::string& kinematicsFilePath);

        void update(const ShaderHandler& shaderHandler);
        Eigen::Vector3<double> getPosition();
        Eigen::Quaterniond     getOrientation();

        glm::vec3 getPositionAsGlm()    const;
        glm::quat getOrientationAsGlm() const;

    private:
        void init(const std::string& kinematicsFilePath);

        StlMesh    shape_;
        Kinematics kinematics_;
};

#endif