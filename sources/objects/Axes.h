#ifndef AXES_H
#define AXES_H

#pragma once
#include "ShaderHandler.h"
#include "Line.h"

class Axes
{
    public:
        Axes();
        Axes(float length);

        void update(const ShaderHandler& shaderHandler);

    private:
        glm::vec3 position_    {0.0f, 0.0f, 0.0f};
        glm::vec3 xOrientation_{0.0f, 0.0f, 0.0f};
        glm::vec3 yOrientation_{0.0f, 0.0f, glm::radians(90.0f)};
        glm::vec3 zOrientation_{0.0f, glm::radians(-90.0f), 0.0f};
        float     length_      {1.0};
        float     brightness_  {0.8};

        Line xAxis_{length_, glm::vec3(brightness_, 0.0f, 0.0f)};
        Line yAxis_{length_, glm::vec3(0.0f, brightness_, 0.0f)};
        Line zAxis_{length_, glm::vec3(0.0f, 0.0f, brightness_)};
};

#endif