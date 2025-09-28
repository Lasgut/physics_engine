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
Entity::updateEntity()
{
    auto wrench    = appliedForcesAndMoments();
    auto isUpdated = updateKinematics(wrench);
    return isUpdated;
}


void 
Entity::init(const std::string& kinematicsFilePath)
{
    setPosition(Eigen::Vector3<double>   (0.0, 0.0, -100.0));
    setVelocity(Eigen::Vector3<double>   (7,0,0));

    double heading = glm::radians(0.0);
    glm::quat orientationGlm{glm::vec3(glm::radians(0.0), 0.0f, heading)}; // roll, pitch, yaw
    Eigen::Quaterniond orientation;
    orientation.x() = orientationGlm.x;
    orientation.y() = orientationGlm.y;
    orientation.z() = orientationGlm.z;
    orientation.w() = orientationGlm.w;

    setOrientation(orientation, heading);

    loadKinematicsData(kinematicsFilePath);
}

void 
Entity::updateTrueEntityStates()
{
    trueEntityStates_.position     = getPosition();
    trueEntityStates_.velocity     = getVelocity();
    trueEntityStates_.acceleration = getAcceleration();
    trueEntityStates_.eulerAngels  = getEulerAngles();
    trueEntityStates_.angularVelocity     = getAngularVelocity();
    trueEntityStates_.angularAcceleration = getAngularAcceleration();
}
