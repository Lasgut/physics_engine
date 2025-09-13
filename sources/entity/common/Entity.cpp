#include "Entity.h"
#include "entity_utilities/Kinematics.h"
#include "Clock.h"
#include "EventState.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 


Entity::Entity(const std::string& kinematicsFilePath)
{
    init(kinematicsFilePath);
}


bool 
Entity::update()
{
    auto wrench    = appliedForcesAndMoments();
    auto isUpdated = kinematics_.update(wrench);
    return isUpdated;
}


Eigen::Vector3<double>
Entity::getPosition() const
{
    return kinematics_.getPosition();
}


Eigen::Quaterniond
Entity::getOrientation() const
{
    return kinematics_.getOrientation();
}


Eigen::Vector3<double>
Entity::getEulerAngles() const
{
    return kinematics_.getEulerAngles();
}


glm::vec3 
Entity::getPositionAsGlm() const
{
    return kinematics_.getPositionAsGlm();
}


glm::quat 
Entity::getOrientationAsGlm() const
{
    return kinematics_.getOrientationAsGlm();
}


void 
Entity::init(const std::string& kinematicsFilePath)
{
    kinematics_.setPosition(Eigen::Vector3<double>   (0.0, 0.0, -100.0));
    kinematics_.setVelocity(Eigen::Vector3<double>   (7,0,0));

    double heading = glm::radians(0.0);
    glm::quat orientationGlm{glm::vec3(glm::radians(0.0), 0.0f, heading)}; // roll, pitch, yaw
    Eigen::Quaterniond orientation;
    orientation.x() = orientationGlm.x;
    orientation.y() = orientationGlm.y;
    orientation.z() = orientationGlm.z;
    orientation.w() = orientationGlm.w;

    kinematics_.setOrientation(orientation, heading);

    kinematics_.loadKinematicsData(kinematicsFilePath);
}
