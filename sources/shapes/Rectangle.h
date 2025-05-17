#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once
#include <glad/gl.h>
#include "ShaderHandler.h"
#include "Shape.h"
#include <vector>

class Rectangle
    : public Shape
{
    public:
        Rectangle();
        Rectangle(double length, double width, double height);

        void draw(const ShaderHandler& shaderHandler, 
                  const glm::vec3&     position,
                  const glm::vec3&     orientation);

    private:
        std::vector<double> createVertices();

        double length_{1};
        double width_{1};
        double height_{1};
};

#endif