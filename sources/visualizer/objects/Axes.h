#ifndef AXES_H
#define AXES_H

#pragma once
#include "visualizer_utilities/ShaderHandler.h"
#include "shapes/Line.h"
#include <Eigen/Dense>

class Axes
{
    public:
        Axes();
        Axes(double length);

        void update(const ShaderHandler& shaderHandler);
        void setPosition(const Eigen::Vector3<double>&  position);
        void setOrientation(const Eigen::Quaterniond&  orientation);

    private:
        glm::vec3 position_    {0.0f, 0.0f, 0.0f};
        glm::quat xOrientation_{glm::vec3(0.0f, 0.0f, 0.0f)}; // roll, pitch, yaw
        glm::quat yOrientation_{glm::vec3(0.0f, 0.0f, glm::radians(90.0f))};
        glm::quat zOrientation_{glm::vec3(0.0f, glm::radians(-90.0f), 0.0f)};
        double     length_      {1.0};
        double     brightness_  {0.8};

        Line xAxis_{length_, glm::vec3(brightness_, 0.0f, 0.0f)};
        Line yAxis_{length_, glm::vec3(0.0f, brightness_, 0.0f)};
        Line zAxis_{length_, glm::vec3(0.0f, 0.0f, brightness_)};
};

#endif