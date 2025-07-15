#include "Entity.h"
#include "Clock.h"
#include "entity_utilities/PidController.h"


Entity::Entity(const std::string& kinematicsFilePath)
{
    init(kinematicsFilePath);
}


bool 
Entity::update()
{
    auto controlForces = computeControlForces();
    auto isUpdated = kinematics_.update(controlForces);
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

Eigen::Vector<double, 6> Entity::computeControlForces()
{
    //Aircraft 
    Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    Eigen::Vector3d         desiredRates(0, 0, 0); // [p_ref, q_ref, r_ref] (roll, pitch, yaw rates)

    if (EventState::getInstance().keyboard.up)
        desiredRates[1] = -0.5; // Pitch down
    if (EventState::getInstance().keyboard.down)
        desiredRates[1] = 0.5;  // Pitch up
    if (EventState::getInstance().keyboard.left)
        desiredRates[0] = -0.5; // Roll left
    if (EventState::getInstance().keyboard.right)
        desiredRates[0] = 0.5;  // Roll right
    if (EventState::getInstance().keyboard.space)
        controlForces[0] = 2.0; // Thrust (optional for now)
    else
        controlForces[0] = velocityController_.control(12, kinematics_.getVelocity()[0]);

    // if (desiredRates[1] == 0)
    //     desiredRates[1]= pitchController_.control(0.0, kinematics_.getEulerAngles()[1]);

    controlForces[3] = rollRateController_.control(desiredRates[0], kinematics_.getAngularVelocity()[0]);
    controlForces[4] = pitchRateController_.control(desiredRates[1], kinematics_.getAngularVelocity()[1]);

    // underwater
    // double force = 0.3;
    // Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    // if (EventState::getInstance().keyboard.up)
    // {
    //     controlForces[0] = force;
    // }
    // if (EventState::getInstance().keyboard.down)
    // {
    //     controlForces[0] = -force;
    // }
    // if (EventState::getInstance().keyboard.left)
    // {
    //     controlForces[5] = -0.2*force;
    // }
    // if (EventState::getInstance().keyboard.right)
    // {
    //     controlForces[5] = 0.2*force;
    // }
    // if (EventState::getInstance().keyboard.space)
    // {
    //     controlForces[2] = force;
    // }
    return controlForces;
}