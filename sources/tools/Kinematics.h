#ifndef KINEMATICS_H
#define KINEMATICS_H

#pragma once
#include "KinematicsData.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>

class Kinematics
{
public:
    Kinematics() = default;

    void eulerIntegration(float deltaTime);

    void setPosition(   const Eigen::Vector<float,3>& pos);
    void setVelocity(   const Eigen::Vector<float,3>& vel);
    void setOrientation(const Eigen::Vector<float,3>& orient);
    void setMass(float mass);

    const Eigen::Vector<float,3>& getPosition()    const;
    const Eigen::Vector<float,3>& getVelocity()    const;
    const Eigen::Vector<float,3>& getOrientation() const;
    float getMass() const;

    const glm::vec3 getPositionAsGlm() const;
    const glm::vec3 getOrientationAsGlm() const;

    void systemMatrices();

private:
    Eigen::Matrix<float,3,3> skew(const Eigen::Vector<float,3>& v);
    Eigen::Matrix<float,3,3> Rzyx(float phi, float theta, float psi); 
    Eigen::Matrix<float,3,3> Tzyx(float phi, float theta); 

    KinematicsData data_; 
};

#endif