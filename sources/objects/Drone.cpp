#include "Drone.h"
#include "Clock.h"

Drone::Drone()
{
    init();
}

Drone::~Drone()
{

}

void 
Drone::update(const ShaderHandler& shaderHandler, const Clock& clock)
{
    shape_.draw(shaderHandler, 
                kinematics_.getPositionAsGlm(), 
                kinematics_.getOrientationAsGlm());

    kinematics_.eulerIntegration(clock.getDeltaTime());
}

void Drone::init()
{
    kinematics_.setMass(2.0); 
    kinematics_.setPosition(Eigen::Vector3<float>(0,0,-1));
    kinematics_.setVelocity(Eigen::Vector3<float>(0,0,0));
    kinematics_.setOrientation(Eigen::Vector3<float>(0,0,0));
}
