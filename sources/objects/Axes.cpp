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
    glm::quat orientationGlm(orientation.w(), orientation.x(), orientation.y(), orientation.z());

    xOrientation_ = orientationGlm * xOrientation_;
    yOrientation_ = orientationGlm * yOrientation_;
    zOrientation_ = orientationGlm * zOrientation_;
}
