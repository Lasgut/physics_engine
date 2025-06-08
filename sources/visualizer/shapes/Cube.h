#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/gl.h>
#include "shapes/Shape.h"
#include "visualizer_utilities/ShaderHandler.h"

class Cube 
    : public Shape
{
    public:
        Cube();
        Cube(double length, double width, double height);

        void draw(const ShaderHandler& shaderHandler, 
                const glm::vec3&     position,
                const glm::vec3&     orientation);

    private:
        std::vector<double> createVertices();

        double length_{0.1};
        double width_{0.1};
        double height_{0.1};        
};

#endif
