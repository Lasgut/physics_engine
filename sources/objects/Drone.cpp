#include "Drone.h"

Drone::Drone()
{
    kinematics_.position.x = 0.0;
    kinematics_.position.y = 0.0;
    kinematics_.position.z = -0.7;
}

Drone::~Drone()
{

}

void 
Drone::update(const ShaderHandler& shaderHandler)
{
    shape_.draw(shaderHandler, 
                kinematics_.position, 
                kinematics_.orientation);
}
