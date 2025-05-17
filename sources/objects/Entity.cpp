#include "Entity.h"
#include "Clock.h"


Entity::Entity(const std::string& meshPath, const std::string& kinematicsFilePath)
    : shape_(meshPath)
{
    init(kinematicsFilePath);
}


void 
Entity::update(const ShaderHandler& shaderHandler)
{
    shape_.draw(shaderHandler, 
                kinematics_.getPositionAsGlm(), 
                kinematics_.getOrientationAsGlm());

    Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    if (EventState::getInstance().keyboard.up)
    {
        controlForces[0] = 0.05;
    }
    if (EventState::getInstance().keyboard.down)
    {
        controlForces[0] = -0.05;
    }
    if (EventState::getInstance().keyboard.left)
    {
        controlForces[5] = -0.05;
    }
    if (EventState::getInstance().keyboard.right)
    {
        controlForces[5] = 0.05;
    }
    if (EventState::getInstance().keyboard.space)
    {
        controlForces[2] = -0.05;
    }
    kinematics_.update(controlForces);
}


Eigen::Vector3<double>
Entity::getPosition()
{
    return kinematics_.getPosition();
}


Eigen::Quaterniond
Entity::getOrientation()
{
    return kinematics_.getOrientation();
}

void 
Entity::init(const std::string& kinematicsFilePath)
{
    kinematics_.setPosition(Eigen::Vector3<double>   (0.0, 0.0, 0.0));
    kinematics_.setVelocity(Eigen::Vector3<double>   (0,0,0));

    glm::quat orientationGlm{glm::vec3(0.0f, 0.0f, glm::radians(0.0))}; // yaw, pitch, roll
    Eigen::Quaterniond orientation;
    orientation.x() = orientationGlm.x;
    orientation.y() = orientationGlm.y;
    orientation.z() = orientationGlm.z;
    orientation.w() = orientationGlm.w;

    kinematics_.setOrientation(orientation);

    kinematics_.loadKinematicsData(kinematicsFilePath);
}
