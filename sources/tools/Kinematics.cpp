#include "Kinematics.h"
#include "KinematicsData.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>

Kinematics::Kinematics()
{
}

Kinematics::~Kinematics()
{
}

void 
Kinematics::eulerIntegration(float deltaTime) 
{
    const float g = 9.81;
    const float b = -9.7;
    const Eigen::Vector3<float> force = Eigen::Vector3<float>(0,0, g + b); 
    Eigen::Vector3<float> acceleration = force / data_.mass;

    data_.velocity += acceleration * deltaTime;
    data_.position += data_.velocity * deltaTime;
}

void 
Kinematics::setPosition(const Eigen::Vector3<float>& pos) 
{
    data_.position = pos;
}

void 
Kinematics::setVelocity(const Eigen::Vector3<float>& vel) 
{
    data_.velocity = vel;
}

void 
Kinematics::setOrientation(const Eigen::Vector3<float>& orient) 
{
    data_.orientation = orient;
}

void 
Kinematics::setMass(float mass) 
{
    data_.mass = mass;
}

const Eigen::Vector3<float>& 
Kinematics::getPosition() const 
{
    return data_.position;
}

const Eigen::Vector3<float>& 
Kinematics::getVelocity() const 
{
    return data_.velocity;
}

const Eigen::Vector3<float>& 
Kinematics::getOrientation() const 
{
    return data_.orientation;
}

float 
Kinematics::getMass() const 
{
    return data_.mass;
}

const glm::vec3
Kinematics::getPositionAsGlm() const
{
    glm::vec3 pos;
    pos.x = data_.position.x();
    pos.y = data_.position.y();
    pos.z = data_.position.z();
    return pos;
}

const glm::vec3
Kinematics::getOrientationAsGlm() const
{
    glm::vec3 ori;
    ori.x = data_.orientation.x();
    ori.y = data_.orientation.y();
    ori.z = data_.orientation.z();
    return ori;
}
