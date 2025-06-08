#include "Axes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Axes::Axes()
{
}

Axes::Axes(double length)
    : length_(length)
{
}

void 
Axes::update(const ShaderHandler &shaderHandler)
{
    xAxis_.draw(shaderHandler,
                position_,
                xOrientation_);

    yAxis_.draw(shaderHandler,
                position_,
                yOrientation_);

    zAxis_.draw(shaderHandler,
                position_,
                zOrientation_);
}


void 
Axes::setPosition(const Eigen::Vector3<double>& position)
{
    position_.x = position.x();
    position_.y = position.y();
    position_.z = position.z();
}


void 
Axes::setOrientation(const Eigen::Quaterniond& orientation)
{
    glm::quat orientationGlm;
    orientationGlm.x = orientation.x();
    orientationGlm.y = orientation.y();
    orientationGlm.z = orientation.z();
    orientationGlm.w = orientation.w();

    glm::quat qZ90 = glm::angleAxis(glm::radians(90.0f),  glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat qY90 = glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    xOrientation_ = orientationGlm;                      
    yOrientation_ = orientationGlm * qZ90;                
    zOrientation_ = orientationGlm * qY90;                
}
