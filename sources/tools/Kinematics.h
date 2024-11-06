#ifndef KINEMATICS_H
#define KINEMATICS_H

#pragma once
#include "KinematicsData.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>

class Kinematics
{
public:
    Kinematics();
    ~Kinematics();

    void eulerIntegration(float deltaTime);

    void setPosition(const Eigen::Vector3<float>& pos);
    void setVelocity(const Eigen::Vector3<float>& vel);
    void setOrientation(const Eigen::Vector3<float>& orient);
    void setMass(float mass);

    const Eigen::Vector3<float>& getPosition() const;
    const Eigen::Vector3<float>& getVelocity() const;
    const Eigen::Vector3<float>& getOrientation() const;
    float getMass() const;

    const glm::vec3 getPositionAsGlm() const;
    const glm::vec3 getOrientationAsGlm() const;

private:
    KinematicsData data_; 
};

#endif